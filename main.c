#include "headers.h"

void handleZ()
{
    if(foregroundwaalapid==-1)
    {
        return;
    }
       
    //kill(foregroundwaalapid,SIGTSTP);
    // bg_proc[count++]=foregroundwaalapid;
}
void handleC()    
{
    if (foregroundwaalapid==-1)
    {
        return;
    }
    // kill(foregroundwaalapid,SIGINT);
    printf("\n");
}


int main()
{   
    pid=-1,foregroundwaalapid=-1;
    count= 0;
    getcwd(orgDir,STR_LIM); //gets the starting directory
    signal(SIGINT,handleC);
    signal(SIGTSTP,handleZ);
    signal(SIGCHLD,sigHandle);
    while (1)
    {
        char promptStr[STR_LIM];
        char *inputStr = (char *)malloc(STR_LIM);
        size_t BUF = STR_LIM;
        prompt(promptStr);
        printf("%s", promptStr);
        if (getline(&inputStr, &BUF, stdin)==EOF)
        {
            exit(0);
        }
        
        char **comList = inpBreaker(inputStr);
        ll comNum = 0;
        while (comList[comNum] != NULL)
        {
            char **argList = comBreaker(comList[comNum]) ;
            pipeCaller(argList);
            free(argList);
            comNum++;
        }
        free(comList);
    }
    return 1;
}
