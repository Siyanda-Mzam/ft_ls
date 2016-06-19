#include "../includes/ft_ls.h"

static char *lsperms(int mode)
{
    static const char **rwx;
    static char bits[11];

	rwx = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
    bits[0] = file_type_letter(mode);
    strcpy(&bits[1], rwx[(mode >> 6)& 7]);
    strcpy(&bits[4], rwx[(mode >> 3)& 7]);
    strcpy(&bits[7], rwx[(mode & 7)]);
    if (mode & S_ISUID)
    	if (mode & S_IXUSR)
        	bits[3] = 's'
        else
        	bits[3] = 'S';
    if (mode & S_ISGID)
    {
    	if (mode & S_IXGRP)
        	bits[6] = 's'
        else
        	bits[6] = 'l';
	}
	if (mode & S_ISVTX)
    {
    	if (mode & S_IXUSR)
        	bits[9] = 't'
        else
        	bits[9] = 'T';
	}
	bits[10] = '\0';
	return(bits);
}

static int file_type_letter(int mode)
{
    char    c;

    if (S_ISREG(mode))
        c = '-';
    else if (S_ISDIR(mode))
        c = 'd';
    else if (S_ISBLK(mode))
        c = 'b';
    else if (S_ISCHR(mode))
        c = 'c';
#ifdef S_ISFIFO
    else if (S_ISFIFO(mode))
        c = 'p';
#endif  /* S_ISFIFO */
#ifdef S_ISLNK
    else if (S_ISLNK(mode))
        c = 'l';
#endif  /* S_ISLNK */
#ifdef S_ISSOCK
    else if (S_ISSOCK(mode))
        c = 's';
#endif  /* S_ISSOCK */
#ifdef S_ISDOOR
    /* Solaris 2.6, etc. */
    else if (S_ISDOOR(mode))
        c = 'D';
#endif  /* S_ISDOOR */
    else
    {
        /* Unknown type -- possibly a regular file? */
        c = '?';
    }
    return(c);
}
