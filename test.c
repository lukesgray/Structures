#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sPerson
{
    int age;
    struct sPerson *nextInLine;
    struct sPerson *nextInLine2;
};

struct sPerson *getNewPerson(const int age);
// struct sPerson *getNewPerson2(const int age);
void printPerson(const struct sPerson *person, const char *comment);
void printList(const struct sPerson *list);
void CleanUp(struct sPerson *list);
struct sPerson *findMatch(struct sPerson *list, int age);

int main(int argc, char *argv[])
{
    // create pointers of type 'struct sPerson' and initialize them to NULL
    struct sPerson *first = NULL;
    struct sPerson *added = NULL;

    char command[64];
    int age;
    int insert_person;

    while (1)
    {
        printf("Enter a command or value: ");
        fgets(command, 64, stdin);
        if (strcmp("q\n", command) == 0)
        {
            printf("Quitting...\n");
            break;
        }
        else if (strcmp("print\n", command) == 0)
        {
            printf("Printing...\n");
            printList(first);
        }
        else if (sscanf(command, "%d", &age) != 0)
        {
            printf("Adding %d\n", age);
            if (first == NULL)
            {
                first = getNewPerson(age);
                if (first != NULL)
                {
                    added = first;
                }
            }
            else
            {
                (*added).nextInLine = getNewPerson(age);
                if ((*added).nextInLine != NULL)
                {
                    added = (*added).nextInLine;
                }
            }
        }
        else if (strcmp("insert\n", command) == 0)
        {
            printf("Adding %d\n", age);
            if (first == NULL)
            {
                printf("Enter new person:\n");
                scanf("%d", &age);
                first = getNewPerson(age);
                if (first != NULL)
                {
                    added = first;
                }
            }
            else
            {
                printf("Enter person who you would like to insert after:\n");
                fgets(command, 64, stdin);
                sscanf(command, "%d", &insert_person);

                printf("Enter new person:\n");
                fgets(command, 64, stdin);
                sscanf(command, "%d", &age);

                struct sPerson *matched_person = NULL;
                // function with age and pointer to struct as parameters and pointer to matching person as return value
                matched_person = findMatch(first, insert_person);

                if (matched_person)
                {
                    struct sPerson *utility_person = NULL;
                    utility_person = getNewPerson(age);
                    (*utility_person).nextInLine = (*matched_person).nextInLine;
                    (*matched_person).nextInLine = utility_person;
                }
                else
                {
                    printf("No match found");
                }
            }
        }
    }

    CleanUp(first);
    first = NULL;
    added = NULL;

    return 0;
};

struct sPerson *findMatch(struct sPerson *list, int age)
{
    struct sPerson *next;
    while ((*list).age != age)
    {
        list = (*list).nextInLine;
    }
    if (list == NULL)
    {
        return NULL;
    }
    else
    {
        return list;
    }
}

struct sPerson *getNewPerson(const int age)
{
    struct sPerson *newPerson = NULL;
    newPerson = malloc(sizeof(struct sPerson));
    if (newPerson != NULL)
    {
        (*newPerson).nextInLine = NULL;
        (*newPerson).age = age;
        printf("created new person at%p\n", newPerson);
    }
    else
    {
        printf("Allocation Failure!! \n");
    }

    return newPerson;
}

// struct sPerson *getNewPerson2(const int age)
// {
//     struct sPerson *newPerson = NULL;
//     newPerson = malloc(sizeof(struct sPerson));
//     if (newPerson != NULL)
//     {
//         (*newPerson).nextInLine2 = NULL;
//         (*newPerson).age = age;
//         printf("created new person at%p\n", newPerson);
//     }
//     else
//     {
//         printf("Allocation Failure!! \n");
//     }

//     return newPerson;
// }

void printPerson(const struct sPerson *person, const char *comment)
{
    if (person == NULL)
    {
        printf("%s is NULL\n", comment);
    }
    else
    {
        printf("%s: age:%d address:%p nextInLine:%p\n", comment, (*person).age, person, (*person).nextInLine);
    }
}

void printList(const struct sPerson *list)
{
    printf("Printing List:\n");
    const struct sPerson *t;
    t = list;
    if (t == NULL)
    {
        printf("list is empty\n");
    }
    else
    {
        while (t)
        {
            printPerson(t, "t");
            t = (*t).nextInLine;
        }
    }
}

void CleanUp(struct sPerson *list)
{
    struct sPerson *next;
    while (list)
    {
        next = (*list).nextInLine;
        printf("Cleaning %d\n", (*list).age);
        free(list);
        list = next;
    }
}