#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa05.h"

int main(int argc, char** argv){
  
    FILE* fptr;
    int len = 0;
    char bit_char  ;
    HuffNode* head;
    
    
    if(!CheckArgCount(argc)){
       return EXIT_FAILURE;
    }
    if((fptr = OpenFile(argv[1], "rb")) == NULL){
        return EXIT_FAILURE;
    }
    
    len = strlen(argv[1]);
    bit_char = argv[1][len - 1];
    

    head = headerfileread(fptr,bit_char);
    
    Huff_postOrderPrint(head);
    CloseFile(fptr);
    
    DestroySnode(head);
    
    return EXIT_SUCCESS;
}

