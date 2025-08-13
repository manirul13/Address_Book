#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct
{
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct
{
    Contact contacts[100];
    int contactCount;
} AddressBook;

void listContacts(AddressBook *addressBook, int sortCriteria);
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void initialize(AddressBook *addressBook);

#endif
