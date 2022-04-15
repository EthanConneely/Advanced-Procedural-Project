// TODO Remove clang stuff below
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#include <conio.h>
#include <stdbool.h>  // bools in c int would work too
#include <stdio.h>
#include <stdlib.h>

// Linked list node
typedef struct node
{
    int crn;            // Company Registration Number (Assume an integer – must be unique)
    char name[50];      // Company Name
    char country[50];   // Company Country
    int year;           // Year Company Founded
    char email[50];     // Email Address (must contain an @, a full stop and a .com)
    char contact[50];   // Company Contact Name
    int lastOrder;      // Last Order
    int numEmployees;   // Number of Employees
    int avgOrder;       // Average Annual Order
    struct node* next;  // Next node
} nodeT;

bool addNode(nodeT** head, int crn);
bool removeNode(nodeT** head, int crn);
bool displayNode(nodeT** head, int crn);

void printNode(nodeT* node);
void readNode(nodeT* node);

void displayAll(nodeT** head);
void getPassword(char* password, int size);

int main()
{
    // char input[30];
    // getPassword(input, 30);
    nodeT* database = NULL;

    int choice;

    while (true)
    {
        // show user menu
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
                int crn;
                printf("Enter the client's registration number: ");
                scanf("%d", &crn);
                if (addNode(&database, crn))
                {
                    printf("\nClient added successfully\n\n");
                }
                else
                {
                    printf("\nClient already exists\n\n");
                }
                break;

            case 2:
                displayAll(&database);
                break;

            case 3:
                int client;
                printf("Enter the client's registration number: ");
                scanf("%d", &client);
                if (!displayNode(&database, client))
                {
                    printf("\nClient not found\n\n");
                }
                break;

            default:
                printf("Exit\n");
                // Save the data to a file
                exit(0);
        }
    }

    printf("End\n");
    return 0;
}

// Add a node to the list returning true if the node was added
bool addNode(nodeT** head, int crn)
{
    // Add the first node
    if ((*head) == NULL)
    {
        (*head) = (nodeT*)malloc(sizeof(nodeT));
        readNode(*head);
        (*head)->crn = crn;
        (*head)->next = NULL;
        return true;
    }
    else
    {
        // A clean way to loop through a linked list
        for (nodeT* node = *head; node != NULL; node = node->next)
        {
            if (node->crn == crn)
            {
                return false;
            }

            if (node->next == NULL)
            {
                nodeT* newNode = (nodeT*)malloc(sizeof(nodeT));
                readNode(newNode);
                newNode->crn = crn;
                newNode->next = NULL;
                node->next = newNode;
                return true;
            }
        }
        return true;
    }
}

// Remove a node retirning true if the node was removed
bool removeNode(nodeT** head, int crn)
{
    // A clean way to loop through a linked list
    for (nodeT* node = *head; node != NULL; node = node->next)
    {
        if (node->crn == crn)
        {
            return false;
        }
    }
    return true;
}

bool displayNode(nodeT** head, int crn)
{
    // A clean way to loop through a linked list
    for (nodeT* node = *head; node != NULL; node = node->next)
    {
        if (node->crn == crn)
        {
            printNode(node);
            return true;
        }
    }

    return false;
}

void displayAll(nodeT** head)
{
    // A clean way to loop through a linked list
    for (nodeT* node = *head; node != NULL; node = node->next)
    {
        printNode(node);
    }
}

void printNode(nodeT* node)
{
    printf("Client Details\n");
    printf("Registration Number: %d\n", node->crn);
    // printf("Company Name: %s\n", node->name);
    // printf("Company Country: %s\n", node->country);
    // printf("Year Company Founded: %d\n", node->year);
    // printf("Email Address: %s\n", node->email);
    // printf("Company Contact Name: %s\n", node->contact);
    // printf("Last Order: %d\n", node->lastOrder);
    // printf("Number of Employees: %d\n", node->numEmployees);
    // printf("Average Annual Order: %d\n", node->avgOrder);
    printf("\n");
}

void readNode(nodeT* node)
{
    printf("Client Details\n");
    // printf("Company Name: ");
    // scanf("%s", node->name);
    // printf("Company Country: ");
    // scanf("%s", node->country);
    // printf("Year Company Founded: ");
    // scanf("%d", &node->year);
    // printf("Email Address: ");
    // scanf("%s", node->email);
    // printf("Company Contact Name: ");
    // scanf("%s", node->contact);
    // printf("Last Order: ");
    // scanf("%d", &node->lastOrder);
    // printf("Number of Employees: ");
    // scanf("%d", &node->numEmployees);
    // printf("Average Annual Order: ");
    // scanf("%d", &node->avgOrder);
    printf("\n");
}

void getPassword(char* password, int size)
{
    for (int i = 0; i < size; i++)
    {
        password[i] = getch();
        putch('*');
        // enter key finishes input
        if (password[i] == 13)
        {
            break;
        }
    };
}
