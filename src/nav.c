#include <hidapi/hidapi.h>
#include "nav.h"



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

    CommandStruct* commandStruct = getCommandStructFromBuf(handle);

    return 0;
}


CommandStruct* getCommandStructFromBuf(hid_device* handle) {

    unsigned char buf[65];

    buf[0] = 0x01; // First byte is report number

    // Read requested state
    int res = hid_read_timeout(handle, buf, 65, 50);
    int i;

    CommandStruct* commandStruct = (CommandStruct*) malloc(sizeof(CommandStruct));

    if (res < 0) {
        printf("Unable to read()\n");
    }

    // Print out the returned buffer.
    for (i = 0; i < res; i++) {
        printf("buf[%d]: %d\n", i, buf[i]);

        switch (i) {

            case 2 :
                commandStruct->button1 = buf[i];
                break;

        }
    }

    return commandStruct;
}