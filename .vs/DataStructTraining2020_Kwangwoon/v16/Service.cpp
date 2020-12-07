#pragma once
#include "Service.h"
#include <string>
#include <iostream>
using namespace std;
Service::Service(int idx) {
	serviceidx = idx;
}
void Service::setConent(string mcontent) {
	content = mcontent;
}
void Service::setCost(int mcost) {
	addcost = mcost;
}
int Service::getCost() {
	return addcost;
}
string Service::getContent() {
	return content;
}

string Service::toString() {
	string result = "";
	result += "Service ID: " + to_string(serviceidx)+"\n";
	result += "Service Content: " + content + "\n";
	result += "Service Cost: " + to_string(addcost) + "\n";
	return result;
}


