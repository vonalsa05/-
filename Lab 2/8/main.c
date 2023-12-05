#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <malloc.h>
#include <stdlib.h>

enum StatusCode{
    OK = 0,
    WRONG_NUMBER_RANGE = 1,
    SYSTEM_NUMBER_ERROR = 2
};
enum StatusCodeMemory{
    MEMORY_DOUBLE_VARIABLE_ARRAY_ALLOCATION_ERROR = 3,
    MEMORY_BOOL_ARRAY_ALLOCATION_ERROR = 4    
};




void free_memory(char**, int);
int double_type_has_finite_representation(char **,int * ,int ,int, int, ...);
int main(void){

    int number_simbols_after_point = 14;
    int count_arguments = 3;
    
    char ** result_double = (char **) malloc(  count_arguments  * sizeof(char *));


    for (int i=0;i< count_arguments ; i++){
        result_double[i] = (char *) malloc(number_simbols_after_point * sizeof(char));
        if (result_double[i] == NULL){
            free(result_double);
            return MEMORY_DOUBLE_VARIABLE_ARRAY_ALLOCATION_ERROR;
        
        }
    }

    if (result_double == NULL){
        return MEMORY_DOUBLE_VARIABLE_ARRAY_ALLOCATION_ERROR;
    
    }   


    int * result_bool = (int *) malloc(count_arguments * sizeof(int));

    if (result_bool  == NULL){
        free_memory(result_double, count_arguments);
        return MEMORY_BOOL_ARRAY_ALLOCATION_ERROR;
    
    }

    switch(double_type_has_finite_representation(result_double,result_bool, number_simbols_after_point,2 , count_arguments, (double) 1/5,(double) 0.6875,(double) 1/4 )){
        case 0:
            for(int i=0;i<count_arguments;i++){
                if (result_bool[i] == 0){
                    printf("%s: the fraction has no finite representation\n",result_double[i]);
                }
                else{
                    printf("%s: fraction has a finite representation\n",result_double[i]);

                }
            }     
            free_memory(result_double, count_arguments);
            free(result_bool);
            break;     
        case 1:
            free_memory(result_double, count_arguments);
            free(result_bool);
            return 5;
            break;
        case 2:
            free_memory(result_double, count_arguments);
            free(result_bool);
            return 6;
            break;
        case 3:
            free_memory(result_double, count_arguments);
            free(result_bool);
            return 7;
            break;
        case 4:
            free_memory(result_double, count_arguments);
            free(result_bool);
            return 8;
            break; 
  
        
    }
    


    return OK;
}

void free_memory(char** buffer_string, int len) {

    for (int i = 0; i < len; i++) {
        free(buffer_string[i]);
    }
    free(buffer_string);
}

int double_type_has_finite_representation(char** result_double,int * result_bool,int number_simbols_after_point ,int system_number, int count_arg, ...){
    
    va_list vl;
    va_start( vl, count_arg);

    for (int i = 0; i< count_arg;i++){

        double val = va_arg(vl, double);
        if ( (val > 1) || (val < 0) ){
            free_memory(result_double, count_arg);
            va_end( vl );
            return WRONG_NUMBER_RANGE;
        }

        if ( (system_number < 2) && (system_number > 36) ){
            va_end( vl );
            return SYSTEM_NUMBER_ERROR;
        }


        
        int count_list = 2;

        char sum[15] = "0."; 
        bool flag = false;

        int mod = 0;
        int count = 0;
        int old_system_number = system_number;
        bool flag_final_representation = false;
        while (count_list < number_simbols_after_point){
            
            while (mod != system_number - 1){

                val *= (double)system_number;
                if(val == 0){
                    flag_final_representation = true;
                    break;
                }
                mod = (int) val % system_number;
                sum[count_list++] = mod + '0';
 

            }
            if (flag_final_representation){
                break;
            }
            val = val - mod; 

            mod = 0;
            system_number = old_system_number;  
        }

        strcpy(result_double[i],sum);


        if (flag_final_representation){
            result_bool[i] = 1;
        }
        else{
            result_bool[i] = 0;
        }

    }



    va_end( vl );
    return OK;
}
