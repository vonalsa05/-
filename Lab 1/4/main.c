#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>


FILE * file_row_three;
int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Enter file name in arguments console command");
        return 1;
    } 
    if ((file_row_three = fopen(argv[1],"r")) == NULL){
        printf("Invalid reading file");
        return 2;
    }  
    char c;int max_count_string = -1;  
    while((c=getc(file_row_three)) != EOF){
        int count = 0;
        while (c != '\n'){
            ++count;
            c = getc(file_row_three);
        }
        if (count >= max_count_string ){
            max_count_string = count;
        }
    }  
    rewind(file_row_three);
    FILE * outputFile = fopen("output.txt", "w");
    char strings[max_count_string+2];
    char first[max_count_string+2];
    char second[max_count_string+2];
    char third[max_count_string+2];
    while(fgets(strings, sizeof(strings), file_row_three) != NULL){
        sscanf(strings, "%s %s %s", first,second,third);
        fprintf(outputFile, "%s %s %s\n", third,first,second);
    }


    fclose(file_row_three);
    fclose(outputFile);
    
}
