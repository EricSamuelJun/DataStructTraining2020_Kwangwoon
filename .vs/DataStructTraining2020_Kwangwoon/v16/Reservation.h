#pragma once
#include "Room.h"
#include "Service.h"
#include <vector>
#include <time.h>
class Reservation
{
private:
	Room* myroom;
	int personCnt;
	std::vector<Service> myService;
	int cost;
	time_t entryTime;
	time_t exitTime;
	std::string customer;
	std::string content;
	int reservationIdx;
public:
	Reservation(Room* mRoom, int pcnt);
	Reservation(int idx) { reservationIdx = idx; }
	void setRoom(Room* mRoom) { myroom = mRoom; }
	void setPcnt(int person) { personCnt = person; }
	void setEntry(time_t m) { entryTime = m; }
	void setExit(time_t m) { exitTime = m; }
	void setCustomer(std::string person) { customer = person; }
	void setContent(std::string mcont) { content = mcont; }
	void setCost(int mcost) { cost = mcost; }
	void setTime(time_t on, time_t out) { entryTime = on; exitTime = out; }
	void addService(Service mservice);
	std::vector<Service> getService();
	Room* getRoom();
	std::string toString();
	int getCost();
};

