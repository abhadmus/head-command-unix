/*

Implementing file process command head in C

Author Name: Abdus'Samad Bhadmus

Completion Status:
Covers the following test cases:
 - ./head -n 3 input.txt
 - ./head -n 3 -e/-o input.txt
 - ./head -h
 - ./head -V
 - ./head input.txt (assumes a default of 10 lines)

 Does not cover test cases where -n isn't accompanied
 by a number K, given that this wasn't required in the brief. This
 program is also limited to files with a maximum number of lines of 100.

Program Description: Implements the head file processing
                     function in C, to be called from a UNIX system

*/

/* ===== System Header Files ===== */

#include <stdio.h>         // Provides standard input/output functions like printf, fgets
#include <stdlib.h>        // Includes string-to-number conversion (strtol) and exit codes
#include <unistd.h>        // Adds POSIX functionality for getopt to parse command-line options

/* ===== Constants ===== */
// These serve the role of improving readability and maintaining consistency

#define ERROR 1            // Defines return value for error conditions
#define SUCCESS 0          // Defines return value for successful execution
#define MAXLENGTH 100      // Sets max number of lines and chars per line for array
#define DEFAULT_NUM_LINES 10 // Default number of lines to print if -n not specified

/* ===== Function 1: Process File ===== */
/*

This function takes in the relevant parameters:
- optind:   a integer which contains the index of the first argument not parsed
            by getopt in main. In the context of this file this will point
            to the filename if it was provided
- argc:     a integer value denoting the number of arguments passed to the function
- argv:     a array of pointers to strings, each of which contains one of the
            arguments passed to the file in order
- filename: a string which will contain the name of the file in the case that
            a filename is provided in the head function call
- array:    the 2D array whose rows will be used to store each of the lines of the
            file, whole length is capped to MAXLENGTH

These parameters are used to open and collect data from the relevant file.
The data is then stored in an array using a while loop to be printed later on.
Error checks and closing the file after use is also included.
Over the course of this function length_array, a new value initialised in the
function, will count and eventually return the total number of lines read with
fgets into array

*/


int processfile(int optind, int argc, char *argv[], char *filename, char array[][MAXLENGTH]) {
    int length_array = 0;        // Initializes counter for number of lines read

    FILE *fp = filename ? fopen(filename, "r") : stdin;  // Opens file if filename given, else uses stdin

    if (!fp) {                   // Checks if file pointer is NULL (open failed)
        perror("Error opening file");  // Prints error message with system error details
        return ERROR;            // Returns error code if file cannot be opened
    }

    while (fgets(array[length_array], sizeof(array[length_array]), fp) != NULL && length_array < MAXLENGTH) {  // Reads lines into array until EOF or limit
        length_array++;          // Increments line counter after each successful read
    }
    printf("\n");

    fclose(fp);                  // Closes the file stream (safe since fp isn�t stdin here)
    return length_array;         // Returns total number of lines read
}

/* ===== Function 2: Print from the file ===== */
/*

This function takes the parameters:
- setting: depending on the arguments provided, the switch statement in main will
           have last triggered one of either -n, -e or -o for one of either
           the regular print setting, the even print setting or the odd print
           setting
- array:   this is the array first used in processfile and filled with
           elements from the file. this will now be used to print the file
           elements. again capped to MAXLENGTH
- length_array: having been initialised and returned in processfile, this
                will be used to control when to stop printing values from
                array, in tandem with no_lines
- no_lines: deduced by strtol in main, this represents the number K of lines
            to print in total

These functions are used with if statements to print either the even lines,
the odd lines or all of the lines within predefined limits

*/

void printfirstX(char setting, char array[][MAXLENGTH], int length_array, int no_lines) {
    int i;                       // Loop variable for iterating over array indices
    int printed = 0;             // Tracks number of lines actually printed

    if (setting == 'n') {        // Checks if normal printing mode is selected
        for (i = 0; ((i < length_array) && (i < no_lines)); i++) {  // Loops up to smaller of lines read or requested
            printf("%s", array[i]);  // Prints each line in sequence
        }
    }
    else if (setting == 'e') {   // Checks if even-line printing mode is selected
        for (i = 0; i < length_array && printed < no_lines; i++) {  // Loops until no_lines even lines are printed
            if ((i % 2) != 0) {  // Filters for even-numbered lines (1-based: 2, 4, 6...)
                printf("%s", array[i]);  // Prints the even line
                printed++;       // Increments count of printed even lines
            }
        }
    }
    else if (setting == 'o') {   // Checks if odd-line printing mode is selected
        for (i = 0; i < length_array && printed < no_lines; i++) {  // Loops until no_lines odd lines are printed
            if ((i % 2) == 0) {  // Filters for odd-numbered lines (1-based: 1, 3, 5...)
                printf("%s", array[i]);  // Prints the odd line
                printed++;       // Increments count of printed odd lines
            }
        }
    }
    printf("\n");                // Adds final newline for output formatting
}

/* ===== Function 3: Version Information ===== */
/*

This function doesn't take any parameters. When triggered it simply prints
the version message, as denoted by the brief, to inform the user about
the function's role, and details about the person who made it

*/

void versioninformation() {
    printf("Program Version: Implementation of head function in C\n");  // Prints program purpose
    printf("Name: Abdus'Samad Bhadmus\n");        // Prints author�s name
    printf("Email: abdus.bhadmus@ucdconnect.ie\n");  // Prints author�s email
    printf("Student Number: 23405234\n");         // Prints author�s student number
}

/* ===== Function 4: Help message ===== */
/*

This function doesn't take any parameters. When triggered it simply prints
the help message, as denoted by the brief, to teach the user how to use the
program

*/

void helpmessage () {
    printf("Usage: {head} [OPTION ] . . . [ FILE ]\n"); // Describes usage format
    printf("-n K output the first K lines\n");    // Describes -n option with K lines
    printf("-V output version info: your name, email, and student number\n");  // Describes -V option
    printf("-h displays all options (something like this text describing the options) and exit the application\n");  // Describes -h option
    printf("-e|-o print even|odd lines.\n");      // Describes -e and -o options
}

/* ===== Function 5: Main ===== */
/*

This function takes in two parameters, which are the summary of the various
options the user may have called the function with:

- argc:     a integer value denoting the number of arguments passed to the function
- argv:     a array of pointers to strings, each of which contains one of the
            arguments passed to the file in order

The contents of argv are parsed one by one with getopt, and with while loop
logic this is iterated until the end of the array is reached, and -1 is returned.

On each loop, a switch statement checks opt against the four relevant options,
n, V, h, e and o:
- If none of these are provided, the program terminates with an
  error message, telling the user that they provided an invalid parameter and to
  consult the help section for guidance.
- If V or h is provided, their respective versioninformation or helpmessage
  functions are called and the program terminates with success.
- If n, e or o are provided, the setting is switched to represent the last
  of them provided to argv, intended to be either e/o or n depending on whether
  regular or special printing is desired
- In the case of n, strtol, a function which extracts the numbers from a string
  and converts it to int formatting, is used to check for a valid K argument,
  store it in no_lines, and if it's valid continues to the next part of the
  program. If it's invalid, either because there is no K parameter (the case
  of optarg == endptr, which implies that no numbers were extracted at all,
  endptr is simply the entire next argument), there's a negative number
  (the extracted no_lines number is less then zero), or there's trailing junk
  after the K number (*endptr doesn't equal to the null character, rather is
  equal to something else, meaning something followed the numbers in the
  argument, for e.g -n 3a rather then -n 3), an error message requesting
  a valid K argument is printed and the program terminates on an error

Using the logic of optind < argc (if the first non argument input exists before
the end of argv's array, thus meaning that it exists as a given argument),
it's checked whether a filename was provided or not. Whether this filename
points to a file that exists is checked later in the processfile function.

Processfile and PrintfirstX are finally called at the end, given that the
settings required have been collected and all the relevant parameters have
been initialised.

*/

int main(int argc, char *argv[]) {
    char opt;                    // Stores the current option character from getopt
    char setting = 'n';          // Sets default print mode to normal (all lines)
    int length_array;            // Will hold the number of lines read from processfile
    char array[MAXLENGTH][MAXLENGTH];  // 2D array to store up to MAXLENGTH lines
    char *filename = NULL;       // Pointer to filename, NULL if stdin is used
    int no_lines = DEFAULT_NUM_LINES;  // Initializes to default 10 lines

    while ((opt = getopt(argc, argv, "n:Vheo")) != -1) {  // Loops through options until no more (-1)
        switch (opt) {           // Switches on current option character
            case 'n':            // Handles -n K option for number of lines
                setting = 'n';   // Sets mode to normal printing
                char *endptr;    // Declares pointer for strtol to track parsing end
                no_lines = strtol(optarg, &endptr, 10);  // Converts optarg (K) to integer
                if (optarg == endptr || no_lines <= 0 || *endptr != '\0') {  // Validates K: no digits, negative, or junk
                    printf("Invalid argument K, must be a positive integer. See the help section with -h for more details\n");  // Prints error for invalid K
                    return ERROR;  // Exits with error code
                }
                break;
            case 'e':            // Handles -e option for even lines
                setting = 'e';   // Sets mode to even-line printing
                break;
            case 'o':            // Handles -o option for odd lines
                setting = 'o';   // Sets mode to odd-line printing
                break;
            case 'V':            // Handles -V option for version info
                versioninformation();  // Calls function to print version details
                return SUCCESS;  // Exits successfully after printing
            case 'h':            // Handles -h option for help
                helpmessage();   // Calls function to print help text
                return SUCCESS;  // Exits successfully after printing
            default:             // Handles unrecognized options
                printf("Unexpected parameter. See the help section with -h to see all the valid parameters.\n");  // Prints error for invalid option
                return ERROR;    // Exits with error code
        }
    }

    if (optind < argc) {         // Checks if a filename argument exists after options
        filename = argv[optind];  // Assigns filename from argv if provided
        printf("File %s Provided Successfully\n", filename);  // Confirms file input
    }                            // Else filename remains NULL for stdin

    length_array = processfile(optind, argc, argv, filename, array);  // Reads lines into array, returns count
    if (length_array == ERROR) { // Checks if processfile failed (e.g., file not found)
        return ERROR;            // Exits with error code if file processing failed
    }
    printfirstX(setting, array, length_array, no_lines);  // Prints lines based on mode and count

    return SUCCESS;              // Returns success code on completion
}


