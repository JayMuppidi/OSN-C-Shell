#ifndef __INPUT_H
#define __INPUT_H

#include "headers.h"
void processCom(char ** argList);
char **comBreaker(char *command);
char **inpBreaker(char *input);
void redirecter (char **argList);
int pipeCaller(char** argList);

#endif
