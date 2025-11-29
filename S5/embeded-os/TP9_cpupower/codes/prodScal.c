#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>


#ifndef RAND_MAX
#define RAND_MAX ((int) ((unsigned) ~0 >> 1))
#endif

double produit (double * V1 , double *V2, long TAILLE)
{
  
   double res=0.0; 
  
   // *** a compléter --> Calcul du produit verctoriel  
  
   return res; 
}

void genVectors (double *V1, double *V2, long TAILLE){
   
	long i; 
	for (i =0; i< TAILLE; i++){
		V1[i] = (double) rand() / RAND_MAX ; 
		V2[i] = (double) rand() / RAND_MAX; 
	}   
	
		
}

int main (int argc, char *argv[])
{
    if (argc < 2){
	printf (" Usage %s Taille\n", argv[0]); 
	exit(0);
   } 
   
   

   
   long TAILLE = atol(argv[1]);
   

   double * V1;  // *** a compléter --> Allocation dynamique de V1 
   double * V2; // *** a compléter -->  Allocation dynamique de V2
   
   srand((int) time(NULL));
   genVectors (V1, V2, TAILLE); 

   printf ("%lf\n", produit (V1, V2, TAILLE)); 

   free(V1); 
   free(V2); 

   

   return  EXIT_SUCCESS; 
  
}


