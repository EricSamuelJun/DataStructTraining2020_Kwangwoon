#include "Reservation.h"
#include "Room.h"
#include <time.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;
Reservation::Reservation(Room* mRoom, int pcnt) {
	myroom = mRoom;
	personCnt = pcnt;
}
void Reservation::addService(Service mservice) {
	myService.push_back(mservice);
}
vector<Service> Reservation::getService() {
	return myService;
}
Room* Reservation::getRoom() {
	return myroom;
}
string Reservation::toString() {
	string result = "";
	result += "Reservation: \n";
	result += "Customer: " + customer;
	result += "Room data: ========================================================\n";
	result += myroom->toString();
	result += "===================================================================\n";
	if (myService.size() < 1) {
		result += "Added Service: \n";
		vector<Service>::iterator serviter;
		for (serviter = myService.begin(); serviter != myService.end(); serviter++) {
			result += "\t";
			result += serviter->toString(); 
			result += "\n";
		}
	}
	result += "\n";
	try {
		result += "Entry Time: ";
		struct tm tm;
		//tm = localtime(&entryTime);
		localtime_s(&tm, &entryTime);
		result += to_string(tm.tm_year + 1900)+"/";
		result += to_string(tm.tm_mon + 1) +"/";
		result += to_string(tm.tm_mday)+".";
		result += to_string(tm.tm_hour)+":";
		result += to_string(tm.tm_min);
		result += "\n";
		result += "Exit Time: ";
		//struct tm* tm;
		//tm = localtime(&exitTime);
		localtime_s(&tm, &exitTime);
		result += to_string(tm.tm_year + 1900) + "/";
		result += to_string(tm.tm_mon + 1) + "/";
		result += to_string(tm.tm_mday) + ".";
		result += to_string(tm.tm_hour) + ":";
		result += to_string(tm.tm_min);
		result += "\n";
	} catch (exception e) {
		result += "error: can not acces time \n";
	}
	result += "===================================================================\n";
	result += "All cost: "+to_string(getCost())+"\n";
	result += "Please take a rest in our hotel.\n";
	return result;
}
int Reservation::getCost() {
	int rescost = cost;
	if (myService.size() < 1) {
		vector<Service>::iterator serviter;
		for (serviter = myService.begin(); serviter != myService.end(); serviter++) {
			rescost += serviter->getCost();
		}
	}
	return rescost;
}