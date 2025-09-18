#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortChoice) 
{
    char temp1[30];
    char temp2[20]; 
    char temp3[50];

    for (int i = 0; i < addressBook->contactCount - 1; i++) 
    {
        for (int j = i + 1; j < addressBook->contactCount; j++) 
        {
            int compare = 0;

            if (sortChoice == 1)
                compare = strcmp(addressBook->contacts[i].name, addressBook->contacts[j].name);
            else if (sortChoice == 2)
                compare = strcmp(addressBook->contacts[i].phone, addressBook->contacts[j].phone);
            else if (sortChoice == 3)
                compare = strcmp(addressBook->contacts[i].email, addressBook->contacts[j].email);

            if (compare > 0) 
            {
                // Swap name
                strcpy(temp1, addressBook->contacts[i].name);
                strcpy(addressBook->contacts[i].name, addressBook->contacts[j].name);
                strcpy(addressBook->contacts[j].name, temp1);

                // Swap phone
                strcpy(temp2, addressBook->contacts[i].phone);
                strcpy(addressBook->contacts[i].phone, addressBook->contacts[j].phone);
                strcpy(addressBook->contacts[j].phone, temp2);

                // Swap email
                strcpy(temp3, addressBook->contacts[i].email);
                strcpy(addressBook->contacts[i].email, addressBook->contacts[j].email);
                strcpy(addressBook->contacts[j].email, temp3);
            }
        }
    }

    // Print the sorted contacts
    printf("\n--- Sorted Contact List ---\n");
    printf("----------------------------------------------------------------\n");
    printf("   Name\t\t       Phone number\t    email ID           |\n");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
    

    printf("%-17s|\t%-13s|\t%-23s|\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
       
    }
    printf("----------------------------------------------------------------\n");
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

    int res;
    char name[20];
    char phone[15];
    char mail[30];
   
    do
     {
        printf("Enter the name: ");
        scanf(" %[^\n]",name);

         int res = name_validation(name);
         
         if(res == 0)
         {
           printf("Invaild name! please Enter only alphabets and space\n");
         }
         else
         break;
     }while(res == 0);

    do
     {
        printf("Enter the phone number: ");
        scanf(" %s",phone);

        res = phone_validation(phone) && unique_phone(addressBook,phone);
        
        if(res == 0)
        {
            printf("Invaild number! please Enter correct number\n");
        }

     }while(res == 0);
    

     do
     {
        printf("Enter the mail ID: ");
        scanf(" %s",mail);

        res = mail_validation(mail);
        if(res == 0)
        {
            printf("Invaild mail ID! please Enter correct mail ID\n");
        }
     }while(res == 0);



    //storing the contacts in structure
     if(addressBook -> contactCount < 100)
     {
     strcpy(addressBook->contacts[addressBook->contactCount].name,name);
     strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
     strcpy(addressBook->contacts[addressBook->contactCount].email,mail);

     addressBook -> contactCount++;
     printf("Contact added successfully!\n");

     }

     else
     {
        printf("AddressBook is full, cannot add more contact\n");
     }


}
    



void searchContact(AddressBook *addressBook) 
{
    int option;
    int found =0;
    char input[50];
    int index = -1;

    printf("\nSearch Contact By:\n");
    printf("1. Name\n2. Phone number\n3. Mail ID\nEnter your option: ");
    scanf("%d",&option);

    switch(option)
    {
        case 1:
        printf("Enter the Name: ");
        scanf(" %[^\n]",input);
        if(!name_validation(input))
        {
            printf("Invaild name!\n");
            return;
        }
        index = search_by_name(addressBook,input);
        break;


        case 2:
        printf("Enter the Phone number: ");
        scanf(" %s",input);
        if(!phone_validation(input))
        {
            printf("Invaild phone number!\n");
            return;
        }

        int unique= unique_phone(addressBook,input);
        index = search_by_phone(addressBook,input);
        break;

        case 3:
        printf("Enter the Mail ID: ");
        scanf(" %s",input);
        if(!mail_validation(input))
        {
            printf("Invaild mail ID!\n");
            return;
        }
        index = search_by_mail(addressBook,input);
        break;

        default:
        printf("Invalid option!\n");
        return;

    }
    if(index != -1) 
    {
        printf("\nContact Found\nName: %s\nPhone: %s\nMail ID: %s\n",
            addressBook->contacts[index].name,addressBook->contacts[index].phone,
            addressBook->contacts[index].email);
    } 
    else 
    {
        printf("Contact not found.\n");

    }
    
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int searchOption;
    int index = -1;
    char input[50];

    printf("\nEdit Contact:\n");
    printf("Search by:\n1. Name\n2. Phone No\n3. Email ID\nEnter option: ");
    scanf("%d", &searchOption);

    switch (searchOption)
    {
        case 1:
            printf("Enter Name to search: ");
            scanf(" %[^\n]", input);
            index = search_by_name(addressBook,input);
            break;

        case 2:
            printf("Enter Phone to search: ");
            scanf(" %s", input);
            index = search_by_phone(addressBook,input);
            break;

        case 3:
            printf("Enter Mail to search: ");
            scanf(" %s", input);
            index = search_by_mail(addressBook,input);
            break;

        default:
            printf("Invalid option.\n");
            return;
    }

    if (index == -1)
    {
        printf("Contact not found.\n");
        return;
    }

    int editOption;
    char newValue[50];
    printf("What do you want to edit?\n1. Name\n2. Phone\n3. Mail\nEnter option: ");
    scanf("%d", &editOption);

    switch (editOption)
    {
        case 1:
            printf("Enter new name: ");
            scanf(" %[^\n]", newValue);
            if (name_validation(newValue))
            {
                strcpy(addressBook->contacts[index].name, newValue);
                printf("Name updated successfully.\n");
            }
            else
            {
                printf("Invalid name.\n");
            }
            break;

        case 2:
            while(1)
            {
                printf("Enter new phone: ");
                scanf("%s", newValue);
                if (phone_validation(newValue) && unique_phone(addressBook,newValue))
                {
                    strcpy(addressBook->contacts[index].phone, newValue);
                    printf("Phone number updated successfully.\n");
                    break;
                }
                else
                {
                    printf("Invalid phone number.\n");
                }
            }
            break;

        case 3:
            printf("Enter new mail: ");
            scanf("%s", newValue);
            if (mail_validation(newValue))
            {
                strcpy(addressBook->contacts[index].email, newValue);
                printf("Mail updated successfully.\n");
            }
            else
            {
                printf("Invalid mail.\n");
            }
            break;

        default:
            printf("Invalid edit option.\n");
    }
}


void deleteContact(AddressBook *addressBook)

{
 int searchOption;
 int index = -1;
 char input[50];

    printf("\nDelete Contact:\n");
    printf("Search by:\n1. Name\n2. Phone\n3. Mail\nEnter option: ");
    scanf("%d", &searchOption);

    switch (searchOption) 
    {
        case 1:
            printf("Enter Name: ");
            scanf(" %[^\n]", input);
            if (!name_validation(input)) 
            {
                printf("Invalid name format.\n");
                return;
            }
            index = search_by_name(addressBook,input);
            break;

        case 2:
            printf("Enter Phone: ");
            scanf(" %[^\n]", input);
            if (!phone_validation(input)) 
            {
                printf("Invalid phone format.\n");
                return;
            }
            index = search_by_phone(addressBook,input);
            break;

        case 3:
            printf("Enter Mail: ");
            scanf(" %[^\n]", input);
            if (!mail_validation(input)) 
            {
                printf("Invalid mail format.\n");
                return;
            }
            index = search_by_mail(addressBook,input);
            break;

        default:
            printf("Invalid option.\n");
            return;
    }

    if (index == -1) 
    {
        printf("Contact not found.\n");
        return;
    }

    // Delete contact by shifting
    for (int i = index; i < addressBook->contactCount - 1; i++) 
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;

    printf("Contact deleted successfully.\n");
}


//name validation
int name_validation(char *name)    
{
    int i;
    for( i=0; name[i]!='\0';i++)
    {
        char ch = name[i];
        if(!((ch >= 'A' && ch <= 'Z') || (ch >='a' && ch<='z') || ch ==' '))
        {
            return 0;  
        }
        
    }
    return 1;

}

//phone number vaildation
int phone_validation(char *phone)
{
    
    int i=0;
    for(i=0;i<=phone[i]!='\0';i++)
    {
        char ph =phone[i];
        if(!(ph >= '0' && ph<= '9'))
        {
           return 0;
        }
    }
 
    if(i != 10) //exact 10 digit
    {
        return 0;
    }
    return 1;

}

//mail ID validation
int mail_validation(char *mail)
{
    int i;
    for(i=0;mail[i]!='\0';i++)
    {
        char ch = mail[i];
        if(!((ch >= 'a' && ch <= 'z') || ch == '@' || ch == '.' || (ch >= '0'&& ch<= '9')))
        {
           return 0;
        }
    }
        char *ptr1 = strstr(mail,"@");
        char *ptr2 = strstr(mail,".com");

        if(ptr1 + 1 == ptr2)
        {
            return 0;
        }
        else
        return 1;

}


//search funtions
int search_by_name(AddressBook *addressBook,char *name) 
{
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0) 
        {
            return i;
        }
    }
    return -1;
}

int search_by_phone(AddressBook *addressBook,char *phone)
{
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0) 
        {
            return i;
        }
    }
    return -1;
}

int search_by_mail(AddressBook *addressBook,char *mail) 
{
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].email, mail) == 0) 
        {
            return i;
        }
    }
    return -1;
}

int unique_phone(AddressBook *addressBook,char *phone)
{
    for(int i=0;i < addressBook->contactCount; i++)
    {
         if (strcmp(addressBook->contacts[i].phone, phone) == 0) 
         {
            printf("This number is already present in the addressbook\n");
            return 0;
         }

    }
    return 1;

}







