#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "utility.h"

int main(int argc, char** argv){
  
    FILE* fptr;
    LEAF* head;
    
    
    if(!CheckArgCount(argc)){
       return EXIT_FAILURE;
    }
    if((fptr = OpenFile(argv[1], "rb")) == NULL){
        return EXIT_FAILURE;
    }

    head = headerfileread(fptr);
    
    PostOrderWalk(head);
    CloseFile(fptr);
    
    DestroySnode(head);
    
    return EXIT_SUCCESS;
}

