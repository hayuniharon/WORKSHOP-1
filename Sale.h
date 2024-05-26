#pragma once
#ifndef SALE_H
#define SALE_h

#include <string>
#include <vector>
#include "DBConnection.h"

class Sale
{
public:
	int TreatmentID, Price;
	std::string Payment_Date, NameT, start, end;
	double Total_Payment,value;

	Sale(sql::ResultSet* data);

	static std::vector<Sale> salesReport(std::string start, std::string end, std::vector<int> TreatmentID, bool sortByDate, bool ascending);


	~Sale() 
	{
	}
};


#endif
