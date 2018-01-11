#include <string.h>
#include <stdio.h>
#include <dir.h>

void main(void)
 {
    char s[MAXPATH];
    char drive[MAXDRIVE];
    char dir[MAXDIR];
    char file[MAXFILE];
    char ext[MAXEXT];

    getcwd(s,MAXPATH);             	 /* get the current working directory */
    strcat(s,"\\");                  /* append on a trailing \ character */
    fnsplit(s,drive,dir,file,ext);	 /* split the string to separate elems */
    strcpy(file,"DATA");
    strcpy(ext,".TXT");
    fnmerge(s,drive,dir,file,ext);   /* merge everything into one string */
    puts(s);                         /* display resulting string */
}

