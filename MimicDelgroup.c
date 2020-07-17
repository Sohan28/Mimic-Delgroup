#include<stdio.h>
#include "CProjectHeaders.h"
#include "CProjectFunctions.c"

int main()
{
    //Takes command from user and stores it in an array. 
    scanf("%[^\n]s",&commandline);

    //The command given by user is then split into three, the command, the name (group to be deleted) and option, i.e. the extra arguments(if any). 
    splitline(commandline);

    //This function call checks if the user has given the correct command and correct option and there are no spelling errors.
    check(command,option);

    //If the commands given are correct, we simultaneously check if there are any options and if options are present, i.e.,
    //the "--only-if-empty" option, we check if the given groupname is empty (has no users). If it is not empty, we exit the 
    //program. We only check in the "group" file. 
    firstfile(files1,1);

    //If the option command is not given or the given group is already empty, we proceed to delete the group from the other three files. 
    if(overall == true)
        files(files2,3);
    
}