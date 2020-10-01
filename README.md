#DONE BY

Nidhi Gupta
Second Semester
J Section
PES2UG19CS256

#Assignment Q

Write a program in C that verifies the integrity of the users and authentication information. 
It checks that all entries in /etc/passwd and /etc/shadow have the proper format and contain valid data. 
The user is prompted to delete entries that are improperly formatted or which have other uncorrectable errors. 
Refer man pages for the command “pwck”.

Pwck Utility for Checking the Integrity of Password File
Pwck, is a system administration command that removes corrupt or duplicate entries in
the /etc/passwd and /etc/shadow files. Pwck verifies the integrity of the system
authentication information. All entries in the /etc/passwd and /etc/shadow are checked to
see that the entry has the proper format and valid data in each field. The user is prompted
to delete entries that are improperly formatted or that have other in-correctable errors.

#How to Execute

This program is run by giving the following command:-

./output pwck

It is assumed that this program is run in etc folder which contains shadow and passwd files.

The files are checked for all the conditions and passwd.modified and shadow.modified is created to view our results.

This program will also tell which users were deleted.