/*
 * Please fill the functions in this file.
 * You can add additional functions. 
 *
 * For this assignment, you must use qsort and give appropriate
 * comparison functions.
 *
 * You can assume that the input files have no empty lines and the
 * last line ends with '\n'.  You can count the number of lines by
 * counting the occurrences of '\n'.
 *
 * Hint: 
 * You can write additonal functions.
 *
 */

#include "pa02.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INT     0
#define STRING  1
#define FAILURE 0
#define SUCCESS 1

/*
This function int_cmp is used to sort the numbers in the file and to make sure that 
they are sorted from smallest to largest.
*/
int int_cmp(const void *a, const void *b) 
{ 
    const int *ia = (const int *)a; // casting pointer types 
    const int *ib = (const int *)b;
    return *ia  - *ib; 
	/* integer comparison: returns negative if b > a 
	and positive if a > b */ 
} 
/*
This function is used to compare the strings and to sort
them in an accending manner.
*/
static int cmpstringp(const void *p1, const void *p2)
{
   return strcmp(* (char * const *) p1, * (char * const *) p2);
}

/*This funciton sorts the integers in an accending manner*/
void sortInt(char * inName, char * outName)
{
 int ch = 0;
 int lines = 0;
 int j = 0;
 FILE * fptr;
 FILE * fp;
 fptr = fopen(inName, "r");
 fp = fopen(outName,"w");
 int * buff;

//Printf Statement for if the output file pointer cannot be opened
 if(fptr == NULL)
 {
   printf("Invalid FileName");
   return;
 }


  while ((ch = fgetc(fptr)) != EOF)
    {
      if (ch == '\n')
	{ 
	  lines++; 
	}
    }
    //Allocating memory to the buffer array
     buff = malloc(sizeof(int )*lines);
    //Setting the output file pointer to the front of the file after we use it.
     fseek(fptr,0,SEEK_SET);
     for(j = 0; j < lines;j++)
     {
       fscanf(fptr,"%d",&buff[j]);       
     }
     
     qsort(buff,lines,sizeof(int),int_cmp);
     
   //For loop used to print the buffer to the output file
  for( j = 0; j < lines; j++)
  {
    fprintf(fp,"%d\n",buff[j]);    
  }  
  
  free(buff);
  fclose(fp);   
  fclose(fptr);
}

/*
 * =================================================================
 * read the strings from the file whose name is inName
 * sort the strings
 * stored the sorted strings in the file whose name is outName
 *
 * The strings are sorted by ASCII order (using strcmp). Thus, 'B' will
 * appear before 'a'.
 */


void sortString(char * inName, char * outName)
   {
  int ch = 0;
  
  int lines = 0;
  size_t len = 0;
  long int read = 0;
  int i = 0;
  FILE * fp;
  FILE * fptr;
  char** storage;
  char * buff = NULL;
  fptr = fopen(inName, "r");
  fp = fopen(outName,"w");
  //print statement is used when the input file cannot be opened
  
  if(fptr == NULL)
  {
    printf("Invalid FileName");
    return;
  }
    while ((ch = fgetc(fptr)) != EOF)
    {
      if (ch == '\n')
	{ 
	  lines++; 
	}
    }
    //fseek used to set the input file pointer back to the fron 
    // of the file when you use the pointer
    fseek(fptr,0,SEEK_SET);
    storage = malloc(sizeof(char*) * lines);
    

    for( i = 0; i < lines; i++)
    {
      
       read = getline(&buff,&len,fptr);
       storage[i] = malloc(len);
       strcpy(storage[i],buff); 
  
    }
    //qsort is used to sort  the strings into the right order
    qsort(storage,lines,sizeof(char*),cmpstringp);
    
    fseek(fp,0,SEEK_SET);
    for( i = 0; i < lines;i++) 
    {
      fprintf(fp,"%s",storage[i]);
      
    }
    //both of these fclose statements are used to close the file pointers 
    fclose(fptr);
    fclose(fp);
    //this for loop is used to free the string elemets of the 2nd demension in the array
    for(i = 0; i < lines; i++)
    {
      free(storage[i]); 
    }
    //These free statements are used to free the "one" demensional arrays called 
    //storage and buff
    free(storage);
    free(buff);
    
}
