#include "prompt.h"
#include "process.h"
#include "spec2.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <sys/wait.h>
#include <signal.h>
#include<sys/types.h>
#include<sys/resource.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <pwd.h>
#include <errno.h>
#include <dirent.h>
#include <stdio.h> 
#include <unistd.h>
#include <string.h> 
#include <fcntl.h>  
#include <sys/wait.h>
#include<sys/types.h>
#include<sys/resource.h>
#include <sys/utsname.h>
#include<errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<string.h>
#include<pwd.h>
#include <dirent.h>
#include<locale.h>
#include<grp.h>
#include<time.h>
#include "ls.h"
#include "pinfo.h"
#include "input.h"
#include "jobs.h"
//#include "discover.h"
#define ll long long 
#define STR_LIM 9999
char orgDir[STR_LIM],currDir[STR_LIM];
char start[STR_LIM],mid[STR_LIM];
// Process.h stuff
int bg_proc[STR_LIM],count;
pid_t pId, pid,shellpid,foregroundwaalapid;
