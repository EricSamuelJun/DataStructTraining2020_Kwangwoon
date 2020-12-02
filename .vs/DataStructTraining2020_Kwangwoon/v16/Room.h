#pragma once
#include <string>
#include <vector>

/// <summary>
/// 방의 등급. 스탠다드=기본 -> 스위트 = 최상급
/// 파티룸 10, 레지던스 20
/// </summary>
enum RoomGrade
{
	standard = 0,
	superior = 1,
	delux = 2,
	executive = 3,
	suite = 4,
	party = 10,
	residence = 20
};
/// <summary>
/// 적용 가능한 침대 종류. 소파배드는 -1
/// </summary>
enum Bed
{
	sofa = -1,
	single = 0,
	supersingle = 1,
	doub = 2,
	queen = 3,
	king = 4,
	family = 5
};
/// <summary>
/// 방 클래스
/// </summary>
class Room
{
private:
	/// <summary>
	/// 방 등급
	/// </summary>
	RoomGrade grade;
	/// <summary>
	/// 방 호수. PK
	/// </summary>
	int roomNum;
	/// <summary>
	/// 기본 인원
	/// </summary>
	int defaultNumOfPeople;
	/// <summary>
	/// 최대 인원. 기본적으론 기본 인원 + 2
	/// </summary>
	int maxmanNumOfPeople;
	/// <summary>
	/// 소파배드 추가가능여부
	/// </summary>
	bool isSofabed;
	/// <summary>
	/// 내용 / 해시태그
	/// </summary>
	std::string content;
	/// <summary>
	/// 침대 수
	/// </summary>
	int bedcnt;
	/// <summary>
	/// 침대 있는 것 들
	/// </summary>
	std::vector<Bed> beds;
public:
	Room(int roomNum,RoomGrade rg, int defn, int maxn);
#pragma region setMethod
	void setcontent(std::string tcontent);
	void addBeds(Bed bed);
	void setSofabed(bool sofa);
#pragma endregion

#pragma region getMethod
	
	RoomGrade getGrade();
	std::string toString();
	int getBedCnt();
	std::vector<Bed> getBeds();
	int getRoomNum();
#pragma endregion


};

