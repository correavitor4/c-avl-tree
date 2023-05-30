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

Node* removeNode(Node *root, int key){
    if (root == NULL){
        printf("Value not found");
        return NULL;
    }
    if (root->value == key){
        if (root->left == NULL && root->right == NULL){
            free(root);
            printf("Element removed: %d\n", key);
            return NULL;
        }
        if (root->left != NULL && root->right != NULL){
            Node *aux = root->left;
            while (aux->right != NULL){
                aux = aux->right;
            }
            root->value = aux->value;
            aux->value = key;
            printf("Element swapped:  %d !\n", key);
            root->left = removeNode(root->left, key);
            return root;
        } else{
            Node* aux;
            if(root->left != NULL){
                aux = root->left;
            } else{
                aux = root->right;
            }
            free(root);
            printf("Element with 1 child removed: %d\n", key);
            return aux;
        }
    }else{
        if (key > root->value){
            root->right = removeNode(root->right, key);
        } else{
            root->left = removeNode(root->left, key);
        }
    }

    root->height = greater(height(root->left), height(root->right)) + 1;
    root = balance(root);
    return root;
}

void printTree(Node *root, int level){
    int i;
    if(root != NULL){
        printTree(root->right, level + 1);
        printf("\n\n");
        for (i = 0; i < level; i++){
            printf("\t");
        }

        printf("%d", root->value);
        printTree(root->left, level + 1);
    }
}

int main() {
    Node *tree = NULL;
    int elements[] = {5,8,6,10,5,7,9, 11,4,1,33,21,22};
    for (int i = 0; i <= 12; i++){
        tree = insertElement(tree, elements[i]);
    }

    printTree(tree, 1);
    for (int i=0; i<=12; i++){
        tree = removeNode(tree ,elements[i]);
    }
    return 0;
}