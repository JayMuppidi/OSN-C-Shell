#include "headers.h"

void jobs(char **args)
{
    if (args[3] != NULL)
    {
        printf("Too many arguments\n");
        return ;
    }
    int jobs = 1,sFlag,rFlag;
    int iterator = 0;
    while(args[iterator])
    {
        if(strstr(args[iterator],"-r"))rFlag=1;
        if(strstr(args[iterator],"-s"))sFlag=1;
        if(strstr(args[iterator],"-rs")||strstr(args[iterator],"-sr"))sFlag=rFlag=1;
        if(rFlag && sFlag)break;
        iterator++;
    }
    for (int i = 0; i <= count; i++)
    {
        char cmd[STR_LIM],path[STR_LIM], cmdline[STR_LIM], stat[STR_LIM], line[STR_LIM];
        char pidStr[STR_LIM];
        sprintf(pidStr,"%d",bg_proc[i]);
        sprintf(cmdline, "/proc/%s/cmdline", pidStr), sprintf(stat, "/proc/%s/status", pidStr);
        FILE * fd = fopen(cmdline, "r");
        if (fd==NULL)
        {
            continue;
        }
        FILE *fd2 = fopen(stat,"r");
        if(fd2==NULL)
        {
            continue;
        }
        printf(" [%d] ",jobs++);
        while(fgets(line,sizeof(line),fd2)!=NULL)
        {
            if(strstr(line,"State:")&& strstr(line,"stopped")&& sFlag)printf("Stopped");
            else if(strstr(line,"State:")&&rFlag)printf("Running");
        }    
        read(fd,cmd,STR_LIM);
        printf(" %s [%s] \n",cmd,pidStr);
        fclose(fd),fclose(fd2);
    }
    
}

void fg( char ** args)
{

}
void bg(char **args)
{
    if (args[2] != NULL)
        perror("Invalid arguments");
    int flag = 0, pnum = atoi(args[1]), numJob = 1, shellpid = getpid();
    for (int p = 0; p < count; p++)
    {
        int pid1 = bg_proc[p];
        char pidStr[STR_LIM], base[STR_LIM];
        sprintf(pidStr, "%d", pid1);
        sprintf(base, "%s%s%s", "/proc/", pidStr, "/cmdline");
        int fd1 = open(base, O_RDONLY);
        if (fd1 == -1)
        {
            continue;
        }
        if (numJob == pnum)
        {
            flag = 1;
            int y = kill(pid1, SIGCONT);
            break;
        }
        numJob++;
        close(fd1);
    }
    if (!flag)
        printf("Not found");
}