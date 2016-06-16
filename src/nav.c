#include <hidapi/hidapi.h>
#include <unistd.h>
#include "nav.h"

CommandStruct* commandStruct;

int main(int argc, char* argv[])
{
    int res;
    wchar_t wstr[MAX_STR];
    hid_device *handle;

    // Open the device using the VID, PID,
    handle = hid_open(0x054c, 0x0268, NULL);

    // Read the Manufacturer String
    res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
    printf("Manufacturer String: %ls\n", wstr);

    // Read the Product String
    res = hid_get_product_string(handle, wstr, MAX_STR);
    printf("Product String: %ls\n", wstr);

    // Read the Serial Number String
    res = hid_get_serial_number_string(handle, wstr, MAX_STR);
    printf("Serial Number String: %ls", wstr);
    printf("\n");

    // Set the hid_read() function to be non-blocking.
    hid_set_nonblocking(handle, 1);

    commandStruct = malloc(sizeof(CommandStruct));

    startPolling(handle);

    return 0;
}

void startPolling(hid_device* handle) {

    while (1) {
        navPoll(handle);
    }
}

void navPoll(hid_device* handle) {

    commandStruct = readHidCommands(handle);
    printCommandStruct();
}

void printCommandStruct() {

    printf("Buttons 1 (L3, D-pad) : %d\n", commandStruct->button1);
    printf("Buttons 2 (X, Circle, L1, L2) : %d\n", commandStruct->button2);
    printf("PS button : %d\n", commandStruct->psButton);
    printf("Stick X-axis : %d\n", commandStruct->xAxisStick);
    printf("Stick Y-axis : %d\n", commandStruct->yAxisStick);
    printf("D-pad UP : %d\n", commandStruct->dPadUp);
    printf("D-pad RIGHT : %d\n", commandStruct->dPadRight);
    printf("D-pad DOWN : %d\n", commandStruct->dPadDown);
    printf("D-pad LEFT : %d\n", commandStruct->dPadLeft);
    printf("L2 button value : %d\n", commandStruct->l2);
    printf("L1 button value : %d\n", commandStruct->l1);
    printf("Circle button value : %d\n", commandStruct->circle);
    printf("X button value : %d\n", commandStruct->xButton);
    printf("Battery level : %d\n", commandStruct->battery);

}

CommandStruct* readHidCommands(hid_device* handle) {

    unsigned char buf[65];

    buf[0] = 0x01; // First byte is report number

    // Read requested state
    int res = hid_read_timeout(handle, buf, 65, 50);
    int i;

    if (res < 0) {
        printf("Unable to read()\n");
    }

    // Print out the returned buffer.
    for (i = 0; i < res; i++) {

        switch (i) {

            case 2 :
                commandStruct->button1 = buf[i];
                break;
            case 3 :
                commandStruct->button2 = buf[i];
                break;
            case 4 :
                commandStruct->psButton = buf[i];
                break;
            case 6 :
                commandStruct->xAxisStick = buf[i];
                break;
            case 7 :
                commandStruct->yAxisStick = buf[i];
                break;
            case 14 :
                commandStruct->dPadUp = buf[i];
                break;
            case 15 :
                commandStruct->dPadRight = buf[i];
                break;
            case 16 :
                commandStruct->dPadDown = buf[i];
                break;
            case 17 :
                commandStruct->dPadLeft = buf[i];
                break;
            case 18 :
                commandStruct->l2 = buf[i];
                break;
            case 20 :
                commandStruct->l1 = buf[i];
                break;
            case 23 :
                commandStruct->circle = buf[i];
                break;
            case 24 :
                commandStruct->xButton = buf[i];
                break;
            case 30 :
                commandStruct->battery = buf[i];
                break;

        }
    }

    return commandStruct;
}