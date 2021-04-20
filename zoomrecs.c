#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zoomrecs.h"

struct ZoomRecord;
struct ZoomRecord*head;

void printLinkedList(){
    struct ZoomRecord *temp=head;
    while ( temp != NULL){
        printf("Here is the email: %s\n", temp->email);
        temp=temp->next;
    }
}

struct ZoomRecord *addNode(struct ZoomRecord *head, struct ZoomRecord *newnode){
    newnode->next = head;
    head = newnode;
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
    printf("Running add new node..\n");
    struct ZoomRecord *newnode = malloc(sizeof(struct ZoomRecord));
    if (newnode == NULL)
    {
        printf("Error! program run out of memory");
        exit(1);
    }
    StringCopy(pEmail, newnode->email);
    StringCopy(pName, newnode->name);
    newnode->durations[lab-65] = pTime;
    newnode->next = NULL;
    //printf("Making new node with a email of: %s\n", newnode->email);

    return newnode;
}

struct ZoomRecord *addZoomRecord(char *pEmail, char *pName, int pTime, char lab){
    printf("Running addZoomRecord...\n");
    struct ZoomRecord*traversingNode = head;
    while ( traversingNode->next != NULL || traversingNode->email != pEmail ){
        traversingNode=traversingNode->next;
    }
    if (traversingNode == NULL){
        head = addNewNode(pEmail,pName,pTime,lab);
    }

    return NULL;
}

void generateAttendance(){
    printf("Testing generateAttendance...\n");
}


