#include <stdlib.h>
#include <stdio.h>
#include <utility.h>
#include "tree.h"
#include "bst.c"

/* DO NOT MODIFY THIS FUNCTION!!! */
void Huff_postOrderPrint(HuffNode *tree)
{
  
    FILE * fptr;
    fptr = fopen(argv[2],"w");
    
    if(fptr == NULL)
    {
      PrintError(FILEERROR);
      
      
    }
    
    // Base case: empty subtree
    if (tree == NULL) {
		return;
    }
    
    // Recursive case: post-order traversal

    // Visit left
    printf("Left\n");
    Huff_postOrderPrint(tree->left);
	fprintf(fptr,"Back\n");
    // Visit right
    printf("Right\n");
    Huff_postOrderPrint(tree->right);
	fprintf(fptr,"Back\n");
    // Visit node itself (only if leaf)
    if (tree->left == NULL && tree->right == NULL) {
		fprintf(fptr,"Leaf: %c\n", tree->value);
    }
    

}