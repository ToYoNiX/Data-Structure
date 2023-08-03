#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// create struct node for sllinked list
typedef struct node
{
    int number;
    struct node *prev;   
    struct node *next;
}
node;

// insert a new value to the list
node *insert (node *list, int value)
{
    // creating a new node
    node *temp = malloc(sizeof(node));

    // insert the new value
    temp->number = value;

    // prepend the address of the list to the new node
    if (list != NULL)
    {
        list->prev = temp;
    }
    temp->next = list;

    // return the address for the new node
    return temp;
}

// search for a value in the list
bool search(node *ptr, int value)
{
    // if the end of the list -> exit with false
    if (ptr == NULL)
    {
        return false;
    }

    // if found -> exit with true
    if (ptr->number == value)
    {
        return true;
    }

    // still searching
    return search(ptr->next, value);
}

// remove a value from the list
node *delete(node *root ,node *ptr, int value)
{
    // if the end of the list -> return the original root
    if (ptr == NULL)
    {
        return root;
    }

    // if not the wanted value -> go to the next node
    if (ptr->number != value)
    {
        return delete(root, ptr->next, value);
    }

    // if it's the start of the list -> return the new address
    if (ptr->prev == NULL)
    {
        node *temp = ptr->next;
        free(ptr);
        return temp;
    }
    // or change it to the next address
    ptr->prev->next = ptr->next;

    // if it's not the end of the list
    if (ptr->next != NULL)
    {
        ptr->next->prev = ptr->prev;
    }

    // free the the node
    free(ptr);

    // return the original root
    return root;
}

// print all values in the list
void print_list(node *ptr)
{
    if (ptr == NULL)
    {
        return;
    }

    printf("%i\n", ptr->number);
    return print_list(ptr->next);
}

// free the list
void unload(node *ptr)
{
    // if the end of the list -> exit
    if (ptr == NULL)
    {
        return;
    }

    // store the next address before freeing the node
    node *temp = ptr->next;

    // free the node
    free(ptr);

    // move to the next node
    return unload(temp);
}

int main ()
{
    // n for how many int
    int n;
    scanf("%i", &n);

    // creating a list
    node *list = NULL;

    for (int i = 0; i < n; i++)
    {
        // scan for an input
        int val;
        scanf("%i", &val);

        // insert the new value to the list and prepend the new address to the list
        list = insert(list, val);
    }

    // remove any number from the list
    list = delete(list, list, 5);

    // print all list values
    print_list(list);

    // search for elements
    char output[][10] = {"Not Found", "Found"};
    printf("3 -> %s\n", output[search(list, 3)]);

    // cleaning the list
    unload(list);

    return 0;
}