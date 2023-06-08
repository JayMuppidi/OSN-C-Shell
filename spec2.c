#include "headers.h"



void echo(char **argList)
{
    ll argNum =1;
    while(argList[argNum]!=NULL)
    {
        printf("%s ",argList[argNum++]);  
    }
    printf("\n");
    return;
}
void cd(char **argList)
{
    
    if(argList[1]==NULL)
    {
        chdir("~"),chdir(orgDir);
        strcpy(currDir,orgDir);
        return;
    }
    if(argList[1][0]=='/')
    {
        chdir("/");
        getcwd(currDir,STR_LIM);
    }
    else
    {
        if(strcmp(argList[1],".")==0)
        {
            getcwd(currDir,STR_LIM);
            printf("%s\n",currDir);
        }
        else if(strcmp(argList[1],"~")==0)
        {
            chdir("~"),chdir(orgDir);
            getcwd(currDir,STR_LIM);
        }
        else
        {
            ll ret = chdir(argList[1]);
            if(ret!=-1)
            {
                char temp[STR_LIM];
                getcwd(currDir,STR_LIM);
            }
            else
            {
                perror("Error");
                return;
            }
        }
        if(strstr(currDir,orgDir)==NULL)
        {
            getcwd(currDir,STR_LIM);
        }
        return;
    }
}
void pwd(void)
{
    getcwd(currDir, STR_LIM);
    printf("%s\n",currDir);
}
