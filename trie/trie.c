#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef struct trie_node
{
    struct trie_node *names[ALPHABET_SIZE];

    // if is_end_of_word is true -> represent end of a word
    bool is_end_of_word;
}
trie_node;

// returns new trie node (initialized to NULLs)
trie_node *get_node(void)
{
    trie_node *temp = malloc(sizeof(trie_node));
    
    // initialize all values to null
    temp->is_end_of_word = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        temp->names[i] = NULL;
    }

    return temp;
}

// insert a new node
void insert(trie_node *root, char *key)
{
    trie_node *ptr = root;
    int size = strlen(key);
    for (int i = 0; i < size; i++)
    {
        int index = key[i] - 'a';

        // Check if there is a node or not
        if (!ptr->names[index])
        {
            ptr->names[index] = get_node();
        }

        ptr = ptr->names[index];
    }

    // mark last node as leaf
    ptr->is_end_of_word = true;
}

// search for a node
bool search(trie_node *root, char *key)
{
    trie_node *ptr = root;
    int size = strlen(key);
    for (int i = 0; i < size; i++)
    {
        int index = key[i] - 'a';

        // check if any char not found from the current leaf
        if (!ptr->names[index])
        {
            return false;
        }

        ptr = ptr->names[index];
    }

    return ptr->is_end_of_word;
}

int main ()
{
    char *keys[] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};

    trie_node *root = get_node();

    for (int i = 0; i < 8; i++)
    {
        insert(root, keys[i]);
    }

    // Search for different keys
    char output[][32] = {"Not present in trie", "Present in trie"};
 
    // Search for different keys
    printf("the ___ %s\n", output[search(root, "the")]);
    printf("these ___ %s\n", output[search(root, "these")]);

    return 0;
}