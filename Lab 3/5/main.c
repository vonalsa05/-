#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

enum StatusCodeArguments{
    NO_FILE_PATH_ARGUMENTS_ERROR = 1,   
    NO_TRACE_FILE_PATH_ARGUMENTS_ERROR = 2, 
    TOO_MANY_ARGUMENTS_ERROR = 3,        
};
enum StatusCode{
   OK = 0       
};
enum StatusCodeFile{
    INVALID_COUNT_PARAMETERS_FILE = 4,  
    NULL_IMPORTANCE_ERROR = 5  
};

enum StatusCodeMemory{
    ALLOCATION_MEMORY__READ_FILE_ERROR = 6,    
    ALLOCATION_MEMORY__WRITE_FILE_ERROR = 7,
    INPUT_INCORRECTED_COUNT_ERROR = 8,
    INCORRECTED_INPUT_INFORMATION_ERROR
};


typedef struct Student {
    unsigned id;
    char surname[50];
    char name[50]; 
    char group[50]; 
    unsigned char * assessments;
} Student;
void print_struct(Student *, int);
int compareById(const void *, const void *);
int compareByName(const void *, const void *);
int compareBySurname(const void *, const void *);
int compareByGroup(const void *, const void *);
double student_average_grade(Student);
int input_file_search_id(FILE * , Student);
int search_by_id(Student*, int, int, FILE * );
int check_students_average_rating(Student* , int , FILE *);


int main(int argc, char *argv[]) {

    if (argc == 1) {
        return NO_FILE_PATH_ARGUMENTS_ERROR;
    }


    if (argc > 3) {
        return TOO_MANY_ARGUMENTS_ERROR;
    }



    FILE *file_read, *file_write;

    if ((file_read = fopen(argv[1], "r")) == NULL) {
        return ALLOCATION_MEMORY__READ_FILE_ERROR;
    }




    int count_students= 0;
    Student *students = NULL;

    do {
        Student student; 
        student.assessments = (unsigned char *)malloc(5 * sizeof(unsigned char));  

        if (fscanf(file_read, "id:%u\nsurname:%s\nname:%s\ngroup:%s\nMatematic:%u\nSociety:%u\nRussian language:%u\nEnglish language:%u\ndon net program:%u\n\n",
                &student.id,
                student.surname,
                student.name,
                student.group,
                &student.assessments[0],
                &student.assessments[1],
                &student.assessments[2],
                &student.assessments[3],
                &student.assessments[4]) != 9){
                return INVALID_COUNT_PARAMETERS_FILE;
        }
        
        Student *tempPtr = (Student *) realloc (students,  ++count_students * sizeof(Student) );
        students = tempPtr;
        students[count_students-1] = student;



    } while (!feof(file_read));
    

    print_struct(students, count_students);

    qsort(students, count_students, sizeof(Student), compareById);




    printf("do you need a trace file? (Y/N): ");
    char answer_user[5];
    bool flag_file_output;
    if (scanf("%s",answer_user) != 1){
        return INPUT_INCORRECTED_COUNT_ERROR;
    }
    else{
        if ((strcmp(answer_user,"Yes") == 0) 
        || (strcmp(answer_user,"yes") == 0) 
        || (strcmp(answer_user,"Y") == 0) 
        || (strcmp(answer_user,"y") == 0)){

            if (argc == 2){
                return NO_TRACE_FILE_PATH_ARGUMENTS_ERROR;       
            }
            flag_file_output = true;
        }
        else if ((strcmp(answer_user,"No") == 0) 
                || (strcmp(answer_user,"no") == 0) 
                || (strcmp(answer_user,"NO") == 0) 
                || (strcmp(answer_user,"N") == 0)
                || (strcmp(answer_user,"n") == 0)){
            flag_file_output = false;
            //Well, we have processed this case, but it does not have an implementation.
        }
        else{
            return INCORRECTED_INPUT_INFORMATION_ERROR;
        }
    }   
    if (flag_file_output){
        if ((file_write = fopen(argv[2], "w")) == NULL) {
            return ALLOCATION_MEMORY__WRITE_FILE_ERROR;
        }  
    }






    printf("do you need to search for user by id?(Y/N): ");

    if (scanf("%s",answer_user) == 1){
        if ((strcmp(answer_user,"Yes") == 0) 
                || (strcmp(answer_user,"yes") == 0) 
                || (strcmp(answer_user,"YES") == 0) 
                || (strcmp(answer_user,"Y") == 0)
                || (strcmp(answer_user,"y") == 0)){

                    printf("enter the id of the student you want to find: ");

                    int search_id_input = 0;
                    switch(scanf("%d",&search_id_input)){
                        case 1:
                            if(search_by_id(students, count_students, search_id_input, file_write)) {return 11;};
                            break;
                        default:
                            return INPUT_INCORRECTED_COUNT_ERROR;
                    }

                    
                }
                else if ((strcmp(answer_user,"No") == 0) 
                || (strcmp(answer_user,"no") == 0) 
                || (strcmp(answer_user,"NO") == 0) 
                || (strcmp(answer_user,"N") == 0)
                || (strcmp(answer_user,"n") == 0)){
                    //basically nothing happens
                }
                else{
                    return INPUT_INCORRECTED_COUNT_ERROR;
                }

    }
    else{
        return INPUT_INCORRECTED_COUNT_ERROR;
    }

    
    printf("Should you display students whose average score is higher than the average score of all students?(Y/N): ");

    if (scanf("%s",answer_user) == 1){
        if ((strcmp(answer_user,"Yes") == 0) 
            || (strcmp(answer_user,"yes") == 0) 
            || (strcmp(answer_user,"YES") == 0) 
            || (strcmp(answer_user,"Y") == 0)
            || (strcmp(answer_user,"y") == 0)){
                    if(check_students_average_rating(students, count_students, file_write)) {return 12;};

                    
                }
                else if ((strcmp(answer_user,"No") == 0) 
                || (strcmp(answer_user,"no") == 0) 
                || (strcmp(answer_user,"NO") == 0) 
                || (strcmp(answer_user,"N") == 0)
                || (strcmp(answer_user,"n") == 0)){
                    //basically nothing happens
                }
                else{
                    return INPUT_INCORRECTED_COUNT_ERROR;
                }

    }
    else{
        return INPUT_INCORRECTED_COUNT_ERROR;
    }


    print_struct(students, count_students);



    return OK;
}
int readStudents(FILE *file, Student **students, int *count_students){
    do {
        Student student;
        student.assessments = (unsigned char *)malloc(5 * sizeof(unsigned char));
        if (fscanf(file, "id:%u\nsurname:%s\nname:%s\ngroup:%s\nMatematic:%u\nSociety:%u\nRussian language:%u\nEnglish language:%u\ndon net program:%u\n\n",
            &student.id,
            student.surname,
            student.name,
            student.group,
            &student.assessments[0],
            &student.assessments[1],
            &student.assessments[2],
            &student.assessments[3],
            &student.assessments[4]) != 9) {
            return INVALID_COUNT_PARAMETERS_FILE;
        }

        Student *tempPtr = (Student *)realloc(*students, ++*count_students * sizeof(Student));
        *students = tempPtr;
        (*students)[*count_students - 1] = student;
    } while (!feof(file));

    return OK;    
}
int compareById(const void *a, const void *b) {
   return ((Student *)a)->id - ((Student *)b)->id ;
}
int compareByName(const void *a, const void *b) {
   return ((Student *)a)->name - ((Student *)b)->name ;
}
int compareBySurname(const void *a, const void *b) {
   return strcmp( ((Student *)a)->surname,((Student *)b)->surname ) ;
}
int compareByGroup(const void *a, const void *b) {
   return strcmp( ((Student *)a)->group,((Student *)b)->group ) ;
}
double student_average_grade(Student student_parameters){
    double sum_students_grade = 0;
    for (int j = 0; j < 5; j++){
        sum_students_grade += (double) student_parameters.assessments[j];
    }
    sum_students_grade /= 5.0;
    return sum_students_grade;
}
int input_file_search_id(FILE * output_file, Student students_parameters){

    printf("do i need to output the data of the found user to a file?(Y/N): ");
    char answer[5];

    if(scanf("%s",answer) == 1){
       if ((strcmp(answer,"Yes") == 0) 
        || (strcmp(answer,"yes") == 0) 
        || (strcmp(answer,"Y") == 0) 
        || (strcmp(answer,"y") == 0)){

            fprintf(output_file, "data of the found id:\n\n");
            fprintf(output_file, "search id:%u\nsurname:%s\nname:%s\ngroup:%s\naverage grade:%f\n\n", students_parameters.id, students_parameters.surname, students_parameters.name, students_parameters.group,student_average_grade(students_parameters));                               

        }
        else if ((strcmp(answer,"No") == 0) 
                || (strcmp(answer,"no") == 0) 
                || (strcmp(answer,"NO") == 0) 
                || (strcmp(answer,"N") == 0)
                || (strcmp(answer,"n") == 0)){

            printf("\ndata of the found id:\n\n");
            printf("search id:%u\nsurname:%s\nname:%s\ngroup:%s\naverage grade:%f\n\n", students_parameters.id, students_parameters.surname, students_parameters.name, students_parameters.group,student_average_grade(students_parameters));                               

        }
        else{
            return INCORRECTED_INPUT_INFORMATION_ERROR;
        }

    }
    else{
        return INPUT_INCORRECTED_COUNT_ERROR;
    }

    return OK;

     
}
int search_by_id(Student* students, int n, int search_id, FILE * output) {
    if (output == NULL){
        return NULL_IMPORTANCE_ERROR;
    }

    for (int i = 0; i < n; i++) {
        if (students[i].id == search_id) {

            if (input_file_search_id(output,students[i]) ){
                return 10;
            }
            return OK;
        }

    }
    printf("Not found id student\n");
    return OK;
} 
int check_students_average_rating(Student* students, int n, FILE * output){

    if (output == NULL){
        return NULL_IMPORTANCE_ERROR;
    }
    


    double sum_average_rating = 0;
    for (int i = 0; i < n; i++) { sum_average_rating += student_average_grade(students[i]);}
    sum_average_rating /= (double) n;
    
    printf("do i need to output the data of the found user to a file?(Y/N): ");
    char answer[5];
    bool flag_file_cout;
    if(scanf("%s",answer) == 1){
       if ((strcmp(answer,"Yes") == 0) 
        || (strcmp(answer,"yes") == 0) 
        || (strcmp(answer,"Y") == 0) 
        || (strcmp(answer,"y") == 0)){
            flag_file_cout = true;
        }
        else if ((strcmp(answer,"No") == 0) 
                || (strcmp(answer,"no") == 0) 
                || (strcmp(answer,"NO") == 0) 
                || (strcmp(answer,"N") == 0)
                || (strcmp(answer,"n") == 0)){

            flag_file_cout = false;
        }
        else{
            return INCORRECTED_INPUT_INFORMATION_ERROR;
        }

    }
    else{
        return INPUT_INCORRECTED_COUNT_ERROR;
    }
    if (flag_file_cout){
        fprintf(output, "last name and first name of the student whose average score is higher than the average grade-rating:\n");
    }
    else{
        printf( "\nlast name and first name of the student whose average score is higher than the average grade-rating:\n");
    }
    for (int i = 0; i < n; i++) {
        double sum_average_grade = student_average_grade(students[i]);
        if ( sum_average_rating < sum_average_grade ){
            if (flag_file_cout){
                fprintf(output, "\nsurname:%s\nname:%s\naverage grade:%f\n",students[i].surname, students[i].name, sum_average_grade);
            }
            else{
                printf( "\nsurname:%s\nname:%s\naverage grade:%f\n",students[i].surname, students[i].name, sum_average_grade);
            }
            
        }
        
    }

    return OK;

}
void print_struct(Student *struct_students, int count_st){
    for (int i = 0; i < count_st; i++){
    printf("%u ",struct_students[i].id);
    printf("%s ",struct_students[i].surname);
    printf("%s ",struct_students[i].name);
    printf("%s ",struct_students[i].group);
    for (int j = 0; j < 5; j++){
        printf("%u ",struct_students[i].assessments[j] );
    }
    printf("\n");
    }
}