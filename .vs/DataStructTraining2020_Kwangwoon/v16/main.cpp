#include "Reservation.h"
#include "Room.h"
#include "dbms.h"
#include <iostream>
using namespace std;

void SystemPrefare();

void DataConnecting();

void ScreenCall();

int main(int argc, char *argv[]) {
    // 1. Setting
    // 2. DataConnecting
    // 3. callScreen
    // 4.

    int selecMenu;

    while (1) {
        printf("1. alarm\n: ");
        scanf("%d", &selecMenu);
        switch (selecMenu) {
        case 1:
            printf("1. how to		2. set alarm\n: ");
            scanf("%d", &selecMenu);
            switch (selecMenu) {
            case 1:
                howToAlarm();
                break;
            case 2:
                alarm_client();
                break;
            }
            break;

        default:
            break;
        }
        printf("\n");
    }
    return 0;
}
