#include <stdio.h>
#include <dCLinkedList.h>
 
#define BOOLEAN unsigned char
#define TRUE 1
#define FALSE 0
 
/*----- function prototypes -------------------------------------------------*/
extern void readFromFile(NODE **, char *);
extern void writeToFile(char *, int, BOOLEAN, BOOLEAN);
extern int encodeCharacter(NODE **, char *, char);
extern void calculateTrueEncodeValue(int clockwiseValue, int lengthList, char *fileName, char data);
extern void decodeCharacter(NODE **, char *, int);
extern BOOLEAN validateInteger(char *, int);
