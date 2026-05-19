//
// Standard Verlet Header Implemetation
//

#include "vcollect.h"

struct collect_out COLLECT_OUT_NULL = {AVSME_NULL, NULL, NULL};
/* Represents nothing in terms of struct collect_out. */

avsme AVSME_NONE = AVSME_SET(0, ASCII, 0);
avsme AVSME_TRUE = AVSME_SET(0, ASCII, 1);
avsme AVSME_FALSE = AVSME_SET(0, ASCII, 2);
/* Boolean AVSMEs. */

struct collect_out collect_immediate(char * _str) {
    if(!_str) return COLLECT_OUT_NULL;
    /* If the given string is NULL, char class is -1 and the pointers to tokens are NULL. */
    else if(!*_str) return COLLECT_OUT_NULL;
    /* If the given string is empty, char class is 0 and the pointers to tokens are NULL. */

    uint_least16_t char_class = charclass(_str[0]); // Char class of the first char.
    char * current_token = _str++; // Pointer to the current token (updates _str)

    while ((*_str) && (char_class == charclass(*_str))) _str++;
    /* Traversing the string unless the char class changes. */
    
    struct collect_out ret = {char_class, current_token, _str};
    return ret;
    /* Returning the collect_out of the char class and the pointers. */
}

struct collect_out collect_immediate_in(char * _str) {
    static char * current_string = NULL;
    /* To be able to reset when the given string changes. */

    static struct collect_out out;
    /* To store the collect’s return value. */

    if (_str != current_string) {
        /* If the given string doesn’t match the string that we’ve been keeping track of, all the tracking resets. Thus, new tracking for new strings. */
        current_string = _str;
        out.new_token = _str;
    }

    out = collect_immediate(out.new_token); // Collection of token and pointers to tokens

    return out; // Returning collect_out
}

size_t print_out_collective(struct collect_out out) {
    size_t count = (size_t)(out.new_token - out.old_token); // number of char(s)

    for (int i = 0; i < count; i++) printf("%d", out.char_class); // printing of charclass

    return count; // returning the length of printed string
}

size_t print_str_collective_immediate(char * _str) {
    struct collect_out out; /* To store the return value of collect. */
    size_t count; /* To store the number of char(s). */
    size_t ret; /* To store the number of printed char(s). */

    while (( out collects(_str) )) {
        // number of char(s)
        ret += (count = (size_t)(out.new_token - out.old_token));

        // printing of charclass
        for (int i = 0; i < count; i++) printf("%d", AVSME_GET(out.char_class, MAINCLASS));
    }

    collect_immediate_in(NULL); // resetting collect_in
    return ret; // returning the length of printed string
}


#define collect_variation(_str, _vlut)                                              \
                   __collect_variation  (										    \
                                            _str,								    \
                                            _vlut.n_keys,						    \
                                            (avsme *)_vlut.table,					\
                                            sizeof(*(_vlut.table)) / sizeof(avsme)	\
                                        ) /* Parameter Extraction Layer */

struct collect_out __collect_variation  (
                                            char * 	_str,
                                            size_t 	n_keys,
                                            avsme * table,
                                            size_t 	_stride
                                        ) /* Actual Function */
{
    if(!_str) return COLLECT_OUT_NULL;
    /* If the given string is NULL, char class is -1 and the pointers to tokens are NULL. */
    else if(!*_str) return COLLECT_OUT_NULL;
    /* If the given string is empty, char class is 0 and the pointers to tokens are NULL. */

    avsme char_class = charclass(_str[0]);	// Char class of the first char.
    avsme new_char_class; 				    // Char class of the new char.
    char * current_token = _str; 			// Pointer to the current token (updates _str)

    for ( ; *(++_str) ; )
    { 
        new_char_class = charclass(*_str);
        /* Traversal of the string. Assignment of the new char class. */

        if (char_class != new_char_class) for (int i = 0; i < n_keys; i++) {
            /* Char Class comparison, if not equal, iterating over table to table for new char class’s entry. */

            if AVSME_OVERLAP(char_class, table[i*_stride]) for (int j = 2; j < table[i*_stride + 1] + 2; j++) {
                /* If the char class entry is found, iterating over all the values of the found entry. */
                    
                    if
                    (
                        AVSME_BOOLEAN(table[i*_stride + j]) ||
                        AVSME_OVERLAP(new_char_class, table[i*_stride + j]) 
                    ) {
                        /* If the entry contains the new char class. */
                        
                        if ( (AVSME_BOOLEAN(table[i*_stride + j]) == AVSME_FALSE) || AVSME_VARIANT(table[i*_stride + j]) ) // if the entry is for variance,
                        {
                            struct collect_out ret = {char_class, current_token, _str};
                            return ret; // return.
                        }
                        else goto VLUT_NEXT_CHAR; // else, continue.
                    }
                    
                    else if (j == table[i*_stride + 1] + 1) VLUT_NO_VALUE_HANDLE; // goto VLUT_ERROR_CHECK for safety
                }

            else if (i == n_keys - 1) VLUT_NO_KEY_HANDLE; // goto VLUT_ERROR_CHECK for safety



        VLUT_NEXT_ENTRY:
        }
        
    VLUT_NEXT_CHAR:
    }

    /* Default behaviour of collect_variation */

    VLUT_ERROR_CHECK:

    if (!*_str) {
        struct collect_out ret = {char_class, current_token, _str};
        return ret; // return.
    }

    VLUT_ERROR_HANDLE;
    return VLUT_ERROR_RETURN_HANDLE;
}


#define collect_variation_in(_str, _vlut)	                                            \
                   __collect_variation_in   (					                        \
                                                _str,                                   \
                                                _vlut.n_keys,                           \
                                                (avsme *)_vlut.table,                   \
                                                sizeof(*(_vlut.table)) / sizeof(avsme)  \
                                            ) /* Parameter Extraction Layer */

struct collect_out __collect_variation_in   (
                                                char * _str,
                                                size_t n_keys,
                                                avsme * table,
                                                size_t _stride
                                            ) /* Actual Function */
{
    static char * current_string = NULL;
    /* To be able to reset when the given string changes. */

    static struct collect_out out;
    /* To store the collect’s return value. */

    if (_str != current_string) {
        /* If the given string doesn’t match the string that we’ve been keeping track of, all the tracking resets. Thus, new tracking for new strings. */
        current_string = _str;
        out.new_token = _str;
    }

    out = __collect_variation(out.new_token, n_keys, table, _stride);
    if (out.old_token == out.new_token) out.new_token += 1;
    // Collection of token and pointers to tokens

    return out; // Returning collect_out
}


#define print_str_collective_variation(_str, _vlut)                                 \
                   __print_str_collective_variation  (								\
                                            _str,								    \
                                            _vlut.n_keys,						    \
                                            (avsme *)_vlut.table,					\
                                            sizeof(*(_vlut.table)) / sizeof(avsme)	\
                                        ) /* Parameter Extraction Layer */

size_t __print_str_collective_variation (
                                            char * 	_str,
                                            size_t 	n_keys,
                                            avsme * table,
                                            size_t 	_stride
                                        ) /* Actual Function */
{
    struct collect_out out; /* To store the return value of collect. */
    size_t count; /* To store the number of char(s). */
    size_t ret; /* To store the number of printed char(s). */

    while (( out __collecting(_str, n_keys, table, _stride) )) {
        // number of char(s)
        ret += (count = (size_t)(out.new_token - out.old_token));

        // printing of charclass
        for (int i = 0; i < count; i++) printf("%d",  AVSME_GET(out.char_class, MAINCLASS));
    }

    __collect_variation_in(NULL, 0, NULL, 0); // resetting collect_in
    return ret; // returning the length of printed string
}
