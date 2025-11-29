#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

// Vérifie si un nombre nb est prmier 
int  isPrime (int nb){
	
	

}

//Compte le nombre de nombres premiers 
int primeNumbers (int N){

	int count=0;
	int i;	 
	for (i =  2; i< N; i++){
		count += isPrime(i); 
	}	
	return count;
}


int main (int argc, char ** argv){
	

	if (argc < 2){
		printf ("Usage %s N\n", argv[0]);  
		exit(0); 
	}
	

	int N = atoi(argv[1]); 
	printf("Le nombre de nombre premiers entre 2 et %d est : %d\n",N , primeNumbers(N)); 

	
   	
   	return  EXIT_SUCCESS;  
 
}


