#include <stdio.h>
#include "device_manager.h"

int sd_read() {
    printf("sd read data...\n");
    return 10;
}

int udisk_read() {
    printf("udisk read data...\n");
    return 20;
}

struct storage_device sd = {"sdcard", sd_read};
struct storage_device udisk = {"udisk", udisk_read};

int main() {

    register_device(sd);
    register_device(udisk);

    read_device("udisk");
    read_device("udisk");
    read_device("uk");
    read_device("sdcard");
    read_device("sdcard");

    return 0;
}
