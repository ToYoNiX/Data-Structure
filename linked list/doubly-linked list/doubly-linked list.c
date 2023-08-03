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

void delete(node *ptr, int value)
{
    if(ptr == NULL)
    {
        return;
    }

    if (ptr->number != value)
    {
        return delete(ptr->next, value);
    }

    if(ptr->prev != NULL)
    {
        (ptr->next)->prev = ptr->prev;
    }
    else
    {
        (ptr->next)->prev = NULL;
    }

    if(ptr->next != NULL)
    {
        (ptr->prev)->next = ptr->next;
    }
    else
    {
        (ptr->prev)->next = NULL;
    }

    free(ptr);
}

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

    delete(list, 3);

    print_list(list);

    // search for elements
    //char output[][10] = {"Not Found", "Found"};
    //printf("3 -> %s\n", output[search(list, 3)]);

    // cleaning the list
    unload(list);

    return 0;
}