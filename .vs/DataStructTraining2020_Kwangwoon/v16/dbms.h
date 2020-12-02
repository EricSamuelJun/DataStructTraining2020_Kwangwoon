#pragma once
#include <string>
#include "Room.h"
#include "Reservation.h"
#include <vector>
int dbmsConnection();

bool DataConnection();

std::string strDataConnection();

std::vector<Room> RoomSetting(std::vector<Room> m);

std::vector<Reservation> ReservationSetting(std::vector<Reservation> m);

std::vector<Service> ServiceSetting(std::vector<Service> m);

bool dbLoad();

bool dbSave();