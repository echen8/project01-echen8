# PROJECT 01 -- Shell
Eric Chen


### Implemented Features
* Acts as another terminal
* Takes multiple commands in one line and processes each command independently of each other.
* 


### Attempted Features
* Simple redirection with '>' or '<'
* Simple pipes


### Known Bugs/Annoyances
* Because of the separate forks for multiple commands, each command used in one line will be independent of each other. (Not necessarily a bad thing)
* cd command is a little wonky.


### Function Headers

* split_commands()

```/* ===================================================

   char ** split_commands()

   ARGS:
   [ char * line ] - String to be parsed with semicolons in case multiple commands are given.
   
   OUT:
   [ char ** args ] - A string array populated by single commands.
   
   USE:
   Allows processing of multiple commands at once.  Although it could be integrated into one command
   with parse_args(), I decided to leave them separate just for modularity.
   
   =================================================== */
```

* parse_args()

```/* ===================================================

   char ** parse_args()

   ARGS:
   [ char * line ] - String to be parsed by spaces to prepare it for processing with execvp.

   OUT:
   [ char ** args ] - A string array populated by the command as well as its flags/parameters.

   USE:
   Prepares the command line input for processing via execvp.

   =================================================== */
```

* run_cmd()

```/* ===================================================

   void run_cmd()

   ARGS:
   [ char * command ] - Unparsed command line to be ran.

   OUT:
   Void

   USE:
   Parses a single command and forks off a child to process it. Its looped usage in boot()
   will cause it to fork many times to perform these tasks.

   =================================================== */
```

* boot()

```/* ===================================================

   void boot()

   ARGS:
   None

   OUT:
   Void

   USE:
   An alternative main() function that is loopable. It prints the shell prompt and will
   continue to loop as long as there is input. Contains UI formatting, as well.

   It also parses command lines by semicolon and repeatedly runs these parsed commands
   with run_cmd().

   =================================================== */
```

* main()

```/* ===================================================

   int main()

   ARGS:
   None

   OUT:
   [ int ] - 0.

   USE:
   Houses function calls for clearing the terminal and booting up the E-Shell.
   
   Well, that's about it.

   =================================================== */
```


### Mini-DevLog
12-03-17	Removed gets() dependence for slightly uglier but safer input method.

12-01-17	Added multi-command support.

12-01-17	Transferred code from boot() into run_cmd() to prepare for multi-command support.

12-01-17	Made function split_commands() to split commands up for parsing to prepare for multi-command support.

12-01-17	Updated user interface.

11-30-17	Added function headers.

11-30-17	README!

11-29-17	Debug.

11-28-17	Debug.

11-27-17	Added quick-exit. (Leaving command line empty)

11-25-17	Transferred code from main() into boot() for loopability.

11-25-17	Created files.

















