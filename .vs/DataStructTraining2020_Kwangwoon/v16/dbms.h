#pragma once
#include <string>
#include "Room.h"
#include "Reservation.h"
#include "alarm_client.cpp"
#include <vector>
#include <map>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/filestream.h>
int dbmsConnection();

bool DataConnection();

std::string strDataConnection();

void RoomLoad();

void ReservationLoad();

void ServiceLoad();

bool dbLoad();

bool dbSave();
void GetHttp(std::wstring data);
void GetHttpAsync(std::wstring urldata);
void GetJson2(std::wstring data);
web::json::value GetJson(std::wstring p_sUrl, std::wstring p_sQueryPath = U(""), std::vector<std::pair<std::wstring, std::wstring>>* p_pvQuery = nullptr);
web::uri_builder GetBuilder(std::wstring p_sQueryPath, std::vector<std::pair<std::wstring, std::wstring>>* p_pvQuery);

int alarm_client();

void howToAlarm();
