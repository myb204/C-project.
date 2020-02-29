#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <codeMessage.h>
 
/* read from a file specified by a file name*/
extern void readFromFile(NODE **headNode, char *fileName){
 
    FILE *fp;
    char ch;
 
    if ((fp = fopen(fileName, "r")) == NULL)
    {
        printf("Unable to open file for read access.\n");
        fprintf(stderr, "Error %d: %s\n", errno, strerror(errno));
        exit(1);
    }
 
    while (!feof(fp))
    {
        ch = fgetc(fp);
        if (ch != 10 && ch != -1) {
            insertNodeAtEnd(headNode, ch);
        }
    }
 
    fclose(fp);
}
 
/* write to a file specified by a file name*/
extern void writeToFile(char *fileName, int ch, BOOLEAN clearFile, BOOLEAN decoder){
 
    FILE *fp;
 
    if (clearFile){
        fp = fopen(fileName, "w");
        return;
    } else {
        fp = fopen(fileName, "a");
    }
 
    if (fp == NULL){
        printf("Unable to write to file.\n");
        fprintf(stderr, "Error %d: %s\n", errno, strerror(errno));
        exit(1);
    }
 
    if (decoder){
        fprintf(fp, "%c", ch);
    } else {
        fprintf(fp, "%d\n", ch);
    }
    fclose(fp);
}
 
/* return a clockwise distance value for a node from the current head node*/
extern int encodeCharacter(NODE **headNode, char *fileName, char data){
 
    int posMoved = 0;
    BOOLEAN nodeFound = FALSE;
    NODE *tempNode = *headNode;
 
    do{
        if (tempNode->data != data) {
            tempNode = tempNode->next;
            posMoved++;
        } else {
            nodeFound = TRUE;
            break;
        }
    } while (tempNode != *headNode);
 
    if (nodeFound) {
        *headNode = tempNode;
    } else {
        writeToFile(fileName, 0, TRUE, FALSE);
        printf("Node %c could not be found.\n", data);
        fprintf(stderr, "Error: Node %c could not be found\n", data);
        exit(1);
    }
    return posMoved;
}
 
/* calculate the true value for encoding the node */
extern void calculateTrueEncodeValue(int clockwiseValue, int lengthList, char *fileName, char data){
 
        int anticlockwiseValue;
        anticlockwiseValue = (clockwiseValue - lengthList);
 
        if (abs(clockwiseValue)>abs(anticlockwiseValue)){
            printf("Character: %c, Value: %+d\n", data, anticlockwiseValue);
            writeToFile(fileName, anticlockwiseValue, FALSE, FALSE);
        } else {
            printf("Character: %c, Value: %+d\n", data, clockwiseValue);
            writeToFile(fileName, clockwiseValue, FALSE, FALSE);
        }
}
 
/* locate the node at the position directed by the value argument*/
extern void decodeCharacter(NODE **headNode, char *fileName, int value){
 
    int i;
    NODE *currNode = *headNode;
 
    if (value >= 0){
        for(i = 0; i < value; i++){
        currNode = currNode->next;
        }
        printf("Value: %+d, Character: %c\n", value, currNode->data);
    } else {
        for(i = 0; i > value; i--){
        currNode = currNode->prev;
        }
        printf("Value: %+d, Character: %c\n", value, currNode->data);
    }
    writeToFile(fileName, currNode->data, FALSE, TRUE);
    *headNode = currNode;
}
 
/* check if the argument is a positive or negative integer*/
extern BOOLEAN validateInteger(char *argPointer, int argc){
 
    int i;
    for(i = 0; i<strlen(argPointer); i++){
        if (i == 0 && argPointer[i] == '-'){
            continue;
        } else {
           if (argPointer[i] > 47 && argPointer[i] < 57){
                continue;
            } else {
                return FALSE;
            }
        }
    }
    return TRUE;
}
 
int main(int argc, char **argv){
 
    NODE *headNode = NULL;
 
    if (argc <= 4){
        printf("Insufficient parameters.\n");
        fprintf(stderr, "Insufficient parameters provided. Please read documentation.\n");
        exit(1);
    }
 
    int arguments;
    printf("Parameter listing:\n");
    for (arguments = 1; arguments < argc; arguments++){
        printf("%3d: %s\n", arguments, argv[arguments]);
    }
 
    readFromFile(&headNode, argv[1]);
    printf("\nCoding wheel values:\n");
    printf("  ");
    printLinkedList(headNode);
    writeToFile(argv[2], 0, TRUE, FALSE);
 
    int i;
    if (*argv[3] == 'D'){
        char *argPointer;
        printf("\nDecoding values...\n");
        for(i = 4; i<argc ; i++){
            argPointer = argv[i];
            if (validateInteger(argPointer, argc)){
                decodeCharacter(&headNode, argv[2], atoi(argv[i]));
            } else {
                printf("Invalid decode parameter.\n");
                fprintf(stderr, "Invalid decode value: %s\n", argPointer);
                writeToFile(argv[2], 0, TRUE, FALSE);
                exit(1);
            }
        }
    } else if (*argv[3] == 'C') {
        printf("\nEncoding values... \n");
        char *argMessage = argv[4];
        int clockwiseValue;
        int lengthList = lengthLinkedList(headNode);
 
        for(i = 0; i<strlen(argMessage); i++){
            clockwiseValue = encodeCharacter(&headNode, argv[2], argMessage[i]);
            calculateTrueEncodeValue(clockwiseValue, lengthList, argv[2], argMessage[i]);
        }
    } else {
        printf("Invalid decode/encode parameter.\n");
        fprintf(stderr, "Error: Invalid decode/encode parameter.\n");
        exit(1);
    }
 
    emptyLinkedList(&headNode);
    return 0;
}
