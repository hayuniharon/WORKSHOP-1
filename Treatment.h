#pragma once
#ifndef TREATMENT_H
#define TREATMENT_H
#include <string>
#include <vector>
#include "DBConnection.h"
using namespace std;

class Treatment
{
public:
	int TreatmentID;
	double Price;
	std::string Description, NameT;

	Treatment();
	void updateTreatment();
	void removeTreatment();

	Treatment(sql::ResultSet* data);

	~Treatment();

	static Treatment searchTreatment(int TreatmentID);
	static std::vector<Treatment> findTreatment(int TreatmentID, std::string NameT, std::string Description, int minPrice, int maxPrice, bool ascending);
	
};

#endif

