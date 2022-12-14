//
// Created by 蔡昊文 on 25/7/20.
//

#ifndef INC_9024_C_PROJECT_RBTREE_H
#define INC_9024_C_PROJECT_RBTREE_H

#endif //INC_9024_C_PROJECT_RBTREE_H
// Red-Black Tree ADT interface ... COMP9024 20T2

#include <stdbool.h>

typedef int Item;      // item is just a key

typedef struct Node *Tree;

Tree newTree();        // create an empty Tree
void freeTree(Tree);   // free memory associated with Tree
void showTree(Tree);   // display a Tree (sideways)

bool TreeSearch(Tree, Item);   // check whether an item is in a Tree
Tree TreeInsert(Tree, Item);   // insert a new item into a Tree