#ifndef CONTACT_H
#define CONTACT_H




#define MAX_COUNT   100
#define MAX_NAME_SIZE 30
#define MAX_MAIL_SIZE 40

typedef struct
{
    char name[MAX_NAME_SIZE];
    char number[11];
    char email[MAX_MAIL_SIZE];

}contact;

typedef struct
{
    contact contacts[MAX_COUNT];
    int contact_count;

}Addressbook;


int validate_name(char *name);
int validate_num(char *num);
int validate_mail(char *mail);
void intialize(Addressbook *addrbk);
void SaveandExit(Addressbook *addrbk);
int SearchContact(Addressbook *addrbk);
void createContact(Addressbook *addrbk);
void deleteContact(Addressbook *addrbk);
void editContact(Addressbook *addrbk);
void printContact(Addressbook *addrbk, int choice);


#endif