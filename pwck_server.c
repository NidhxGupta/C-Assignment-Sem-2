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

/* store_parameters() function will read each line of the file. After reading the line it will split the line about delimiter ":" and stores the parameters in the structure. It also checks if all the conditions are satisfied for each parameter. If not satisfied, it will delete the user.*/
void store_parameters_infof1()
{
    char line[200], orig[200];
    FILE *passwdfile;
    FILE *tempfile1;

    passwdfile = fopen("passwd","r");
    tempfile1 = fopen("passwd.modified","w");

    if (passwdfile  == NULL) 
    {
        printf("Error opening password file");
        // Program exits if file pointer returns NULL.
        exit(1);
    }
    if (tempfile1 == NULL) 
    {
        printf("Error opening password file");
        // Program exits if file pointer returns NULL.
        exit(1);
    }

    // Storing the parameters
    while( fgets( line, sizeof(line), passwdfile ) != NULL )
    {
        bool write_flag = false;
        int i=0, nStrLen, nField=0;
        char* token ;
        char* pwd_para[7];

        strcpy(orig,line);
        token = strtok(line,":");

        if (searchPattern("::",orig))
        {
            write_flag = false;

            if(write_flag == false)
            {
                printf("Deleting entry %s\n", orig);
            }

            continue;
        }


        while( token != NULL )
        {
            pwd_para[i++] = token;
            //printf(" %s\n", token);
            token = strtok(NULL,":");
            nField++;
        }

        if (nField != 7 )
        {
            continue;
            /* Invalid entries in password file */
        }

        //msanand:x:1001:1001:,,,:/home/msanand:/bin/bash

        nStrLen = strlen(pwd_para[0]);
        //printf ("\nLen: %d\n", nStrLen);
        infof1.username = (char*) malloc(nStrLen+1);
        strcpy(infof1.username, pwd_para[0]);
            
        nStrLen = strlen(pwd_para[1]);
        infof1.password = (char*) malloc(nStrLen+1);
        strcpy(infof1.password, pwd_para[1]);
    
        infof1.UID = atoi(pwd_para[2]);
        infof1.GID = atoi(pwd_para[3]);

        nStrLen = strlen(pwd_para[4]);
        infof1.comments = (char*) malloc(nStrLen+1);
        strcpy(infof1.comments, pwd_para[4]);

        nStrLen = strlen(pwd_para[5]);
        infof1.HD = (char*) malloc(nStrLen+1);
        strcpy(infof1.HD, pwd_para[5]);

        nStrLen = strlen(pwd_para[6]);
        infof1.SD = (char*) malloc(nStrLen+1);
        strcpy(infof1.SD, pwd_para[6]);

        // printf("%s is printed\n",pwd_para[0]);

        //Checking all parameters in order and writing to file if it's correct.
        if (is_valid_name(infof1.username) && orig[0] != ':')
        {
            if(is_valid_pwd_pointer(infof1.password))
            {
                if(is_valid_uid (pwd_para[2]))
                {
                    if(is_valid_gid (pwd_para[3]))
                    {                       
                        fwrite(orig,strlen(orig),1,tempfile1); 
                        write_flag = true;                      
                    }
                }
            }
        }

        if(write_flag == false)
        {
            printf("Deleting entry %s\n", orig);
        }

    }

   fclose(passwdfile); 
   fclose(tempfile1); 
   //remove("passwdfile");
   //rename("tempfile1","passwdfile");   
}

// Check if usernames are unique
// To check all conditions for the username 
bool is_valid_name (const char *name)
{
    int nLen = strlen(name);
    /*
     * User/group names must match [a-z_][a-z0-9_-]*[$]
     */
    if (('\0' == *name) ||
        !((('a' <= *name) && ('z' >= *name)) || ('_' == *name))) {
        return false;
    }

    while ('\0' != *++name) {
        if (!(( ('a' <= *name) && ('z' >= *name) ) ||
              ( ('0' <= *name) && ('9' >= *name) ) ||
              ('_' == *name) ||
              ('-' == *name) ||
              ( ('$' == *name) && ('\0' == *(name + 1)) )
             )) {
            return false;
        }
    }

    if (nLen == 0 || nLen >32)
    {
        return false;
    }


    return true;
}

// To check if a pointer x exists which points to shadow file
bool is_valid_pwd_pointer (const char *pwd_pointer)
{
   if (strcmp("x",pwd_pointer) != 0)
    {
        return false;
    }

    return true;
}

// check if uid's are unique
// Checking if UID is non-integer
bool is_valid_uid (char *uid)
{
    unsigned int nUID = atoi(uid);
    int nStrLen = strlen(uid), i;

    for (i =0; i < nStrLen; i++)
    {
        if ( isdigit(uid[i]) == 0 )
        {
            return false;
        }
    }


    if( nUID > 999 )
    {
        return false;
    }

    return true;
}

// gid can be same. No need to check for uniqueness
// Checking if GID is non-integer
bool is_valid_gid (char *gid)
{
    unsigned int nGID = atoi(gid);
    int nStrLen = strlen(gid), i;

    for (i =0; i < nStrLen; i++)
    {
        if ( isdigit(gid[i]) == 0 )
        {
            return false;
        }
    }

    if( nGID > 32767 )
    {
        return false;
    }

    return true;
}

bool searchPattern(char* pat, char* txt) 
{ 
    int M = strlen(pat); 
    int N = strlen(txt); 
  
    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++) { 
        int j; 
  
        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++) 
            if (txt[i + j] != pat[j]) 
                break; 
  
        if (j == M) // if pat[0...M-1] = txt[i, i+1, ...i+M-1] 
        {
            //printf("Pattern found at index %d \n", i); 
            return true;
        }
    } 

    return false;
} 

// Function to store parameters of shadow file
void store_parameters_infof2()
{
    char line[200], orig[200];

    FILE *shadowfile;
    FILE *tempfile2;

    shadowfile = fopen("shadow","r");
    tempfile2 = fopen("shadow.mod1","w");

    if (shadowfile  == NULL) 
    {
        printf("Error opening shadow file");
        // Program exits if file pointer returns NULL.
        exit(1);
    }
    if (tempfile2 == NULL) 
    {
        printf("Error opening shadow file");
        // Program exits if file pointer returns NULL.
        exit(1);
    }

    //Write a function to copy usernames from passwd file to shadow's temp file
    // Storing the parameters
    while( fgets( line, sizeof(line), shadowfile ) != NULL )
    {
        bool write_flag = false;
        int i=0, nStrLen;
        char* token ;
        char* spwd_para[8];

        strcpy(orig,line);
        token = strtok(line,":");


        while( token != NULL )
        {
            spwd_para[i++] = token;
            //printf(" %s\n", token);
            token = strtok(NULL,":");
        }

        //msanand:$6$Qi/jjPZi$0pbjgglt3VPahDmnYM5oFYLinGQN07UQEpLCzx.iQOcEsmlBiGF3FoMop6S5HtbqCI6LEBq7TljMQmEKveou7.:18389:0:99999:7:::

        nStrLen = strlen(spwd_para[0]);
        //printf ("\nLen: %d\n", nStrLen);
        infof2.username = (char*) malloc(nStrLen+1);
        strcpy(infof2.username, spwd_para[0]);
        
        nStrLen = strlen(spwd_para[1]);
        infof2.password = (char*) malloc(nStrLen+1);
        strcpy(infof2.password, spwd_para[1]);

        infof2.last_pass_change = atoi(spwd_para[2]);
        infof2.min_pass_change = atoi(spwd_para[3]);
        infof2.max_pass_change = atoi(spwd_para[4]);
        infof2.warn_pass_change = atoi(spwd_para[5]); 
        infof2.inactive_days = atoi(spwd_para[6]);
        infof2.expire = atoi(spwd_para[6]);

        if (is_valid_name(infof2.username) && orig[0] != ':')
        {
            if(is_valid_last_pass_change(spwd_para[2]))
            {
                if (is_valid_min_pass_change (spwd_para[3]))
                {
                    if(is_valid_max_pass_change (spwd_para[4]))
                    {
                        fwrite(orig,strlen(orig),1,tempfile2);
                        write_flag = true;
                    }
                }
            }
        }
        
        if(write_flag == false)
        {
            printf("Deleting entry %s\n", orig);
        }    
    }

   fclose(shadowfile); 
   fclose(tempfile2); 
}

// lpc can be same. No need to check for uniqueness
// Checking if last_pass_change is non-integer
bool is_valid_last_pass_change (char *lpc)
{
    unsigned int nLPC = atoi(lpc);
    int nStrLen = strlen(lpc), i;

    for (i =0; i < nStrLen; i++)
    {
        if ( isdigit(lpc[i]) == 0 )
        {
            return false;
        }
    }

    if( nLPC > 18406 ) //Checking validity of user's as on 24th May, 2020 from Jan 1, 1970
    {
        return false;
    }

    return true;
}

// mpc can be same. No need to check for uniqueness
// Checking if min_pass_change is non-integer
bool is_valid_min_pass_change (char *mpc)
{
    unsigned int nMPC = atoi(mpc);
    int nStrLen = strlen(mpc), i;

    for (i =0; i < nStrLen; i++)
    {
        if ( isdigit(mpc[i]) == 0 )
        {
            return false;
        }
    }

    if( nMPC > 18406 ) //Checking validity of user's as on 24th May, 2020 from 1st Jan, 1970
    {
        return false;
    }

    return true;
}

// mapc can be same. No need to check for uniqueness
// Checking if max_pass_change is non-integer
bool is_valid_max_pass_change (char *mapc)
{
    unsigned int nMaPC = atoi(mapc);
    int nStrLen = strlen(mapc), i;

    for (i =0; i < nStrLen; i++)
    {
        if ( isdigit(mapc[i]) == 0 )
        {
            return false;
        }
    }

    if( nMaPC > 99999 ) //Set automatically/set by default
    {
        return false;
    }

    return true;
}

// Function to compare the passwd and shadow files after verifying passwd file and update the shadow file with changes made(if any)
void compare_files_1()
{
    FILE *passwdfile;
    FILE *tempfile1;

    char line[200];

    passwdfile = fopen("passwd.modified","r");

    tempfile1 = fopen("shadow.modified","w");

    int i=0, nStrLen;
    char* token ;
    char* pwd_para[7], *shadowRow;

    while( fgets( line, sizeof(line), passwdfile ) != NULL )
    {
        //printf(" pwd: \n");
        i = 0;
        token = strtok(line,":");

        while( token != NULL )
        {
            pwd_para[i++] = token;
            //printf(" %s\n", token);
            token = strtok(NULL,":");
        }

        shadowRow =  getShadowEntry(pwd_para[0]);
        if( shadowRow != NULL)
        {
            //printf("\n 1Found: %s", shadowRow);
            fwrite(shadowRow,strlen(shadowRow),1,tempfile1);
        }    
    }

    fclose(passwdfile);
    fclose(tempfile1);

}

char * getShadowEntry(const char *name)
{
    FILE *shadowfile;
    static char line[200];

    //passwdfile = fopen("passwd","r");
    //Open corrected file
    shadowfile = fopen("shadow.mod1","r");

    //printf("\n Name: ");


    while( fgets( line, sizeof(line), shadowfile ) != NULL )
    {
        if(searchPattern((char *)name,line))
        {
            fclose(shadowfile);
            //printf("\n 2Found: %s", line);
            return line;
        }
    }

    fclose(shadowfile);
    return NULL;
}

void cleanUpFiles(void)
{
    remove("shadow.mod1");
}