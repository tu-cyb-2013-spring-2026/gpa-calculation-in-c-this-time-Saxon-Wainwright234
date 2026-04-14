#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>


void convertToUpper(char str[]){
    int i = 0;
    while(str[i] != '\0'){
        str[i] = toupper((unsigned char)str[i]);
        i++;
    }
}

float gradeToPoint(char upperGrade[]){
    convertToUpper(upperGrade);
    if (strcmp(upperGrade, "A") == 0){
        return 4.0;
    }
    else if (strcmp(upperGrade, "B") == 0)
    {
        return 3.0;
    }
    else if (strcmp(upperGrade, "C") == 0)
    {
        return 2.0;
    }
    else if (strcmp(upperGrade, "D") == 0)
    {
        return 1.0;
    }
    else if (strcmp(upperGrade, "F") == 0)
    {
        return 0.0;
    }
    else
    {
        printf("error one of your entered grades isnt a true grade try again");
    }
    
    

}


int main(){
    int going = 1;
    
    printf("Enter your grades in format of 'grade' 'hours' 'semester' 'year' ex: A 3 FALL 2025\n");
    printf("In order to get result enter 'break'\n");
    typedef struct{
        char grade[2];
        int hours;
        char semester[10];
        int year;
    } Cource;
    
    int count = 0;
    Cource courses[100];
    
    
    while (going == 1)
    {
        char formatGrades[50];
        printf("enter your grades in that format: ");
        fgets(formatGrades, sizeof(formatGrades), stdin);
        if (strcmp(formatGrades, "break\n") == 0){
            going = 0;
            break;
        }

        char * grade = strtok(formatGrades, " ");
        char * hours = strtok(NULL, " ");
        char * semester = strtok(NULL, " ");
        char * year = strtok(NULL, " ");

        if (year == NULL || atoi(year) > 2026){
            printf("that wasnt a valid answer please rerun and try again\n");
            continue;

        }


        strcpy(courses[count].grade, grade);
        courses[count].hours = atoi(hours);
        strcpy(courses[count].semester, semester);
        courses[count].year = atoi(year);
        count++;
        
    }
     int totalTotalHours = 0;
    float totalTotalPoint = 0.0;
    printf("Unoffical Transcript ----------------------------------\n");
    int seen[100]={0};
    int length = sizeof(seen) / sizeof(seen[0]);
    for (int i = 0; i < count; i++) {
        if (seen[i] == 0){
            seen[i] = 1;
            int totalhours = courses[i].hours;
            float totalPoints = gradeToPoint(courses[i].grade) * courses[i].hours;

            for(int j = i+1; j<count; j++){
                if (courses[j].year == courses[i].year && strcmp(courses[j].semester, courses[i].semester) ==0){
                    seen[j] = 1;
                    totalhours = totalhours + courses[j].hours;
                    totalPoints = totalPoints + (gradeToPoint(courses[j].grade) * courses[j].hours);
                }
        
        }
        totalTotalHours = totalTotalHours + totalhours;
        totalTotalPoint = totalTotalPoint + totalPoints;
        printf("%s %d (%d hours) %.3f\n", courses[i].semester, courses[i].year, totalhours, totalPoints / totalhours);
        



    }
    
    }
    printf("---------\n");
    printf("%d total hours \n",totalTotalHours);
    if (totalTotalPoint == 0){
        printf("You havent entered any grade");
        abort();

    }

    printf("%.3f final gpa", totalTotalPoint/totalTotalHours);
    return 0;
}