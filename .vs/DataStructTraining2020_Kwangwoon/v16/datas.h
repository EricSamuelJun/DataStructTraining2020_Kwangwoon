#pragma once
#include "Room.h"
#include "Reservation.h"
#include "Service.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
using namespace std;

map<int, Room> rooms;
map<int, Service> services;
queue<Reservation> reservations;