// TODO Remove clang stuff below
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#include <conio.h>
#include <stdbool.h>  // bools in c int would work too
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

enum TurnOver
{
    LessThan1Mil,
    LessThan10Mil,
    Over10Mil,
};

enum Employes
{
    LessThan10,
    LessThan100,
    Over100,
};

enum AreaOfSales
{
    ICT,
    Medical,
    Other,
};

// Linked list node
typedef struct Node
{
    int crn;  // Company Registration Number (Assume an integer – must be unique)
    // char name[50];     // Company Name
    // char country[50];  // Company Country
    // int year;          // Year Company Founded
    // char email[50];    // Email Address (must contain an @, a full stop and a .com)
    // char contact[50];  // Company Contact Name
    // int lastOrder;     // Last Order
    // int numEmployees;  // Number of Employees
    // int avgOrder;      // Average Annual Order

    bool vatRegistered;          // Is the Client Vat Registered?
    enum TurnOver turnover;      // What are the Clients Average Turnover?
    enum Employes employees;     // How many staff are employed in the Client Company?
    enum AreaOfSales salesArea;  // Which area of sales is the company?

    struct Node* next;  // Next node
} NodeT;

// Linked list node
typedef struct LoginNode
{
    char username[50];       // Username
    char password[50];       // Password
    struct LoginNode* next;  // Next node
} LoginNodeT;

bool addNode(NodeT** head, int crn);
bool removeNode(NodeT** head, int crn);
bool updateNode(NodeT** head, int crn);
bool displayNode(NodeT** head, int crn);
bool deleteNode(NodeT** head, int crn);

void generateStatistics(NodeT** head);
void listClients(NodeT** head);

void writeFile(NodeT** head);
void readFile(NodeT** head);

void printNode(NodeT* node);
void readNode(NodeT* node);

void displayAll(NodeT** head);
void getPassword(char* password, int size);

// Menu and option handling
int main()
{
    LoginNodeT* login = NULL;

    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    getPassword(password, 50);

    FILE* logins = fopen("logins.txt", "r");

    LoginNodeT* user = NULL;
    while (!feof(logins))
    {
        LoginNodeT* newNode = (LoginNodeT*)malloc(sizeof(LoginNodeT));
        fscanf(logins, "%s %s\n", newNode->username, newNode->password);
        newNode->next = NULL;

        if (login == NULL)
        {
            login = newNode;
            user = login;
        }
        else
        {
            user->next = newNode;
        }
        user = newNode;
    }

    bool isValidPassword = false;
    printf("%s\n", password);
    printf("%s\n", username);

    // It would make more sense to have checked it when
    // reading it in instead of using a linked list but cant argu with the requirements
    for (LoginNodeT* node = login; node != NULL; node = node->next)
    {
        printf("\n");
        printf("%s\n", node->username);
        printf("%s\n", node->password);
        printf("%d\n", strcmp(node->username, username));
        printf("%d\n", strcmp(node->password, password));
        if (strcmp(node->username, username) == 0 && strcmp(node->password, password) == 0)
        {
            isValidPassword = true;
            printf("Access granted\n");
            break;
        }
    }

    NodeT* head = NULL;
    readFile(&head);

    int choice;

    while (isValidPassword)
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

        int crn;

        switch (choice)
        {
            case 1:
            {
                printf("Enter the client's registration number: ");
                scanf("%d", &crn);
                if (addNode(&head, crn))
                {
                    printf("\nClient added successfully\n\n");
                }
                else
                {
                    printf("\nClient already exists\n\n");
                }
            }
            break;

            case 2:
            {
                displayAll(&head);
            }
            break;

            case 3:
            {
                printf("Enter the client's registration number: ");
                scanf("%d", &crn);
                if (!displayNode(&head, crn))
                {
                    printf("\nClient not found\n\n");
                }
            }
            break;

            case 4:
            {
                printf("Enter the client's registration number: ");
                scanf("%d", &crn);
                if (!updateNode(&head, crn))
                {
                    printf("\nClient not found\n\n");
                }
            }
            break;

            case 5:
            {
                printf("Enter the client's registration number: ");
                scanf("%d", &crn);
                if (!deleteNode(&head, crn))
                {
                    printf("\nClient not found\n\n");
                }
            }
            break;

            case 6:
            {
                generateStatistics(&head);
            }
            break;

            case 7:
            {
                writeFile(&head);
            }
            break;

            case 8:
            {
                listClients(&head);
            }
            break;

            default:
            {
                writeFile(&head);
                printf("Exiting\n");
                exit(0);
            }
            break;
        }
    }

    return 0;
}

// Add a node to the list returning true if the node was added
bool addNode(NodeT** head, int crn)
{
    // Add the first node
    if ((*head) == NULL)
    {
        (*head) = (NodeT*)malloc(sizeof(NodeT));
        readNode(*head);
        (*head)->crn = crn;
        (*head)->next = NULL;
        return true;
    }
    else
    {
        // A clean way to loop through a linked list
        for (NodeT* node = *head; node != NULL; node = node->next)
        {
            if (node->crn == crn)
            {
                return false;
            }

            if (node->next == NULL)
            {
                NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));
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

// Update a node returning true if the node was found
bool updateNode(NodeT** head, int crn)
{
    for (NodeT* node = *head; node != NULL; node = node->next)
    {
        if (node->crn == crn)
        {
            readNode(node);
            return true;
        }
    }
    return false;
}

// Print statistics really vaguely written in the document
void generateStatistics(NodeT** head)
{
    printf("Generate Statistics based on:\n");
    printf("(0 = Area of Company Sales, 1 = Number of Employees)\n");

    int option;
    printf("Enter your choice: ");
    scanf("%d", &option);

    printf("\n");

    int count[9] = {0};  // Initialize all to zero

    for (NodeT* node = *head; node != NULL; node = node->next)
    {
        if (option == 0)  // Area of Company Sales
        {
            count[(node->turnover * 3) + node->salesArea]++;
        }
        else
        {
            count[(node->turnover * 3) + node->employees]++;
        }
    }

    if (option == 0)  // Area of Company Sales
    {
        printf("ICT:\n");
        printf("    Less than 1 Million: %d\n", count[0]);
        printf("    Less than 10 Million: %d\n", count[1]);
        printf("    Over 10 Million: %d\n", count[2]);

        printf("Medical:\n");
        printf("    Less than 1 Million: %d\n", count[3]);
        printf("    Less than 10 Million: %d\n", count[4]);
        printf("    Over 10 Million: %d\n", count[5]);

        printf("Other:\n");
        printf("    Less than 1 Million: %d\n", count[6]);
        printf("    Less than 10 Million: %d\n", count[7]);
        printf("    Over 10 Million: %d\n", count[8]);
    }
    else
    {
        printf("LessThan10:\n");
        printf("    Less than 1 Million: %d\n", count[0]);
        printf("    Less than 10 Million: %d\n", count[1]);
        printf("    Over 10 Million: %d\n", count[2]);

        printf("LessThan100:\n");
        printf("    Less than 1 Million: %d\n", count[3]);
        printf("    Less than 10 Million: %d\n", count[4]);
        printf("    Over 10 Million: %d\n", count[5]);

        printf("Over100:\n");
        printf("    Less than 1 Million: %d\n", count[6]);
        printf("    Less than 10 Million: %d\n", count[7]);
        printf("    Over 10 Million: %d\n", count[8]);
    }
    printf("\n");
}

// Display a node with crn if its found otherwise return false
bool displayNode(NodeT** head, int crn)
{
    for (NodeT* node = *head; node != NULL; node = node->next)
    {
        if (node->crn == crn)
        {
            printNode(node);
            return true;
        }
    }

    return false;
}

// Write the linked list to clients.txt
void writeFile(NodeT** head)
{
    FILE* file = fopen("clients.txt", "w");
    for (int option = 0; option < 2; option++)
    {
        int count[9] = {0};  // Initialize all to zero

        for (NodeT* node = *head; node != NULL; node = node->next)
        {
            if (option == 0)  // Area of Company Sales
            {
                count[(node->turnover * 3) + node->salesArea]++;
            }
            else
            {
                count[(node->turnover * 3) + node->employees]++;
            }
        }

        for (int j = 0; j < 9; j++)
        {
            fprintf(file, "%d\n", count[j]);
        }
    }

    for (NodeT* node = *head; node != NULL; node = node->next)
    {
        fprintf(file, "%d\n", node->crn);
        // fprintf(file, "%s\n", node->name);
        // fprintf(file, "%s\n", node->country);
        // fprintf(file, "%d\n", node->year);
        // fprintf(file, "%s\n", node->email);
        // fprintf(file, "%s\n", node->contact);
        // fprintf(file, "%d\n", node->lastOrder);
        // fprintf(file, "%d\n", node->numEmployees);
        // fprintf(file, "%d\n", node->avgOrder);
        // fprintf(file, "%d\n", node->avgOrder);

        fprintf(file, "%d\n", node->vatRegistered);
        fprintf(file, "%d\n", node->turnover);
        fprintf(file, "%d\n", node->employees);
        fprintf(file, "%d\n", node->salesArea);
        fprintf(file, "\n");
    }

    printf("\n");

    fclose(file);

    printf("\nFile written successfully\n\n");
}

// Read in a password
void getPassword(char* password, int size)
{
    for (int i = 0; i < size; i++)
    {
        int c = getch();

        // enter key finishes input
        if (c == 13)
        {
            break;
        }
        else
        {
            password[i] = c;
            putch('*');
        }
    }

    printf("\n");
}

// Read in the clients.txt file and add the nodes to the list
void readFile(NodeT** head)
{
    struct stat buffer;
    if (stat("clients.txt", &buffer) == 0)
    {
        FILE* file = fopen("clients.txt", "r");
        NodeT* node = *head;

        for (int i = 0; i < 18; i++)
        {
            int throwAway;
            fscanf(file, "%d", &throwAway);
        }

        while (true)
        {
            NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));

            fscanf(file, "%d", &newNode->crn);
            // fscanf(file, "%s\n", newNode->name);
            // fscanf(file, "%s\n", newNode->country);
            // fscanf(file, "%d\n", &newNode->year);
            // fscanf(file, "%s\n", newNode->email);
            // fscanf(file, "%s\n", newNode->contact);
            // fscanf(file, "%d\n", &newNode->lastOrder);
            // fscanf(file, "%d\n", &newNode->numEmployees);
            // fscanf(file, "%d\n", &newNode->avgOrder);

            int temp;
            fscanf(file, "%d", &temp);
            newNode->vatRegistered = temp;
            fscanf(file, "%d", &newNode->turnover);
            fscanf(file, "%d", &newNode->employees);
            fscanf(file, "%d", &newNode->salesArea);
            newNode->next = NULL;

            if (node == NULL)
            {
                (*head) = newNode;
            }
            else
            {
                node->next = newNode;
            }
            node = newNode;

            fscanf(file, "\n");

            if (feof(file))
            {
                break;
            }
        }

        fclose(file);
    }
}

// Lists clients ordered by turnover
void listClients(NodeT** head)
{
    for (int i = 0; i < 3; i++)
    {
        for (NodeT* node = *head; node != NULL; node = node->next)
        {
            if (node->turnover == i)
            {
                printNode(node);
            }
        }
    }
}

// Prints out all nodes in linked list
void displayAll(NodeT** head)
{
    for (NodeT* node = *head; node != NULL; node = node->next)
    {
        printNode(node);
    }
}

// Deletes node from linked list with crn
bool deleteNode(NodeT** head, int crn)
{
    NodeT* prev = NULL;
    for (NodeT* node = *head; node != NULL; node = node->next)
    {
        // is the node the first node
        if (node->crn == crn)
        {
            if ((*head)->crn == crn)
            {
                NodeT* temp = *head;
                (*head) = (*head)->next;
                free(temp);
            }
            else
            {
                //   0  |   1  |   2
                // prev | node | temp
                NodeT* temp = node->next;
                free(node);
                prev->next = temp;
            }
            return true;
        }
        prev = node;
    }
    return false;
}

// Stream lets me reuse the same function for console and file output
void printNode(NodeT* node)
{
    printf("\n");
    printf("Registration Number: %d\n", node->crn);
    // printf("Company Name: %s\n", node->name);
    // printf("Company Country: %s\n", node->country);
    // printf("Year Company Founded: %d\n", node->year);
    // printf("Email Address: %s\n", node->email);
    // printf("Company Contact Name: %s\n", node->contact);
    // printf("Last Order: %d\n", node->lastOrder);
    // printf("Number of Employees: %d\n", node->numEmployees);
    // printf("Average Annual Order: %d\n", node->avgOrder);

    printf("Vat Registered:%d\n", node->vatRegistered);
    printf("Turnover:%d\n", node->turnover);
    printf("Employed:%d\n", node->employees);
    printf("Salesarea:%d\n", node->salesArea);
    printf("\n");
}

// Reads in a client from the console
void readNode(NodeT* node)
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

    printf("Is Vat Registered (0 or 1): ");
    int temp;
    scanf("%d", &temp);
    node->vatRegistered = temp;
    printf("Turnover: (Less than 1 Million, Less than 10 Million, Over 10 Million)");
    scanf("%d", &node->turnover);
    printf("Employed (Less than 10, Less than €100, Over 100)");
    scanf("%d", &node->employees);
    printf("Sales Area (ICT, Medical Devices, Other area)");
    scanf("%d", &node->salesArea);
    printf("\n");
}
