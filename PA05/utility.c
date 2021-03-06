#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa05.h"


/* DO NOT MODIFY THIS FUNCTION!!! */
void Huff_postOrderPrint(HuffNode *tree)
{  
    if(tree == NULL){
      
    return;
    }
  printf("Left\n");
  Huff_postOrderPrint(tree->left);
  printf("Back\n");
  printf("Right\n");
  Huff_postOrderPrint(tree->right);
  printf("Back\n");
  if(tree->left == NULL && tree->right == NULL){
    printf("Leaf: %c\n", tree->value);
  }
  return;
    

}

/* This function checks if the number of command-line arguments provided is
 * appropriate for this program */
int CheckArgCount(int argc)
{
  if(argc < 2) {
   PrintError(ARGCOUNTERROR);
   return FALSE;
  }
  return TRUE;
}

/* This function attempts to open the file containing the set of characters.  If
 * unsuccessful, the function returns NULL, otherwise it returns the address
 * to the file */
FILE* OpenFile(char FileName[], char mode[])
{
  FILE* fp;
  fp = fopen(FileName, mode);
  
  if(fp == NULL)
  {  
    PrintError(FILEERROR);   
  }
  return fp;
  
}


/*Function used to get the bits in the file*/

int fgetbits(FILE* fp,int number,unsigned int * ct,unsigned char * ch)
{
  //char ch = 0;				//ct is leftover bits from read
  //static int ct = 0;
  unsigned char character;
  
  if (*ct == 0){
     fread(ch, 1, 1, fp);
     *ct = 8;
  }
  if (*ct<number){
    character= *ch;
    character=(character<<(8-*ct));
    fread(ch, 1, 1, fp);
    character = (character|(*ch >> *ct));
   
    return character;
  }
     character=*ch;
     if(number==1)
     { 
     character=(character>>(*ct-number))&0x01;
     *ct = (*ct - 1);
     }
     else {character=(character>>(*ct-number));
     *ct = 0;
     }
    
  return ((int) character);

}


/* Node construct constructs a nod that has two leaves*/
HuffNode *nodeconstruct(int key)
{
  // LLIST *new_node = malloc(sizeof(LLIST));
   HuffNode* node = malloc(sizeof(HuffNode));

  /* Check if memory allocation is successful.  If not, the function should
   * print an error message from PrintError() and return NULL */
  if (node == NULL){
    PrintError(MEMORYERROR);
    return NULL;
  }
  
  /* Place the character into the new node and return it */
  (*node).value = key;
  (*node).left = NULL;
  (*node).right = NULL;
  return node;
}

/*Destroying a Leaf */
void destroyleaf(LLIST *leaf)
{
   LLIST *curr = (*leaf).next ;
   LLIST *prev = (*curr).next;
   free(curr);
   curr = prev;  
   (*leaf).next = NULL;
  
}


/*THis function essentially makes a stack node after reahhead function reports that a new stack head needs to be created*/ 
LLIST* SNodeCreate(HuffNode* lptr,LLIST* head)
{
  LLIST* lnode = malloc(sizeof(LLIST));
  (*lnode).next = head;
  (*lnode).lptr = lptr;

  while(lnode == NULL)
  {
    PrintError(MEMORYERROR);
    return NULL;  
  }
  
  
  return lnode;
  

}

/*This function essentially does everything that is needed for ipa2_1 most of the rest of the function that are new are just called in this function and used to create the stack and pop the stack*/
// I worked heavily on this portion of my algorithm with siriam Rangaramanujan and Alex groh
HuffNode* headerfileread(FILE* fp,char bit_char)
{
  //BIT field;
  unsigned int ct = 0;
  unsigned char build = 0;
  char ch = '0';
  fseek(fp,0,SEEK_SET);
  LLIST *stackhead = NULL;
  int initial = 1;
  int check = 0;
  
  check = fgetc(fp);
  
  /*this function does all of the functional parts of headerfileread
  it takes return character of fgetbits(fp) and pops or pushes the character of 
  fgetbits(fp) onto or of of the stack essentially doin all of the 
  work needed for this part of the prodject*/
  if(bit_char == 't')
  {
    rewind(fp);
  while((ch = fgetbits(fp,1,&ct,&build) == 1) ||(initial == 1)|| (*stackhead).next != NULL)   
  {
    initial = 0;
    /*if the character is a 1 continue to create a new head and add to the stack the head*/
    if(ch ==  1)
    {
    ch = fgetbits(fp,8,&ct,&build);
    stackhead = SNodeCreate(NULL,stackhead);
    (*stackhead).lptr = nodeconstruct(ch);
    }
    /*if the character is a zero *pop* the last two items the left and the right child off of the stack*/
    if(ch == 0)
    {
      HuffNode * base = nodeconstruct(0);
      (*base).right = (*stackhead).lptr;
      stackhead = SNodeDestruct(stackhead);
      (*base).left = (*stackhead).lptr;
      stackhead = SNodeDestruct(stackhead);
      stackhead = SNodeCreate(base,stackhead);
    }
  }


  }
  
  if(bit_char == 'h')
  {
     rewind(fp);
     while((ch = fgetc(fp) == '1') ||(initial == '1')|| (*stackhead).next != NULL)   
       {
         initial = 0;
          /*if the character is a 1 continue to create a new head and add to the stack the head*/
         if(ch ==  1)
       {
         ch = fgetc(fp);
         stackhead = SNodeCreate(NULL,stackhead);
         (*stackhead).lptr = nodeconstruct(ch);
       }
         /*if the character is a zero *pop* the last two items the left and the right child off of the stack*/
      if(ch == 0)
       {
          HuffNode * base = nodeconstruct(0);
          (*base).right = (*stackhead).lptr;
          stackhead = SNodeDestruct(stackhead);
          (*base).left = (*stackhead).lptr;
	  stackhead = SNodeDestruct(stackhead);
	  stackhead = SNodeCreate(base,stackhead);
    }
  }
      
  }
   LLIST* temp = stackhead;
  free(stackhead);
  return temp -> lptr; 

}

/*This function will destroy the stack top after we use it. It wil return a new top being the (*node).next */
LLIST* SNodeDestruct(LLIST* node) 
{
  //fgetc(fp)
  LLIST* p = (*node).next;
   
  free(node);
  return p;
}

/* Prints appropriate error message for potential errors that may occur
 * during program execution */
void PrintError(int error)
{
    switch(error)
    {
        case ARGCOUNTERROR:
            printf("Not enough arguments.\n Use: ex6 <filename>\n");
            break;
        case FILEERROR:
            printf("Error opening file!\n");
            break;
        case MEMORYERROR:
            printf("Error allocating memory! Exiting Program!\n");
            break;
	case ORDERERROR:
	    printf("Set of characters unordered! Exiting Program\n");
        default:
            break;
    }
}

/* This function closes the file containing the set of characters */
void CloseFile(FILE* fp)
{
  fclose(fp);
}

/* This function recursively destroys all of the nodes of the BST. This is
 * by destroying the left subtree first, then the right subtree, then the
 * node itself */
void DestroySnode(HuffNode* tree){
  /* If you reach a leaf in the tree, leave the function */
  if(tree == NULL)
   {    
     return;
   }
  DestroySnode((*tree).left);
  DestroySnode((*tree).right);
  free(tree);
  return ;
}