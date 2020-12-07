#pragma once
#include <string>
#include <vector>

/// <summary>
/// ���� ���. ���Ĵٵ�=�⺻ -> ����Ʈ = �ֻ��
/// ��Ƽ�� 10, �������� 20
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
/// ���� ������ ħ�� ����. ���Ĺ��� -1
/// </summary>
enum Bed
{
	single = 0,
	supersingle = 1,
	doub = 2,
	queen = 3,
	king = 4,
	family = 5,
	sofabed = -1,
	lakulaku = -2,
	bunkbed = -3,
	waterbed = -4,
	lovebed = -5,
	stonebed = -6

};
/// <summary>
/// �� Ŭ����
/// </summary>
class Room
{
private:
	/// <summary>
	/// �� ���
	/// </summary>
	RoomGrade grade;
	/// <summary>
	/// �� ȣ��. PK
	/// </summary>
	int roomNum;
	/// <summary>
	/// �⺻ �ο�
	/// </summary>
	int defaultNumOfPeople;
	/// <summary>
	/// �ִ� �ο�. �⺻������ �⺻ �ο� + 2
	/// </summary>
	int maxmanNumOfPeople;
	/// <summary>
	/// ���Ĺ�� �߰����ɿ���
	/// </summary>
	bool isSofabed;
	/// <summary>
	/// ���� / �ؽ��±�
	/// </summary>
	std::string content;
	/// <summary>
	/// ħ�� ��
	/// </summary>
	int bedcnt;
	/// <summary>
	/// ħ�� �ִ� �� ��
	/// </summary>
	std::vector<Bed> beds;
	int roomCost;
public:
	Room(int roomNum,RoomGrade rg, int defn = 0 , int maxn =0);
#pragma region setMethod
	void setcontent(std::string tcontent);
	void addBeds(Bed bed);
	void setSofabed(bool sofa);
	void setCost(int cost) { roomCost = cost; }
#pragma endregion

#pragma region getMethod
	
	RoomGrade getGrade();
	std::string toString();
	int getBedCnt();
	std::vector<Bed> getBeds();
	int getRoomNum();
	int getCost() { return roomCost; }
	int getDefNum() { return defaultNumOfPeople; }
	int getMaxNum() { return maxmanNumOfPeople; }
	int getBedsize() { return beds.size(); }
	std::string getBedstring();
	int getintsofabed() { int re;  isSofabed == true ?  re = 1 : re = 10; return re; }
	std::string getContent() { return content; }
#pragma endregion
};