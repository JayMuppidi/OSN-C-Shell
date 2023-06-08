#include "headers.h"

void namer()
{
    char outp[STR_LIM];
    sprintf(outp,"%s%s>",start,mid);
    printf("%s",outp);
}

char * prompt(char arr[])
{
    char hostName[STR_LIM];
    char *userName = (char *)malloc(STR_LIM);
    getcwd(orgPath2,STR_LIM);
    struct passwd *p = getpwuid(getuid());
    gethostname(hostName, sizeof(hostName));
    userName = p->pw_name;
    getcwd(currDir, STR_LIM);
    //sprintf(arr, "%s@%s %% ", userName, hostName);
    sprintf(start,"%s@%s:~>",userName,hostName);
    strcpy(arr,start);
    return arr;
}
