
#include "avlTree.h"
#include <graphics.h>
#include <cstdlib>
#include <cctype>
#include <cstring>

using namespace std;

const int x = 600;
const int y = 100;

int avlTree::height(avl_node* temp) {
    int h = 0;
    if (temp != NULL) {
        int l_height = height(temp->left);
        int r_height = height(temp->right);
        int max_height = (l_height > r_height) ? l_height : r_height;
        h = max_height + 1;
    }
    return h;
}

int avlTree::diff(avl_node* temp) {
    int l_height = height(temp->left);
    int r_height = height(temp->right);
    int b_factor = l_height - r_height;
    return b_factor;
}

avl_node* avlTree::rr_rotation(avl_node* parent) {
    avl_node* temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

avl_node* avlTree::ll_rotation(avl_node* parent) {
    avl_node* temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

avl_node* avlTree::lr_rotation(avl_node* parent) {
    avl_node* temp;
    temp = parent->left;
    parent->left = rr_rotation(temp);
    return ll_rotation(parent);
}

avl_node* avlTree::rl_rotation(avl_node* parent) {
    avl_node* temp;
    temp = parent->right;
    parent->right = ll_rotation(temp);
    return rr_rotation(parent);
}


avl_node* avlTree::balance(avl_node* temp) {
    int bal_factor = diff(temp);
    if (bal_factor > 1) {
        if (diff(temp->left) > 0)
            temp = ll_rotation(temp);
        else
            temp = lr_rotation(temp);
    } else if (bal_factor < -1) {
        if (diff(temp->right) > 0)
            temp = rl_rotation(temp);
        else
            temp = rr_rotation(temp);
    }
    return temp;
}

avl_node* avlTree::balanceTree(avl_node* root) {
    if (root == NULL)
        return root;
    root->left = balanceTree(root->left);
    root->right = balanceTree(root->right);
    return balance(root);
}


avl_node* avlTree::insert(avl_node* root, int value) {
    if (root == NULL) {
        root = new avl_node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        return root;
    } else if (value < root->data) {
        root->left = insert(root->left, value);
        root = balance(root);
    } else if (value >= root->data) {
        root->right = insert(root->right, value);
        root = balance(root);
    }
    return root;
}


avl_node* avlTree::deleteNode(avl_node* root, int value) {
    if (root == NULL) {
        return root;
    }
    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL || root->right == NULL) {
            avl_node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            avl_node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    if (root == NULL) {
        return root;
    }
    return balance(root);
}

avl_node* avlTree::findMax(avl_node* root) {
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

avl_node* avlTree::findMin(avl_node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}


void avlTree::display(avl_node* ptr, int level) {
    int i;
    if (ptr != NULL) {
        display(ptr->right, level + 1);
        cout << endl;
        if (ptr == root)
            cout << "Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout << "        ";
        cout << ptr->data;
        display(ptr->left, level + 1);
    }
}

void avlTree::drawNode(avl_node* node, int x, int y, int level) {
    int nodeRadius = 20;
    if (node == NULL) {
        return;
    }
    setcolor(WHITE);
    circle(x, y, nodeRadius);
    string nodeData = to_string(node->data);
    outtextxy(x - 10, y - 10, const_cast<char*>(nodeData.c_str()));

    int childXOffset = pow2(3 - level) * 20;
    int childYOffset = 50;

    if (node->left) {
        line(x - nodeRadius, y + nodeRadius, x - childXOffset + nodeRadius, y + childYOffset - nodeRadius);
        drawNode(node->left, x - childXOffset, y + childYOffset, level + 1);
    }

    if (node->right) {
        line(x + nodeRadius, y + nodeRadius, x + childXOffset - nodeRadius, y + childYOffset - nodeRadius);
        drawNode(node->right, x + childXOffset, y + childYOffset, level + 1);
    }
}

void avlTree::drawTree(avl_node* root, int x, int y) {
    if (root == NULL) {
        return;
    }
    drawNode(root, x, y, 0);
}


void avlTree::inorder(avl_node* tree) {
    if (tree == NULL)
        return;
    inorder(tree->left);
    cout << tree->data << "  ";
    inorder(tree->right);
}


void avlTree::preorder(avl_node* tree) {
    if (tree == NULL)
        return;
    cout << tree->data << "  ";
    preorder(tree->left);
    preorder(tree->right);
}


void avlTree::postorder(avl_node* tree) {
    if (tree == NULL)
        return;
    postorder(tree->left);
    postorder(tree->right);
    cout << tree->data << "  ";
}


void avlTree::bfs(avl_node* tree) {
    int h = height(tree);
    for (int i = 1; i <= h; i++) {
        printGivenLevel(tree, i);
    }
}

void avlTree::dfs(avl_node* tree) {
    if (tree == NULL) return;
    cout << tree->data << " ";
    dfs(tree->left);
    dfs(tree->right);
}

void avlTree::printGivenLevel(avl_node* root, int level) {
    if (root == NULL) return;
    if (level == 1) {
        cout << root->data << " ";
    } else if (level > 1) {
        printGivenLevel(root->left, level - 1);
        printGivenLevel(root->right, level - 1);
    }
}

// Validating input
int avlTree::validate(string s) {
    int count = 0;
    if (checkInput(s)) {
        return 100;
    }
    return 400;
}

bool avlTree::checkInput(string s) {
    int length = s.length();
    for (int i = 0; i < length; i++) {
        if (isdigit(s[i]) == false) {
            return false;
        }
    }
    return true;
}

void avlTree::drawButton(int left, int top, int right, int bottom, const char* label) {
    setcolor(WHITE);
    rectangle(left, top, right, bottom);
    setcolor(GREEN);
    outtextxy(left + 10, top + 10, const_cast<char*>(label));
}

bool avlTree::isButtonClicked(int left, int top, int right, int bottom, int mx, int my) {
    return (mx > left && mx < right && my > top && my < bottom);
}

string avlTree::inputText(int left, int top, int right, int bottom) {
    char str[20] = "";
    setcolor(WHITE);
    rectangle(left, top, right, bottom);
    setcolor(GREEN);
    outtextxy(left + 5, top + 5, const_cast<char*>("Ingresa un numero: "));
    while (1) {
        if (kbhit()) {
            char c = getch();
            if (c == 13) {
                break;
            } else if (c == 8) {
                if (strlen(str) > 0) {
                    str[strlen(str) - 1] = '\0';
                    outtextxy(left + 10, top + 25, str);
                }
            } else {
                strncat(str, &c, 1);
                outtextxy(left + 10, top + 25, str);
            }
        }
    }
    return string(str);
}
