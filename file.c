#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
  
FILE * fptr = fopen("contacts.csv", "w");

fprintf(fptr,"#%d\n",addressBook->contactCount);

for(int i =0; i< addressBook->contactCount;i++)
{
   
    fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
}

fclose(fptr);
}




void loadContactsFromFile(AddressBook *addressBook) 
{

FILE *fp = fopen("contacts.csv","r");
//check
    if(fp == NULL)
    {
        printf("File is not found\n");
        return ;
    }

    fscanf(fp,"#%d\n",&addressBook->contactCount);
    
    for(int i =0; i< addressBook->contactCount;i++)
{
   
    fscanf(fp,"%[^,],%[^,],%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
}

fclose(fp);
    
}
