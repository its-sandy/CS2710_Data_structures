 /*   File containing function definitions for the tree and queue data structures
    some Print statements are commented for output readability
                                                                            */

// including necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rb_tree.h"                                   // .h file having structure definitions and function prototypes of tree
#include "queue.h"                                          // .h file having structure definitions and function prototypes of queue

bool already_there = false;

node *newNode(int value, node* parent)                      
{
    /* function used to initialize new nodes in the tree */
    node *temp =  (node *)malloc(sizeof(node));
    temp->value = value;
    temp->colour = true;                                 // indicates whether the node has been deleted or not
    temp->left = temp->right = NULL;
    temp->parent = parent;
    return temp;                                            // returns the newly allocated node
}

void inorder(node *root, bool first)
{
    /* function used to perform inorder traversal (ascending order)
    of the tree.*/
    if(first == true)                                       // variable to indicate first level recursive call (for tidier printing)
    {
        if(root != NULL)
            printf("The inorder traversal is:-\n");
        else
            printf("There are no elements\n");
    }
    if (root != NULL)
    {
        inorder(root->left, false);                         // left subtree printed before current node
        printf("%d ", root->value);
        inorder(root->right, false);                        // right subtree printed after current node
    }
    if(first == true)
        printf("\n");
}

void left_rotate(node** root_ptr, node* p)
{
    node* x = p -> right;

    p -> right = x -> left;
    if(x->left != NULL)
        (x -> left) -> parent = p;
    
    x -> parent = p -> parent;
    if(p->parent == NULL)
        *root_ptr = x;
    else
    {
        if((p -> parent) -> left == p)
            (p -> parent) -> left = x;
        else  
            (p -> parent) -> right = x;
    }
    x -> left = p;
    p -> parent = x;
}

void right_rotate(node** root_ptr, node* p)
{
    node* x = p -> left;

    p -> left = x -> right;
    if(x->right != NULL)
        (x -> right) -> parent = p;
    
    x -> parent = p -> parent;
    if(p->parent == NULL)
        *root_ptr = x;
    else
    {
        if((p -> parent) -> left == p)
            (p -> parent) -> left = x;
        else  
            (p -> parent) -> right = x;
    }
    x -> right = p;
    p -> parent = x;
}

node* insert(node* root, int key)
{
    /* A utility function to insert a new node with given key in BST 
    returns the location where the node was inserted*/
    if(root == NULL)                                        // if tree does not exist, the new node by itself is the root
        return newNode(key, NULL);                          
    if(root->value == key)                                  // checks if a node with the given value is already present
    {
        already_there = true;
        return root;
    }
    else if(key > root->value)                              // if key is bigger than node, move to right subtree
    {
        if(root -> right == NULL)                           // if subtree doesn't exist
        {
            root->right = newNode(key, root);
            return root->right;
        }
        else                                                // if subtree exists, recursively call in it
            return insert(root->right, key);
    }
    else                                                    // if key is smaller than node, move to left subtree
    {
        if(root -> left == NULL)                            // if subtree doesn't exist
        {
            root->left = newNode(key, root);
            return root->left;
        }
        else                                                // if subtree exists, recursively call in it
            return insert(root->left, key);         
    }
}

node* uncle(node* x)
{
    if(((x->parent)->parent)->left == x->parent)
        return ((x->parent)->parent)->right;
    else
        return ((x->parent)->parent)->left;
}

node* sibling(node* x)
{
    if((x->parent)->left == x)
        return (x->parent)->right;
    else
        return (x->parent)->left;
}

node* grandparent(node* x)
{
    return (x->parent)->parent;
}

bool colour(node* x)
{
    if(x == NULL)
        return false;
    else
        return x->colour;
}

node* substitute_node(node* x)
{
    while(x->right != NULL)
        x = x->right;
    return x;
}

void insert_alterations(node** root_ptr, node* x)
{
    if(x == *root_ptr)
        x -> colour = false;
    if(x != *root_ptr && (x->parent)->colour == true)
    {
        node* u =  uncle(x);
        node* p = x->parent;
        node* g = grandparent(x);
        if(colour(u) == true)
        {
            p->colour = u->colour = false;
            g->colour = true;
            insert_alterations(root_ptr,g);
        }
        else
        {
            if(g->left == p && p->left == x)
            {
                right_rotate(root_ptr, g);
                p->colour = false;
                g->colour = true;
            }
            else if(g->right == p && p->right == x)
            {
                left_rotate(root_ptr, g);
                p->colour = false;
                g->colour = true;
            }
            else if(g->left == p && p->right == x)
            {
                left_rotate(root_ptr, p);
                insert_alterations(root_ptr, p);
            }
            else if(g->right == p && p->left == x)
            {
                right_rotate(root_ptr, p);
                insert_alterations(root_ptr, p);
            }
        }
    }
}

node* insertion(node** root_ptr, int key) // takes address of root as input
{
    /* function used to manage the different processes in insertion 
    receives the address of root pointer so that root can itself be changed
    if required*/
    printf("insertion starts with key %d\n",key);
    already_there = false;
    node* x = insert(*root_ptr, key);                // pointer to location where key was inserted
    
    if(already_there == false)
    {
        if(*root_ptr == NULL)                                   // if it were an empty tree, root has to be altered
            *root_ptr = x;

        insert_alterations(root_ptr, x);        
    }
        
    printf("element is inserted\n");
    inorder(*root_ptr, true);
    printLevelOrder(*root_ptr);
    printf("\n");
    return *root_ptr;                                       // returns the root node
}

node* findNode(node* root, int key)
{
    /* utility function to find if element is present in
    tree and is not deleted */
    if(root == NULL)
        return NULL;                                        // NULL is returned if either root is not there
    if(root -> value == key)                                // or node is present in tree but is delete
        return root;                                    // if node is available, we return its address

    if(key < root -> value)                                 // we move into the 2 subtress depending on node's value
        return findNode(root -> left, key);
    else
        return findNode(root -> right, key);
}

void freeNodes(node* root)
{
    /*utility function to delete all nodes in the subtree under root*/
    if(root != NULL)
    {
        freeNodes(root -> left);                            // should be performed in post-order traversal form
        freeNodes(root -> right);
        free(root);
    }
}

void search(node* root, int key)
{
    /*function that simply prints output based on what findNode function returns */
    node* temp = findNode(root, key);
    // if(temp == NULL)
    // printf("the element is not present in the tree\n");
    // else
    // printf("the element is present in the tree\n");
}

void printLevelOrder(node* root)
{
    /* function that prints all nodes in the tree in 
    Level Order (even if they are not available)  */
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
                    printf("(red) ");
                else
                    printf("(black) ");
                enQueue(q, n->element->left);
                enQueue(q, n->element->right);
            }
        }
        printf("\n");
    }
}

void double_black(node** root_ptr, node* u)
{
    if(u != *root_ptr)
    {
        node* s = sibling(u);
        node* r = NULL;
        node* p = u->parent;

        if(!colour(s)) //case3.2 a and b
        {
            if(p->right == s && colour(s->right))
            {
                printf("double black 3.2 a iii\n");
                r = s->right;
                left_rotate(root_ptr, p);
                r->colour = false;
            }
            else if(p->left == s && colour(s->left))
            {
                printf("double black 3.2 a i\n");
                r = s->left;
                right_rotate(root_ptr, p);
                r->colour = false;
            }
            else if(p->right == s && colour(s->left))
            {
                printf("double black 3.2 a iv\n");
                r = s->left;
                right_rotate(root_ptr, s);
                left_rotate(root_ptr, p);
                r->colour = false;
            }
            else if(p->left == s && colour(s->right))
            {
                printf("double black 3.2 a ii\n");
                r = s->right;
                left_rotate(root_ptr, s);
                right_rotate(root_ptr, p);
                r->colour = false;
            }
            else                    // both of siblings children are black
            {
                printf("double black 3.2 b\n");
                s->colour = true;
                if(p->colour == true)
                    p->colour = false;
                else
                    double_black(root_ptr, p);
            }
        }
        else
        {
            if(p->right == s)
            {   
                printf("double black 3.2 c ii\n");
                (s->left)->colour = true;
                left_rotate(root_ptr, p);
                s->colour = false;
            }
            else
            {
                printf("double black 3.2 c i\n");
                (s->right)->colour = true;
                right_rotate(root_ptr, p);
                s->colour = false;
            }       
        }
    }
}

node* deletion(node** root_ptr, int key)
{
    printf("Deletion starts with key %d\n",key);
    /* function to delete the given node in tree, if it is available */
    node* v = findNode(*root_ptr, key);                  // we check if node is available
    if(v == NULL)
        printf("the element is not present in the tree\n");
    else                                                    // if node is available
    {
        if(v->left != NULL && v->right != NULL)
        {
            node* temp1 = substitute_node(v->left);
            v->value = temp1->value;
            v = temp1;
        }

        node* u;
        if(v->right == NULL)
            u = v->left;
        else
            u = v->right;

        if((colour(u) || colour(v)) == false)
            {
                double_black(root_ptr, v); //both u and v are black
                printf("double black completed\n");
            } 
        else
            printf("either u or v is red\n");
        
        if((colour(u) || colour(v)) && u != NULL)
            u->colour = false;
            
        if(v == *root_ptr)
        {
            free(v);
            *root_ptr = u;
            if(u != NULL)
                u->parent = NULL;
        }
        else
        {
            if((v->parent)->left == v)
                (v->parent)->left = u;
            else
                (v->parent)->right = u; 
            if(u != NULL)
               u->parent = v->parent;
            free(v);
        }
    }
    printf("deletion completed\n");
    inorder(*root_ptr, true);
    printLevelOrder(*root_ptr);
    printf("\n");
    return *root_ptr;                                       // we return the root (updated or otherwise)
}