#include "headers.h"
void pinfo(char* pid)
{
    char path[STR_LIM],exe[STR_LIM],stat[STR_LIM],line[STR_LIM];
    sprintf(exe,"/proc/%s/exe",pid),sprintf(stat,"/proc/%s/status",pid);
    FILE* fd=fopen(stat,"r");
    if(!fd)
    {
        perror("Error");
    }
    while(fgets(line,sizeof(line),fd))
    {
        if(strstr(line,"State:"))
        {
            printf("%s",line);
        }
    }
    struct rusage use;
    readlink(exe,path,STR_LIM);
    getrusage(RUSAGE_SELF,&use);
    printf("PID: %s \nExecutable path: %s \nMem Usage: %ld \n",pid,path,use.ru_maxrss);
    fclose(fd);
}