#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zoomrecs.h"

struct ZoomRecord;
struct ZoomRecord*head;



struct ZoomRecord *addNode(struct ZoomRecord *head, struct ZoomRecord *newnode){
    //printf("Inserting a node: ");
    struct ZoomRecord *traversingHead = head;

    if (strcmp(newnode->email,traversingHead->email)<0){
        //printf("Swapped Right Away\n");
        newnode->next = head;
        head = newnode;
        return head;
    }
    while ( traversingHead->next != NULL){
        if (strcmp(newnode->email,traversingHead->next->email)<0){
            //printf("Found the right place in line\n");
            struct ZoomRecord*temp= traversingHead->next;
            traversingHead->next=newnode;
            newnode->next=temp;
            return head;
        }
        traversingHead=traversingHead->next;
    }
    if (traversingHead->next==NULL){
        //printf("Adding to the end of the line\n");
        traversingHead->next=newnode;
        return head;
    }
    printf("$$$$$$$$$$should not reach here$$$$$$$$$$$$$$$$\n");
    return head;
}

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

struct ZoomRecord *addNewNode(char *pEmail, char *pName, int pTime, char lab)
{
    //printf("Running add new node..\n");
    struct ZoomRecord *newnode = malloc(sizeof(struct ZoomRecord));
    if (newnode == NULL)
    {
        printf("Error! program run out of memory");
        exit(1);
    }
    StringCopy(pEmail, newnode->email);
    StringCopy(pName, newnode->name);
    for (int i=0; i<9; i++){
        newnode->durations[i]=0;
    }
    printf("Adding node, lab: %c, in number: %d, with time: %d\n", lab, (lab-65), pTime);
    newnode->durations[lab-65] = pTime;
    newnode->next = NULL;
    //printf("Making new node with a email of: %s\n", newnode->email);

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
    //printf("searching through nodes\n");
    struct ZoomRecord* searchingNode = head;
    while ( searchingNode != NULL && strcmp(searchingNode->email,pEmail)){
        //printf("This is the email we are looking for: %s, and the one that we are on: %s\n", pEmail, searchingNode->email);
        searchingNode=searchingNode->next;
        
    }
    //If the node was found, update the lab data.
    if (searchingNode != NULL){
        //printf("this is the email of not null: %s\n", searchingNode->email);
        searchingNode->durations[pLab-65] = searchingNode->durations[pLab-65]+ pTime;
        return;
    }
    //If the node was not found 
    if (searchingNode == NULL){
        //printf("this is the email of null: %s\n", searchingNode->email);
        newNode = addNewNode(pEmail, pName,pTime, pLab);
        head = addNode(head, newNode);
        return;
    }
}

void generateAttendance(){
    printf("Testing generateAttendance...\n");
    struct ZoomRecord *temp=head;
    while ( temp != NULL){
        printf("%s", temp->email);
        for (int i=0; i<9; i++){
            printf(",%d",temp->durations[i]);
        }
        printf("\n");
        temp=temp->next;
    }
}


