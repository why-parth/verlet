#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define class_no_prefix
#include "vclass.h"


class(Person){

    char *name;
    int age;
    long long int phoneNumber;

    function(Person, void, dial, int phoneNumber) now  {
        printf("%s's phone number : %llu", this->name, this->phoneNumber);
        printf("\n\tcalling %llu...", this->phoneNumber);
    }

    construct(Person) later;

};


int main (void) {


    return 0;
}

// later function(Person, void, dial, int phoneNumber) {
//     printf("%s's phone number : %llu", this->name, this->phoneNumber);
//     printf("\n\tcalling %llu...", this->phoneNumber);
// }
