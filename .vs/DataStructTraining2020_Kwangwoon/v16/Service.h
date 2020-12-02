#pragma once
#include "Reservation.h"
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
};

