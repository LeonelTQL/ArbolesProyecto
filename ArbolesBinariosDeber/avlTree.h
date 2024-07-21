
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <cstring>

using namespace std;
#define pow2(n) (1 << (n))

struct avl_node {
    int data;
    avl_node* left;
    avl_node* right;
};

class avlTree {
public:
    avl_node* root;
    avlTree() {
        root = NULL;
    }

    int height(avl_node*);
    int diff(avl_node*);
    avl_node* rr_rotation(avl_node*);
    avl_node* ll_rotation(avl_node*);
    avl_node* lr_rotation(avl_node*);
    avl_node* rl_rotation(avl_node*);
    avl_node* balance(avl_node*);
    avl_node* balanceTree(avl_node*);
    avl_node* insert(avl_node*, int);
    avl_node* deleteNode(avl_node*, int);
    avl_node* findMax(avl_node*);
    avl_node* findMin(avl_node*);
    void display(avl_node*, int);
    void drawNode(avl_node*, int, int, int);
    void drawTree(avl_node*, int, int);
    void inorder(avl_node*);
    void preorder(avl_node*);
    void postorder(avl_node*);
    void bfs(avl_node*);
    void dfs(avl_node*);
    void printGivenLevel(avl_node*, int);
    int validate(string s);
    bool checkInput(string s);
    void drawButton(int, int, int, int, const char*);
    bool isButtonClicked(int, int, int, int, int, int);
    string inputText(int, int, int, int);
};
#endif // AVL_TREE_H
