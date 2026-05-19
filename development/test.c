#include <stdio.h>
#include <stdlib.h>

#include "vutils.h"

#include "vcollect.h"

avsme IDVALID = 0;
avsme NUMBERS = 0;
avsme SYMBOLS = 0;

#define charclass(c) AVSME_SET( ( __char_idvalid(c) ? IDVALID : (__char_digit(c) ? NUMBERS : SYMBOLS) ), ASCII, c)

_Noreturn void VLUT_exit(void) {
    printf("\033[31m<! VLUT case is not registered. !>\033[0m");
    exit(-1);
}
#define VLUT_NO_VALUE_HANDLE goto VLUT_ERROR_CHECK
#define VLUT_NO_KEY_HANDLE goto VLUT_ERROR_CHECK
#define VLUT_ERROR_HANDLE VLUT_exit()
#define VLUT_ERROR_RETURN_HANDLE COLLECT_OUT_NULL

#include "vcollect.h"

int main(void) {

    IDVALID = AVSME_SET(IDVALID, MAINCLASS, 1);
    NUMBERS = AVSME_SET(NUMBERS, MAINCLASS, 2);
    SYMBOLS = AVSME_SET(SYMBOLS, MAINCLASS, 3);

    VLUT_DECLARE(vlut, 4, 4);

    VLUT_PUSH_KEY(vlut) IDVALID;  // index 0
    
    VLUT_PUSH_VALUE(vlut, 0) AVSME_SET(SYMBOLS, VARIANCE, 1);
    VLUT_PUSH_VALUE(vlut, 0) AVSME_TRUE;

    VLUT_PUSH_KEY(vlut) SYMBOLS;  // index 1
    
    VLUT_PUSH_VALUE(vlut, 1) AVSME_SET(AVSME_SET(0, ASCII, 'n'), VARIANCE, 1);
    VLUT_PUSH_VALUE(vlut, 1) AVSME_FALSE;

    VLUT_PUSH_KEY(vlut) NUMBERS;  // index 2
    
    VLUT_PUSH_VALUE(vlut, 2) NUMBERS;
    VLUT_PUSH_VALUE(vlut, 2) AVSME_FALSE;

    char string[] = "int main34(void){return 0;}";
    
    printf("%s\n", string);

    // struct collect_out out;

    // while (( out collecting(string, vlut) ))

    // print_collected(out), putchar('\n');

    print_str_collective_variation(string, vlut);
    // print_str_collective_immediate(string);

    return 0;
}


