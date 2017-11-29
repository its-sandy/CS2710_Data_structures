 /*                     RED BLACK TREES

 write a program to implement a red black tree with insert, delete and search features
                                                                            */

// including necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rb_tree_cormen.h"                                   // .h file having structure definitions and function prototypes of tree
#include "queue.h"                                          // .h file having structure definitions and function prototypes of queue


rbtree* createTree()                                        // function to initialize the tree
{
    rbtree* tree = (rbtree* )malloc(sizeof(rbtree));        //allocate memory to the tree
    node* temp = (node *)malloc(sizeof(node));              // we create a sentinel node that has fixed values
    temp -> parent = temp -> left = temp -> right = temp ;
    temp -> colour = false;
    temp -> value = -1;
    tree->root = tree->nil = temp;                          //root and nil of the tree are made as the new node
    return tree;
}

void left_rotate(rbtree* T, node* x)                        //function to perform left rotation
{
    node* y = x -> right;                                   // y is the right child of x (it should exist for left rotation)

    x -> right = y -> left;                                 // y's right childbecomes x's left child
    if(y->left != T->nil)
        (y -> left) -> parent = x;
    
    y -> parent = x -> parent;                              // y's parent becomes x's parent
    if(x->parent == T->nil)                                 //if x was earlier the root, y becomes new root
        T->root = y;
    else if(x == (x->parent)->left)
        (x->parent)->left = y;
    else
        (x->parent)->right = y;

    y->left = x;                                            //x becomes y's left child
    x->parent = y;
}

void right_rotate(rbtree* T, node* x)                       //function to perform right rotation
{
    node* y = x -> left;                                    // y is the left child of x (it should exist for right rotation)

    x -> left = y -> right;                                 // y's left childbecomes x's right child
    if(y->right != T->nil)
        (y -> right) -> parent = x;
    
    y -> parent = x -> parent;                              // y's parent becomes x's parent
    if(x->parent == T->nil)                                 //if x was earlier the root, y becomes new root
        T->root = y;
    else if(x == (x->parent)->right)
        (x->parent)->right = y;
    else
        (x->parent)->left = y;

    y->right = x;                                           //x becomes y's right child
    x->parent = y;
}

node* tree_minimum(rbtree* T, node* x)                      // function to find left-most child of given node
{
    if(x != T->nil)
    {
        while(x->left != T->nil)
            x = x->left;
    }
    return x;
}

void rb_insert_fixup(rbtree* T, node* z)                    //function to alter the tree after insertion to satisfy red black properties
{
    while((z->parent)->colour == true)                      //properties are violated only if parent is red
    {
        if(z->parent == ((z->parent)->parent)->left)        //if parent is left child of it's parent
        {
            node* y = ((z->parent)->parent)->right;         // y is uncle

            if(y->colour == true)                           //case: uncle is red
            {
                (z->parent)->colour = false;
                y->colour = false;
                ((z->parent)->parent)->colour = true;
                z = (z->parent)->parent;
            }
            else                                            //case: uncle is black
            {
                if(z == (z->parent)->right)                 //case: if z is right child of its parent
                {
                    z = z->parent;
                    left_rotate(T, z);
                }

                (z->parent)->colour = false;
                ((z->parent)->parent)->colour = true;
                right_rotate(T, (z->parent)->parent);
            }        
        }
        else                                                //if parent is right child of it's parent
        {
            node* y = ((z->parent)->parent)->left;          // y is uncle

            if(y->colour == true)                           //case: uncle is red
            {
                (z->parent)->colour = false;
                y->colour = false;
                ((z->parent)->parent)->colour = true;
                z = (z->parent)->parent;
            }
            else                                            //case: uncle is black
            {
                if(z == (z->parent)->left)                  //case: if z is left child of its parent
                {
                    z = z->parent;
                    right_rotate(T, z);
                }

                (z->parent)->colour = false;
                ((z->parent)->parent)->colour = true;
                left_rotate(T, (z->parent)->parent);
            }
        }
    }
    (T->root)->colour = false;                              // root is always black by property
}

void rb_insert(rbtree* T, int key)                          // function to perform insertion into the tree
{
    node* z = (node*) malloc( sizeof(node));                //we create a new node with the given key
    z -> value = key ;
    z -> colour = true ;
    z -> right = z -> left = z -> parent = T->nil ;

    node* y = T->nil;                                       // nodes pointing to root and nil
    node* x = T->root;

    while(x != T->nil)                                      //we find the spot where node should be inserted
    {
        y = x;
        if(z->valuex < x->value)
            x = x->left;
        else if ( z->value > x -> value )
            x = x->right;
        else
            return;                                         // if key is already there in the tree, we simply return 
    }

    z->parent = y;                                          // y becomes parent of z

    if(y == T->nil)                                         // z becomes child of y (also check if z should be root)
        T->root = z;
    else if(z->value < y->value)
        y->left = z;
    else
        y->right = z;

    z->left = T->nil;                                       // children of z are made nil
    z->right = T->nil;
    z->colour = true;                                       // colour of z is red (by default)

    rb_insert_fixup(T, z);                                  // we recover the red black properties
}

node* findNode(rbtree* T, node* root, int key)              // function to return node with a given value
{       
    if(root == T->nil)
        return T->nil;                                      // nil is returned if either root is not there
    if(root -> value == key)                                
        return root;                                        // if node is available, we return its address

    if(key < root -> value)                                 // we move into the 2 subtress depending on node's value
        return findNode(T, root -> left, key);
    else
        return findNode(T, root -> right, key);
}


void search(rbtree* T, int key)                             //function that simply prints output based on what findNode function returns
{
    node* temp = findNode(T, T->root, key);
    // if(temp == NULL)
    // printf("the element is not present in the tree\n");
    // else
    // printf("the element is performsent in the tree\n");
}

void rb_transplant(rbtree* T, node* u, node* v)             // function that replaces node v in place of node u
{
    if(u->parent == T->nil)                                 // checks if v should become the new root
        T->root = v;
    else if (u == (u->parent)->left)                        // assigns link from parent
        (u->parent)->left = v;
    else
        (u->parent)->right = v;
    v->parent = u->parent;                                  // changes parent of v
}

void rb_delete_fixup(rbtree* T, node* x)                    //function to alter the tree after deletion to satisfy red black properties
{
    node* w;                                                // node w is sister of node x
    while(x != T->root && x->colour == false)               // we proceed as long as there is double black
    {
        if(x == (x->parent)->left)                          //case: if x is left child of parent
        {
            w = (x->parent)->right;
            if(w->colour == true)                           //case: sister is RED
            {
                w->colour == false;
                (x->parent)->colour == true;
                left_rotate(T, x->parent);
                w = (x->parent)->right;
            }

            if((w->right)->colour == false && (w->left)->colour == false)   //case: if both children of sister are BLACK
            {
                w->colour = true;
                x = x->parent;
            }
            else 
            {
                if((w->right)->colour == false)            //case: if left child of sister is RED
                {
                    (w->left)->colour = false;
                    w->colour = true;
                    right_rotate(T, w);
                    w = (x->parent)->right;
                }

                w->colour = (x->parent)->colour;            //case: if at least left child of sister is RED
                (x->parent)->colour = false;
                (w->right)->colour = false;
                left_rotate(T, x->parent);
                x = T->root;
            }
        }
        else                                                //case: if x is left child of parent
        {
            w = (x->parent)->left;
            if(w->colour == true)                           //case: sister is RED
            {
                w->colour == false;
                (x->parent)->colour == true;
                right_rotate(T, x->parent);
                w = (x->parent)->left;
            }

            if((w->left)->colour == false && (w->right)->colour == false)            //case: if both children of sister are BLACK
            {
                w->colour = true;
                x = x->parent;
            }
            else 
            {
                if((w->left)->colour == false)              //case: if right child of sister is RED
                {
                    (w->right)->colour = false;
                    w->colour = true;
                    left_rotate(T, w);
                    w = (x->parent)->left;
                }

                w->colour = (x->parent)->colour;            //case: if at least right child of sister is RED
                (x->parent)->colour = false;
                (w->left)->colour = false;
                right_rotate(T, x->parent);
                x = T->root;
            }
        }    
    }

    x->colour = false;                                      //we get rid of the double black
}

void rb_delete(rbtree* T, int key)                          //function to perform insertion given the key
{
    node* z = findNode(T, T->root, key);                    //finds location where key is present

    if(z != T->nil)                                         //if key exists in the tree
    {
        node* y = z;
        node* x;
        bool y_original_colour = y->colour;                 //stores original colour of node to be deleted

        if(z->left == T->nil)                               //if node to be deleted has at most one child
        {
            x = z->right;
            rb_transplant(T, z, z->right);                  //directly transfer it 
        }
        else if(z->right == T->nil)
        {
            x = z->left;
            rb_transplant(T, z, z->left);
        }
        else                                               // if node to be deleted has both children
        {
            y = tree_minimum(T, z->right);                 // find leftmost node of right subtree
            y_original_colour = y->colour;                 //this becomes the new node to be deleted
            x = y->right;

            if(y->parent == z)                              //if y is just one step below z
                x->parent = y;
            else
            {
                rb_transplant(T, y, y->right);              //we transplant it to y
                y->right = z->right;
                (y->right)->parent = y;
            }

            rb_transplant(T, z, y);                         //y is replaced by z
            y->left = z->left;
            (y->left)->parent = y;
            y->colour = z->colour;
        }

        if(y_original_colour == false)                      // if the node deleted was black, it may give double black
            rb_delete_fixup(T, x);                          //thus, we fix the tree
    }
}

void printLevelOrder(rbtree* T)                             //function that prints all nodes in the tree in Level Order 
{
    node* root = T->root;

    if(root == NULL)                                        // checks if tree is empty
        printf("the tree is empty\n");
    else
    {
        Queue *q = createQueue();                           // we utilize a queue data structure to perform level order
        QNode *n;
        printf("the level order of tree is :-\n");
        enQueue(q, root);                                   // root becomes the first QNode in the queue

        while(q -> front != NULL)                           // while queue is not empty
        {
            n = deQueue(q);                                 // front element is dequed
            if(n->element != NULL)                          // if it is not NULL
            {
                printf("%d", n->element->value);           // weprint its value and enque its children at the end
                if(n->element->colour)
                    printf("(red, ");
                else
                    printf("(black, ");
                if((n->element)->parent != NULL)
                    printf("%d) ",((n->element)->parent)->value);
                else
                    printf("null) ");
                enQueue(q, n->element->left);
                enQueue(q, n->element->right);
            }
        }
        printf("\n");
    }
}

void freeTree(rbtree* T)                                    // function to delete the complete tree                                  
{
    freeNodes(T->root, T->nil);
    free(T->nil);
    free(T);
}

void freeNodes(node* root, node* sentinel)                  //function to delete all nodes in the subtree under root
{   
    if(root != sentinel)
    {
        freeNodes(root -> left, sentinel);                  // should be performed in post-order traversal form
        freeNodes(root -> right, sentinel);
        free(root);
    }
}

