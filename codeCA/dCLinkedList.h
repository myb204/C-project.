#ifndef UTIL_DCLL_H
#define UTIL_DCLL_H

#include <stdio.h>
#include <stdlib.h>

/*----- structure definition -------------------------------------------------*/
typedef struct LinkedNode {
    char data;
    struct LinkedNode *next;
    struct LinkedNode *prev;
} NODE;

/*----- function prototypes -------------------------------------------------*/
static NODE *newNode(char);
extern void insertNodeAtEnd(NODE **, char);
extern void printLinkedList(NODE *);
extern int lengthLinkedList(NODE *);
extern void emptyLinkedList(NODE **);

#endif
