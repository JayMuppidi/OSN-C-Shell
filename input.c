
#include "headers.h"

char **inpBreaker(char *input)
{
    char **comList = malloc(STR_LIM);
    char *command;
    command = strtok(input, ";");
    ll numCom = 0;
    while (command != NULL)
    {
        comList[numCom++] = command;
        command = strtok(NULL, ";");
    }
    comList[numCom] = NULL;
    return comList;
}

char **comBreaker(char *command)
{
    char **argList = malloc(STR_LIM);
    char *arg;
    arg = strtok(command, "\t\r\n\a ");
    ll argNum = 0;
    while (arg != NULL)
    {
        argList[argNum++] = arg;
        arg = strtok(NULL, "\t\r\n\a ");
    }
    argList[argNum] = NULL;
    return argList;
}

void processCom(char ** argList)
{
    if(argList[0]==NULL)
    {
        return;
    }
    if(!strcmp(argList[0],"cd"))
    {
        cd(argList);
        return;
    }
    if(!strcmp(argList[0],"pwd"))
    {
        pwd();
        return;
    }
    if(!strcmp(argList[0],"echo"))
    {
        echo(argList);
        return;
    }
    if(!strcmp(argList[0],"ls"))
    {
        ls(argList);
        return;
    }
    if(!strcmp(argList[0],"exit")) exit(0);
    if(!strcmp(argList[0],"pinfo"))
    {
        if(argList[1]==NULL)
        {
            int pd = getpid();
            char pid[200];
            sprintf(pid,"%d",pd);
            pinfo(pid);
            return;
        }
        pinfo(argList[1]);
        return;
    }
    if(!strcmp(argList[0],"discover"))
    {
       // discover(argList);
    }
    if(!strcmp(argList[0],"jobs"))
    {
       jobs(argList);
       return;
    }
    if(!strcmp(argList[0],"bg"))
    {
       bg(argList);
       return;
    }
    if(!strcmp(argList[0],"fg"))
    {
       fg(argList);
       return;
    }
    starter(argList);
}

void redirecter (char **argList)
{
    int i =0; 
    if(argList[0]==NULL)
    {
        return;
    }
    int numTok,inpPos,outPos,outF,bgF;
    numTok = bgF = 0;
    inpPos=outPos=outF = -1;
    while(argList[numTok])
    {
        if(!strcmp(argList[numTok],"<"))
        {
            inpPos = numTok;
        }
        if(!strcmp(argList[numTok],">"))
        {
            outPos = numTok;
            outF = 0;
        }
        if(!strcmp(argList[numTok],">>"))
        {
            outPos = numTok;
            outF =1;
        }
        if(!strcmp(argList[numTok],"&"))
        {
            bgF=1;
        }
        numTok++;
    }
    if(inpPos!=-1 && outPos!=-1)
    {
        int inpOrg = dup(0),outOrg = dup(1),out,inp=(open(argList[inpPos+1],O_RDWR));
        if(inp==-1)
        {
            perror("Invalid input file");
            return;
        }
        if(!outF)
        {
            out = open(argList[outPos+1],O_CREAT | O_RDWR  | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        }
        else
        {
            out = open(argList[outPos+1],O_CREAT | O_RDWR | O_APPEND , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        }
        dup2(inp,0),dup2(out,1);
        char** recList = malloc(STR_LIM);
        int numRec,iter;
        numRec = iter=0;
        while(argList[iter])
        {
            if(iter==inpPos || iter==outPos || iter ==inpPos+1 || outPos+1)
            {
                iter++;
                continue;
            }
             
            recList[numRec++]=argList[iter];
            iter++;
        }
        recList[numRec]=NULL;
        redirecter(recList);
        dup2(inpOrg,0),dup2(outOrg,1);
       // close(inp),close(out);
        return;
    }
    else if(inpPos!=-1)//Only inp redirected
    {
        int inpOrg=dup(0);
        int inp =open(argList[inpPos+1],O_RDONLY);
        if(inp==-1)
        {
            perror("Invalid input file");
            return;
        }
        dup2(inp,0);
        char** recList = malloc(STR_LIM);
        int numRec,iter;
        numRec = iter=0;
        while(argList[iter])
        {
            if(iter==inpPos || iter ==inpPos+1 )
            {
                iter++;
                continue;
            }
            else 
                recList[numRec++]=argList[iter];
            iter++;
        }
        recList[numRec]=NULL;
        redirecter(recList);
        dup2(inpOrg,0);
        close(inp);
        return;
    }
    else if(outPos!=-1)
    {
        int outOrg = dup(1),out;
        if(!outF)
        {
            out = open(argList[outPos+1],O_CREAT | O_WRONLY  | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        } 
        else
        {
            out = open(argList[outPos+1],O_CREAT | O_WRONLY | O_APPEND , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        }
        dup2(out,1);
        char** recList = malloc(STR_LIM);
        int numRec,iter;
        numRec = iter=0;
        while(argList[iter])
        {
            if(iter==outPos || iter ==outPos+1 )
            {
                iter++;
                continue;
            }
            else 
                recList[numRec++]=argList[iter];
            iter++;
        }
        recList[numRec]=NULL;
        redirecter(recList);
        dup2(outOrg,1);
        close(out);
        return;
    }
    else
    {
        processCom(argList);
        return;
    }
}

int pipeCaller(char** argList)
{
    int pipeArr[STR_LIM][2],numArgs=0,numPipes=0;    
    if(argList[0]==0) return 1;// No commands
    while(argList[numArgs]!=NULL)
    {
        if(!strcmp(argList[numArgs],"|"))numPipes++;
        numArgs++;
    }
    if(!numPipes)//No pipes
    {
        redirecter(argList);
        return 1;
    }
    int lastPipe=0,pipeCount=0,inOrg,outOrg;
    inOrg=dup(0),outOrg=dup(1);
    for( int v = 0;v<numArgs;v++)
    {
        if(!strcmp(argList[v],"|"))
        {
            char** argList1 = malloc(STR_LIM);
            for(int i = lastPipe;i<=v;i++)// Transferring commands between pipes into another array
            {
                if(i==v)
                    argList1[i-lastPipe]=NULL;
                else
                    argList1[i-lastPipe]=argList[i];
            }
            lastPipe = v+1;
            if(pipeCount==0)
            {
                pipe(pipeArr[0]);
                dup2(pipeArr[0][1],1);
                redirecter(argList1);
                dup2(outOrg,2),dup2(inOrg,2);
            }
            else
            {
                pipe(pipeArr[pipeCount]);
                close(pipeArr[pipeCount-1][1]);
                dup2(pipeArr[pipeCount-1][0],0),dup2(pipeArr[pipeCount-1][1],1);
                redirecter(argList1);
                dup2(outOrg,2),dup2(inOrg,2);
            }
            pipeCount++;
        }
    }
    char ** argsLast=malloc(STR_LIM);
    int a = 0;
    while(argList[lastPipe]!=NULL)argsLast[a++]=argList[lastPipe++];
    argsLast[a]=NULL;
    close(pipeArr[pipeCount-1][1]);
    dup2(pipeArr[pipeCount-1][0],0),dup2(outOrg,1);
    redirecter(argsLast);
    dup2(inOrg,0);
    return 1;
}

