# Operating Systems and Networks C Shell
### The files in this repository for the shell are 
* ```main.c ``` contains the main shell loop, all kinds of variable declarations and a function that processes all commands given to it.
* ``` prompt.c``` contains the function to generate the promptline every time it's called based on cwd. 
* ``` headers.h``` contains all the headers used. 
* `spec2.c`

  - Echo: prints user input after removing excess spaces/tabs
  - `cd: allows user to navigate to different directories

- `ls.c`

  - Prints all files/sub-directories in a location
  - Flags implemented: `a` and `l`
  - Multiple directories supported

- `pinfo.c`
  - Prints info about process with given PID (current process if none is given)

- Exiting from the Shell
  - `Ctrl+D` or `Ctrl+C` allows you to exit the shell.

## Requirements
- GCC compiler
- Linux OS 
