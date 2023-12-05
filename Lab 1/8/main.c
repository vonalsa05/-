#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void random_generated(void);
void odd_numbers(int size);
void even_numbers(int size);
int far_element(int size);
int sum_before(int size);
int small_sum(int size);
int read_file(void);
// динамический размер считываемых текстовых данных
#define SIZE 50

int sum = 0;
int index_element,output_variable;
int buffer[SIZE];
int required_array[128];
FILE * job_file, * random_generated_file;
int buffer_index,new_count_index = 0;


int main(void){
    srand(time(NULL));

    // просто ради прикола загенерил текстовый документ до 128 чисел.
    if ((random_generated_file = fopen("Lab_file.txt", "w")) == NULL){
        printf("System Error: Incorrect reading due to the fact that the file is missing (write)");
        return -1;
    }

    random_generated();

   // считывание документа
    if ((job_file = fopen("Lab_file.txt","r")) == NULL){
        printf("System Error: Incorrect reading due to the fact that the file is missing (read)");
        return -2;
    }
    char c;
    if ((c = fgetc(job_file)) == EOF){
        printf("Data Error: Invalid corrected data files. (0 amount text data)");
        return 1;
    }


    int result_size;
    result_size = read_file();

    if (result_size>128){
        printf("System Error: array dimension exceeded");
        return -3;        
    }

    char char_stdin;

    //вопрос пользователю и ожидание варианта в стандартном потоке вывода.
    printf("a) numbers on odd positions;\n");
    printf("b) Even numbers;\n");
    printf("c) for the current element: the farthest (by value) from it value from the same array;\n");
    printf("d) for the current element: the sum of the elements that it preceded;\n");
    printf("e) for the current element: the sum of elements that are smaller than it. The index value of the current element for items c-e must be received from standard input.\n");
    printf("To create a new array, enter (char only): ");
    scanf("%c",&char_stdin);

    switch (char_stdin)
        {
        case 'a':
            odd_numbers(result_size);
            break;
        case 'b':
            even_numbers(result_size);
            break;    
        case 'c':
            // значение одно, поэтому и так понятно, что можно записать его в первую ячейку.
            required_array[0] =  far_element(result_size);
            new_count_index += 1;
            break;   
        case 'd':
            required_array[0] = sum_before(result_size);
            new_count_index += 1;
            break;
        case 'e':
            required_array[0] = small_sum(result_size); 
            new_count_index += 1; 
            break;    
        default:
            printf("What you entered is not what is intended");
            break;            
    }
    if (new_count_index != 0){
        //вывод
        printf("NEW ARRAY: [ ");
        for(output_variable = 0; output_variable<=new_count_index-1; output_variable++){
            //выводим только те элементы, которые отличны от пустых ячеек
            printf("%d ", required_array[output_variable]);
        }
        printf("]");   
    }
		return 0;
}
void random_generated(void){
    int i;int rand_int; char random_intString[10];  

    // цикл создающий рандомные числа, преобразовывая их в строку, а затем вставляя их в файл.   
    for(i=0;i<= SIZE-1; i++){
        rand_int = rand();
        sprintf(random_intString, "%d\n", rand_int);
        fputs(random_intString, random_generated_file);
    }

    fclose(random_generated_file);
}

int read_file(void){
    // возврат в начало файла
    rewind(job_file);

    char buffer_case_string[10];
    int int_element_array, count_data_file = 0;
    // построчное считывание, преобразование в число и добавление в массив.
    while(!feof(job_file)){  
        int_element_array = atoi(fgets(buffer_case_string, sizeof(buffer_case_string), job_file));
        if (int_element_array == 0){
            break;
        } 
        buffer[count_data_file] = int_element_array;
        ++count_data_file;  
    };
    fclose(job_file);    
    return count_data_file;
}

void odd_numbers(int result_size){
    printf("OLD ARRAY: [ ");
    for(buffer_index = 0; buffer_index<=result_size-1; buffer_index++){
        printf("%d ", buffer[buffer_index]);
    }  
    printf("]\n");
    printf("Here is your new array of odd positions\n");
    for (buffer_index = 0; buffer_index<=result_size-1; buffer_index++){
        if( (buffer_index + 1) % 2 != 0){
            required_array[new_count_index] = buffer[buffer_index];
            ++new_count_index;
        }
        else{
            continue;
        }
    } 
}

void even_numbers(int result_size){
    printf("OLD ARRAY: [ ");
    for(buffer_index = 0; buffer_index<=result_size-1; buffer_index++){
        printf("%d ", buffer[buffer_index]);
    }  
    printf("]\n");
    printf("Here is your new array of even numbers\n");
    for(buffer_index = 0; buffer_index<=result_size-1; buffer_index++){
        if(buffer[buffer_index] % 2 == 0){
            required_array[new_count_index] = buffer[buffer_index];
            ++new_count_index;
        }
        else{
            continue;
        }
    }    
}

int far_element(int result_size){
    printf("current element index value: ");
    scanf("%d",&index_element);
    printf("OLD ARRAY: [ ");
    for(buffer_index = 0; buffer_index<=result_size-1; buffer_index++){
        printf("%d ", buffer[buffer_index]);
    }  
    printf("]\n");
    int element_far = buffer[0];
    int difference = abs(buffer[index_element] - buffer[0]);
    if (index_element > result_size-1){
        new_count_index = -1;        
        printf("Incorected Error: input index element");
        return 2;
    }   
    for(buffer_index=1;buffer_index<=result_size-1; buffer_index++){
     
        if (abs((buffer[index_element] - buffer[buffer_index])) >  difference ){
            element_far = buffer[buffer_index];
        }
    }
    return element_far;
}
int sum_before(int result_size){
    printf("current element index value: ");
    scanf("%d",&index_element);
    printf("OLD ARRAY: [ ");
    for(buffer_index = 0; buffer_index<=result_size-1; buffer_index++){
        printf("%d ", buffer[buffer_index]);
    }  
    printf("]\n");
    if (index_element > result_size-1){
        new_count_index = -1;
        printf("Incorected Error: input index element");
        return 3;
    }
    for(buffer_index=0;buffer_index<=index_element-1; buffer_index++){
        sum += buffer[buffer_index];
    }  
    return sum;  
}
int small_sum(int result_size){
    printf("current element index value: ");
    scanf("%d",&index_element);
    printf("OLD ARRAY: [ ");
    for(buffer_index = 0; buffer_index<=result_size-1; buffer_index++){
        printf("%d ", buffer[buffer_index]);
    }  
    printf("]\n");
    if (index_element > result_size-1){
        new_count_index = -1;
        printf("Incorected Error: input index element");
        return 4;
    }
    for(buffer_index=0;buffer_index<=result_size-1; buffer_index++){
        if (buffer[buffer_index] < buffer[index_element]){
            sum += buffer[buffer_index];
        }
        else{
            continue;
        }
    }
    return sum;                
}
