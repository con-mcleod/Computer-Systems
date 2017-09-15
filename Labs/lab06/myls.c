// myls.c ... my very own "ls" implementation
// z5058240 Connor McLeod

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAXDIRNAME 100
#define MAXFNAME   200
#define MAXNAME    20

char *rwxmode(mode_t, char *);
char *username(uid_t, char *);
char *groupname(gid_t, char *);

int main(int argc, char *argv[])
{
   // string buffers for various names
   char dirname[MAXDIRNAME];
   char uname[MAXNAME+1];
   char gname[MAXNAME+1];
   char mode[MAXNAME+1];

   // collect the directory name, with "." as default
   if (argc < 2)
      strlcpy(dirname, ".", MAXDIRNAME);
   else
      strlcpy(dirname, argv[1], MAXDIRNAME);

   // check that the name really is a directory
   struct stat info;
   if (stat(dirname, &info) < 0)
      { perror(argv[0]); exit(EXIT_FAILURE); }
   if ((info.st_mode & S_IFMT) != S_IFDIR)
      { fprintf(stderr, "%s: Not a directory\n",argv[0]); exit(EXIT_FAILURE); }

   // open the directory to start reading
   DIR *df;
   df = opendir(dirname);

   if (df == NULL) {
      printf ("Cannot open directory '%s'\n", argv[1]);
      return 1;
   }   

   // read directory entries
   struct dirent *entry;
   
   // create struct for storing file info
   struct stat currFile;

   while ((entry = readdir(df)) != NULL) {

      char buffer[MAXDIRNAME];
      sprintf(buffer, "%s/%s", dirname, entry->d_name);

      if ((entry->d_name[0]) == '.') {
         continue;
      }

      //lstat(entry->d_name, &info);
      if (lstat(buffer, &currFile) < 0) {
         perror(argv[0]); break;
      }
      
      mode_t permissions = currFile.st_mode;
      uid_t uid = currFile.st_uid;
      gid_t gid = currFile.st_gid;      
      long long Size = currFile.st_size;
      char *ObjectName = entry->d_name;

      //printf("%hu  %-8.8u %-8.8u %8lld  %s\n", permissions, uid, gid, (long long) Size, ObjectName);
      printf("%s  %-8.8s %-8.8s %8lld  %s\n", rwxmode(permissions, mode), username(uid, uname), groupname(gid, gname), (long long)Size, ObjectName);
   }

   // finish up
   closedir(df);
   return EXIT_SUCCESS;
}

// convert octal mode to -rwxrwxrwx string
char *rwxmode(mode_t mode, char *str)
{
   if (S_ISLNK(mode)) str[0] = 'l';
   else if (S_ISDIR(mode)) str[0] = 'd';
   else if (S_ISREG(mode)) str[0] = '-';
   else str[0] = '?';

   if (mode & S_IRUSR) str[1] = 'r'; else str[1] = '-';
   if (mode & S_IWUSR) str[2] = 'w'; else str[2] = '-';
   if (mode & S_IXUSR) str[3] = 'x'; else str[3] = '-';
   if (mode & S_IRGRP) str[4] = 'r'; else str[4] = '-';
   if (mode & S_IWGRP) str[5] = 'w'; else str[5] = '-';
   if (mode & S_IXGRP) str[6] = 'x'; else str[6] = '-';
   if (mode & S_IROTH) str[7] = 'r'; else str[7] = '-';
   if (mode & S_IWOTH) str[8] = 'w'; else str[8] = '-';
   if (mode & S_IXOTH) str[9] = 'x'; else str[9] = '-';
   return str;
}

// convert user id to user name
char *username(uid_t uid, char *name)
{
   struct passwd *uinfo = getpwuid(uid);
   if (uinfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)uid);
   else
      snprintf(name, MAXNAME, "%s", uinfo->pw_name);
   return name;
}

// convert group id to group name
char *groupname(gid_t gid, char *name)
{
   struct group *ginfo = getgrgid(gid);
   if (ginfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)gid);
   else
      snprintf(name, MAXNAME, "%s", ginfo->gr_name);
   return name;
}
