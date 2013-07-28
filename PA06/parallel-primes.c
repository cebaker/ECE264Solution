
/**
 * The ENTIRE assignment should be completed within this file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

#include "pa06.h"

// void PrimeTest(object * obj);
typedef struct prime
{
  
  int Pval;
  uint128 start;
  uint128 end;
  uint number;
  
}object;

void PrimeTest(void * obj);
/**
 * Read a uint128 from a string.
 * This function is provided for your convenience.
 */
uint128 alphaTou128(const char * str)
{
    uint128 ret = 0;
    while(*str >= '0' && *str <= '9') {
	ret *= 10; // "left-shift" a base-ten number
	ret += (*str - '0'); // add in the units
	++str;
    }
    return ret;
}

/**
 * The caller is responsible for freeing the result 
 */
char * u128ToString(uint128 value)
{
    int cnt
    char strnum;
    uint128 mask1 = 0;
    uint128 mask2 = 0;
    
   // mask1 = value & 1111111111;
    //mask2 = value & 00000000001111111111;

    copy = mask1 + mask2;
    printf("\n%c = num\n");


    return copy;
}

/**
 * Test is 'value' is prime.
 * 'n_threadss' is the number of threads to create to complete this computation.
 * Return TRUE of FALSE.
 * 
 * LEAK NO MEMORY
 *
 * Good luck!
 */

int primalityTestParallel(uint128 value, int n_threads)
{
    if(value == 1 || value == 2)
    {
      return TRUE;
      
    }
    
    if(value % 2 == 0)
    {
    return FALSE;
    }
    uint128 i,j;
    uint128 max = floor(sqrt(value));
    uint128 chunk;
    chunk  = (max + n_threads + 1) / n_threads;
    object * piece = malloc(sizeof(object)*n_threads);
    pthread_t thread[n_threads];
    
    for(i = 0;i < n_threads;i++)
    {
      piece[i].start = i * chunk;
      piece[i].end = (i + 1) * chunk - 1;
      piece[i].number = value;
      if( piece[i].start < 3)
      {
	piece[i].start = 3;
      }
      if((piece[i].start % 2) == 0)
      {
	piece[i].start = piece[i].start + 1;
      }
      pthread_create(&thread[i],NULL,PrimeTest,&piece[i]);
      
    }
    for(j = 0;j < n_threads;j++)
    {
      pthread_join(thread[j],NULL);
      if(piece[j].Pval == 1)
      {
	return TRUE;
      }
      
    }
    
    
   
  return FALSE;  
           
}


void PrimeTest(void * obj)
{
    object * test;

    uint128 i;
    for(i = test->start; i <= test -> end; i += 2)
      {
       if((test->number % i) == 0)
         {
	   test->Pval = FALSE;
   	   return;
         }
   
      }
      test->Pval = TRUE;
    
    return ;
}

