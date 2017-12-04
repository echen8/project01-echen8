#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>

/* ===================================================

   char ** split_commands()

   ARGS:
   [ char * line ] - String to be parsed with semicolons in case multiple commands are given.
   
   OUT:
   [ char ** args ] - A string array populated by single commands.
   
   USE:
   Allows processing of multiple commands at once.  Although it could be integrated into one command
   with parse_args(), I decided to leave them separate just for modularity.
   
   =================================================== */

char ** split_commands( char * line ) {

  char ** args = ( char ** )calloc( 3, sizeof( line ) );

  int i;
  for ( i = 0; line; i++ ) {
    args[i] = strsep( &line, ";" );
  }
  args[i] = 0;

  return args;
  
}

/* ===================================================

   char ** parse_args()

   ARGS:
   [ char * line ] - String to be parsed by spaces to prepare it for processing with execvp.

   OUT:
   [ char ** args ] - A string array populated by the command as well as its flags/parameters.

   USE:
   Prepares the command line input for processing via execvp.

   =================================================== */


char ** parse_args( char * line ) {

  // printf( "line: [%s]\n", line );

  char ** args = ( char ** )calloc( 3, sizeof( line ) );
  
  int i;
  for ( i = 0; line; i++ ) {
    args[i] = strsep( &line, " " );
    // printf( "adding [%s]...\n", args[i] );
  }
  args[i] = 0;

  return args;
  
}

/* ===================================================

   void run_cmd()

   ARGS:
   [ char * command ] - Unparsed command line to be ran.

   OUT:
   Void

   USE:
   Parses a single command and forks off a child to process it. Its looped usage in boot()
   will cause it to fork many times to perform these tasks.

   =================================================== */

void run_cmd( char * command ) {

  char ** args = parse_args( command );

  int f = fork();
  int status;

  if ( f ) {
    wait( &status );
  }

  if ( !f ) {

    // Check for 'cd' command
    if ( strcmp( args[0], "cd" ) == 0 ) {
      chdir( args[1] );
    }

    // Check for 'exit' command
    if ( strcmp( args[0], "exit" ) == 0 ) {
      kill( 0, SIGINT );
    }
    
    // If the command did not run correctly
    else if ( execvp( args[0], args ) == -1 ) {
      char * errmsg;
      sprintf( errmsg, "The command [%s] is unrecognized by E-Shell. It's not you, it's me. :(\n", args[0] );
      perror( errmsg );
    }
  }
}


/* ===================================================

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

void boot() {

  // Command placeholder
  char line[256];

  // Gets host name
  char host[256];
  gethostname( host, sizeof( host ) );

  // Gets current working dir
  char cwd[256];
  getcwd( cwd, sizeof( cwd ) );

  // User interface
  printf( "\n\n\n=================== E-Shell Terminal ===================\n" );
  printf( "Hostname: %s\n", host );
  printf( "Current Working Directory: %s\n", cwd );
  printf( "=================== ================ ===================\n" );
  printf( "Command Line: " );

  /*
  get( line );
  // Worry about gets alternative later
  */

  fgets( line, sizeof( line ), stdin );
  char * pos;
  if ( ( pos = strchr( line, '\n' ) ) != NULL ) {
    * pos = '\0';
  }
  
  // Check for input
  if ( !strlen( line ) ) {
    printf( "No input found.  E-Shell will now exit.\n" );
    exit( 0 );
  }

  // Multi-command functionality
  char ** commands = split_commands( line );
  int i;

  // Loop for multiple commands
  for ( i = 0; commands[i]; i++ ) {
    run_cmd( commands[i] );
  }

  boot();
  
} // END BOOT


/* ===================================================

   int main()

   ARGS:
   None

   OUT:
   [ int ] - 0.

   USE:
   Houses function calls for clearing the terminal and booting up the E-Shell.
   
   Well, that's about it.

   =================================================== */
int main () {

  system("clear");

  boot();
  
  return 0;
} // END MAIN
