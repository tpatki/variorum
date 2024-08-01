#include <variorum.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Hello, world!\n");
    char *s = NULL;
    variorum_get_energy_json( &s );
    //variorum_print_energy();
    //free(s);
    return 0;
}
