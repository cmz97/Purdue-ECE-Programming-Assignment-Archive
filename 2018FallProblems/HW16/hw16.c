/****************** Modify this file at specified place *************************/
#include <stdio.h>
#include <stdlib.h>
#include "hw16.h"


/********** Do Not modify the file above this line, you can modify below ***********/
#ifdef TEST_FREETREE
// FreeBinaryTree
// This function frees up the memory from the root node

void FreeBinaryTree(treeNode *root)
{
    if(root==NULL)return;
    FreeBinaryTree(root->left);
    FreeBinaryTree(root->right);
}

#endif

#ifdef TEST_SEARCH
// This function recursively searches for a given value in a tree
// and returns the node which has that value
void searchHelper(treeNode * tn, int value, treeNode ** rttn);
void searchHelper(treeNode * tn, int value, treeNode ** rttn){
    if (tn == NULL) {
        return;
    }
    
    if (tn->value == value) {
        *rttn = tn;
    }
    
    searchHelper(tn->leftChild,value,rttn);
    searchHelper(tn->rightChild,value,rttn);
}


treeNode* search(treeNode * tn, int value)
{
    treeNode * rtNode = NULL;
    searchHelper(tn,value,&rtNode);
    return rtNode;
}
#endif


#ifdef TEST_SUBTREE
/* This function checks if `needle` is subtree of `haystack`. By subtree, it means that all the values of
*  `needle` are in `haystack`. For example in Example 1 (README),
*  treeNode with value 10 in Tree1 is subtree of Tree2 but Tree1 is not subtree of Tree2 . Please note this function is different from `isContained`,
* as it recursively compares two Trees/subtrees from the treeNodes given as input.
* It is consistent with  strstr function in C i.e. "strstr(const char \*haystack, const char \*needle)"
*/
bool isSubTree(treeNode* haystack, treeNode *needle)
{
    if (haystack == NULL && needle == NULL)
        return true;
    
    if (haystack == NULL || needle == NULL)
        return false;
    
    return (haystack->data == needle->data   &&
            isSubTree(haystack->left, needle->left) &&
            isSubTree(haystack->right, needle->right) );
}
#endif



#ifdef TEST_CONTAINED
// returns true if needle is contained in haystack
// returns false if needle is not contained in haystack
// needle and haystack may NOT be binary search tree
// Please note that order of arguments are important
// It is consistent with  strstr function in C i.e.
// "strstr(const char \*haystack, const char \*needle)"
bool isContained(treeNode * haystack, treeNode * needle)
{
    treeNode * newRoot = search(haystack,needle->value);
    if (newRoot == NULL) {
        return false;
    }
    return isSubTree(newRoot,needle);
}


#endif
