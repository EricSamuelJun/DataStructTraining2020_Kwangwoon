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
	sofa = -1,
	single = 0,
	supersingle = 1,
	doub = 2,
	queen = 3,
	king = 4,
	family = 5
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

