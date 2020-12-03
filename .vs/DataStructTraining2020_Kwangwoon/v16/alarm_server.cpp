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

void sigintHandler(int signum);

key_t mykey = 0;
int msqid = 0;

int main(int argc, char const *argv[]) {
    char *nowTime;
    time_t rawtime;
    MsgTime msgTime;
    MsgRslt msgRslt;
    pid_t pid;

    mykey = ftok("mykey", 1);                // 키 생성
    msqid = msgget(mykey, IPC_CREAT | 0644); // 메시지 큐 생성
    signal(SIGINT, sigintHandler);
    while (1) {
        puts("Wait ...");

        memset(&msgTime, 0x00, sizeof(msgTime));
        msgrcv(msqid, &msgTime, MSG_SIZE_TIME, MSG_TYPE_TIME, 0);
        printf("Receive: room %d - %.3s/%.2d - %.2d:%2d - %d Alarm set\n\n",
               msgTime.room, msgTime.time.mon, msgTime.time.date,
               msgTime.time.hour, msgTime.time.minute, msgTime.num);

        pid = fork();
        if (pid == -1) {
            perror("fork() error!\n");
        } else if (pid == 0) { // Child
            do {
                sleep(5);
                rawtime = time(NULL);
                nowTime = ctime(&rawtime);
            } while (!((strncmp(&(nowTime[4]), msgTime.time.mon, 3) == 0) &&
                       (atoi(&(nowTime[8])) == msgTime.time.date) &&
                       (atoi(&(nowTime[11])) == msgTime.time.hour) &&
                       (atoi(&(nowTime[14])) == msgTime.time.minute)));

            memset(&msgRslt, 0x00, sizeof(MsgRslt));
            msgRslt.mtype = MSG_TYPE_RSLT;
            msgRslt.room = msgTime.room;
            msgRslt.num = msgTime.num;

            msgsnd(msqid, &msgRslt, MSG_SIZE_RSLT, 0);
            printf("Send: %d room - %d alarm Ring~\n\n", msgRslt.room,
                   msgRslt.num);
        }
    }
    return 0;
}

void sigintHandler(int signum) {
    if (signum == SIGINT) {
        msgctl(msqid, IPC_RMID, NULL);
        exit(0);
    }
}
