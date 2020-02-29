#include <dCLinkedList.h>
#include <stdlib.h>

/* dynamically create a new node and return a pointer to it*/
static NODE *newNode(char data){
    NODE *tempNode = (NODE*)malloc(sizeof(NODE));

    if (tempNode == NULL)
    {
        fprintf(stderr,"Not enough memory: line %d, file %s\n.", __LINE__, __FILE__);
        exit(-1);
    }

    tempNode->data = data;
    tempNode->prev = NULL;
    tempNode->next = NULL;
    return tempNode;
}

/* insert a node at the end of the doubly circualar linked list*/
extern void insertNodeAtEnd(NODE **headNode, char data){
    if (*headNode == NULL)
    {
        NODE *tempNode = newNode(data);
        tempNode->next = tempNode->prev = tempNode;
        *headNode = tempNode;
        return;
    }

    NODE *last = (*headNode)->prev;
    NODE *tempNode = newNode(data);

    tempNode->next = *headNode;
    (*headNode)->prev = tempNode;
    tempNode->prev = last;
    last->next = tempNode;
}

/* print the contents of the doubly circular linked list*/
extern void printLinkedList(NODE *headNode){

    if (headNode == NULL){
        printf("\n");
        return;
    }

    NODE *tempNode = headNode;

    while (tempNode->next != headNode) {
        printf("%c", tempNode->data);
        tempNode = tempNode->next;
    }
    printf("%c\n", tempNode->data);
}

/* return the length of the doubly circular linked list*/
extern int lengthLinkedList(NODE *headNode){
    int sizeCounter = 1;
    NODE *tempNode = headNode;

    while (tempNode->next != headNode) {
        sizeCounter++;
        tempNode = tempNode->next;
    }
    return sizeCounter;
}

/* empty all nodes in the doubly circular linked list*/
extern void emptyLinkedList(NODE **headNode){

    while(*headNode != NULL){

        NODE *currNode = *headNode;
        NODE *prevNode = (*headNode)->prev;

        if (currNode->next==(*headNode) && prevNode==(*headNode)){
            (*headNode) = NULL;
            free(currNode);
            return;
        }

        *headNode = (*headNode)->next;
        prevNode->next = *headNode;
        (*headNode)->prev = prevNode;
        free(currNode);
    }
}
