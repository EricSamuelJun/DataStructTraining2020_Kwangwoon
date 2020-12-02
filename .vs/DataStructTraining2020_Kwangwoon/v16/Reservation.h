#pragma once
#include "Room.h"
#include "Service.h"
#include <vector>
class Reservation
{
private:
	Room myroom;
	int personCnt;
	std::vector<Service> myService;
public:
	Reservation(Room mRoom, int pcnt);
	void addService(Service mservice);
	Service getService();
};

