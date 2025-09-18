#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
int name_validation(char *name);
int phone_validation(char *phone);
int mail_validation(char *mail);
int search_by_name(AddressBook *,char *name);
int search_by_phone(AddressBook *,char *phone);
int search_by_mail(AddressBook *,char *mail);
int unique_phone(AddressBook *addressBook,char *phone);
#endif
