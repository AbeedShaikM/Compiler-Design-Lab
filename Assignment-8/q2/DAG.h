#ifndef AST_H
#define AST_H

#include <bits/stdc++.h>

// Node structure for the AST
typedef struct Node {
    char *value;
    struct Node *left;
    struct Node *right;
} Node;

// Function declarations
extern Node* createNode(char *value, Node *left, Node *right);
extern void printDAG(Node *node, int level);

#endif
