/*************************************
 * Walter J. Galan
 * 915753857
 * wgalan@mail.sfsu.edu
 * Clang compiler v(700.1.81)
 *************************************/

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

const int NUMENTRIES = 7;
const int PASSGRADE = 50.0;
const int READDATA = 1;
const int EXIT = 2;

typedef struct {
 char name[50];
 int id;
 double subject_a;
 double subject_b;
 bool pass;
} student;

void display_menu();
void read_file(FILE *ptr, student *students);
student ascending_order(student *students);
double calculate_average_sub_a(student *students);
double calculate_average_sub_b(student *students);
double calculate_standard_deviation_sub_a(student *students);
double calculate_standard_deviation_sub_b(student *students);
void write_file(FILE *ptr, student *students, student temp_ascend, double sub_a_aver, double sub_b_aver, double sub_a_stand_dev, double sub_b_stand_dev);

int main(int argc, const char * argv[]) {
 
 student students[NUMENTRIES];
 student temp_ascending;
 
 int choice;
 
 double subject_a_average;
 double subject_b_average;
 double subject_a_standard_dev;
 double subject_b_standard_dev;
 
 FILE *ptr_file;
 
 display_menu();
 
 printf("\n");
 
 scanf(" %d", &choice);
 
 printf("\n");
 
 while (choice != EXIT) {
  
  switch (choice) {
   case READDATA:
    read_file(ptr_file, students);
    
    temp_ascending = ascending_order(students);
    
    // Calculate Average Subject A
    subject_a_average = calculate_average_sub_a(students);
    
    // Calculate Average Subject B
    subject_b_average = calculate_average_sub_b(students);
    
    // Calculate Standard Deviation Subject A
    subject_a_standard_dev = calculate_standard_deviation_sub_a(students);
    
    // Calculate Standard Deviation Subject B
    subject_b_standard_dev = calculate_standard_deviation_sub_b(students);
    
    write_file(ptr_file, students, temp_ascending, subject_a_average, subject_b_average, subject_a_standard_dev, subject_b_standard_dev);
    
    printf("\n");
    printf("\n");
    
    // Clear struct
    memset(students, 0, sizeof(students));
    
    display_menu();
    printf("\n");
    scanf(" %d", &choice);
    break;
    
   case EXIT:
    return 0;
    break;
    
   default:
    return 0;
    break;
  }
 }
 return 0;
}

void display_menu() {
 
 printf("*******************************\n");
 printf("*      Select an option:      *\n");
 printf("*******************************\n");
 printf("*    1. Read data from file   *\n");
 printf("*    2. Exit                  *\n");
 printf("*******************************\n");
 printf("\n");
 printf("Enter your selection: ");

}

void read_file(FILE *ptr, student *students) {

 int i;
 
 ptr = fopen("data.txt","r");
 
 for (i = 0; i < NUMENTRIES ; i++) {
  
  fscanf(ptr, "%s %d %lf %lf", students[i].name, &students[i].id, &students[i].subject_a, &students[i].subject_b);
  
  // Determine if student receives diploma
  if (((students[i].subject_a) >= PASSGRADE) && (students[i].subject_b) >= PASSGRADE) {
   students[i].pass = true;
  }
 }
 
 fclose(ptr);
}

student ascending_order(student *students) {
 
 int i, j;
 
 student temp;
 
 for (i = 0; i < NUMENTRIES; i++) {
  for (j = 0; j < NUMENTRIES; j++) {
   if (students[i].subject_a < students[j].subject_a) {
    temp = students[i];
    students[i] = students[j];
    students[j] = temp;
   }
  }
 }
 
 return *students;
}

double calculate_average_sub_a(student *students) {

 int i;
 double sum_subject_a = 0;
 double average_subject_a;
 
 for(i = 0; i < NUMENTRIES; i++) {
  
  sum_subject_a += students[i].subject_a;
 }
 
 average_subject_a = (sum_subject_a) / NUMENTRIES;
 
 return average_subject_a;
}

double calculate_average_sub_b(student *students) {
 
 int i;
 double sum_subject_b = 0;
 double average_subject_b;
 
 for(i = 0; i < NUMENTRIES; i++) {
  
  sum_subject_b += students[i].subject_b;
 }
 
 average_subject_b = sum_subject_b/NUMENTRIES;
 
 return average_subject_b;
}

double calculate_standard_deviation_sub_a(student *students) {
 
 int i;
 double mean_subject_a = 0;
 double sum_deviation_subject_a = 0;
 double square_deviation_subject_a = 0;
 
 for(i=0; i < NUMENTRIES; i++) {
  
  mean_subject_a += students[i].subject_a;
 }
 
 mean_subject_a = mean_subject_a / NUMENTRIES;
 
 for(i=0; i < NUMENTRIES; i++) {
  
  sum_deviation_subject_a += (students[i].subject_a - mean_subject_a) * (students[i].subject_a - mean_subject_a);
 }
 
 square_deviation_subject_a = sqrt(sum_deviation_subject_a / NUMENTRIES);
 
 return square_deviation_subject_a;
}

double calculate_standard_deviation_sub_b(student *students) {
 
 int i;
 double mean_subject_b = 0;
 double sum_deviation_subject_b = 0;
 double square_deviation_subject_b = 0;
 
 for(i=0; i < NUMENTRIES; i++) {
  
  mean_subject_b += students[i].subject_b;
 }
 
 mean_subject_b = mean_subject_b / NUMENTRIES;
 
 for(i=0; i < NUMENTRIES; i++) {
  sum_deviation_subject_b += (students[i].subject_b - mean_subject_b) * (students[i].subject_b - mean_subject_b);
 }
 
 square_deviation_subject_b = sqrt(sum_deviation_subject_b / NUMENTRIES);
 
 return square_deviation_subject_b;
}

void write_file(FILE *ptr, student *students, student temp_ascend, double sub_a_aver, double sub_b_aver, double sub_a_stand_dev, double sub_b_stand_dev) {
 
 int i;
 
 //Write to file "output.txt"
 ptr = fopen("output.txt","w");
 
 for (i = 0; i < NUMENTRIES; i++) {
  if (students[i].pass == true) {
  
   printf("Pass or Fail: Pass\n");
   fprintf(ptr, "Pass or Fail: Pass\n");
   
   printf("ID: %d\n", students[i].id);
   fprintf(ptr, "ID: %d\n", students[i].id);
   
   printf("Name: %s\n", students[i].name);
   fprintf(ptr, "Name: %s\n", students[i].name);
   
   printf("Subject A: %.1lf\n",students[i].subject_a);
   fprintf(ptr, "Subject A: %.1lf\n",students[i].subject_a);
   
   printf("Subject B: %.1lf\n",students[i].subject_b);
   fprintf(ptr, "Subject B: %.1lf\n",students[i].subject_b);
   
   printf("\n");
   fprintf(ptr, "\n");
  }
 }
 
 temp_ascend = ascending_order(students);
 
 printf("In Ascending Order by Subject A: \n");
 fprintf(ptr, "In Ascending Order by Subject A: \n");
 
 for(i=0; i < NUMENTRIES; i++) {
  printf("Subject A: %.1lf, Name: %s, ID: %d, Subject B: %.1lf\n",students[i].subject_a, students[i].name, students[i].id, students[i].subject_b);
  fprintf(ptr, "Subject A: %.1lf, Name: %s, ID: %d, Subject B: %.1lf\n",students[i].subject_a, students[i].name, students[i].id, students[i].subject_b);
 }
 
 printf("\n");
 fprintf(ptr, "\n");
 
 printf("Average Subject A: %.1lf\n",sub_a_aver);
 fprintf(ptr, "Average Subject A: %.1lf\n",sub_a_aver);
 
 printf("Average Subject B: %.1lf\n",sub_b_aver);
 fprintf(ptr, "Average Subject B: %.1lf\n",sub_b_aver);
 
 printf("\n");
 fprintf(ptr, "\n");
 
 printf("Standard Deviation Subject A: %.1lf\n",sub_a_stand_dev);
 fprintf(ptr, "Standard Deviation Subject A: %.1lf\n",sub_a_stand_dev);
 
 printf("Standard Deviation Subject B: %.1lf\n",sub_b_stand_dev);
 fprintf(ptr, "Standard Deviation Subject B: %.1lf\n",sub_b_stand_dev);
 
 
 fclose(ptr);
}