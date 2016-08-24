#include "stdio.h"
#include "my_string.c"
// String get_ips(char* ips) {
// }

int main(int argc, char *argv[]) {
        String* my_string = String_new();
        String_add_element(my_string, 'a');
        String_add_element(my_string, 'c');
        String_add_element(my_string, 'b');
        return 0;
}
