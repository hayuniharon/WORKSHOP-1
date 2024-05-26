#pragma once
#ifndef STAFF_H
#define STAFF_H

#include <string>
#include <vector>
#include <iostream>
#include "DBConnection.h"

class Staff
{
public:
	int StaffID, category;
	std::string Staff_Username, Staff_Password, Staff_FullName, Staff_PhoneNum, Staff_Email, Staff_Address, Staff_Position;

	Staff(); // constructor method
	Staff(int StaffID, std::string Staff_Username, std::string Staff_Password, std::string Staff_FullName, std::string Staff_PhoneNum, std::string Staff_Email, std::string Staff_Address, std::string Staff_Position);

	Staff(sql::ResultSet* data);

	bool usernameExists(const std::string& Staff_Username);

	bool loginStaff();
	void insertStaff();
	void updateStaff();
	void removeStaff();
	static std::string getMaskedInputS(const std::string& prompt);

	static Staff findStaff(int StaffID);
	static std::vector<Staff> searchStaff(std::string Staff_FullName, std::string Staff_Position, bool ascending);

	~Staff(); // destructor method

};

#endif 