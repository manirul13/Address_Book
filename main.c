#include <stdio.h>
#include "contact.h"
#include "file.h"
#include "populate.h"


int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook);

    do {
        //Menu fro Addressbook
        printf("\n📒Address Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook, 0);  // Ensure sortCriteria is defined as 0
                break;
            case 6:
                printf("Saving contacts and exiting...\n");
                saveContactsToFile(&addressBook);   // Call the save function before exit

                break;
            default:
                printf("⚠ Invalid choice!!! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
