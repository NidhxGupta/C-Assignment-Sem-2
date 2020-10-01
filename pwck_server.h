// Function declarations
void store_parameters_infof1();
bool is_valid_name (const char *name);
bool is_valid_pwd_pointer (const char *pwd_pointer);
bool is_valid_uid (char *uid);
bool is_valid_gid (char *gid);
bool searchPattern(char* pat, char* txt) ;
char * getShadowEntry(const char *name);
void cleanUpFiles(void);

void compare_files_1();

void store_parameters_infof2();
bool is_valid_last_pass_change (char *lpc);
bool is_valid_min_pass_change (char *mpc);
bool is_valid_max_pass_change (char *mapc);

// Structure of password file
// The /etc/passwd file contains vital user login data. The data is separated by colon.
struct passwd_file
{
    char *username; // Username (should be unique); should be between 1 and 32 characters in length
    char *password; // Password ; It contains an "x" (points to the /etc/shadow file for actual password) 
    uid_t UID;  // User ID ; Each user must be assigned a user ID (UID). UID 0 (zero) is reserved for root and UIDs 1-99 are reserved for other predefined accounts. Further UID 100-999 are reserved by system for administrative and system accounts/groups.
    gid_t GID; // Group ID ; Users may have same GID(Gives them same access rights on files and directories), other users will not get access to the files. The primary group ID (stored in /etc/group file)
    char *comments; // The comment field ; It allows you to add extra information about the users such as user‟s full name, phone number etc.
    char *HD; // Home directory ; The absolute path to the directory the user will be in when they log in. If this directory does not exist, then users directory becomes /
    char *SD; // Command/shell: The absolute path of a command or shell (/bin/bash). Typically, this is a shell. 
}infof1;

// Structure of shadow file
struct shadow_file
{
    char *username; // Username (should be unique); should be between 1 and 32 characters in length
    char *password; //
    // Password aging is set on user accounts to control access.
    int last_pass_change; //The number of days (since January 1, 1970) since the password was last changed.
    int min_pass_change; // The minimum number of days required between password changes i.e. the number of days left before the user is allowed to change his/her password
    int max_pass_change; // The maximum number of days the password is valid (after that user is forced to change his/her password)
    int warn_pass_change; // The number of days before password is to expire that user is warned that his/her password must be changed
    int inactive_days; // The number of days after password expires that account is disabled
    int expire; // days since Jan 1, 1970 that account is disabled i.e. an absolute date specifying when the login may no longer be used.
}infof2;