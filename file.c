#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

#define FILE_NAME "contacts.txt"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *file = fopen(FILE_NAME, "w");
    if (!file)
    {
        printf("Error saving contacts.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(file, "%s,%s,%s\n", addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(file);
    printf("Contacts saved to file.\n");
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *file = fopen(FILE_NAME, "r");
    if (!file)
    {
        return; // No file means no saved contacts yet
    }

    while (fscanf(file, "%49[^,],%19[^,],%49[^\n]\n",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) != EOF)
    {
        addressBook->contactCount++;
    }

    fclose(file);
    printf("Contacts loaded from file.\n");
}
