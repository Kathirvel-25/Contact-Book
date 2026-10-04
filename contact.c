#include "contact.h"
#include "file.h"
#include "string.h"
#include "stdlib.h"
#include "file.h"
#include "stdio.h"
#include "ctype.h"


int validate_name(char *name)
{
    if (!(name[0] >= 'A' && name[0] <= 'Z')) return 0;

    for(int i = 1; name[i] != '\0'; i++)
    {
        if(!((name[i] >= 'a' && name[i] <= 'z') || name[i] == ' ')) return 0;
    }

    return 1;
}

int validate_num(char *num)
{

    int i = 0;
    
    for(i = 0; num[i] != '\0'; i++)
    {
        if(!(num[i] >= '0' && num[i] <= '9')) return 0;

        if(i >= 10) return 0;
    }

    if(i != 10) return 0;

    return 1;
}


int validate_mail(char *mail)
{
     int at_pos = -1;
     int dot_pos = -1;

     for(int i = 0; mail[i] != 0; i++)
     {

        if(mail[i] == '@')
        {
            if(at_pos != -1) return 0;

            at_pos = i;
        }

        if(mail[i] == '.') dot_pos = i;
     }

     if(at_pos == 0 || dot_pos == at_pos + 1) return 0;

     if(dot_pos == -1 || at_pos == -1 || dot_pos < at_pos || at_pos+6 != dot_pos) return 0;

     int len = 0;

     while(mail[len] != '\0') len++;

     if(len < 5) return 0;

     if(mail[len-1] != 'm' || mail[len-2] != 'o' || mail[len-3] != 'c' || mail[len-4] != '.') return 0;

     for(int i = 0; mail[i] != '\0'; i++)
     {
        if(!(mail[i] >= 'a' && mail[i] <= 'z' || mail[i] >= 'A' && mail[i] <= 'Z' ||
             mail[i] == '.' || mail[i] == '_' || mail[i] == '-' || mail[i] == '+' || mail[i] == '@')) 
        {
                return 0;
        }
     }

     return 1;
}

void intialize(Addressbook *addrbk)
{
    addrbk->contact_count = 0;

    LoadFromFile(addrbk);
}


void SaveandExit(Addressbook *addrbk)
{
    SaveToFile(addrbk);

    exit(EXIT_SUCCESS);
}


void createContact(Addressbook *addrbk)
{
    printf("\n.............Create Conatct..............\n");
    printf("Enter the details: \n");
    char name[MAX_NAME_SIZE], number[11], email[MAX_MAIL_SIZE];
    int choice;

    do
    {
        printf("Enter the Name:");
        scanf(" %[^\n]",name);
        printf("Enter the Phone Number:");
        scanf(" %[^\n]",number);
        printf("Enter the Email:");
        scanf(" %[^\n]",email);

        if(validate_name(name) && validate_num(number) && validate_mail(email))
        {
            strcpy(addrbk->contacts[addrbk->contact_count].name, name);
            strcpy(addrbk->contacts[addrbk->contact_count].number, number);
            strcpy(addrbk->contacts[addrbk->contact_count].email, email);
            addrbk->contact_count++;

            printf("\nContact added Successfully\n");
            printf("1.Add Another Contact\n");
            printf("2.Exit\n");
            printf("Enter Your choice: ");
            scanf("%d",&choice);
        }
        else
        {
            printf("ivalid data...\n");
            return;
        }
    }while(choice != 2);
}

int SearchContact(Addressbook *addrbk)
{
    printf("\n............Search Contact...........\n1. Name\n2. Phone Number\n3. Email\n4. Back to manu\n");
    printf("Enter Choice: ");
    int choice;
    scanf(" %d", &choice);

    if(choice == 1)
    {
        printf("Enter the Name:");
        char name[MAX_NAME_SIZE];
        scanf(" %[^\n]", name);
        for(int i = 0; i < addrbk->contact_count; i++)
        {
            int cmp = strcmp(addrbk->contacts[i].name,name);
            if(cmp == 0)
            {
                printf("Contact found at the index: %d\n", i);
                printf("Name: %s\n", addrbk->contacts[i].name);
                printf("Phone Number: %s\n", addrbk->contacts[i].number);
                printf("Email id: %s\n", addrbk->contacts[i].email);
                return 1;
            }
        }
        printf("\n No result found!\n");
    }

    else if(choice  == 2)
    {
        printf("Enter the Phone Number:");
        char num[11];
        scanf(" %[^\n]", num);
        for(int i = 0; i < addrbk->contact_count; i++)
        {
            int cmp = strcmp(addrbk->contacts[i].number, num);
            if(cmp == 0)
            {
                printf("Contact found at the index: %d\n", i);
                printf("Name: %s\n", addrbk->contacts[i].name);
                printf("Phone Number: %s\n", addrbk->contacts[i].number);
                printf("Email id: %s\n", addrbk->contacts[i].email);
                return 1;
            }
        }
        printf("\n No result found!\n");
    }

    else if(choice == 3)
    {
        printf("Enter the Email id:");
        char mail[MAX_MAIL_SIZE];
        scanf(" %[^\n]", mail);

        for(int i = 0; i < addrbk->contact_count; i++)
        {
            int cmp = strcmp(addrbk->contacts[i].email, mail);
            if(cmp == 0)
            {
                printf("Contact found at the index: %d\n", i);
                printf("Name: %s\n", addrbk->contacts[i].name);
                printf("Phone Number: %s\n", addrbk->contacts[i].number);
                printf("Email id: %s\n", addrbk->contacts[i].email);
                return 1;
            }
        }
        printf("\n No result found!\n");
    }

    else if(choice == 4)
    {
        printf("Exit is pressed\n");
        return 4;
    }

    else
    {
        printf("Inavlid Chioce\n");
        return 0;
    }
    return 0;
}

void deleteContact(Addressbook *addrbk)
{

    printf("\n .................DELETE CONTACT.............. \n");
    int find = SearchContact(addrbk);

    if(find != 1)
    {
        printf("Contact not Found");
        return;
    }

    printf("Enter the Index of the Contact: ");
    int idx;
    scanf("%d", &idx);

    for(int i = idx; i < addrbk->contact_count-1; i++)
    {
        strcpy(addrbk->contacts[i].name, addrbk->contacts[i+1].name);
        strcpy(addrbk->contacts[i].number, addrbk->contacts[i+1].number);
        strcpy(addrbk->contacts[i].email, addrbk->contacts[i+1].email);
    }
    addrbk->contact_count--;
    printf("Contact Successfully deleted\n");

}


void editContact(Addressbook *addrbk)
{

    printf("\n ..............EDIT CONTACT...............\n");

    int cmp = SearchContact(addrbk);

    if(cmp != 1) return;

    if(cmp == 1)
    {
        printf("Enter the Index Number:");
        int idx;
        scanf("%d", &idx);

        printf("\n EDIT....\n1.Name \n2.Number \n3.Mail \nEnter the Choice:");
        int choice;
        scanf("%d", &choice);

        if(choice == 1)
        {
            char name[MAX_NAME_SIZE];
            printf("Enter the Name:");
            scanf(" %[^\n]", name);
            int vali = validate_name(name);
            if(vali == 1)
            {
                strcpy(addrbk->contacts[idx].name, name);
                printf("Updated Successfully...\n");
            }
            else printf("Ivalid name\n");
        }

        else if(choice == 2)
        {
            char num[11];
            printf("Enter the Number:");
            scanf(" %[^\n]", num);
            int vali = validate_num(num);
            if(vali == 1)
            {
                strcpy(addrbk->contacts[idx].number, num);
                printf("Updated Successfully...\n");
            }
            else printf("Ivalid name\n");
        }

        else if(choice == 3)
        {
            char mail[MAX_MAIL_SIZE];
            printf("Enter the Mail:");
            scanf(" %[^\n]", mail);
            int vali = validate_mail(mail);
            if(vali == 1)
            {
                strcpy(addrbk->contacts[idx].email, mail);
                printf("Updated Successfully...\n");
            }
            else printf("Ivalid name\n");
        }

        else 
        {
            printf("Ivalid Choice");
        }

    }
}

void printContact(Addressbook *addrbk, int choice)
{

    printf("\n ..............PRINT CONTACT...............\n");

    contact temp;

    if(choice == 1)
    {
        printf("\nSorting by the Name\n");
        for(int i = 0; i < (addrbk->contact_count)-1; i++)
        {
            for(int j = 0; j < (addrbk->contact_count)-1-i; j++)
            {
                if(strcasecmp(addrbk->contacts[j].name, addrbk->contacts[i].name))
                {
                    temp = addrbk->contacts[j];
                    addrbk->contacts[j] = addrbk->contacts[i];
                    addrbk->contacts[i] = temp;
                }
            }
        }

        for(int i = 0; i < addrbk->contact_count; i++)
        {
            printf("%-30s %-30s %-30s\n", addrbk->contacts[i].name, addrbk->contacts[i].number, addrbk->contacts[i].email);
        }
    }

    else if(choice == 3)
    {
        printf("Sorting by the Number\n");
        for(int i = 0; i < (addrbk->contact_count)-1; i++)
        {
            for(int j = 0; j < (addrbk->contact_count)-1-i; j++)
            {
                if(strcasecmp(addrbk->contacts[j].number, addrbk->contacts[i].number))
                {
                    temp = addrbk->contacts[j];
                    addrbk->contacts[j] = addrbk->contacts[i];
                    addrbk->contacts[i] = temp;
                }
            }
        }

        for(int i = 0; i < addrbk->contact_count; i++)
        {
            printf("%-30s %-30s %-30s\n", addrbk->contacts[i].name, addrbk->contacts[i].number, addrbk->contacts[i].email);
        }
    }

    else if(choice == 3)
    {
        printf("Sorting by the mail\n");
        for(int i = 0; i < (addrbk->contact_count)-1; i++)
        {
            for(int j = 0; j < (addrbk->contact_count)-1-i; j++)
            {
                if(strcasecmp(addrbk->contacts[j].email, addrbk->contacts[i].email))
                {
                    temp = addrbk->contacts[j];
                    addrbk->contacts[j] = addrbk->contacts[i];
                    addrbk->contacts[i] = temp;
                }
            }
        }

        for(int i = 0; i < addrbk->contact_count; i++)
        {
            printf("%-30s %-30s %-30s\n", addrbk->contacts[i].name, addrbk->contacts[i].number, addrbk->contacts[i].email);
        }
    }

    else if(choice == 4)
    {
        for(int i = 0; i < addrbk->contact_count; i++)
        {
            printf("%-30s %-30s %-30s\n", addrbk->contacts[i].name, addrbk->contacts[i].number, addrbk->contacts[i].email);
        }
    }
}