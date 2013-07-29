#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include "pa13.h"

#define SUCCESS 0
#define FAILURE -1

int GetBit(long data, long bit);
void *SSSthread(void* arg);


typedef struct
{
  long index1;
  long index2;
  int targetNum;
  int* intset;
  int length;
  int* numofsolutions;
  pthread_mutex_t *mutex;
}Subset;
/*
 * Write a parallel C program that returns the answer for the following problem:
 * Given a nonempty set S, with elements {a1, a2, a3, ...}, and a integer N, 
 * find the number of nonempty subsets of S, such that the sum of all elements 
 * in this subset equals to N.
 *
 * Arguments:
 *	intset - pointer to an array of a integer set
 *	length - size (length) of the integer set
 *	N - target sum value
 *	numThread - number of threads 
 * Return value:
 *	numOfSolutions - Number of nonempty subsets in which the subsetSum value 
 *	matches with N. This variable should be protected as the critical 
 *	sections by using mutex objects.
 *
 * Hint: The total number of possible subsets is (2^(length)-1). You may use
 * 	math library function 'pow()' to assign the index for each thread.
 * 	pthread.h and math.h are already included in this file.
 */
int subsetSum(int * intset, int length, int N, int numThread)
{ 
  int lastInd = 1;
  int counter;
  int Numofsolutions = 0;
  
  int i;
 
  counter = pow(2, length) -1;
  
  pthread_mutex_t * mutex = malloc(numThread * sizeof(pthread_mutex_t));
  
  pthread_t * th = malloc(numThread * sizeof(pthread_t));
  
  pthread_attr_t * attr = malloc(numThread* sizeof(pthread_attr_t));
  
  Subset * s = malloc(numThread * sizeof(Subset));
  
  if(mutex == NULL)
    {
      printf("Unable to allocate memory\n");
      return EXIT_FAILURE;
    }
  
  if(th == NULL)
    {
      printf("Unable to allocate memory\n");
      return EXIT_FAILURE;
    }
  
  if(attr == NULL)
    {
      printf("Unable to allocate memory\n");
      return EXIT_FAILURE;
    }
  
  if(s == NULL)
    {
      printf("Unable to allocate memory\n");
      return EXIT_FAILURE;
    }
  
  pthread_mutex_init(mutex, NULL);
  
  
  // loop through the number of threads the program will spawn
		
  //Calculate the starting and ending indices for the data region
  //the thread will be inverting
	
  //Store the location of the data into the structure
		
  //Initialize the attributes for the thread
  
  for(i=0; i<numThread; i++)
    {
      s[i].index1 = lastInd;
      lastInd += (counter/numThread);
      s[i].index2 = lastInd;
      lastInd++;
    
      s[i].intset = intset;
      s[i].numofsolutions = &Numofsolutions;
      s[i].mutex = mutex;
      s[i].length = length;
      s[i].targetNum = N;
    
      pthread_attr_init(&attr[i]);
    
    }
  
  	
  //Make sure the ending index of the last thread is within the bounds 
  //of the data
  
  s[numThread-1].index2 = counter+1;
  
  // loop through the number of threads the program will spawn
	
  //Print the starting and ending indicies of the structure for 
  //the thread
	
  //Create the thread
  
  for(i=0; i<numThread; i++)
    {
      pthread_create(&(th[i]), &(attr[i]), SSSthread, (void*) &(s[i]));
    }
    
     // loop through the number of threads the program will spawn
		
  //Wait for all of the threads to finish executing
  
  for(i=0; i<numThread; i++)
    {
      pthread_join(th[i], NULL);
    }
  
  //deallocate memory
  
  free(th);
  free(attr);
  free(s);
  free(mutex);
  
  return Numofsolutions;
}




int GetBit(long data, long bit)    
{
  return data & (1 << bit);     //masking
}




void *SSSthread(void* arg)
{
  Subset* s = (Subset*)arg;  //typecast argument
  long index;
  int sum;
  int i;
  
  for(index = s->index1; index < s->index2; index++)
    {
    
      sum=0;  //initialize sum to zero
      for(i=0; i < s->length; i++)
	{
      
	  if(GetBit(index, i) != 0) 
	    sum += s->intset[i];       //increment sum
	}
    
      if(sum == s->targetNum)          //if sum = the required sum, lock the mutex and increment number of solutions
	{
	  pthread_mutex_lock(s->mutex);
	  (*(s->numofsolutions))++;
	  pthread_mutex_unlock(s->mutex);  //unlock mutex again
	}
    }
  
  pthread_exit(SUCCESS);
  return SUCCESS;
}
