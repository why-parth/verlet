#include <stdio.h>
#include "v_ReadWrite.h"

// Making a dummy translator
/*
    We will treat each line as an instruction.
    We will initialise the instructions in the loop itself (translation will be hard coded)

    Syntax:

    include:x
        x is included
    
    start:
        starts execution
    
    print:x
        x is printed (only when it starts and ends with ")
    
    x:y
        makes a variable x that stores y in it (only when y starts and ends with ")
    
    Dummy code:

    include:stdio.h
    main:
    print:"Hello World"
    a:"this is nice"
    print:a

*/

#define filename !!type the file name here!!

int main (int argc, char * argv[]) {

    printf("---translation starts---\n");

    Open(".\\tr-filename.c") Writer
    Open(".\\filename.txt") Reader

    int colon = 0;
    char cmd_type[512];
    char * backslash_n = NULL;

    ReadLine(cmd, 1024) {
        
        for (; cmd[colon] != ':'; colon++) {
            if (cmd[colon] != ' ') cmd_type[colon] = cmd[colon];
        }
        cmd_type[colon] = '\0';
        
        if ((backslash_n = strrchr(cmd, '\n'))) *backslash_n = '\0';
        cmd[colon++] = '\0';

        #define cmd_type_is(_type) (!strcmp(#_type, cmd_type))
        
        if cmd_type_is(include) WriteFormat("#include<%s>", cmd + colon);
        else if cmd_type_is(start) WriteLine("\nint main (void) {");
        else if cmd_type_is(print) WriteFormat("    printf(\"%%s\", %s);", cmd + colon);
        else WriteFormat("    char %s[] = %s;", cmd, cmd + colon);
        
        WriteChar('\n');
        colon = 0;
    }

    WriteLine("\treturn 0;\n}");

    CloseReader;
    CloseWriter;
    printf("---translation ends---");


    return 0;
}
