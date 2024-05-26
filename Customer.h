#pragma once
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Cust
{
public:
	int CustID;
	std::string Cust_Username, Cust_Password, Cust_FullName, Cust_PhoneNum, Cust_Email, Cust_Address;

	Cust(); // constructor method
	Cust(int CustID, std::string Cust_Username, std::string Cust_Password, std::string Cust_FullName, std::string Cust_PhoneNum, std::string Cust_Email, std::string Cust_Address);

	bool loginCust();
	void insertCust();
	void updateCust();
	void removeCust();
	static std::string getMaskedInput(const std::string& prompt);

	~Cust(); // destructor method

};

#endif 

