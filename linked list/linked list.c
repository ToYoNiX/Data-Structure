#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

void unload(node *ptr)
{
    if (ptr == NULL)
    {
        return;
    }

    node *temp = ptr->next;
    free(ptr);
    return unload(temp);
}

int main ()
{
    // N for how many int
    int n;
    scanf("%i", &n);

    // Creating a list
    node *list = NULL;

    for (int i = 0; i < n; i++)
    {
        // Creating a new node
        node *temp = malloc(sizeof(node));
        if (temp == NULL)
        {
            return 1;
        }

        // Scaning for input & saving it in the node
        scanf("%i", &(temp->number));

        // Prepend the new node to the list
        temp->next = list;
        list = temp;
    }

    // Creating a pointer to iterate on the list
    node *ptr = list;
    while (ptr != NULL)
    {
        printf("%i ", ptr->number);
        ptr = ptr->next;
    }

    // Cleaning the list
    unload(list);

    // New line for the look
    printf("\n");
    return 0;
}