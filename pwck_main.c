/*
Write a program in C that verifies the integrity of the users and authentication information. 
It checks that all entries in /etc/passwd and /etc/shadow have the proper format and contain valid data. 
The user is prompted to delete entries that are improperly formatted or which have other uncorrectable errors. 
Refer man pages for the command “pwck”.
*/

// User Account types:-
// 1) root user - possesses full powers on the system. Superuser/administator has full access tp all services and administrative functions.
// 2) normal users - have user level priveleges and can't perform administrative functions. Can run and execute application and programs that they are authorized to execute.
// 3) service accounts - They are responsible for taking care of the installed services. Eg: mail, printing, etc.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "pwck_server.h"

int main(int argc, char *argv[], char *envp[])
{
    FILE *passwd, *shadow;

    if (argc < 2) //if sufficient no. of arguments not provided
    {
        printf("%s: %s\n", argv[0], "Expecting pwck command.");
        return 0;
    }
    else if (argc > 2 && !strcmp(argv[1], "pwck") && strcmp(argv[2], "--system")) //if pwck with more than one path
    {
        printf("%s\n", "Expecting pwck command only.");
        return 0;
    }
    else if (strcmp(argv[1], "pwck")) //if 2nd argument is other than 'pwck'
    {
        printf("%s: %s\n", argv[0], "Expecting pwck command.");
        return 0;
    }
  
    store_parameters_infof1();
    store_parameters_infof2();

    //align file from passwd and shadow
    compare_files_1();
    cleanUpFiles();

}