#include "stdio.h"
#include "file.h"
#include "contact.h"


int main()
{
    int choice;
    Addressbook addrbk;
    intialize(&addrbk);

    do{
        printf("\n------------------------------------\n");
        printf("         CONTACT BOOK MENU  \n");
        printf("------------------------------------\n");

        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. print all contacts\n");
    	  printf("6. Save contacts\n");		
        printf("7. Exit\n------------------------------------");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: 
                  createContact(&addrbk);
                  break;
            case 2:
                  SearchContact(&addrbk);
                  break;
            case 3:
                  editContact(&addrbk);
                  break;
            case 4:
                  deleteContact(&addrbk);
                  break;
            case 5: 
                  int sort;
                  printf("\nCONTACTS\n-----------\nSort by: \n1. Name\n2. Phone\n3. Email\n4. Default sort\nEnter your choice: ");
                  scanf("%d", &sort);
                  printContact(&addrbk, sort);
                  break;
            case 6:
                  SaveandExit(&addrbk);
                  break;
            default:
                  printf("Ivalid Choise\n Returning to Menu");
        }
    }while(choice != 7);

}