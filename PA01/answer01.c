/*
 * Please fill the functions in this file.
 * You can add additional functions. 
 *
 * Hint: 
 * You can write additonal functions.
 *
 * You may create additional arrays if needed.  The maximum size
 * needed is specified by MAXLENGTH in pa01.h.
 */

#include "pa01.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * =================================================================
 * This function prints all partitions of a positive integer value
 * See the file "expected/example-output" for the output specification
 */

void recursivePartition(int * arr, int ind, int val);
void printPartition(int * arr, int len);
void recursiveIncreasing(int * arr, int ind, int val);
void recursiveUnique(int * arr, int ind, int val);
void printpermute(char * charset, int len);
void swap(char * var1, char * var2);
void permutehelp(char * arr, int ind, int len);



void printPartition(int * arr, int len)           /*this prints the array after it has been partitioned*/
{
  int lcv;

  printf("= ");
  
  for(lcv = 0; lcv < len - 1; lcv++)
    {
      printf("%d + ", arr[lcv]);
    }
  printf("%d\n", arr[len - 1]);
  
}
    
void recursivePartition(int * arr, int ind, int val)  /*this does the entire process of partitioning which calls itself recursively and print function*/
{
  int lcv;

  if(val == 0)
    {
      printPartition(arr, ind);
    }
      
  for(lcv = 1; lcv <= val; lcv++)
    {
      arr[ind] = lcv;
      recursivePartition(arr, ind + 1, val - lcv);
    }
}
      

void partitionAll(int value)             /*this is the first step to partition the positive integers*/
{
      
  printf("partitionAll %d\n", value);
      
  int array[MAXLENGTH];                 
      
  recursivePartition(array, 0, value);
    
}
/*
 * =================================================================
 * This function prints the partitions that use increasing values.
 *
 * For example, if value is 5
 * 2 + 3 and
 * 1 + 4 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 3 + 2 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 * See the file "expected/example-output" for the output specification
 */

void recursiveIncreasing(int * arr, int ind, int val)  /*this does the entire process to make the numbers increasing*/
{
  int lcv;
    
  if(val == 0)
    {
      printPartition(arr, ind);
    }
    
  for(lcv = 1; lcv <= val; lcv++)
    {
      arr[ind] = lcv;
		
      if(ind == 0)
	{
	  recursiveIncreasing(arr, ind + 1, val - lcv);
	}
      else
	{
	  if(arr[ind - 1] < arr[ind])       /*to print increasing*/
	  //if(arr[ind - 1] <= arr[ind])       /*to print non-decreasing*/
	   
	   //if(arr[ind-1] > arr[ind])        /*to print decreasing*/
	    {
	      recursiveIncreasing(arr, ind + 1, val - lcv);  
	    }
	}
    }
      
}

void partitionIncreasing(int value)                  /*this is the first step to partition the numbers in increasing order*/
{
      
  printf("partitionIncreasing %d\n", value);
      
  int array[MAXLENGTH];
      
  recursiveIncreasing(array, 0, value);
      
}
/*
 * =================================================================
 * This function prints the partitions that use unique values.
 *
 * For example, if value is 5
 * 2 + 3 and
 * 3 + 2 and
 * 1 + 4 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 are invalid partitions.
 *
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 * See the file "expected/example-output" for the output specification
 */

void recursiveUnique(int * arr, int ind, int val)      /*this does the entire process to make the partition numbers Unique*/
{
  int lcv;
  
    
  if(val == 0)
    {
      printPartition(arr, ind);
    }
    
  for(lcv = 1; lcv <= val; lcv++)
    {
      arr[ind] = lcv;
		
      if(ind == 0)
	{
	  recursiveUnique(arr, ind + 1, val - lcv);
	}
      else
	{
	  int i = 0;
	  int j = 0;
	  for(i = ind - 1; i >= 0; i--)
	    {
	      if(arr[ind] == arr[i])
		{
		  //Indicates there are duplicates
		  j = 1;
		}
	    }
	  //if j == 0 it indicates all values are Unique
	  if(j == 0)
	    {
	      recursiveUnique(arr, ind + 1, val - lcv);
	    }
	}
    }
}



void partitionUnique(int value)         /*this is the firt step to make the partition numbers Unique*/
{
  printf("partitionUnique %d\n", value);
  
  int array[MAXLENGTH];
      
  recursiveUnique(array, 0, value);
}

/*
 * =================================================================
 * See the file "expected/example-output" for the output specification
 */

void printpermute(char * charset, int len)    /* prints the complete array after the permutation process is completed*/
{
  int ind;
  for(ind = 0; ind < len; ind++)
    {
      printf("%c ", charset[ind]);
    }
  printf("\n");
}

void swap(char * var1, char * var2)              /*this is used to swap two arrays during the process of permutation*/ 
{
  char var3 = * var1;
  (* var1) = (* var2);
  (* var2) = var3;
}


void permute(char * charset, int len)    
{
  
  printf("permute %d\n", len);
  
  permutehelp(charset, 0, len);
 
}

void permutehelp(char * arr, int ind, int len)  /*this is the function which does the entire process of permutation of the array*/
{
  int lcv;
  if(ind == (len))
    {
      printpermute(arr, len);
    }
  for(lcv = ind; lcv < len; lcv++)
    {
      swap(&arr[lcv], &arr[ind]);
      permutehelp(arr, ind + 1, len);
      swap(&arr[lcv], &arr[ind]);
    }
}



