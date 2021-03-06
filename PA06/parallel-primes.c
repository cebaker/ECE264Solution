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
  uint128 number;
  
}object;

void *PrimeTest(void * obj);
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
    int len = 0;
    uint128 tmp = value;
    uint128 tmp2 = value;
    int i;
    
    while(tmp != 0)
    {
      tmp /= 10;
      len++;
    }
    char * string = malloc(sizeof(char)*(len + 1));
    
    string[len] = '\0';
    for( i = len - 1 ;i >= 0;i--)
    {
      string[i] = (tmp2 % 10) + '0';
      
      tmp2 = tmp2 / 10;
    }
    return string;
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
    uint128 i,j,k;
    int result = 0;
    uint128 max = floor(sqrt(value));
    uint128 chunk;
    chunk  = (max + n_threads + 1) / n_threads;
    
    object * piece = malloc(sizeof(object)*n_threads);
    pthread_attr_t * attr = malloc(n_threads * sizeof(pthread_attr_t));
    
    pthread_t * thread = malloc(n_threads * sizeof(pthread_t));
    
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
      pthread_attr_init(&attr[i]);
      pthread_create(&thread[i],&attr[i],PrimeTest, (void*)&piece[i]);
      
    }
    for(j = 0;j < n_threads;j++)
    {
      pthread_join(thread[j],NULL);
      
    }
    
    result = 1;
    
    for(k = 0;k < n_threads;k++)
    {
      if(piece[k].Pval != 1)
      {
	result = FALSE;
	k = n_threads;
      }
      
      
    }

    
    free(piece);
    free(attr);
    free(thread);
    
  return result;  
           
}


void *PrimeTest(void * obj)
{
    object * test = (object*)obj;

    uint128 i;
    for(i = test->start; i <= test->end; i += 2)
      {
       if((test->number % i) == 0)
         {
	   test->Pval = FALSE;
   	   return NULL;
         }
   
      }
      test->Pval = TRUE;
    
    return NULL;
}
