#include "headers.h"


void permPrinter(mode_t st)
{
    char perms[11]; 
    if(st && S_ISREG(st)) perms[0]='-'; 
    else if(st && S_ISBLK(st)) perms[0]='b'; 
    else if(st && S_ISDIR(st)) perms[0]='d'; 
    else if(st && S_ISSOCK(st)) perms[0]='s'; 
    else if(st && S_ISFIFO(st)) perms[0]='|'; 
    else if(st && S_ISCHR(st)) perms[0]='c'; 
    else perms[0]='l';  // S_ISLNK 
    perms[1] = (st && S_IRUSR) ? 'r':'-'; 
    perms[2] = (st && S_IWUSR) ? 'w':'-'; 
    perms[3] = (st && S_IXUSR) ? 'x':'-'; 
    perms[4] = (st && S_IRGRP) ? 'r':'-'; 
    perms[5] = (st && S_IWGRP) ? 'w':'-'; 
    perms[6] = (st && S_IXGRP) ? 'x':'-'; 
    perms[7] = (st && S_IROTH) ? 'r':'-'; 
    perms[8] = (st && S_IWOTH) ? 'w':'-'; 
    perms[9] = (st && S_IXOTH) ? 'x':'-'; 
    printf("%s", perms); 
}
int fileExist(char path[STR_LIM])
{
    struct stat stats;
    stat(path,&stats);
    if((stats.st_mode & F_OK) || (S_ISDIR(stats.st_mode)))
        return 1;
    return 0;
}
void normal(char path[])
{
    DIR* dir=opendir(path);
    struct dirent* file;
    while(file=readdir(dir))
    {
        if(file->d_name[0]!='.')
            printf("%s\n",file->d_name);
    }
    printf("\n");
    free(file),free(dir);
}
void a (char path[])
{
    DIR* dir;
    struct dirent* file;
    dir=opendir(path);
    while(file= readdir(dir))
        printf("%s\n",file->d_name);
    printf("\n");
    free(file),free(dir);
}
void lAndla (char path[], int flAg)
{
    DIR *dir=opendir(path);
    struct dirent *file;
    struct stat bufferstat;
    char buffer[STR_LIM];
    while(file=readdir(dir))
    {
        sprintf(buffer,"%s",file->d_name);
        if(buffer[0]=='.'&& !flAg)continue;
        stat(buffer,&bufferstat);
        struct passwd *user = getpwuid(bufferstat.st_uid);
        struct group *groupp = getgrgid(bufferstat.st_gid);
        permPrinter(bufferstat.st_mode);
        sprintf(buffer,"%hu %s %s %.19s %lld %s \n",bufferstat.st_nlink,user->pw_name,groupp->gr_name,ctime(&bufferstat.st_mtime),bufferstat.st_size,file->d_name);
        printf("%s",buffer);

    }
    closedir(dir);
    free(file);
    
}


void ls(char **argList)
{
    char name[STR_LIM];
    char** arr=(char**)malloc(STR_LIM*sizeof(char*));
    for(int i = 0;i<STR_LIM;i++)
    {
        arr[i] = (char*)malloc(STR_LIM*sizeof(char));
    }
    getcwd(name, STR_LIM);
    int fLag, flAg, j, i = 1;
    fLag = flAg = j = 0;
    while (argList[i])
    {
        if(argList[i][0] == '-'){
            for (int q = 1; q < strlen(argList[i]); q++)
            {
                if(argList[i][q] == 'l')
                {
                    fLag=1;
                }
                else if (argList[i][q]=='a')
                {
                    flAg =1;
                }
            }
        }
        else
            strcpy(arr[j++],argList[i]);
        i++;
    }

    if (!argList[1])
    {
       normal(name);
    }
    else if (!j)
    {
        if (fLag && flAg)
            lAndla(name,flAg);
        else if (fLag)
            lAndla(name,flAg);
        else if (flAg)
            a(name);
    }
    else
    {
        for (int k = 0; k < j; k++)
        {
            strcat(name, "/");
            strcat(name,arr[k]);
            if (!fileExist(arr[k]))
                perror("File not found");
            else if (strcmp(arr[k], "~") == 0)
            {
                printf("%s\n", arr[k]);
                if (fLag && flAg)
                    lAndla(orgPath2,flAg);
                else if (fLag)
                    lAndla(orgPath2,flAg);
                else if (flAg)
                    a(orgPath2);
                else
                    normal(orgPath2);
            }
            else
            {
                printf("%s\n", arr[k]);
                if (fLag && flAg)
                    lAndla(arr[k],flAg);
                else if (fLag)
                    lAndla(arr[k],flAg);
                else if (flAg)
                    a(arr[k]);
                else
                    normal(arr[k]);
            }
        }
    }
}
