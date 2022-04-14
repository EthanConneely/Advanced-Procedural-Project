#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Linked list node
typedef struct node
{
    int crn;  // Company Registration Number (Assume an integer – must be unique)
    // Company Name
    // Company Country
    // Year Company Founded
    // Email Address (must contain an @, a full stop and a .com)
    // Company Contact Name
    // Last Order
    // Number of Employees
    // Average Annual Order
    struct node* next;
} nodeT;

void addNode(nodeT* head, int crn);
bool addUniqueNode(nodeT* head, int crn);  // uses stdbool.h
void removeNode(nodeT* head, int crn);

void displayAll(nodeT* head);

int main()
{
    nodeT* database = malloc(sizeof(nodeT));

    // show user menu
    int choice;

    while (1)
    {
        printf("1. Add client\n");
        printf("2. Display all client details to screen\n");
        printf("3. Display client details\n");
        printf("4. Update a client details\n");
        printf("5. Delete client\n");
        printf("6. Generate statistics\n");
        printf("7. Print all client details into a report file\n");
        printf("8. List all the clients in order of their last average turnover\n");
        printf("9. Exit\n");
        printf("\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:

                break;

            default:
                // Save the data to a file
                exit(0);
        }
    }

    return 0;
}

void addNode(nodeT* head, int crn)
{
    nodeT* newNode = malloc(sizeof(nodeT));
    newNode->crn = crn;
    newNode->next = head->next;
    head->next = newNode;
}

// Add a node to the list returning true if the node was added
bool addUniqueNode(nodeT* head, int crn)
{
    nodeT* current = head;
    while (current->next != NULL)
    {
        if (current->next->crn == crn)
        {
            return false;
        }
        current = current->next;
    }
    addNode(head, crn);
    return true;
}

void removeNode(nodeT* head, int crn)
{
    nodeT* curr = head;
    while (curr->next != NULL)
    {
        if (curr->next->crn == crn)
        {
            nodeT* temp = curr->next;
            curr->next = curr->next->next;
            free(temp);
            return;
        }
        curr = curr->next;
    }
}

void displayAll(nodeT* head)
{
    nodeT* curr = head;
    while (curr->next != NULL)
    {
        printf("%d\n", curr->next->crn);
        curr = curr->next;
    }
}
