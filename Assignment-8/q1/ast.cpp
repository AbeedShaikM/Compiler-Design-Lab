#include "ast.h"
#include <gvc.h>

using namespace std;

// Function to create a new node
Node* createNode(char *value, Node *left, Node *right) {
    
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = strdup(value);  // Use strdup to copy the string
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

void printAST(Node *root, int level = 0) {
    if (root == NULL) return;

    // Initialize a Graphviz context
    GVC_t *gvc = gvContext();

    // Create a directed graph
    Agraph_t *g = agopen(const_cast<char*>("G"), Agdirected, nullptr);

    // Queue to perform a level-order traversal (BFS) of the tree
    std::queue<std::pair<Node*, Agnode_t*>> q;

    // Create the root node in Graphviz
    int counter = 1;
    Agnode_t *gRoot = agnode(g, strdup((std::string(root->value) + "_" + std::to_string(counter++)).c_str()), 1);

    // Enqueue the root node
    q.push({root, gRoot});

    // Traverse the tree using BFS
    while (!q.empty()) {
        Node* curr = q.front().first;
        Agnode_t* gCurr = q.front().second;
        q.pop();

        // Process the left child
        if (curr->left != NULL) {
            Agnode_t *gLeft = agnode(g, strdup((std::string(curr->left->value) + "_" + std::to_string(counter++)).c_str()), 1);
            agedge(g, gCurr, gLeft, nullptr, 1);
            q.push({curr->left, gLeft});
        }

        // Process the right child
        if (curr->right != NULL) {
            Agnode_t *gRight = agnode(g, strdup((std::string(curr->right->value) + "_" + std::to_string(counter++)).c_str()), 1);
            agedge(g, gCurr, gRight, nullptr, 1);
            q.push({curr->right, gRight});
        }
    }

    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "png", "tree_output.png");

    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);

    printf("Tree has been drawn and saved as 'tree_output.png'\n");
}


