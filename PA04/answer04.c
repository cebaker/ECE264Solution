#include "pa04.h"
#include <stdio.h>
#include <stdlib.h>
#define ARGCOUNTERROR 1
#define FILEERROR     2
#define MEMORYERROR   3 
#define ORDERERROR    4


void PrintError(int error);
SparseNode * SparseArray_mergeHelper(SparseNode * array_1,SparseNode * array_2);

/* Create a single instance of a sparse array node with a specific
 * index and value. This is a constructor function that allocates
 * memory, copies the integer values, and sets the subtree pointers to
 * NULL.
 */

SparseNode *SparseNode_create(int index, int value)
{
  SparseNode * one_node = NULL;
  one_node = malloc(sizeof(SparseNode));
 /* if(one_node == NULL) 
  {
    PrintError(MEMORYERROR);
    return NULL;
  } */
  one_node -> left = NULL;
  (*one_node).right = NULL;
  (*one_node).value = value;
  (*one_node).index = index;
  return one_node;
}

/* Add a particular value into a sparse array on a particular index.
 * The sparse array uses the index as a key in a binary search tree.
 * It returns the new sparse array root
 * as its return value. If the index does not exist, create it. 
 * If the index exists, REPLACE the value to the new one. Use the index to
 * determine whether to go left or right in the tree (smaller index
 * values than the current one go left, larger ones go right).
 */

SparseNode * SparseArray_add( SparseNode * array, int index, int value )
{
  if(value != 0 )
  {
    if(array == NULL)
    {
      return SparseNode_create(index,value);
    }
    if(index == (*array).index)
    {
      (*array).value = value;
      return array;
    }
  
    if(index < (*array).index)
    {
 
      (*array).left = SparseArray_add((*array).left,index,value);
        
    }
    if( index > (*array).index)
    {
     
      (*array).right = SparseArray_add((*array).right,index,value);     
    }
  }
   
  return array;
}

/* Build a sparse array from given indices and values with specific length.
 * This function takes an array of indices, an array of values, and 
 * the length as inputs.
 * It returns a sparse array. 
 * You need to insert tree nodes in order:
 * the first sparse array node contains indices[0] and values[0])
 */

SparseNode *SparseArray_build(int * indicies, int * values, int length)
{
  SparseNode * array = NULL;
  int i;
  
  for(i = 0; i < length; i++)
  {
    array = SparseArray_add(array, indicies[i], values[i]);
  }
  return array;
}

/* Destroy an entire sparse array. 
 * traversing the binary tree in postorder. Use the
 * SparseNode_destroy () function to destroy each node by itself.
 */
void SparseArray_destroy ( SparseNode * array )
{

  if(array != NULL)
  {
    if(array->left != NULL)
    {
      
      SparseArray_destroy((*array).left);
    }
    if(array->right != NULL)
    {
       SparseArray_destroy((*array).right);
    }
     if(array->value != 0 )
     {
     free(array);
     }  
   }
     
}
/* Retrieve the smallest index in the sparse array. 
 */
int SparseArray_getMin(SparseNode * array)
{
  if(array != NULL)
  {
    while ((*array).left != NULL ){
      array = (*array).left;
    }
    
      return(*array).index ;
  }
  
  return 0;
}

/* Retrieve the largest index in the sparse array. 
 */
int SparseArray_getMax(SparseNode * array)
{ 
  if(array != NULL)
  {
    while ((*array).right != NULL) {  
      array = (*array).right ;
    }
    
      return ((*array).index) ;
  }
  
  return 0;
}

/* Retrieve the node associated with a specific index in a sparse
 * array.  It returns the value
 * associated with the index. If the index does not exist in the
 * array, it returns NULL. If the given index is smaller than the current
 * node, search left ; if it is larger, search right.
 */
SparseNode * SparseArray_getNode(SparseNode * array, int index)
{
  if(array == NULL)
  {   
    return NULL;
  }
  if(index == (*array).index)
  {
    return array;
  }
  if(index < (*array).index)
  {
    return SparseArray_getNode((*array).left,index);
  }
 
  return SparseArray_getNode((*array).right,index);



}

/* Remove a value associated with a particular index from the sparse
 * array. It returns the new
 * sparse array ( binary tree root ). HINT : You will need to isolate
 * several different cases here :
 * - If the array is empty ( NULL ), return NULL
 * - Go left or right if the current node index is different.

 * - If both subtrees are empty, you can just remove the node.

 * - If one subtree is empty, you can just remove the current and
 * replace it with the non - empty child.

 * - If both children exist, you must find the immediate successor of
 * the current node ( leftmost of right branch ), swap its values with
 * the current node ( BOTH index and value ), and then delete the
 * index in the right subtree.
*/
SparseNode * SparseArray_remove ( SparseNode * array, int index )
{
  if(array == NULL)
  {
    
   return NULL; 
  }
  
  if(index < (*array).index)
  {
    (*array).left = SparseArray_remove((*array).left,index);
    
    return array;
  }
  if(index > (*array).index)
  {
    (*array).right = SparseArray_remove((*array).right,index);
    return array;
  }
  if(((*array).left == NULL) && ((*array).right == NULL))
  {
    free(array);
    return NULL;
  }
  if((*array).left == NULL)
  {
    SparseNode * rbuff = (*array).right;
   
    free(array);
    return rbuff;
  }
  if(((*array).right) == NULL)
  {
    SparseNode * lbuff = (*array).left;
    free(array); 
    return lbuff; 
  }
  SparseNode * su = (*array).right;
  
  
  while((*array).right == NULL)
  {
    su = (*su).left;  
  }
  
  (*array).index = (*su).index;
  (*su).index = index;
  (*array).right = SparseArray_remove((*array).right,index);
  
  return array;
}
SparseNode * SparseArray_mergeHelper(SparseNode * merged,SparseNode * array_2)
{
  SparseNode * ptr = NULL;
  
  if(array_2 != NULL)
  {
  
    merged = SparseArray_mergeHelper(merged,(*array_2).left);
    
    merged = SparseArray_mergeHelper(merged,(*array_2).right);
    
  
    ptr = SparseArray_getNode(merged,(*array_2).index);

    if(ptr == NULL)
    {
      merged = SparseArray_add(merged,(*array_2).index,(*array_2).value);
      
    }
    else
    {
      (*ptr).value += (*array_2).value;

      if((*ptr).value == 0)
      {
	
        merged = SparseArray_remove(merged,(*ptr).index);          
      }
    }
  } 
  return merged;
}
/* The function makes a copy of the input sparse array 
 * and it returns a new copy. 
 */

SparseNode * SparseArray_copy(SparseNode * array)
{
   if(array == NULL)
   {
     return NULL; 
   }
  SparseNode *copy = NULL;
    
    copy = SparseArray_add(copy,(*array).index,(*array).value);
    
    copy -> right = SparseArray_copy(array -> right);
    copy -> left = SparseArray_copy(array -> left);
 
  
  return copy;
}

/* Merge array_1 and array_2, and return the result array. 
 * This function WILL NOT CHANGE the contents in array_1 and array_2.
 * When merging two sparse array:
 * 1. The contents in array_1 and array_2 should not be changed. You should make
 *    a copy of array_1, and do merging in this copy.
 * 2. array_2 will be merged to array_1. This means you need to read nodes in 
 *    array_2 and insert them into array_1.
 * 3. You need to use POST-ORDER to traverse the array_2 tree. 
 * 4. Values of two nodes need to be added only when the indices are the same.
 * 5. A node with value of 0 should be removed.
 * 6. if array_2 has nodes with index different than any nodes in array_1, you
 *    should insert those nodes into array_1.
 * 
 */

SparseNode * SparseArray_merge(SparseNode * array_1, SparseNode * array_2)
{
  SparseNode * merged ;
  

  if(array_1 == NULL || array_2 == NULL)
  {
    return NULL;
  }
  
   merged = SparseArray_copy(array_1);

  return SparseArray_mergeHelper(merged, array_2);
}


// SparseNode * SparseArray_mergeHelper(SparseNode * merged,SparseNode * array_2)
// {
//   SparseNode * ptr = NULL;
//   
//   if(array_2 != NULL)
//   {
//   
//     merged = SparseArray_mergeHelper(merged,(*array_2).left);
//     
//     merged = SparseArray_mergeHelper(merged,(*array_2).right);
//     
//   
//     ptr = SparseArray_getNode(merged,(*array_2).index);
// 
//     if(ptr == NULL)
//     {
//       merged = SparseArray_add(merged,(*array_2).index,(*array_2).value);
//       
//     }
//     else
//     {
//       (*ptr).value += (*array_2).value;
// 
//       if((*ptr).value == 0)
//       {
// 	
//         merged = SparseArray_remove(merged,(*ptr).index);          
//       }
//     }
//   } 
//   return merged;
// }


void PrintError(int error)
{
  switch(error)
  {
    case ARGCOUNTERROR:
      printf("Not enough arguments. \n Use: ex6 <filename>\n");
      break;
    case FILEERROR:
      printf("Error opening file!\n");
      break;
    case MEMORYERROR:
      printf("Error allocating memory! Exiting Program!\n");
      break;
    case ORDERERROR:
      printf("Set of value unordered! Exiting Program\n");
    default:
	break;
  }  
}
  
  
