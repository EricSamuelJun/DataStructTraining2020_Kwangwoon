#pragma warning(disable:4996)
#include <iostream>
#include "dbms.h"
#include <string>
#include "Room.h"
#include "datas.h"
#include "Reservation.h"
#include <vector>
#include <map>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/filestream.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
using namespace utility;
using namespace web;
using namespace web::json;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;


using namespace std;
//DB Connection Data: http://mam675.synology.me/HOTEL/Select/room.php

extern map<int, Room> rooms;
extern map<int, Service> services;
extern queue<Reservation> reservations;
vector<Reservation> reservector;

uri_builder GetBuilder(wstring p_sQueryPath, vector<pair<wstring, wstring>>* p_pvQuery) {
	uri_builder builder;
	if (!p_sQueryPath.empty()) {
		builder.set_path(p_sQueryPath);
		if (!p_pvQuery->empty()) {
			for (pair<wstring, wstring> pQuery : (*p_pvQuery)) {
				builder.append_query(pQuery.first, pQuery.second);
			}
		}
	}
	return builder;
}

void GetHttp(wstring urldata)
{
	//http_client client(U("http://en.cppreference.com/w/"));
	http_client client((urldata));
	auto resp = client.request(U("GET")).get();

	//wcout << U("STATUS : ") << resp.status_code() << endl;
	//wcout << "content-type : " << resp.headers().content_type() << endl;
	wcout << resp.extract_string(true).get() << endl;
}

void GetHttpAsync(wstring urldata)
{
	http_client client(urldata);

	client.request(U("GET")).then([](http_response resp) {
		wcout << U("STATUS : ") << resp.status_code() << endl;
		wcout << "content-type : " << resp.headers().content_type() << endl;

		resp.extract_string(true).then([](string_t sBoby) {
			wcout << sBoby << endl;
			}).wait();

		}).wait();

}

void GetJson2(wstring data)
{
	http_client client(data);

	http_request req(methods::GET);

	client.request(req).then([=](http_response r) {
		wcout << U("STATUS : ") << r.status_code() << endl;
		wcout << "content-type : " << r.headers().content_type() << endl;

		//{
		//		"time": "11:25:23 AM",
		//		"milliseconds_since_epoch" : 1423999523092,
		//		"date" : "02-15-2015"
		//}

		r.extract_json(true).then([](value v) {

			wcout << v.at(U("NUMBER")).as_string() << endl;
			}).wait();

		//r.extract_json(true).then([](json::value v) {
		//	wcout << v.at(U("date")).as_string() << endl;
		//	wcout << v.at(U("time")).as_string() << endl;
		//	}).wait();

		}).wait();

}

value GetJson(wstring p_sUrl, wstring p_sQueryPath, vector<pair<wstring, wstring>>* p_pvQuery) {
	value vJson;
	http_client client(p_sUrl);
	uri_builder builder = GetBuilder(p_sQueryPath, p_pvQuery);
	pplx::task<void> requestTask = client.request(methods::GET, builder.to_string()).then([&](http_response response) {
		return response.extract_json();
		})
		.then([&](pplx::task<value> previousTask) {
			try {
				vJson = previousTask.get();
			} catch (const http_exception& e) {
				printf("Error : %s\n", e.what());
				
			}
			});
	try {
		requestTask.wait();
	}
	catch (const exception& e) {
		printf("ERROR: %s\n", e.what());
	}
	return vJson;
}



int dbmsConnection() {
	return 1;
}



bool DataConnection() {
	return false;
}

string strDataConnection() {
	string result;
	result = "aa";
	return result;
}

int setUrltoJsonVector(vector<value>* jsvec, string url) {
	wstring wurl;
	wurl.assign(url.begin(), url.end());
	int size = 0;
	http_client client(wurl);
	auto resp = client.request(U("GET")).get();
	string temp = resp.extract_utf8string(true).get();
	string strsize = temp.substr(0, temp.find("\n"));
	temp = temp.substr(temp.find("\n") + 1);
	size = stoi(strsize);
	cout << "[" << size << "]" << endl;
	temp = temp.substr(temp.find("[") + 1);
	temp = temp.substr(0, temp.find("]"));
	cout << temp << endl;
	if (size > 0) {
		for (int i = 0; i < size; i++) {
			string myjsonstr;
			value myjson;
			if (i == size - 1) {
				myjsonstr = temp;
			} else {
				//0~'},'
				myjsonstr = temp.substr(0, temp.find("},") + 1);
				temp = temp.substr(temp.find("},") + 2);
			}
			utility::stringstream_t s;
			wstring wstr;
			wstr.assign(myjsonstr.begin(), myjsonstr.end());
			s << wstr;
			myjson = value::parse(s);
			jsvec->push_back(myjson);
		}
	}
	return size;
}

string jsonvaluetoString(value* json,string key) {
	wstring wkey;
	wkey.assign(key.begin(), key.end());
	if (json->at(wkey) != NULL) {
		string result;
		wstring wresult = json->at(wkey).as_string();
		result.assign(wresult.begin(),wresult.end());
		return result;
	} else
		return "";
}

int jsonvaluetoInt(value* json, string key) {
	wstring wkey;
	wkey.assign(key.begin(), key.end());
	if (json->at(wkey) != NULL) {
		int result;
		wstring wresult = json->at(wkey).as_string();
		result = stoi(wresult);
		return result;
	} else
		return 0;
}

void inttojson(value& myjson, string key, int value) {
	wstring wkey;
	wkey.assign(key.begin(), key.end());
	myjson[wkey] = value::number(value);
}

void stringtojson(value& myjson, string key, string value) {
	wstring wkey;
	wkey.assign(key.begin(), key.end());
	wstring wvalue;
	wvalue.assign(value.begin(), value.end());
	myjson[wkey] = value::string(wvalue);
}

void RoomSave() {
	//데이터 담을 Json 선언
	vector<value> jsonVector;
	for (pair<int,Room> pairoom : rooms) {
		Room mroom = pairoom.second;
		// Class 를 json 화
		value* myjson = new value();
		inttojson((*myjson), "NUMBER", mroom.getRoomNum());
		inttojson((*myjson), "GRADE", mroom.getGrade());
		inttojson((*myjson), "COST", mroom.getCost());
		inttojson((*myjson), "DEF_SIZE", mroom.getDefNum());
		inttojson((*myjson), "MAX_SIZE", mroom.getMaxNum());
		inttojson((*myjson), "BED_CNT", mroom.getBedCnt());
		inttojson((*myjson), "SOFABED", mroom.getintsofabed());
		
		stringtojson((*myjson), "BEDS", mroom.getBedstring());
		stringtojson((*myjson), "CONTENT", mroom.getContent());
		jsonVector.push_back(*myjson);
	}

}
void ServiceSave() {
	vector<value> jsonVector;
	for (pair<int, Room> pairoom : rooms) {
		Room mroom = pairoom.second;
		// Class 를 json 화
		value* myjson = new value();
		inttojson((*myjson), "NUMBER", mroom.getRoomNum());
		inttojson((*myjson), "COST", mroom.getCost());
		stringtojson((*myjson), "CONTENT", mroom.getContent());
		jsonVector.push_back(*myjson);
	}
}
void ReservationSave() {

}


void RoomLoad() {
	vector<value> jsonvector;
	int size;
	size = setUrltoJsonVector(&jsonvector, "http://mam675.synology.me/HOTEL/Select/room.php");
	//cout << "size of json: " << jsonvector.size() << "and json's 0 \"NUMBERS: \": ";
	//wcout << jsonvector.at(0).at(U("NUMBER")).as_string() << endl;
	//가져온거 클래스화
	for (int i = 0; i < size; i++) {
		//Room myroom = Room(jsonvector.at(i).at(U("NUMBER")).as_integer(), (RoomGrade)jsonvector.at(i).at(U("GRADE")).as_integer());
		value myjson = jsonvector.at(i);
		int roomidx = jsonvaluetoInt(&myjson, "NUMBER");
		int grade = jsonvaluetoInt(&myjson, "GRADE");
		int max = jsonvaluetoInt(&myjson, "DEF_SIZE");
		int def = jsonvaluetoInt(&myjson, "MAX_SIZE");
		int sofa = jsonvaluetoInt(&myjson, "SOFABED");
		int cost = jsonvaluetoInt(&myjson, "COST");
		int bedcnt = jsonvaluetoInt(&myjson, "BED_CNT");
		string content = jsonvaluetoString(&myjson, "CONTENT");
		string bedstr = jsonvaluetoString(&myjson, "BEDS");
		
		Room* myroom = new Room(roomidx,(RoomGrade) grade,def,max);
		myroom->setSofabed(sofa != 0);
		myroom->setcontent(content);
		myroom->setCost(cost);
		for (int i = 0; i < bedcnt; i++) {
			int bedidx = 0;
			bedidx = stoi(bedstr.substr(0, bedstr.find("_")));
			bedstr = bedstr.substr(bedstr.find("_") + 1);
			myroom->addBeds((Bed)bedidx);
		}

		cout << myroom->toString();
		rooms.insert(pair<int, Room>(roomidx , *myroom));
	}
}

void ReservationLoad() {
	vector<value> jsonvector;
	int size;
	size = setUrltoJsonVector(&jsonvector, "http://mam675.synology.me/HOTEL/Select/reservation.php");
	//cout << "size of json: " << jsonvector.size() << "and json's 0 \"NUMBERS: \": ";
	//wcout << jsonvector.at(0).at(U("NUMBER")).as_string() << endl;
	//가져온거 클래스화
	for (int i = 0; i < size; i++) {
		//Room myroom = Room(jsonvector.at(i).at(U("NUMBER")).as_integer(), (RoomGrade)jsonvector.at(i).at(U("GRADE")).as_integer());
		value myjson = jsonvector.at(i);
		int idx = jsonvaluetoInt(&myjson, "RESERV_IDX");
		int serv_cnt = jsonvaluetoInt(&myjson, "SERV_CNT");
		int roomidx = jsonvaluetoInt(&myjson, "ROOM_IDX");
		int person_cnt = jsonvaluetoInt(&myjson, "PERSON_CNT");
		int cost = jsonvaluetoInt(&myjson, "COST");
		string content = jsonvaluetoString(&myjson, "CONTENT");
		string customer = jsonvaluetoString(&myjson, "CUSTOMER");
		string servs = jsonvaluetoString(&myjson, "SERVICES");
		string entrytime = jsonvaluetoString(&myjson, "ENTRY_TIME");
		string exittime = jsonvaluetoString(&myjson, "EXIT_TIME");
		cout << "enrtry: "<<entrytime << endl;
		Reservation* myreserv = new Reservation(idx);
		myreserv->setCost(cost);
		myreserv->setCustomer(customer);
		myreserv->setContent(content);
		const char* entrychar = entrytime.c_str();
		struct tm t;
		int yyyy=2020, mon=12, dd=6, hh=12, mm=0, ss=0;
		sscanf(entrychar, "%d-%d-%d %d:%d:%d", &yyyy, &mon, &dd, &hh, &mm, &ss);
		t.tm_year = yyyy - 1900;
		t.tm_mon = mon - 1;
		t.tm_mday = dd;
		t.tm_hour = hh;
		t.tm_min = mm;
		t.tm_sec = ss;
		time_t entryt = mktime(&t);
		const char* exitchar = exittime.c_str();
		sscanf(exitchar, "%d-%d-%d %d:%d:%d", &yyyy, &mon, &dd, &hh, &mm, &ss);
		t.tm_year = yyyy - 1900;
		t.tm_mon = mon - 1;
		t.tm_mday = dd;
		t.tm_hour = hh;
		t.tm_min = mm;
		t.tm_sec = ss;
		time_t exitt = mktime(&t);
		myreserv->setTime(entryt, exitt);
		if (rooms.size() > 0) {
			map<int, Room>::iterator riter;
			riter = rooms.find(roomidx);
			if (riter != rooms.end()) {
				Room* test = NULL;
				test = &riter->second;
				myreserv->setRoom(test);
			}
		}
		if (serv_cnt > 0) {
			if (services.size() > 0) {
				map<int, Service>::iterator siter;
				for (int i = 0; i < serv_cnt; i++) {
					int servidx = 0;
					servidx = stoi(servs.substr(0, servs.find("_")));
					servs = servs.substr(servs.find("_") + 1);
					siter = services.find(servidx);
					if (siter != services.end()) {
						Service* servptr = nullptr;
						servptr = &siter->second;
						myreserv->addService(*servptr);
					}
				}
			}
		}
		reservector.push_back(*myreserv);
		cout << myreserv->toString();
	}
}

void ServiceLoad() {
	vector<value> jsonvector;
	int size;
	size = setUrltoJsonVector(&jsonvector, "http://mam675.synology.me/HOTEL/Select/service.php");
	//cout << "size of json: " << jsonvector.size() << "and json's 0 \"NUMBERS: \": ";
	//wcout << jsonvector.at(0).at(U("NUMBER")).as_string() << endl;
	//가져온거 클래스화
	for (int i = 0; i < size; i++) {
		//Room myroom = Room(jsonvector.at(i).at(U("NUMBER")).as_integer(), (RoomGrade)jsonvector.at(i).at(U("GRADE")).as_integer());
		value myjson = jsonvector.at(i);
		int idx = jsonvaluetoInt(&myjson, "SERV_IDX");
		int cost = jsonvaluetoInt(&myjson, "COST");
		string content = jsonvaluetoString(&myjson, "CONTENT");

		cout << "idx: " << idx << " Cost: " << cost << " content: " << content << endl;

		Service myservice = Service(idx);
		myservice.setConent(content);
		myservice.setCost(cost);
		cout << myservice.toString();
		services.insert(pair<int, Service>(idx, myservice));

	}
}

bool dbLoad() {
	//dbmsConnection();
	RoomLoad();
	ServiceLoad();
	ReservationLoad();
	return true;
}

bool dbSave() {
	return true;
}