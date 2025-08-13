#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// Validate phone number should be 10 digits, no repeated will number allow
int isValidPhone(const char *phone, AddressBook *addressBook)
{
    //number length max or min 10 digit
    if (strlen(phone) != 10)
    {
        printf("Error: Phone number must be exactly 10 digits!\n");
        return 0;
    }
    //using loop for containing only digit , not any alphabet or special character
    for (int i = 0; i < 10; i++)
    {
        if (!isdigit(phone[i]))
        {
            printf("Error: Phone number must contain only digits!\n");
            return 0;
        }
    }
    
    // not allow repeated number
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            printf("Error: Phone number already exists!\n");
            return 0;
        }
    }

    return 1;
}

// Validate email must contain '@' and end with '.com' otherwise it will throw error
int isValidEmail(const char *email)
{
    return (strchr(email, '@') && strstr(email, ".com"));
}

void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Error: Address book is full!\n");
        return;
    }

    Contact newContact;
    printf("Enter Name: ");
    scanf(" %[^\n]", newContact.name);

    // Validate phone number to save new contact
    do
    {
        printf("Enter Phone (10 digits only): ");
        scanf(" %[^\n]", newContact.phone);
        if (!isValidPhone(newContact.phone, addressBook))
        {
            printf("Invalid phone number! Try again.\n");
        }
    } while (!isValidPhone(newContact.phone, addressBook));

    // Validate email id to save new contact
    do
    {
        printf("Enter Email: ");
        scanf(" %[^\n]", newContact.email);
        if (!isValidEmail(newContact.email))
        {
            printf("Invalid email! Must contain '@' and end with '.com'. Try again.\n");
        }
    } while (!isValidEmail(newContact.email));

    addressBook->contacts[addressBook->contactCount++] = newContact;
    printf("✅ Contact added successfully!\n");
}

// Search contact by Name, Phone, or Email
void searchContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available.\n");
        return;
    }

    int choice;
    char query[50];
    printf("\nSearch by:\n1. Name\n2. Phone\n3. Email\nEnter choice: ");
    scanf("%d", &choice);
    printf("Enter search term: ");
    scanf(" %[^\n]", query);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        int found = 0;

        if (choice == 1 && strcmp(addressBook->contacts[i].name, query) == 0)
        {
            found = 1;
        }
        else if (choice == 2 && strcmp(addressBook->contacts[i].phone, query) == 0)
        {
            found = 1;
        }
        else if (choice == 3 && strcmp(addressBook->contacts[i].email, query) == 0)
        {
            found = 1;
        }

        if (found)
        {
            printf("\n📞 Name:%s - Ph:%s - Mail:%s\n", addressBook->contacts[i].phone,
                   addressBook->contacts[i].name, addressBook->contacts[i].email);
            return;
        }
    }

    printf("⚠ Contact not found.\n");
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
    
    // Only populate dummy contacts if the file is empty
    if (addressBook->contactCount == 0) {
        populateAddressBook(addressBook);
    }
}

void listContacts(AddressBook *addressBook, int sortCriteria)
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts to display.\n");
        return;
    }

    printf("\n📋All Contacts:\n");
    printf("---------------------------------------------------------------\n");
    printf("S.No | %-20s | %-12s | %-25s\n", "Name", "Phone", "Email");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        //print the dummy contacts as well as user created contacts
        
        printf("%-5d| %-20s | %-12s | %-25s\n", i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
}

void editContact(AddressBook *addressBook)
{
    char phone[20];
    printf("Enter the phone number to edit the contact: ");
    scanf(" %[^\n]", phone);
    //for edit contact using for loop name, ph no. and mail id should be update
    
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            printf("Enter new name: ");
            scanf(" %[^\n]", addressBook->contacts[i].name);
            printf("Enter new email: ");
            scanf(" %[^\n]", addressBook->contacts[i].email);
            printf("Contact updated.\n");
            return;
        }
    }

    printf("Contact not found.\n");
}

void deleteContact(AddressBook *addressBook)
{
    char phone[20];
    printf("Enter the phone number to delete the contact: ");
    scanf(" %[^\n]", phone);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            for (int j = i; j < addressBook->contactCount - 1; j++)
            {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            addressBook->contactCount--;
            printf("Contact deleted.\n");
            return;
        }
    }

    printf("Contact not found.\n");
}