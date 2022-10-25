#include <stdio.h>
#include <string.h>

char * find_char_in_string( char *string, char c ){
    int i=0;
    int len = strlen(string);
    while(i<len)
       if( string[i] == c )
         break;
       else 
         i++;

    if( i < strlen(string) )
       return &string[i];
    else
       return NULL;
}

char * find_char_in_string2( char *string, char c ){
    char *pos = string; 
    while((*pos!='\0')&&(*pos!=c)) //using pointer arithmetic
        pos++;
    return ( *pos == '\0' ? NULL : pos );
}


int main(){
    char string1[] = "Example on strings";
    char *string2 = "Another string";
    printf("%s\n%s\n", string1, string2);

    char *position;
    position = find_char_in_string(string1, 'p');
    printf("%s\n", position);


}
