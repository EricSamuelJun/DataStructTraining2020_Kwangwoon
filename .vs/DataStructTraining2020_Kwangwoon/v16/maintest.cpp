#include <stdio.h>

void maintest(){
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
                break;
            }
            break;

        default:
            break;
        }
        printf("\n");
    }
}
