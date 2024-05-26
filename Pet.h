#pragma once
#ifndef PET_H
#define PET_H

#include <string>
#include <vector>
#include "DBConnection.h"

class Pet
{
public:
	int PetID, CustID;
	std::string Pet_Name, Pet_Species, Pet_Breed, Pet_Color, Pet_Gender, Pet_Weight, Pet_Status;

	Pet();
	Pet(sql::ResultSet* data);
	Pet(int PetID, int CustID, std::string Pet_Name, std::string Pet_Species, std::string Pet_Breed, std::string Pet_Gender, std::string Pet_Weight, std::string Pet_Status);
	int generatedPetID;
	int insertPet();
	void updatePet();
	void updateStatus();
	void removePet();
	
	~Pet();

	static std::vector<Pet> searchPet(std::string Pet_Name, std::string Pet_Species, bool asc);
	static std::vector<Pet> ourPet(int CustID, const std::string Pet_Name, const std::string Pet_Species);
};

#endif

