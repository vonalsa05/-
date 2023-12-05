#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>


enum StatusCode{
    PROGRAM_COMPLETED_SUCCESSFULLY = 0,
    INVALID_COUNT_SPECIFICATION_PARAMETERS = 1,
    INCORRECTED_SPECIFICATION_FORMAT = 2,
    INCORRECTED_ROMAN_NUMBERS_FORMAT = 3,
    SPECITICATION_NOT_FOUND = 4,
    MEMORY_ALLOCATION_ERROR = 5
};
int overfscanf(char *, char *, ...);
int oversscanf(char *,char *, ...);
int overprintf( char *, ...);

int transformation_int_to_string(long long int,char*, int*);
int roman_number_convert(char *,int*);

int main(void){
    char str[40] = "sdsds";
    int a,b,c,d,e,f=1622,h;
    unsigned int q;
    double fal = 40.303;
    char wewq = 's';  
    char Roman[40] =  "XLIX";

    printf("FILE PRINF: \n");
    switch (overprintf( "%d %s %f %c %Ro",f,str,fal,wewq,Roman))
    {
    case(0):
        printf("\nthe program completed successfully");
        break;
    case(1):
        printf("INVALID_COUNT_SPECIFICATION_PARAMETERS");
        break;
    case(2):
        printf("INCORRECTED_SPECIFICATION_FORMAT");
        break;
    case(3):
        printf("INCORRECTED_ROMAN_NUMBERS_FORMAT");
        break;
    case(4):
        printf("SPECITICATION_NOT_FOUND");
        break;
    case(5):
        printf("MEMORY_ALLOCATION_ERROR");
        break;
    default:
        printf("unpredictable program operation");


    }
    printf("\n");




    return 0;
}
int overprintf(char *format, ...){
    va_list arguments;
    va_start(arguments, format); 
    int len = strlen(format)+1;

    char **format_string = (char **)malloc(len * sizeof(char *));
    
    if (format_string == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }
    for (int i = 0; i < len; i++) {
        format_string[i] = (char *)malloc(256 * sizeof(char));
        if (format_string[i] == NULL) {
            free(format_string);
            return MEMORY_ALLOCATION_ERROR;
        }
    }

    

    char substring[256];
    int count = 0;
    int count_buffer_string = 0;


    for (char *formatPtr = format; *formatPtr != '\0'; formatPtr++){
        
        if (*formatPtr != ' '){
            substring[count++] = *formatPtr;

            if(*(formatPtr+1) == '\0'){

                substring[count] = '\0';
                strcpy(format_string[count_buffer_string], substring);


            }
        }
        else{
            substring[count] = '\0';
            strcpy(format_string[count_buffer_string++], substring);

            count = 0;
        }


    }


    int count_index_string = 0;
    for (int i = 0;i< count_buffer_string+1 ;i++){

        if (strcmp(format_string[i],"%d") == 0){

            int val = va_arg(arguments,int);
            char ssprinf_array[256];
            transformation_int_to_string( val,ssprinf_array,&count_index_string);
            printf("%s ", ssprinf_array);
        }

        else if (strcmp(format_string[i],"%f") == 0){
            double val = va_arg(arguments,double);
            double max_depth_mantissa = 1000000;

            int whole_part = (int) val; // получение целого.

            char whole_part_double[256];
            char mantissa[256];

            double fractional_part = val - (double) whole_part; // получение мантиссы

            // преобразование дробной части в целую
            long long int multiplied_val = round(fractional_part * max_depth_mantissa);

            // отбрасывание ненужных нолей
            while (multiplied_val % 10 == 0){multiplied_val /= 10; }; 
            int char_count_whole_part = 0, char_count_mantissa = 0;
            transformation_int_to_string(whole_part,whole_part_double,&char_count_whole_part);
            transformation_int_to_string(multiplied_val,mantissa,&char_count_mantissa);

  
            for (int i = 2-1;i>=0;i--){  putchar(whole_part_double[i]);}
            putchar('.');
            for (int i =3-1;i>=0;i--){  putchar(mantissa[i]);}            
            putchar(' ');
        }

        else if (strcmp(format_string[i],"%s") == 0){
            char * val = va_arg(arguments,char *);
            for (int i = 0; i < strlen(val); i++){  putchar(val[i]);}
            putchar(' ');
        }
        /*
        else if (strcmp(format_string[i],"%c") == 0){
            int val = va_arg(arguments,int);
            putchar(val);
            putchar(' ');
            
        }  
        else if (strcmp(format_string[i],"%Ro") == 0){
            char * val = va_arg(arguments,char *);
            int sum_roman_numbers = 0;

            roman_number_convert(val,&sum_roman_numbers);
            char * string_roman = (char *) malloc((strlen(val) + 1) * sizeof(char));

            if (string_roman == NULL){

                return MEMORY_ALLOCATION_ERROR;
            }
            int count_roman_int  = transformation_int_to_string( sum_roman_numbers, string_roman);

            for (int i = count_roman_int-1;i>=0;i--){  putchar( string_roman[i]);}
            putchar(' ');
        }
        else if (strcmp(format_string[i],"%Cv") == 0)
        {
            char * val = va_arg(arguments,char *);
            int base = va_arg(arguments,int);
            
            if (base < 2 || base > 36) {
                base = 10;
            }
            
            int result = 0; 
            int sign = 1; 
            


            if ( val[0] == '-') {
                sign = -1; 
            }
            

            for (int j = (val[0] == '-' ? 1 : 0); val[j] != '\0'; j++) {

                
                int digit;
                
  
                if (isdigit(val[j])) {
                    digit = val[j] - '0'; 
                } else {
                    digit = val[j] - 'a' + 10; 
                }
                

                if (digit >= 0 && digit < base) {
                    result = result * base + digit; 
                } else {
                    break; 
                }
            }
            
            int wewqe = result * sign;
        }*/
        

          
    }

    va_end(arguments);
    return 0;
}

int transformation_int_to_string(long long int val, char * array_convert_value_to_summary_string, int*count_index_string){

    char array_convert_value_to_string[256];
    int char_count = 0;

    while(val != 0) {array_convert_value_to_string[char_count++] = val%10 + '0';val = val / 10;}
    array_convert_value_to_string[char_count] = '\0';

    for(int i = 4; i>=0; i--){

        array_convert_value_to_summary_string[i] = array_convert_value_to_string[i];   
        *count_index_string += 1;
    
    }

    return 0;
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
/*
int oversscanf(char *buf, char * format, ...){

    va_list arguments;
    va_start(arguments, format); 
    int len = strlen(buf)+1;


    char **buffer_string = (char **)malloc(len * sizeof(char *));
    
    if (buffer_string == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }
    for (int i = 0; i < len; i++) {
        buffer_string[i] = (char *)malloc(256 * sizeof(char));
        if (buffer_string[i] == NULL) {
            free(buffer_string);
            return MEMORY_ALLOCATION_ERROR;
        }
    }

    

    char substring[256];
    int count = 0;
    int count_buffer_string = 0;



    for (char* ptr = buf; *ptr != '\0'; ptr++){
           
        if (*ptr != ' '){
            substring[count++] = *ptr;
    
            if(*(ptr+1) == '\0'){
                substring[count] = '\0';
                strcpy(buffer_string[count_buffer_string], substring);   


            }
        }

        else{
            substring[count] = '\0';
            strcpy(buffer_string[count_buffer_string++], substring);
            count = 0;
        }
    
    }


    char **specification_buffer_string = (char **)malloc(len * sizeof(char *));
    if (specification_buffer_string == NULL) {
        free(buffer_string);
        for (int i = 0; i < len; i++) {
            free(buffer_string[i]);
        }
        return MEMORY_ALLOCATION_ERROR;
    }
    for (int i = 0; i < len; i++) {
        specification_buffer_string[i] = (char *)malloc(256 * sizeof(char));
        if (specification_buffer_string[i] == NULL) {
            free(specification_buffer_string);
            free(buffer_string);
            for (int i = 0; i < len; i++) {
                free(buffer_string[i]);
            }
            return MEMORY_ALLOCATION_ERROR;
        }
    }

    int old_count_buffer_string = count_buffer_string;
    char as_substring[256];
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
            int roman_numbers = 0;
            int sum_roman_numbers = 0;
            for (int j = 0;j<strlen(buffer_string[i]); j++){
                int old_roman_numbers = roman_numbers;
                switch(buffer_string[i][j]){
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
                        sum_roman_numbers += (roman_numbers-old_roman_numbers);
                        sum_roman_numbers -= old_roman_numbers;
            
                }
                else{
                    sum_roman_numbers += roman_numbers;

                }


            }
            

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
            
            if (base < 2 || base > 36) {
                base = 10;
            }
            
            int result = 0; 
            int sign = 1; 
            

            if (buffer_string[i][0] == '-') {
                sign = -1; 
            }
            

            for (int j = (buffer_string[i][0] == '-' ? 1 : 0); buffer_string[i][j] != '\0'; j++) {

                
                int digit;
                
  
                if (isdigit(buffer_string[i][j])) {
                    digit = buffer_string[i][j] - '0'; 
                } else {
                    digit = buffer_string[i][j] - 'a' + 10; 
                }
                

                if (digit >= 0 && digit < base) {
                    result = result * base + digit; 
                } else {
                    break; 
                }
            }
            

            *val = result * sign;
        }
        else if(strcmp(specification_buffer_string[i],"%CV") == 0){
            int *val = va_arg(arguments,int*);
            int base = va_arg(arguments,int);

            if (base < 2 || base > 36) {
                base = 10;
            }
            
            int result = 0; 
            int sign = 1;
            
           
            if (buffer_string[i][0] == '-') {
                sign = -1; 
            }
            
            
            for (int j = (buffer_string[i][0] == '-' ? 1 : 0); buffer_string[i][j] != '\0'; j++) {

                
                int digit;
                
                
                if (isdigit(buffer_string[i][j])) {
                    digit = buffer_string[i][j] - '0'; 
                } else {
                    digit = buffer_string[i][j] - 'A' + 10;
                }
                
                
                if (digit >= 0 && digit < base) {
                    result = result * base + digit; 
                } else {
                    break; 
                }
            }
            
            
            *val = result * sign;
        }
        else{
            free(specification_buffer_string);
            free(buffer_string);
            for (int i = 0; i < len; i++) {
                free(buffer_string[i]);
            }
            for (int i = 0; i < len; i++) {
                free(specification_buffer_string[i]);
            }
            return SPECITICATION_NOT_FOUND; 
        }

    }


    // Освобождение памяти
    for (int i = 0; i < len; i++) {
        free(specification_buffer_string[i]);
    }
    free(specification_buffer_string);   

    // Освобождение памяти
    for (int i = 0; i < len; i++) {
        free(buffer_string[i]);
    }
    free(buffer_string);    


    va_end(arguments);
    return PROGRAM_COMPLETED_SUCCESSFULLY;


}
*/
