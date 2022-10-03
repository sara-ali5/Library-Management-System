#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_book();
void delete_book();
int search_id(int, int);
void unsorted();
void sorted();
int search_name(char*, int, int);

struct book {
 int id;
 char name[100];
 int quantity;
};

struct book library[100]; //array of struct
int no_books = 3; //number of books
int i = 0; //counter
FILE* fptr;
char ch;
int searchtest;

int main()
{

    do
    {
        fptr = fopen("library.txt", "a+");
        if (fptr == NULL)
            printf("File cannot be opened\n");
        else
        {
            int cntr = 0;
            while (cntr < 3)
            {
                fscanf(fptr, "%d%d ", &library[cntr].id, &library[cntr].quantity);
                fscanf(fptr, "%[^\n]%*c", library[cntr].name);
                cntr++;
            }
            fclose(fptr);

            int num;
            int s_id, position; //position of id that user searches for it
            char s_name[21];

            //prompt message
            printf("Hey! This is a library of some books , you can do operations on them:\n\n");
            printf("1-Insert a book (id, quantity, name)\n");
            printf("2-Delete a book by id\n");
            printf("3-Search a book by id and display its name and quantity\n");
            printf("4-Search a book by name and display its id and quantity\n");
            printf("5-Display all books sorted by name, and their corresponding ids and quantity\n");
            printf("6-Display all books unsorted, their ids, quantity and name (as entered)\n");
            printf("Choose an operation by entering its number:");

            scanf("%d", &num);

            switch (num)
            {
                while (ch=='y' || ch=='Y')
                    {
                        case 1:
                            insert_book();
                            break;

                        case 2:
                            delete_book();
                            break;

                        case 3:
                            printf("Enter id:");
                            scanf("%d",&s_id);
                            getchar();
                            position = search_id(s_id, 0);
                            if (position == 0)
                                printf("Not found\n");
                            else
                            {
                                printf("position is %d \n", position);
                                printf("Name of book you've searched is: %s \n",
                                       library[position - 1].name);
                                printf("Quantity of book you've searched is: %d \n",
                                       library[position - 1].quantity);
                            }
                            break;

                        case 4:
                            printf("Enter name:");
                            scanf(" %[^\n]%*c", s_name);
                            sorted();
                            searchtest = search_name(s_name, 0, no_books );
                            if (searchtest == -1)
                                printf("Not found");
                            else
                            {
                                printf("ID of book you've searched is: %d \n",
                                       library[searchtest].id);
                                printf("Quantity of book you've searched is: %d \n",
                                       library[searchtest].quantity);
                            }
                            break;

                        case 5:
                            sorted();
                            for (i = 0; i < no_books; i++)
                            {
                                printf("%d\t%d\t%s\n", library[i].id, library[i].quantity,
                                       library[i].name);
                            }
                            break;

                        case 6:
                            unsorted();
                            break;
                    }
                }
            }

        printf("enter 'y' or 'Y' to do another operation: ") ;
        scanf(" %c",&ch) ;
    }

    while (ch=='y' || ch=='Y');

    return 0;
}

void insert_book()
{
    printf("Enter id:");
    scanf("%d", &library[no_books].id);
    printf("Enter quantity:");
    scanf("%d", &library[no_books].quantity);
    printf("Enter name:");
    scanf(" %[^\n]%*c", library[no_books].name);
    fptr = fopen("library.txt", "a");
    if (fptr != NULL)
    {
        fseek(fptr, 0, SEEK_END);
        fprintf(fptr,"\n%d\t%d\t%s", library[no_books].id, library[no_books].quantity,
                library[no_books].name);
        printf("the book is inserted\n");
        no_books++;
    }
    else
        printf("File cannot be opened\n");
    fclose(fptr);
}

void delete_book()
{
    int del_id, j;
    fptr = fopen("library.txt", "w+");
    printf("Enter id:");
    scanf("%d", &del_id);
    for (i = 0; i < no_books; i++)
    {
        if (library[i].id == del_id)
        {
            /* locate the position of j in the array */
            printf("the book is deleted \n");
            j = 0;
            while (j != i)
                j++;
            /* the position of j in the array will be replaced by the value to its right */ while (j < no_books)
            {
                library[j] = library[j + 1];
                j++;
            }
            no_books--;
            for (int x = 0; x < no_books; x++)
                fprintf(fptr, "%d\t%d\t%s\n", library[x].id, library[x].quantity, library[x].name);
            fclose(fptr);
        }
    }
}

int search_id(int ID, int index)
{
    int pos = 0;
    if (index >= no_books)
        return 0;
    if (library[index].id == ID)
    {
        pos = index + 1;
        return pos;
    }
    else
        search_id(ID, index + 1);
}

int search_name(char* s_name, int low, int high)
{
    int middle;
    while (low <= high)
    {
        middle = (low + high) / 2;
        if (strcmp(s_name, library[middle].name) == 0)
        {
            return middle;
        }
        else if (strcmp(s_name, library[middle].name) < 0)
            high = middle - 1;
        else
            low = middle + 1;
    }
    return -1;
}

void sorted()
{
    int pass;
    char temp[21];
    int tmp_id, tmp_quantity;
    for (pass = 1; pass < no_books; pass++)
    {
        for (i = 0; i < no_books - pass; i++)
        {
            if (strcmp(library[i].name, library[i + 1].name) > 0)
            {
                strcpy(temp, library[i].name);
                strcpy(library[i].name, library[i + 1].name);
                strcpy(library[i + 1].name, temp);
                tmp_id = library[i].id;
                library[i].id = library[i + 1].id;
                library[i + 1].id = tmp_id;
                tmp_quantity = library[i].quantity;
                library[i].quantity = library[i + 1].quantity;
                library[i + 1].quantity = tmp_quantity;
            }
        }
    }
}

void unsorted()
{
    i = 0;
    fptr = fopen("library.txt", "r");
    if (fptr != NULL)
    {
        while (i < no_books)
        {
            printf("%d\t%d\t%s\n", library[i].id, library[i].quantity, library[i].name);
            i++;
        }
    }
    fclose(fptr);
}

