#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <hidapi.h>

#define MAX_STR 255


typedef struct CommandStruct CommandStruct;
struct CommandStruct
{
    unsigned char button1;
    unsigned char button2;
    unsigned char psButton;
    unsigned char xAxisStick;
    unsigned char yAxisStick;
    unsigned char dPadUp;
    unsigned char dPadRight;
    unsigned char dPadDown;
    unsigned char dPadLeft;
    unsigned char l1;
    unsigned char l2;
    unsigned char circle;
    unsigned char xButton;
    unsigned char battery;
};

CommandStruct* readHidCommands(unsigned char buf[], int res);

unsigned char readHid();

void printCommandStruct();
