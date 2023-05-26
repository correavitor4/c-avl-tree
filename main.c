#include <stdio.h>
#include <malloc.h>


typedef struct node{
  int value;
  struct node *left, *right;
  short height;
} Node;

short greater (short a, short b){
    return (a > b) ? a : b;
}

short height(Node *node){
    if (node == NULL){
        return -1;
    }
    else{
        return node->height;
    }
}

short balanceFactor(Node *node){
    if (node)
        return (height(node->left) - height(node->right));
    else
        return 0;
}


Node* rotateLeft(Node *r){
    Node *y, *f;

    y = r->right;
    f = y->left;

    y->left = r;
    r->right = f;

    r->height = greater(height(r->left), height(r->right)) + 1;
    y->height = greater(height(y->left), height(y->right)) + 1;

    return y;
}
Node* rotateRight(Node* r){
    Node *y, *f;

    y = r->left;
    f = y->right;

    y->right = r;
    r->left = f;

    r->height = greater(height(r->left), height(r->right));
    y->height = greater(height(y->right), height(y->left));

    return y;
}


Node* rotateRightLeft(Node *r){
    r->right = rotateRight(r->right);
    return rotateLeft(r);
}

Node* rotateLeftRight(Node *r){
    r->left = rotateLeft(r->left);
    return rotateRight(r);
}

Node* balance(Node *node){
    short bf = balanceFactor(node);

    if(bf < -1){
        if (balanceFactor(node->right) <= 0){
            node = rotateLeft(node);
            return node;
        }

        node = rotateRightLeft(node);
        return node;
    }

    if (bf > 1){
        if(balanceFactor(node->left) >= 0){
            node = rotateRight(node);
            return node;
        }

        return rotateLeftRight(node);
    }

    return node;
}

Node* createNode(Node *node, int value){
    node = (Node *) malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 0;
    return node;
}

Node* insertElement(Node *node,int value){
    if (node == NULL){
        node = createNode(node ,value);
        return node;
    }

    if (value >= node->value){
        node->right = insertElement(node->right, value);
    }
    else{
        node->left = insertElement(node->left, value);
    }

    //Calculate height in all nodes between root and inserted node
    node->height = greater(height(node->left), height(node->right)) + 1;

    //Check if is necessary to balance our tree
    node = balance(node);

    return node;
}

int main() {
    Node *tree = NULL;
    int elements[] = {5,8,6,10,5,7,9, 11,4,1,33,21};
    for (int i = 0; i <= 11; i++){
        tree = insertElement(tree, elements[i]);
    }
    return 0;
}