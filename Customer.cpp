#include "Customer.h"
#include <ctime>
#include "DBConnection.h"
#include <conio.h>
using namespace std;

Cust::Cust()
{
	// initialize
	CustID = 0;
	Cust_Username = "";
	Cust_Password = "";
	Cust_FullName = "";
	Cust_PhoneNum = "";
	Cust_Email = "";
	Cust_Address = "";
}
Cust::Cust(int CustID, std::string Cust_Username, std::string Cust_Password, std::string Cust_FullName, std::string Cust_PhoneNum, std::string Cust_Email, std::string Cust_Address)
{
	this->CustID = CustID;
	this->Cust_Username = Cust_Username;
	this->Cust_Password = Cust_Password;
	this->Cust_FullName = Cust_FullName;
	this->Cust_PhoneNum = Cust_PhoneNum;
	this->Cust_Email = Cust_Email;
	this->Cust_Address = Cust_Address;
}
bool Cust::loginCust()
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM customer WHERE Cust_Username=? AND Cust_Password=?");
	db.stmt->setString(1, Cust_Username);
	db.stmt->setString(2, Cust_Password);
	db.QueryResult();
	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
		{
			CustID = db.res->getInt("CustID");
			Cust_Username = db.res->getString("Cust_Username");
			Cust_Password = db.res->getString("Cust_Password");
			Cust_FullName = db.res->getString("Cust_FullName");
			Cust_PhoneNum = db.res->getString("Cust_PhoneNum");
			Cust_Email = db.res->getString("Cust_Email");
			Cust_Address = db.res->getString("Cust_Address");
		
		}
		db.~DBConnection();
		return true;
	}
	else {
		db.~DBConnection();
		return false;
	}
}
void Cust::insertCust() {
	DBConnection db;
	db.prepareStatement("Insert into customer (Cust_Username, Cust_Password, Cust_FullName, Cust_PhoneNum, Cust_Email, Cust_Address) VALUES ( ?, ?, ?, ?, ?, ?)");
	db.stmt->setString(1, Cust_Username);
	db.stmt->setString(2, Cust_Password);
	db.stmt->setString(3, Cust_FullName);
	db.stmt->setString(4, Cust_PhoneNum);
	db.stmt->setString(5, Cust_Email);
	db.stmt->setString(6, Cust_Address);
	db.QueryStatement();
	db.~DBConnection();
}
void Cust::updateCust() {
	DBConnection db;
	db.prepareStatement("UPDATE customer SET Cust_Username=?, Cust_Password=?, Cust_FullName=?, Cust_PhoneNum=?, Cust_Email=?, Cust_Address=? WHERE CustID=?");
	db.stmt->setString(1, Cust_Username);
	db.stmt->setString(2, Cust_Password);
	db.stmt->setString(3, Cust_FullName);
	db.stmt->setString(4, Cust_PhoneNum);
	db.stmt->setString(5, Cust_Email);
	db.stmt->setString(6, Cust_Address);
	db.stmt->setInt(7, CustID);
	db.QueryStatement();
	db.~DBConnection();
}
void Cust::removeCust()
{
	DBConnection db;
	db.prepareStatement("DELETE FROM customer WHERE CustID=?");
	db.stmt->setInt(1, CustID);
	db.QueryStatement();
	db.~DBConnection();

}

std::string Cust::getMaskedInput(const std::string& prompt)
{
	std::string input;
	std::cout << prompt;

	char c;
	while (true)
	{
		c = _getch();

		if (c == 13 || c == 10) // Enter key
			break;
		else if (c == 8) // Backspace key
		{
			if (!input.empty())
			{
				std::cout << "\b \b"; // Move the cursor back and erase the character
				input.pop_back(); // Remove the last character from the string
			}
		}
		else
		{
			std::cout << '*';
			input += c;
		}
	}

	std::cout << std::endl; // Move to the next line after entering the password
	return input;
}

Cust::~Cust()
{
}

