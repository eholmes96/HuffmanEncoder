/*
 * File:	tree.h
 *
 * Copyright:	2015, Darren C. Atkinson
 *
 * Description:	This file contains the public function declarations for a
 *		simply binary tree abstract data type.
 */

# ifndef TREE_H
# define TREE_H


struct tree *createTree(int data, struct tree *left, struct tree *right);

void destroyTree(struct tree *root);

int getData(struct tree *root);

struct tree *getLeft(struct tree *root);

struct tree *getRight(struct tree *root);

struct tree *getParent(struct tree *root);

void setLeft(struct tree *root, struct tree *left);

void setRight(struct tree *root, struct tree *right);

#endif /* TREE_H */
