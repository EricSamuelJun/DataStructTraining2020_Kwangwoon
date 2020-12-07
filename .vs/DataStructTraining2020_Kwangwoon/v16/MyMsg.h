#ifndef __MYMSG_H__
#define __MYMSG_H__

#define MSG_TYPE_TIME 1 // 숫자 및 연산자
#define MSG_TYPE_RSLT 2 // 결과 메시지

#define MSG_SIZE_TIME (sizeof(MsgTime) - sizeof(long))
#define MSG_SIZE_RSLT (sizeof(MsgRslt) - sizeof(long))

enum AlarmNum {
    breakfast = 0,
    lunch = 1,
    dinner = 2,
    checkout = 3,
    awake = 4,
    nothing = 5
};

struct __Time {
    char mon[3];
    int date;
    int hour;
    int minute;
};
typedef struct __Time Time;

struct __MsgTime {
    long mtype;
    int room;
    enum AlarmNum num = nothing;
    struct __Time time;
};
typedef struct __MsgTime MsgTime;

struct __MsgRslt {
    long mtype;
    int room;
    enum AlarmNum num = nothing;
};
typedef struct __MsgRslt MsgRslt;

#endif //!__MYMSG_H__
