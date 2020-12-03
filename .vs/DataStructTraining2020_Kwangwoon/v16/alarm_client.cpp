#include "MyMsg.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <vector>
using namespace std;

key_t mykey = 0;
int msqid = 0;

int alarm_client() {
    MsgTime msgTime;
    MsgRslt msgRslt;
    pid_t pid;
    int choice = 0, enu = 0, month = 0;

    mykey = ftok("mykey", 1);                // 키 생성
    msqid = msgget(mykey, IPC_CREAT | 0644); // 메시지 큐 생성

    memset(&msgTime, 0x00, sizeof(MsgTime));
    msgTime.mtype = MSG_TYPE_TIME;

    printf("<<< ");
    scanf("%2d %2d %2d %2d %3d %1d", &month, &(msgTime.time.date),
          &(msgTime.time.hour), &(msgTime.time.minute), &(msgTime.room),
          &(enu));
    switch (month) {
    case 1:
        msgTime.time.mon[0] = 'J';
        msgTime.time.mon[1] = 'a';
        msgTime.time.mon[2] = 'n';
        break;
    case 2:
        msgTime.time.mon[0] = 'F';
        msgTime.time.mon[1] = 'e';
        msgTime.time.mon[2] = 'b';
        break;
    case 3:
        msgTime.time.mon[0] = 'M';
        msgTime.time.mon[1] = 'a';
        msgTime.time.mon[2] = 'r';
        break;
    case 4:
        msgTime.time.mon[0] = 'A';
        msgTime.time.mon[1] = 'p';
        msgTime.time.mon[2] = 'r';
        break;
    case 5:
        msgTime.time.mon[0] = 'M';
        msgTime.time.mon[1] = 'a';
        msgTime.time.mon[2] = 'y';
        break;
    case 6:
        msgTime.time.mon[0] = 'J';
        msgTime.time.mon[1] = 'u';
        msgTime.time.mon[2] = 'n';
        break;
    case 7:
        msgTime.time.mon[0] = 'J';
        msgTime.time.mon[1] = 'u';
        msgTime.time.mon[2] = 'l';
        break;
    case 8:
        msgTime.time.mon[0] = 'A';
        msgTime.time.mon[1] = 'u';
        msgTime.time.mon[2] = 'g';
        break;
    case 9:
        msgTime.time.mon[0] = 'S';
        msgTime.time.mon[1] = 'e';
        msgTime.time.mon[2] = 'p';
        break;
    case 10:
        msgTime.time.mon[0] = 'O';
        msgTime.time.mon[1] = 'c';
        msgTime.time.mon[2] = 't';
        break;
    case 11:
        msgTime.time.mon[0] = 'N';
        msgTime.time.mon[1] = 'o';
        msgTime.time.mon[2] = 'v';
        break;
    case 12:
        msgTime.time.mon[0] = 'D';
        msgTime.time.mon[1] = 'e';
        msgTime.time.mon[2] = 'c';
        break;
    default:
        return -1;
        break;
    }
    switch (enu) {
    case 0:
        msgTime.num = breakfast;
        break;
    case 1:
        msgTime.num = lunch;
        break;
    case 2:
        msgTime.num = dinner;
        break;
    case 3:
        msgTime.num = checkout;
        break;
    case 4:
        msgTime.num = awake;
        break;
    default:
        msgTime.num = nothing;
        break;
    }

    msgsnd(msqid, &msgTime, MSG_SIZE_TIME, 0);
    printf("Send: %d room - %d alarm set\n\n", msgTime.room, msgTime.num);

    pid = fork();
    if (pid == -1) {
        perror("fork() error!");
    } else if (pid == 0) { // Child
        memset(&msgRslt, 0x00, sizeof(msgRslt));
        msgrcv(msqid, &msgRslt, MSG_SIZE_RSLT, MSG_TYPE_RSLT, 0);
        printf("Receive: %d room - %d alarm Ring~\n", msgRslt.room,
               msgRslt.num);
    }
    return 0;
}

void howToAlarm(void) {
    printf("MM DD HH MM room_number type\n");
    printf("MM: 1, 2, 3, ..., 12\n");
    printf("DD: 1, 2, 3, ... , 31\n");
    printf("HH: 00, 01, 02, ... , 23\n");
    printf("MM: 00, 01, 02, ... , 59\n");
    printf("room_number: 101, 102, 103, ...\n");
    printf("type: breakfast  = 0, lunch = 1, dinner = 2, checkout = 3, awake = "
           "4\n");
    printf("예시: 6월 13일 오후 3시 5분 302호실 조식 알람\n");
    printf("      Jun 13 15 05 302 0\n\n");
}
