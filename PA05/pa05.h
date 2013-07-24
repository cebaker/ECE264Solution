#ifndef ex3_utility_h
#define ex3_utility_h

#define TRUE 1
#define FALSE 0
#define ARGCOUNTERROR 1 
#define FILEERROR     2
#define MEMORYERROR   3
#define ORDERERROR    4

/* This is a structure implementation for the stack*/
typedef struct llist{
  struct llist* next;
  struct leaf* lptr;
}LLIST;

typedef struct leaf {
    int value;
    struct leaf *left;
    struct leaf *right;
} HuffNode;


//Declare Functions
void Huff_postOrderPrint(HuffNode *tree);
int  CheckArgCount(int argc);
FILE* OpenFile(char FileName[], char mode[]);
void destroyleaf(LLIST *header);
HuffNode* headerfileread(FILE* fptr,char);
LLIST* SNodeDestruct(LLIST* node);
LLIST* SNodeCreate(HuffNode* lptr,LLIST* head);
void CloseFile(FILE* fptr);
void PrintError(int error);
HuffNode* CreateNode(int value);
HuffNode* nodeconstruct(int);
int fgetbits(FILE*,int,unsigned int*,unsigned char*);

void DestroySnode(HuffNode* tree);
#endif