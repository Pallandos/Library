#define _GNU_SOURCE
#include <pthread.h>           /* produit.c */
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

#define NB_CORES (sysconf(_SC_NPROCESSORS_ONLN))

/*********** Data Type ***********/

typedef enum {
    STATE_WAIT,
    STATE_MULT,
    STATE_ADD,
    STATE_PRINT

} State;

typedef struct {
    State state;
    int * pendingMult;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    size_t nbIterations;
    size_t size;
    double * v1;
    double * v2;
    double * v3;
    double result;
} Product;

/*********** Data structure ***********/

Product prod;

/*********** Function ***********/

void initPendingMult(Product * prod)
{
    size_t i;
    for(i=0;i<prod->size;i++) {
        prod->pendingMult[i]=1;
    }
}

int nbPendingMult(Product * prod){
	size_t i;
	int nb=0;
	pthread_mutex_lock(&prod->mutex);
	for(i=0;i<prod->size;i++){
		nb+=prod->pendingMult[i];
	}
	pthread_mutex_unlock(&prod->mutex);
	return(nb);

}

void wasteTime(unsigned long ms)
{
	unsigned long t,t0;
	struct timeval tv;
	gettimeofday(&tv,(struct timezone *)0);
	t0=tv.tv_sec*1000LU+tv.tv_usec/1000LU;

	do {

		gettimeofday(&tv,(struct timezone *)0);
		t=tv.tv_sec*1000LU+tv.tv_usec/1000LU;

	} while(t-t0<ms);
}

/*****************************************************************************/
void * mult(void * data)
{
	size_t index;
	size_t iter;

	/*=>Recuperation de l'index, c'est a dire index = ... */
	index = *((size_t *)data);

    /* Bloc de répartition des charges*/
    cpu_set_t cpu;
    CPU_ZERO(&cpu);
    CPU_SET(index % NB_CORES, &cpu);

    if(sched_setaffinity(getpid(), sizeof(cpu), &cpu) != 0){
        printf("Erreur sched affinity \n");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "Affinity set to core No %d\n", sched_getcpu());
    

	fprintf(stderr,"Begin mult(%d)\n",index);
    
	/* Tant que toutes les iterations n'ont pas eu lieu              */
	for(iter=0;iter<prod.nbIterations;iter++){  
 
 		/*=>Attendre l'autorisation de multiplication POUR UNE NOUVELLE ITERATION...*/

		pthread_mutex_lock(&prod.mutex);
		while(prod.state != STATE_MULT || prod.pendingMult[index] == 0){
			pthread_cond_wait(&prod.cond, &prod.mutex);
		};
		pthread_mutex_unlock(&prod.mutex);

 		fprintf(stderr,"--> mult(%d)\n",index); /* La multiplication peut commencer */

 		/*=>Effectuer la multiplication a l'index du thread courant... */
		prod.v3[index] = prod.v2[index]*prod.v1[index];

 		wasteTime(200+(rand()%200)); /* Perte du temps avec wasteTime() */

 		fprintf(stderr,"<-- mult(%d) : %.3g*%.3g=%.3g\n", index,prod.v1[index], prod.v2[index], prod.v3[index]);
 		
		/*=>Marquer la fin de la multiplication en cours... */
		pthread_mutex_lock(&prod.mutex);
		prod.pendingMult[index] = 0;
		pthread_mutex_unlock(&prod.mutex);


 		/*=>Si c'est la derniere... */
		if(nbPendingMult(&prod) == 0){
    	/*=>Autoriser le demarrage de l'addition... */
			pthread_mutex_lock(&prod.mutex);
			fprintf(stderr, "BROADCAST ADD(%lu) \n",iter + 1);
			prod.state = STATE_ADD;

			pthread_cond_broadcast(&prod.cond); // signal ne fonctionne pas???
			pthread_mutex_unlock(&prod.mutex);
		}
 	}

	fprintf(stderr,"Quit mult(%d)\n",index);
	return(data);
}

/*****************************************************************************/
void * add(void * data) {
	size_t iter;
	fprintf(stderr,"Begin add()\n");
	
	/* Tant que toutes les iterations n'ont pas eu lieu              */
	for(iter=0;iter<prod.nbIterations;iter++){

  		size_t index;

  		/*=>Attendre l'autorisation d'addition... */
		pthread_mutex_lock(&prod.mutex);
		while(prod.state != STATE_ADD){
			pthread_cond_wait(&prod.cond, &prod.mutex);
		}

		// je ne relâche rien : on va manipuler v3 et prod.state

  		fprintf(stderr,"--> add\n"); /* L'addition peut commencer */

  		/* Effectuer l'addition... */
  		
		prod.result=0.0;
  		for(index=0;index<prod.size;index++){
			prod.result += prod.v3[index];
  		}

  		wasteTime(100+(rand()%100)); /* Perdre du temps avec wasteTime() */

  		fprintf(stderr,"<-- add\n");

  		/*=>Autoriser le demarrage de l'affichage... */
		prod.state = STATE_PRINT;

		pthread_mutex_unlock(&prod.mutex); // j'ai tout fini, je relâche
		pthread_cond_broadcast(&prod.cond); // on reveille le main qui attends d'afficher


  	}

	fprintf(stderr,"Quit add()\n");
	return(data);

}

/*****************************************************************************/
int main(int argc,char ** argv) {

	size_t i, iter;
	pthread_t *multTh;
	size_t    *multData;
	pthread_t  addTh;
	void      *threadReturnValue;

	/* A cause de warnings lorsque le code n'est pas encore la...*/
	(void)addTh; (void)threadReturnValue;

	/* Lire le nombre d'iterations et la taille des vecteurs */

	if((argc<=2)||
	(sscanf(argv[1],"%u",&prod.nbIterations)!=1)||
	(sscanf(argv[2],"%u",&prod.size)!=1)||
	((int)prod.nbIterations<=0)||((int)prod.size<=0)){

		fprintf(stderr,"usage: %s nbIterations vectorSize\n",argv[0]);
		return(EXIT_FAILURE);
	}

	/* Initialisations (Product, tableaux, generateur aleatoire,etc) */

	prod.state=STATE_WAIT; // pas de cond on est les premiers à y toucher 

	prod.pendingMult=(int *)malloc(prod.size*sizeof(int));
	initPendingMult(&prod);

	/*=>initialiser prod.mutex ... */
	if (pthread_mutex_init(&prod.mutex, NULL) != 0){
		perror("Erreur mutex");
		exit(EXIT_FAILURE);
	}

	/*=>initialiser prod.cond ...  */
	if (pthread_cond_init(&prod.cond, NULL) != 0){
		perror("Erreur creation cond");
		exit(EXIT_FAILURE);
	}

	/* Allocation dynamique des 3 vecteurs v1, v2, v3 */

	prod.v1=(double *)malloc(prod.size*sizeof(double));
	prod.v2=(double *)malloc(prod.size*sizeof(double));
	prod.v3=(double *)malloc(prod.size*sizeof(double));

	/* Allocation dynamique du tableau pour les threads multiplieurs */

	multTh=(pthread_t *)malloc(prod.size*sizeof(pthread_t));

	/* Allocation dynamique du tableau des MulData */

	multData=(size_t *)malloc(prod.size*sizeof(size_t));

	/* Initialisation du tableau des MulData */

	for(i=0;i<prod.size;i++){
		multData[i]=i;
	}

	/*=>Creer les threads de multiplication... */
	for (size_t i = 0; i < prod.size; i++){
		if (pthread_create(&multTh[i], NULL, mult, &multData[i]) != 0){
			perror("Erreur creation thread mult");
			exit(EXIT_FAILURE);
		}
	}
    // pthread_mutex_lock(&prod.mutex); pk ???
	/*=>Creer le thread d'addition...          */
	if (pthread_create(&addTh, NULL, add, NULL) != 0){
		perror("Erreur creation thread add");
		exit(EXIT_FAILURE);
	}
	
	srand(time((time_t *)0));   /* Init du generateur de nombres aleatoires */

	/* Pour chacune des iterations a realiser, c'est a dire tant que toutes les iterations n'ont pas eu lieu */
	for(iter=0;iter<prod.nbIterations;iter++) 
	{                                       
		size_t j;
	
		/* Initialiser aleatoirement les deux vecteurs */


		pthread_mutex_lock(&prod.mutex);
		fprintf(stderr, "In main : je prends %lu \n",iter +1);

		for(j=0;j<prod.size;j++) {

			prod.v1[j]=10.0*(0.5-((double)rand())/((double)RAND_MAX));
			prod.v2[j]=10.0*(0.5-((double)rand())/((double)RAND_MAX));

		}

		/*=>Autoriser le demarrage des multiplications pour une nouvelle iteration..*/

		fprintf(stderr,"BROADCAST MULT (%lu)\n", iter+1);
		prod.state = STATE_MULT;
		initPendingMult(&prod); // aucune mult n'a été effectuée on remet à 1
		pthread_mutex_unlock(&prod.mutex);
		pthread_cond_broadcast(&prod.cond);

		/*=>Attendre l'autorisation d'affichage...*/
		pthread_mutex_lock(&prod.mutex);
		while(prod.state != STATE_PRINT){
			pthread_cond_wait(&prod.cond, &prod.mutex);
		}
		pthread_mutex_unlock(&prod.mutex);

		/*=>Afficher le resultat de l'iteration courante...*/
		
		fprintf(stderr,"Itérations %lu : result = %f \n", iter + 1, prod.result);

		

	}

	/*=>Attendre la fin des threads de multiplication...*/
	for (size_t i = 0; i<prod.size; i++){
		pthread_join(multTh[i],NULL); // NULL car peu importe le statut de retour
	}

	/*=>Attendre la fin du thread d'addition...*/
	pthread_join(addTh, NULL);

	/*=> detruire prod.cond ... */
	pthread_cond_destroy(&prod.cond);

	/*=> detruire prod.mutex ... */
	pthread_mutex_destroy(&prod.mutex);

	/* Detruire avec free ce qui a ete initialise avec malloc */

	free(prod.pendingMult);
	free(prod.v1);
	free(prod.v2);
	free(prod.v3);
	free(multTh);
	free(multData);
	return(EXIT_SUCCESS);
}