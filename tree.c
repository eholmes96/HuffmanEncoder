/*
 * File: tree.h
 * By Evan Holmes
 *
 *
 *
 */

#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "tree.h"



struct tree{
    int data;
    struct tree *parent;
    struct tree *left;
    struct tree *right;
};


struct tree *createTree(int data, struct tree *left, struct tree *right)
{
    struct tree *tr;       //creates tree
    tr = malloc(sizeof(struct tree));       //allocate memory
    assert(tr != NULL);     //make sure that tr exists
    
    tr->data = data;
    
    if(left != NULL)    //if there is a left tree to be added
    {
        if(left->parent != NULL)    //if it has a parents
        {
            if(left->parent->right == left) //check left/right from parent
            {
                left->parent->right = NULL; //remove from parent
            }
            else if(left->parent->left == left)
            {
                left->parent->left = NULL; //remove from parent
            }
        }//end left->parent

        left->parent = tr;          //attach parent to left
        tr->left = left;            //attatch left to tr

    }//end left
    
    if(right != NULL)
    {
        if(right->parent != NULL)
        {
            if(right->parent->right == right)
            {
                right->parent->right = NULL;
            }
            else if(right->parent->left == right)
            {
                right->parent->left = NULL;
            }
        }//end right->parent
        
    right->parent = tr;
    tr->right = right;

    }//end right
    
    
    return tr;

}

void destroyTree(struct tree *root)
{
    assert(root != NULL);           //make sure that root exists
    if(root->left != NULL)          //if there is a left tree
        destroyTree(root->left);    //recursively destroy it
    if(root->right != NULL)         //Same thing for right tree
        destroyTree(root->right);
    free(root);
    
} //end destroy tree

int getData(struct tree *root)
{
    assert(root != NULL);   //make sure that root exists
    return root->data;
}

struct tree *getLeft(struct tree *root)
{
    assert(root != NULL);   //make sure that root exists
    return root->left;
}

struct tree *getRight(struct tree *root)
{
    //assert(root != NULL);   //make sure that root exists
    return root->right;
}

struct tree *getParent(struct tree *root)
{
    //assert(root != NULL);   //make sure that root exists
    return root->parent;
}


void setLeft(struct tree *root, struct tree *left)
{
    assert(root != NULL);
    if(left != NULL)    //if there is a left tree to be added
    {
        if(left->parent != NULL)    //if it has a parents
        {
            if(left->parent->right == left) //check left/right from parent
            {
                left->parent->right = NULL; //remove from parent
            }
            else if(left->parent->left == left)
            {
                left->parent->left = NULL; //remove from parent
            }
        }//end left->parent
        
        left->parent = root;          //attach parent to left
        root->left = left;            //attatch left to tr
        
    }//end left

}

void setRight(struct tree *root, struct tree *right)
{
    assert(root != NULL);
    
    if(right != NULL)
    {
        if(right->parent != NULL)
        {
            if(right->parent->right == right)
            {
                right->parent->right = NULL;
            }
            else if(right->parent->left == right)
            {
                right->parent->left = NULL;
            }
        }//end right->parent
        
        right->parent = root;
        root->right = right;
        
    }//end right

    
}






