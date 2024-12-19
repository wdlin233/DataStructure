#include "hashtable.h"
#include "dict.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

int read_from_file(FILE * input_file, Dict *d);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        exit(1);
    }
    FILE *input = fopen(argv[1], "r");
    if (input == 0) {
        perror("Fopen Failed ");
        exit(-1);
    }
    Dict d = Dict();
    read_from_file(input, &d);
    fclose(input);
    d.print();
    return 0;
}

int read_from_file(FILE* input_file, Dict *dict) {
    bool flag;
    flag = false;
    char *str=new char[20];
    int n = 0;
    char ch;
    while((c = fgetc(input_file)) != EOF)
    {
        if(isalpha(ch)) {
            str[n++] = tolower(ch);
            flag = true;
        }
        else {
            if(flag) {
                str[n] = '\0';
                dict->insert(str);
                n = 0;
                flag = false;
            }
        }       
    }
    return 0;
}
