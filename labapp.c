#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addZoomRecord(char *pEmail, char *pName, int pTime, char lab);
//struct ZoomRecord *addNewNode(char *pEmail, char *pName, int pTime, char lab);
//struct ZoomRecord *addNode(struct ZoomRecord *head, struct ZoomRecord *newnode);
void generateAttendance();
struct ZoomRecord;
struct ZoomRecord*head;

int main(int argc, char *argv[])
{
    //%%%%%%%%%%%%%%%%%%%Checking Inputs%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if (argc != 3)
    {
        printf("Usage :  ./labapp labdata.csv attendance.csv\n");
        exit(1);
    }

    FILE *sourceFile = fopen(argv[1], "rt");
    if (sourceFile == NULL)
    {
        printf("Error! Unable to open the input file %s\n", argv[1]);
        exit(1);
    }
    //%%%%%%%%%%%%%%%%%%%%%Checking first line is not empty%%%%%%%%%%%%%%%%%%%%%%%%%%%
    char firstLine[100];
    fgets(firstLine, 100, sourceFile);

    if (strlen(firstLine) <= 6)
    {
        printf("Error! input CSV file %s is empty\n", argv[1]);
        exit(1);
    }

    char secondLine[100];
    fgets(secondLine, 100, sourceFile);
    //printf("This is the line: %s\n", secondLine);
    if (strlen(secondLine) <= 6)
    {
        printf("Error! input CSV file %s is empty\n", argv[1]);
        exit(1);
    }
    //%%%%%%%%%%%%%%%%%%%%%%Parsing First Data Line%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //printf("parsing first line...\n");
    char *secondLineEMAIL = strtok(secondLine, ",");
    char *secondLineNAME = strtok(NULL, ",");
    char *secondLineLAB = strtok(NULL, ",");
    char *secondLineMIN = strtok(NULL, ",");

    //printf("$FIRST LINE$\nEmail: %s, Name: %s, Lab: %s, Minutes: %s\n", secondLineEMAIL,secondLineNAME,secondLineLAB, secondLineMIN);

    addZoomRecord(secondLineEMAIL,secondLineNAME ,atoi(secondLineMIN),secondLineLAB[0]);

    //%%%%%%%%%%%%%%%%%%%%%%%%Parsing the rest of the data%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //printf("parsing the next lines...\n");
    
    char line[200];
    while (fgets(line, 200, sourceFile))
    {
        //printf("This is the line: %s\n", line);
        char *EMAIL = strtok(line, ",");
        char *NAME = strtok(NULL, ",");
        char *LAB = strtok(NULL, ",");
        char *MIN = strtok(NULL, ",");

        //printf("$ANOTHER LINE$\nEmail: %s, Name: %s, Lab: %c, Minutes: %s\n", EMAIL,NAME,LAB[0],MIN);

        addZoomRecord(EMAIL,NAME,atoi(MIN),LAB[0]);
        
    }
    //printf("added all data\n");

    generateAttendance();






}