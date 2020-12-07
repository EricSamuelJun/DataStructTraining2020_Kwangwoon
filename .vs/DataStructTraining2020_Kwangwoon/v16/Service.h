#pragma once
#include <string>
class Service
{
private:
	/// <summary>
	/// PK
	/// </summary>
	int serviceidx;
	/// <summary>
	/// Content
	/// </summary>
	std::string content;
	/// <summary>
	/// Add cost value
	/// </summary>
	int addcost;
public:
	Service(int idx);
	void setConent(std::string mcontent);
	void setCost(int mcost);
	int getCost();
	std::string getContent();
	std::string toString();
};

