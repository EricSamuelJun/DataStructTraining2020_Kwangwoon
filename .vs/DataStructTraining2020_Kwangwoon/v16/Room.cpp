#include "Room.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Room::Room(int mroomNum, RoomGrade rg, int defn, int maxn) {
	this->grade = rg;
	this->roomNum = mroomNum;
	this->defaultNumOfPeople = defn;
	this->maxmanNumOfPeople = maxn;
	bedcnt = 0;
	content = "";
}
#pragma region setMethod
void Room::setcontent(string tcontent) {
	this->content += tcontent;
}
void Room::addBeds(Bed bed) {
	bedcnt += 1;
	beds.push_back(bed);
}
void Room::setSofabed(bool sofa) {
	this->isSofabed = sofa;
}
#pragma endregion

#pragma region getMethod

RoomGrade Room::getGrade() {
	return this->grade;
}
string Room::toString() {
	string result;
	result += "┌──────────────────────────────────────────────────────────────────────────────────┐\n";
	result += "  Room Number: " + to_string(roomNum) + "\n";
	switch (grade) {
	case RoomGrade::standard:
		result += "\tRoom Grade: Standard\n";
		break;
	case RoomGrade::superior:
		result += "\tRoom Grade: Standard\n";
		break;
	case RoomGrade::delux:
		result += "\tRoom Grade: Standard\n";
		break;
	case RoomGrade::executive:
		result += "\tRoom Grade: Standard\n";
		break;
	case RoomGrade::suite:
		result += "\tRoom Grade: Standard\n";
		break;
	case RoomGrade::party:
		result += "\tParty Room\n";
		break;
	case RoomGrade::residence:
		result += "\tResidence Room\n";
		break;
	}
	result += "  Beds: \n";
	vector<Bed>::iterator bediter;
	if (bedcnt < 1) {
		result += "\tNo Bed Provided.\n";
	}
	else {
		result += "    We have " + to_string(bedcnt) + " Beds. Take a look\n";
		for (bediter = beds.begin(); bediter != beds.end(); bediter++) {
			switch (*bediter) {
			case Bed::sofabed:
				result += "\tSofa Bed\n\t   1 Person containalbe\n";
				break;
			case Bed::single:
				result += "\tSingle Bed\n\t   1 Person containalbe\n";
				break;
			case Bed::doub:
				result += "\tdouble Bed\n\t   1~2 Person containalbe\n";
				break;
			case Bed::supersingle:
				result += "\tSuper Single Bed\n\t   1~2 Person containalbe\n";
				break;
			case Bed::queen:
				result += "\tQueen Bed\n\t   1~2 Person containalbe\n";
				break;
			case Bed::king:
				result += "\tKing Bed\n\t   2 Person containalbe\n";
				break;
			case Bed::family:
				result += "\tFamily Bed\n\t   2~4 Person containalbe\n";
				break;
			case Bed::bunkbed:
				result += "\tBunker Bed\n\t   2 Person containalbe\n";
				break;
			case Bed::lakulaku:
				result += "\tlaku laku bed\n\t   1 Person containalbe\n";
				break;
			case Bed::waterbed:
				result += "\tWater Bed\n\t   2 Person containalbe\n";
				break;
			case Bed::lovebed:
				result += "\tBed for lovers\n\t   2! Person containalbe\n";
				break;
			case Bed::stonebed:
				result += "\tHard Based Korean Stone Bed\n\t   2~4 Person containalbe\n";
				break;
			}
		}
	}
	if (isSofabed)
		result += "    You can request one more Sofabed.\n";
	result += "\n  [MEMO]=================================\n  "+content +"\n  =======================================\n";
	result += "  All Service Cost: " + to_string(roomCost)+"$\n";
	result += "  Thanks for using our hotel. Please take a rest and having a greatest day of the year.\n";
	result += "└──────────────────────────────────────────────────────────────────────────────────┘\n\n";
	return result;
}
int Room::getBedCnt() {
	return bedcnt;
}
vector<Bed> Room::getBeds() {
	return beds;
}
int Room::getRoomNum() {
	return roomNum;
}
string Room::getBedstring() {
	string result;
	
	for (Bed mbed : beds) {
		result += to_string((int)mbed) + "_";
	}
	result = result.substr(0, result.length() - 1);
	return result;
}
#pragma endregion