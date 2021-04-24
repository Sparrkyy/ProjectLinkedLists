#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zoomrecs.h"

struct ZoomRecord;
struct ZoomRecord*head;



//the function that adds a existing node to the right place in the linked list
struct ZoomRecord *addNode(struct ZoomRecord *head, struct ZoomRecord *newnode){
    
    struct ZoomRecord *traversingHead = head;
    //Check if the node should alphabetically go before the head node
    if (strcmp(newnode->email,traversingHead->email)<0){
        newnode->next = head;
        head = newnode;
        return head;
    }
    //If not, go through the list to find the node that next's node is after it. 
    while ( traversingHead->next != NULL){
        if (strcmp(newnode->email,traversingHead->next->email)<0){
            //this means it found the right place in line 
            struct ZoomRecord*temp= traversingHead->next;
            traversingHead->next=newnode;
            newnode->next=temp;
            return head;
        }
        traversingHead=traversingHead->next;
    }
    //If it simply reached the end of the list, then add to the end of the list
    traversingHead->next=newnode;
    return head;
}

//Custom string copy function cause the normal one was causing errors
void StringCopy(char *sender, char *dest)
{
    int i = 0;
    while (sender[i] != '\0')
    {
        dest[i] = sender[i];
        i++;
    }
    dest[i] = '\0';
}

//creates a new node, and returns it
struct ZoomRecord *addNewNode(char *pEmail, char *pName, int pTime, char lab)
{
    //Creating the node and memory checking
    struct ZoomRecord *newnode = malloc(sizeof(struct ZoomRecord));
    if (newnode == NULL)
    {
        printf("Error! program run out of memory");
        exit(1);
    }

    //Copying all the information to the node
    StringCopy(pEmail, newnode->email);
    StringCopy(pName, newnode->name);
    for (int i=0; i<9; i++){
        newnode->durations[i]=0;
    }
    newnode->durations[lab-65] = pTime;
    newnode->next = NULL;
    

    return newnode;
}

void addZoomRecord(char *pEmail, char *pName, int pTime, char pLab){
    struct ZoomRecord *newNode = NULL;
    //If this is the first node to add, then simply add it at the head
    if (head == NULL){
        head = addNewNode(pEmail, pName, pTime, pLab);
        return;
    }
    //Otherwise, look through the list to see if the email already is a node
    struct ZoomRecord* searchingNode = head;
    while ( searchingNode != NULL && strcmp(searchingNode->email,pEmail)){
        searchingNode=searchingNode->next;
        
    }
    //If the node was found, update the lab data.
    if (searchingNode != NULL){
        searchingNode->durations[pLab-65] = searchingNode->durations[pLab-65]+ pTime;
        return;
    }
    //If the node was not found add a new node, and then add that node to the linked list
    if (searchingNode == NULL){
        newNode = addNewNode(pEmail, pName,pTime, pLab);
        head = addNode(head, newNode);
        return;
    }
}
//Generating the attendence in the destignated file 
void generateAttendance(char* DestinationFileName){
    //Opening the file and checking it to see if it could be opened
    FILE *destFile = fopen(DestinationFileName, "wt");
    if (destFile == NULL)
    {
        printf("Error! Unable to open the output file %s\n", DestinationFileName);
        exit(1);
    }
    //Writing all the information to the file
    fprintf(destFile, "User Email,Name (Original Name),A,B,C,D,E,F,G,H,I,Attendance (Percentage)\n");
    struct ZoomRecord *temp=head;
    while ( temp != NULL){
        fprintf(destFile,"%s,", temp->email);
        fprintf(destFile,"%s", temp->name);
        int numOfAttendedLabs=0;
        for (int i=0; i<9; i++){
            fprintf(destFile,",%d",temp->durations[i]);
            if (temp->durations[i]>=45){
                numOfAttendedLabs++;
            }
        }
        float numOfLabs=9;
        float attendancePercentage=numOfAttendedLabs/numOfLabs;
        fprintf(destFile, ",%.2f", attendancePercentage);
        fprintf(destFile,"\n");
        temp=temp->next;
    }
    //Closing the file
    fclose(destFile);
}

//Freeing all the nodes one by one
void freeDynamicMemory(){
    
   struct ZoomRecord* toFree=NULL;

   while (head)
    {
       toFree = head;
       head = head->next;
       free(toFree);
    }
    
}


