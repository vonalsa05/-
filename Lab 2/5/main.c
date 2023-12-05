#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX_SIZE_DATA 256

enum StatusCodeBase{
    OK = 0
};

enum StatusCodeParameters{
    INVALID_COUNT_SPECIFICATION_PARAMETERS = 1,
    INCORRECTED_SPECIFICATION_FORMAT = 2,
    INCORRECTED_ROMAN_NUMBERS_FORMAT = 3,
    SPECITICATION_NOT_FOUND = 4,
};

enum StatusCodeFile{ 
    ERROR_READING_FILE = 5
};


enum StatusCodeMemory{
    MEMORY_RECEIVED_DATA_ALLOCATION_ERROR = 6,
    MEMORY_SPECIFICATION_DATA_ALLOCATION_ERROR = 7,
    MEMORY_ALLOCATION_ERROR = 8
};

int overfscanf(FILE *, char *, ...);
int oversscanf(char *,char *, ...);

void free_memory(char**, int);
int memory_allocation(char**,char **, int);
int system_number_convert(char *, int, bool );
int main(void){
    char str[40];
    int a,b,c,d,e,f=16,h;
    unsigned int q;
    double flo;
    char wewq;   

    FILE *file= fopen("text.txt", "r");
    

    printf("FILE SCANF: \n");
    switch (overfscanf(file, "%s %d %d %f %c %Ro %Cv %CV %Zr",str,&a,&b,&flo,&wewq,&d,&e,f,&h,16,&q))
    {
    case(0):
        printf("%s %d %d %f %c %d %d %d %u",str,a,b,flo,wewq,d,e,h,q);
        break;
    case(1):

        break;
    case(2):
        break;
    case(3):

        break;
    case(4):

        break;
    case(5):

        break;


    }
    printf("\n");

    printf("STRING SCANF: \n");
    switch (oversscanf("hello 1 2 3 s XLIX 2a 2A 1010101", "%s %d %d %f %c %Ro %Cv %CV %Zr",str,&a,&b,&flo,&wewq,&d,&e,f,&h,16,&q))
    {
    case(0):
        printf("%s %d %d %f %c %d %d %d %u",str,a,b,flo,wewq,d,e,h,q);
        break;
    case(1):
        break;
    case(2):
        break;
    case(3):
        break;
    case(4):
        break;
    case(5):
        break;

    }


    return 0;
}
void free_memory(char** buffer_string, int len) {

    for (int i = 0; i < len; i++) {
        free(buffer_string[i]);
    }
    free(buffer_string);
}

int memory_allocation(char** string_memory_allocation, char** for_memory_leak_string , int len){

        // memory allocation errors
    if (string_memory_allocation  == NULL) {
        if (for_memory_leak_string != NULL){ free_memory(for_memory_leak_string, len);};
        return MEMORY_ALLOCATION_ERROR;
    }
    for (int i = 0; i < len; i++) {
        string_memory_allocation[i] = (char *)malloc(MAX_SIZE_DATA * sizeof(char));

        // memory allocation errors
        if (string_memory_allocation[i] == NULL) {
            free(string_memory_allocation);
            if (for_memory_leak_string != NULL){ free_memory(for_memory_leak_string, len);};
            return MEMORY_ALLOCATION_ERROR;
        }

    }
    return OK;
}

int system_number_convert(char * string_number, int base, bool upper_register){
    if (base < 2 || base > 36) {
        base = 10;
    }
    
    int result = 0; 
    int sign = 1;
    
    
    if (string_number[0] == '-') {
        sign = -1; 
    }
    
    
    for (int j = (string_number[0] == '-' ? 1 : 0); string_number[j] != '\0'; j++) {

        
        int digit;
        
        
        if (isdigit(string_number[j])) {
            digit = string_number[j] - '0'; 
        } else {
            digit = string_number[j] - (upper_register?'A': 'a') + 10;
        }
        
        
        if (digit >= 0 && digit < base) {
            result = result * base + digit; 
        } else {
            break; 
        }
    }
    return result*sign;
           
}

int roman_number_convert(char*array_roman, int*sum){
    int roman_numbers = 0;

    for (int j = 0;j<strlen(array_roman); j++){
        int old_roman_numbers = roman_numbers;
        switch(array_roman[j]){
            case('I'):
                roman_numbers=1;
                break;
            case('V'):
                roman_numbers=5;
                break;
            case('X'):
                roman_numbers=10;
                break;
            case('L'):
                roman_numbers=50;
                break;
            case('C'):
                roman_numbers=100;
                break;
            case('D'):
                roman_numbers=500;
                break;
            case('M'):
                roman_numbers=1000;
                break;
            default:
                return INCORRECTED_ROMAN_NUMBERS_FORMAT;
        }
        //  III 1(0)+1(1) +1 (2)
        // IV 1(0) + 4(1)
        if  ((j!=0) && (old_roman_numbers < roman_numbers)){
                *sum += (roman_numbers-old_roman_numbers);
                *sum -= old_roman_numbers;

        }
        else{
            *sum += roman_numbers;

        }

    }  
}

int overfscanf(FILE *file, char * format, ...){

    va_list arguments;
    va_start(arguments, format); 


    if (file == NULL) {  return ERROR_READING_FILE; }    

    int len =  strlen(format)+1; 
    
    char **buffer_string = (char **)malloc(len * sizeof(char *));

    if (memory_allocation(buffer_string,NULL, len)){ return MEMORY_RECEIVED_DATA_ALLOCATION_ERROR; }

    char c;
    char substring[MAX_SIZE_DATA];
    int count = 0;
    char *ach;
    int count_buffer_string = 0;

    //reading lines from a file.

    while(!feof (file)) {

        if (fgets(substring, MAX_SIZE_DATA, file)){
            int ch = '\n';
            ach=strchr(substring,ch);
            substring[ach-substring] = '\0';
            strcpy(buffer_string[count_buffer_string++], substring);   

        }
    }
       

    fclose(file);
    char **specification_buffer_string = (char **)malloc(len * sizeof(char *));

    if (memory_allocation(specification_buffer_string,buffer_string, len)){ return MEMORY_SPECIFICATION_DATA_ALLOCATION_ERROR; }

    int old_count_buffer_string = count_buffer_string - 1;
    char as_substring[MAX_SIZE_DATA];
    count_buffer_string = 0;
    int c_count = 0;

    for (char *formatPtr = format; *formatPtr != '\0'; formatPtr++){
        
        if (*formatPtr != ' '){
            as_substring[c_count++] = *formatPtr;

            if(*(formatPtr+1) == '\0'){

                as_substring[c_count] = '\0';
                strcpy(specification_buffer_string[count_buffer_string], as_substring);


            }
        }
        else{
            as_substring[c_count] = '\0';
            
            strcpy(specification_buffer_string[count_buffer_string++], as_substring);

            c_count = 0;
        }


    }

    if ( old_count_buffer_string != count_buffer_string){
        free_memory(specification_buffer_string, len);
        free_memory(buffer_string, len);       
        return INVALID_COUNT_SPECIFICATION_PARAMETERS;
    }
    bool flag_error_specification_characters = false;

    for (int i = 0;i< count_buffer_string+1 ;i++){
        if (strcmp(specification_buffer_string[i],"%d") == 0){
            int *val = va_arg(arguments,int*);
            *val = atoi(buffer_string[i]);   
        }
        else if(strcmp(specification_buffer_string[i],"%s") == 0){
            char * val = va_arg(arguments,char *);
            strcpy(val, buffer_string[i]);

        }
        else if(strcmp(specification_buffer_string[i],"%f") == 0){
            double *val = va_arg(arguments,double *);
            *val = atof(buffer_string[i]);     
        }
        else if((strcmp(specification_buffer_string[i],"%c") == 0)){
            if (strlen(buffer_string[i]) != 1){
                return INCORRECTED_SPECIFICATION_FORMAT;
            }
            char * val = va_arg(arguments, char *);   
            *val = buffer_string[i][0];

        }
        else if(strcmp(specification_buffer_string[i],"%Ro") == 0){
            int *val = va_arg(arguments,int*);
            int sum_roman_numbers = 0;
            roman_number_convert(buffer_string[i],&sum_roman_numbers);
            *val = sum_roman_numbers;
        }
        
        else if(strcmp(specification_buffer_string[i],"%Zr") == 0){
            unsigned int *val = va_arg(arguments,unsigned int*);
            unsigned int number = 0;
            unsigned int prevFib = 1;
            unsigned int currentFib = 1;

            while (*buffer_string[i] != '\0') {
                if (*buffer_string[i] == '1') {
                        number += prevFib;
                }

                unsigned int nextFib = prevFib + currentFib;
                prevFib = currentFib;
                currentFib = nextFib;

                *(buffer_string[i]++);
            }

            *val = number;            
        }
        else if(strcmp(specification_buffer_string[i],"%Cv") == 0){
            int *val = va_arg(arguments,int*);
            int base = va_arg(arguments,int);
            *val = system_number_convert(buffer_string[i],base, false);
        }
        else if(strcmp(specification_buffer_string[i],"%CV") == 0){
            int *val = va_arg(arguments,int*);
            int base = va_arg(arguments,int);
            *val =  system_number_convert(buffer_string[i],base, true);
        }
        else{
            free_memory(buffer_string,len);
            free_memory(specification_buffer_string,len);
            return SPECITICATION_NOT_FOUND; 
        }

    }



    free_memory(specification_buffer_string, len);
    free_memory(buffer_string, len);


    va_end(arguments);
    return OK;


}

int oversscanf(char *buf, char * format, ...){

    va_list arguments;
    va_start(arguments, format); 

    int len = strlen(buf)+1;


    char **buffer_string = (char **)malloc(len * sizeof(char *));

    //memory allocation buffer_string
    if (memory_allocation(buffer_string,NULL, len)){ return MEMORY_SPECIFICATION_DATA_ALLOCATION_ERROR; }
    

    char substring[MAX_SIZE_DATA];
    int count = 0;
    int count_buffer_string = 0;

    for (char* ptr = buf; *ptr != '\0'; ptr++) {
        if (*ptr != ' ') {
            substring[count++] = *ptr;

            if (*(ptr + 1) == '\0') {
                substring[count] = '\0';
                strcpy(buffer_string[count_buffer_string], substring);
            }
        } else {
            substring[count] = '\0';
            strcpy(buffer_string[count_buffer_string++], substring);
            count = 0;

        }
    }




 
    char **specification_buffer_string = (char **)malloc(len * sizeof(char *));
    //memory allocation specification string
    if (memory_allocation(specification_buffer_string,buffer_string, len)){ return MEMORY_SPECIFICATION_DATA_ALLOCATION_ERROR; }



    int old_count_buffer_string = count_buffer_string;
    char as_substring[MAX_SIZE_DATA];
    count_buffer_string = 0;
    int c_count = 0;

    for (char *formatPtr = format; *formatPtr != '\0'; formatPtr++){
        
        if (*formatPtr != ' '){
            as_substring[c_count++] = *formatPtr;

            if(*(formatPtr+1) == '\0'){

                as_substring[c_count] = '\0';
                strcpy(specification_buffer_string[count_buffer_string], as_substring);


            }
        }
        else{
            as_substring[c_count] = '\0';
            
            strcpy(specification_buffer_string[count_buffer_string++], as_substring);

            c_count = 0;
        }


    }

    if ( old_count_buffer_string != count_buffer_string){
        free(specification_buffer_string);
        free(buffer_string);
        for (int i = 0; i < len; i++) {
            free(buffer_string[i]);
        }
        for (int i = 0; i < len; i++) {
            free(specification_buffer_string[i]);
        }
        return INVALID_COUNT_SPECIFICATION_PARAMETERS;
    }
    bool flag_error_specification_characters = false;

    for (int i = 0;i< count_buffer_string+1 ;i++){
        if (strcmp(specification_buffer_string[i],"%d") == 0){
            int *val = va_arg(arguments,int*);
            *val = atoi(buffer_string[i]);   
        }
        else if(strcmp(specification_buffer_string[i],"%s") == 0){
            char * val = va_arg(arguments,char *);
            strcpy(val, buffer_string[i]);

        }
        else if(strcmp(specification_buffer_string[i],"%f") == 0){
            double *val = va_arg(arguments,double *);
            *val = atof(buffer_string[i]);     
        }
        else if((strcmp(specification_buffer_string[i],"%c") == 0)){
            if (strlen(buffer_string[i]) != 1){
                return INCORRECTED_SPECIFICATION_FORMAT;
            }
            char * val = va_arg(arguments, char *);   
            *val = buffer_string[i][0];

        }
        else if(strcmp(specification_buffer_string[i],"%Ro") == 0){
            int *val = va_arg(arguments,int*);
            int sum_roman_numbers = 0;
            roman_number_convert(buffer_string[i],&sum_roman_numbers);
            *val = sum_roman_numbers;
        }
        
        else if(strcmp(specification_buffer_string[i],"%Zr") == 0){
            unsigned int *val = va_arg(arguments,unsigned int*);
            unsigned int number = 0;
            unsigned int prevFib = 1;
            unsigned int currentFib = 1;

            while (*buffer_string[i] != '\0') {
                if (*buffer_string[i] == '1') {
                        number += prevFib;
                }

                unsigned int nextFib = prevFib + currentFib;
                prevFib = currentFib;
                currentFib = nextFib;

                *(buffer_string[i]++);
            }

            *val = number;            
        }
        else if(strcmp(specification_buffer_string[i],"%Cv") == 0){
            int *val = va_arg(arguments,int*);
            int base = va_arg(arguments,int);
            *val = system_number_convert(buffer_string[i], base, false  );
        }
        else if(strcmp(specification_buffer_string[i],"%CV") == 0){
            int *val = va_arg(arguments,int*);
            int base = va_arg(arguments,int);
            *val = system_number_convert(buffer_string[i], base, true  ); 
        }
        else{
            free_memory(specification_buffer_string,len);
            free_memory(buffer_string, len);
            return SPECITICATION_NOT_FOUND; 
        }

    }



    free_memory(specification_buffer_string,len);
    free_memory(buffer_string, len);


    va_end(arguments);
    return OK;


}