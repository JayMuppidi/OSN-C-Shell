#include "headers.h"



void sigHandle(int sig)
{
    int stat;
    int flag=0;
    pid_t pid;
    while((pid = waitpid(-1,&stat,WNOHANG)) > 0)
    {
        stat = WIFEXITED(stat);
        for(int c=0;c<count;c++)
        {
            if(bg_proc[c] == pid)
            {
                char* outString = (char*)malloc(150*sizeof(char));
                if(stat)
                {
                    sprintf(outString,"\n Pid %d exited normally\n",bg_proc[c]);
                }
                else
                {
                    sprintf(outString,"\n Pid %d exited abnormally\n",bg_proc[c]);
                }
                write(1,outString,strlen(outString));
                flag=1;
                break;
            }
        }
        
    }
    
    if(flag)
    {
        char* promptStr = (char*)malloc(STR_LIM);
        prompt(promptStr);
        write(1,promptStr,strlen(promptStr));
    }
}

void starter(char ** argList)
{  
    int status,k=0;
    while(argList[k])
    {
        k++;
    }
    if(k==0)
    {
        printf("More arguments needed");
    }
    pId=fork();
    if(!pId)
    {
        if(k>0)
        {
            if(!strcmp(argList[k-1],"&"))
            {
                argList[k-1]=NULL;
                setpgid(0,0);
            }
        }
        if(execvp(argList[0],argList))
        {
            perror("Command not found");
        }
        
        exit(0);
    }
    else if(pId<0)
    {
        perror("Error");
    }
    else
    {
        if(strcmp(argList[k-1],"&"))
        {
            waitpid(pId,&status,WUNTRACED);
            int status;
            if(WIFEXITED(status))
            {
                bg_proc[count++]=pId;
            } // Foreground
        }
        else
        {
            bg_proc[count++]=pId;
            printf("[%d] %d\n",count,pId);
        }
    }
}