#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/*
 ******************************************************************************
 * Take note that this code does not check if the memory allocation           *
 * was successful, it was made for my school projects where memory            *
 * was not a problem, so I wouldn't recomend using it for serious purpuses    *
 * use it at your own risk, whatever you do is not my responsability.         *
 ******************************************************************************
 */


// Struct that will hold the array of chars that is a string.
//
// Elements:
// 	+characters+: [char*] Array of chars that will be the string,
// 						it always and with '\0'.
// 	+size+: [uint] Size of the string minus the '\0' at the end.
typedef struct String {
        char* characters;
        uint size;
} String;


// Creates a new String, with size zero and only the '\0' as a character
//
// Return: A String pointer to the new String
//
// Examples:
//      String* my_string = String_new();
//      printf("%d", my_string->size);
//          > 0
String* String_new() {
        String* string = malloc(sizeof(String));
        string->characters = malloc(sizeof(char));
        string->characters[0] = '\0';
        string->size = 0;
        return string;
}

// Creates a new String copying the characters provided in the params
// Parameters:
//  +characters+: array of chars that will be copied to the new String.
//  +size+: int with the size of the characters array provided, '\0' at the
//              end of characters should not be counted.
// Observations:
// - The new created String will have size equal the provided size, if size is
//      less than characters real size, only a part of characters will be
//      copied. However, if size is bigger than characters real size,
//      characters plus the difference will be copied, probably resulting in
//      segmentation fault.
// Return: A String pointer to the new created string.
//
// Examples:
//      String* my_string = String_new_from("abc", 3);
//      printf("%s", my_string->characters);
//          > abc
//      printf("%d", my_string->size);
//          > 3
//
//      String* my_string = String_new_from("abc", 1);
//      printf("%s", my_string->characters);
//          > a
//      printf("%d", my_string->size);
//          > 1
String* String_new_from(char* characters, int size){
        String* string = malloc(sizeof(String));
        string->characters = malloc((size+1)*sizeof(char));
        for (int i = 0; i < size; i++) {
                string->characters[i] = characters[i];
        }
        string->characters[size] = '\0';
        string->size = size;
        return string;
}

// Adds a char to the end of the provided string.
//
// Parameters:
//  +string+: Pointer to String object that will receive the char.
//  +character+: Char that will be added to the String.
//
// Examples:
//      String* my_string = String_new_from("abc", 3);
//      Atring_add_element(my_string, 'd');
//      printf("%s", my_string->characters);
//          > abcd
//      printf("%d", my_string->size);
//          > 4
void String_add_element(String* string, char character) {
        int real_size_of_string = string->size+1;
        string->characters = realloc(
                string->characters, (real_size_of_string+1) * sizeof(char)
                );
        string->characters[string->size] = character;
        string->characters[string->size+1] = '\0';
        string->size++;
}

// Transforms a string to integer
//
// Parameters:
//  +string+: String pointer that will be transformed to integer.
//
// Examples:
//      String* my_string = String_new_from("12", 2);
//      int number = String_to_int(my_string);
//      printf("%d", number);
//          > 12
int String_to_int(String* string){
        return atoi(string->characters);
}


String* String_int_to_string(int integer){
    char to_string[10];
    sprintf(to_string, "%d", integer);
    return String_new_from(to_string, strlen(to_string));
}

char* String_concat(String* string1, String* string2){
    uint size = string1->size + string2->size + 1;
    char* concated_string = malloc(size*sizeof(char));
    strcat(concated_string, string1->characters);
    strcat(concated_string, string2->characters);
    return concated_string;
}
