#include "stdlib.h"

typedef struct String {
        char* characters;
        int size;
} String;

String* String_new() {
        String* string = malloc(sizeof(String));
        string->characters = malloc(sizeof(char));
        string->characters[0] = '\0';
        string->size = 0;
        return string;
}

void String_add_element(String* string, char character) {
        int real_size_of_string = string->size+1;
        string->characters = realloc(
            string->characters, (real_size_of_string+1) * sizeof(char)
        );
        string->characters[string->size] = character;
        string->characters[string->size+1] = '\0';
        string->size++;
}
