#pragma once
#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>
#include "DBConnection.h"
 
class Admin
{
public: 
	int AdminID;
	std::string Admin_Username, Admin_Password, Admin_FullName, Admin_PhoneNum, Admin_Email;

	Admin(); // constructor method
	Admin(sql::ResultSet* data);

	Admin(int Admin_ID, std::string Admin_Username, std::string Admin_Password, std::string Admin_FullName, std::string Admin_PhoneNum, std::string Admin_Email);

	~Admin(); // destructor method

	static Admin viewAdmin(Admin admins);

	bool loginAd();
	void insertAd();
	void updateAd();
	void removeAd();

	static std::string getMaskedInput(const std::string& prompt);

};

#endif 

