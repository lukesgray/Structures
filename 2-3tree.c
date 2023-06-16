#include <stdio.h>
#include <stdlib.h>

#define MAX_KEYS 2
#define MAX_CHILDREN 3

typedef struct node
{
    int num_keys;        // Number of keys in node
    int key1;            // First key in node
    int key2;            // Second key in node
    struct node *child1; // Pointer to first child
    struct node *child2; // Pointer to second child
    struct node *child3; // Pointer to third child
} Node;

// Create a new node
Node *create_node(int key, Node *left_child, Node *right_child)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->num_keys = 1;
    new_node->key1 = key;
    new_node->key2 = 0;
    new_node->child1 = left_child;
    new_node->child2 = right_child;
    new_node->child3 = NULL;
    return new_node;
}

// Insert a key into a node
void insert_key(Node *node, int key)
{
    if (key < node->key1)
    {
        node->key2 = node->key1;
        node->key1 = key;
    }
    else if (node->num_keys == 1 || key < node->key2)
    {
        node->key2 = key;
    }
    node->num_keys++;
}

// Insert a key into a 2-3 tree
Node *insert(Node *root, int key)
{
    if (root == NULL)
    {
        return create_node(key, NULL, NULL);
    }
    if (root->num_keys == MAX_KEYS)
    {
        Node *new_node = create_node(0, NULL, NULL);
        new_node->child1 = root;
        split(new_node, 0, root);
        root = new_node;
    }
    insert_node(root, key);
    return root;
}

// Split a full node
void split(Node *parent, int index, Node *node)
{
    Node *left_child = node;
    Node *right_child = (Node *)malloc(sizeof(Node));
    right_child->num_keys = 0;
    right_child->key1 = 0;
    right_child->key2 = 0;
    right_child->child1 = NULL;
    right_child->child2 = NULL;
    right_child->child3 = NULL;
    int i;
    if (index == 0)
    {
        parent->key2 = parent->key1;
        parent->key1 = left_child->key1;
    }
    else
    {
        parent->key2 = left_child->key2;
    }
    for (i = MAX_KEYS / 2; i < MAX_KEYS; i++)
    {
        right_child->num_keys++;
        if (i == MAX_KEYS / 2)
        {
            right_child->key1 = left_child->key2;
            left_child->key2 = 0;
        }
        else
        {
            right_child->key2 = left_child->key2;
            left_child->key2 = 0;
        }
    }
    for (i = MAX_CHILDREN / 2; i < MAX_CHILDREN; i++)
    {
        right_child->child3 = left_child->child3;
        left_child->child3 = NULL;
    }
    parent->child2 = right_child;
}

// Insert a key into a non-full node
void insert_node(Node *node, int key)
{
    if (node->child1 == NULL)
    {
        insert_key(node, key);
        return;
    }
}