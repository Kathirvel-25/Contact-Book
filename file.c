#include "file.h"



void SaveToFile(Addressbook *addrbk)
{
    FILE *fptr = fopen("contact.csv", "w");

    if(fptr == NULL)
    {
        printf("File Doesnt Exit");
        return;
    }

    fprintf(fptr, "%d\n", addrbk->contact_count);

    for(int i = 0; i < addrbk->contact_count; i++)
    {
        fprintf(fptr, "%s,%s,%s\n", addrbk->contacts[i].name, addrbk->contacts[i].number, addrbk->contacts[i].email);
    }

    fclose(fptr);
}


void LoadFromFile(Addressbook *addrbk)
{
    FILE *fptr = fopen("contact.csv", "r");

    if(fptr == NULL)
    {
        printf("File doesnt Exit");
        return;
    }
    fscanf(fptr, "%d", &addrbk->contact_count);

    for(int i = 0; i < addrbk->contact_count; i++)
    {
        fseek(fptr, 1, SEEK_CUR);
        fscanf(fptr, " %[^,]", addrbk->contacts[i].name);
        fseek(fptr, 1, SEEK_CUR);
        fscanf(fptr, " %[^,]", addrbk->contacts[i].number);
        fseek(fptr, 1, SEEK_CUR);
        fscanf(fptr, " %[^,]\n", addrbk->contacts[i].email);
    }

    fclose(fptr);
}