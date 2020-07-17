#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "CProjectHeaders.h"

#define MAX 1000
#define MIN 0

char commandline[MAX],name[MAX],option[MAX],command[MAX], groupname[MAX],currentline[MAX],*files1[MAX] = {"group"},*files2[MAX] = {"gshadow","passwd","shadow"};
int iterator1 = MIN, iterator2 = MIN, iterator3 = MIN,iterator4 = MIN,iterator5 = MIN,value,final=1;
bool isEmpty,result,overall;

void splitline(char arr[])
{

    // In this command we split the command given by the user into three.
    // It iterates through the entire line and when we encounter an empty space, we skip the character and store the previous
    //characters in the respective arrays.

    //For example, the command : "delgroup user --only-if-empty" will store "delgroup" in array "command", "user" in "name" and
    //"--only-if-empty" in "option".
    while(arr[iterator1] != '\0')
    {
        if(arr[iterator1] == ' ')
        {
            iterator1++;
            
            while(arr[iterator1]!= '\0')
            {
                if(arr[iterator1] == ' ')
                {
                    iterator1++;

                    while(arr[iterator1] != '\0')
                    {
        
                        option[iterator3] = arr[iterator1];
                        iterator3++;
                        iterator1++;
                    }
                }
                name[iterator2] = arr[iterator1];
                iterator2++;
                iterator1++;
            }
        }

        command[iterator1] = arr[iterator1];
        iterator1++;
    }
}

void check(char com[],char op[])
{
    //This checks if the command given by user is correct
    if(com[0] != 'd' || com[1] != 'e' || com[2] != 'l' || com[3] != 'g' || com[4] != 'r' || com[5] != 'o' || com[6] != 'u' || com[7] != 'p' || com[8] != '\0')
    {
        printf("Error : Command '%s' was not recognised.\nExit Status : 127.\n",command);
        exit(0);
    } 

    if(op[0] != '\0')
    {
        //Here we check if the user has given the "--only-if-empty" option. If yes, then it checks for the spelling and sets the boolean value to 
        //false indicating that the user has given the option. 

        if(option[0] != '-' || option[1] != '-' || option[2] != 'o' || option[3] != 'n' || option[4] != 'l' || option[5] != 'y' || option[6] != '-' || option[7] != 'i' || option[8] != 'f' || option[9] != '-' || option[10] != 'e' || option[11] != 'm' || option[12] != 'p' || option[13] != 't' || option[14] != 'y' || option[15] != '\0')
        {
            printf("Error : Option '%s' was not recognised.\nExit Status : 127.\n",option);
            exit(0);
        }

        isEmpty = false;

    }

    else
    {
        isEmpty = true;
    }
    
}

void firstfile(char **filename,int count)
{
    for(int i = 0; i < count; i++)
    {
        FILE *file1, *file2;

        file1 = fopen(filename[i],"r");

        if(!file1)
        {
            printf("Error : Could not open file1\n");
            exit(0);
        }

        file2 = fopen("temp.txt","w");

        if(!file2)
        {
            printf("Error : Could not open file2\n");
            exit(0);
        }

        while (fgets(currentline, sizeof(currentline), file1) != NULL) 
        {
            getgroupname(currentline);
            {
                //Here we search the name given by the user in the file.
                //If it is present then the respective line is not copied to the temporary file.
                value = strcmp(name,groupname);

                if(value == 0)
                {
                    if(isEmpty == false)
                        result = checkempty(currentline);
                    else
                    {
                        result = true;
                    }
            
                    if(result == true)
                    {
                        final = 0;
                        continue;
                    }

                    else
                    {
                        printf("The group to delete is not empty. No action was performed.\nExit Status : 5.\n");
                        exit(0); 
                    }
                    
                }

                else
                {
                    fputs(currentline,file2);
                }
            }
            
        
        }
        
        if(final == 1)
            printf("There is no such group. No action was performed.\nExit Status : 3.\n");
        
        else
        {
            printf("The action was successfully executed.\nExit Status : 0.\n");
        }
        


        fclose(file1);
        fclose(file2);

        remove(filename[i]);
        rename("temp.txt",filename[i]);

        overall = true;
    }
}

void getgroupname(char arr2[])
{
    //We get the name of the group to be deleted from this function. 
    //It iterates through the current line that we have and stops when it first encounters the colon (:).
    //The characters before it is the group name.
    for(int iterator5 = 0; iterator5 < MAX; iterator5++)
        groupname[iterator5] = '\0';


    while(arr2[iterator4] != ':')
    {
       groupname[iterator4] = arr2[iterator4];
       iterator4++; 
    }

    iterator4 = MIN;
    
}

bool checkempty(char arr3[])
{
    //We check if the given group name has any users present by checking if there is a character present 
    //at the end of the line. If it is a colon then it is empty else not. 
    return (arr3[strlen(arr3)-2] == ':');
}

void files(char **filename,int count)
{
    //Here we do the same thing as the first file (group) but we do not check if it is empty because it has already been done. 
    for(int i = 0; i < count; i++)
    {
        FILE *file1, *file2;

        file1 = fopen(filename[i],"r");

        if(!file1)
        {
            printf("Error : Could not open file1\n");
            exit(0);
        }

        file2 = fopen("temp.txt","w");

        if(!file2)
        {
            printf("Error : Could not open file2\n");
            exit(0);
        }

        while (fgets(currentline, sizeof(currentline), file1) != NULL) 
        {
            getgroupname(currentline);
            {
                value = strcmp(name,groupname);

                if(value == 0)
                {
                    final = 0;
                    continue;
                }

                else
                {
                    fputs(currentline,file2);
                }
            }
        }

        if(final == 1)
            printf("There is no such group. No action was performed.\nExit Status : 3.\n");


        fclose(file1);
        fclose(file2);

        remove(filename[i]);
        rename("temp.txt",filename[i]);

    }

}