#include <stdio.h>

void delay(int ms) {
    for (int i = 0; i < 50000000; ++i) {
        for (int j = 0; i < ms; ++j) {
        }
    }
}

int task_key_scan() {
    int key_value;
    printf("keyboard sacn...\n");
    return key_value;
}

void task_led_show() { printf("led show...\n"); }

void task_temperature_get() { printf("DB185S20 init...\n"); }

void task_temperature_set() { printf("set temperature...\n"); }

int main() {

    while (1) {
        task_temperature_get();
        delay(100);
        task_led_show();
        delay(100);
        task_key_scan();
        delay(100);
        task_temperature_set();
        delay(100);
        printf("\n\n");
    }

    return 0;
}
