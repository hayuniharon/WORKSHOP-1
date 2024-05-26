#include "Admin.h"
#include <ctime>
#include <vector>
#include "DBConnection.h"
#include "Staff.h"
#include <conio.h>

using namespace std;
 
Admin::Admin()
{
	// initialize
	AdminID = 0;
	Admin_Username = "";
	Admin_Password = "";
	Admin_FullName = "";
	Admin_PhoneNum = "";
	Admin_Email = "";
}
Admin::Admin(int Admin_ID, std::string Admin_Username, std::string Admin_Password, std::string Admin_FullName, std:: string Admin_PhoneNum, std::string Admin_Email)
{
	this->AdminID = Admin_ID;
	this->Admin_Username = Admin_Username;
	this->Admin_Password = Admin_Password;
	this->Admin_FullName = Admin_FullName;
	this->Admin_PhoneNum = Admin_PhoneNum;
	this->Admin_Email = Admin_Email;
}
bool Admin::loginAd()
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM Admin WHERE Admin_Username=? AND Admin_Password=?");
	db.stmt->setString(1, Admin_Username);
	db.stmt->setString(2, Admin_Password);
	db.QueryResult();
	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
		{
			AdminID = db.res->getInt("AdminID");
			Admin_Username = db.res->getString("Admin_Username");
			Admin_Password = db.res->getString("Admin_Password");
			Admin_FullName = db.res->getString("Admin_FullName");
			Admin_PhoneNum = db.res->getString("Admin_PhoneNum");
			Admin_Email = db.res->getString("Admin_Email");
	   }
		db.~DBConnection();
		return true;
	}
	else {
		db.~DBConnection();
		return false;
	}
}
void Admin::insertAd() {
	DBConnection db;
	db.prepareStatement("Insert into Admin (Admin_Username, Admin_Password, Admin_FullName, Admin_PhoneNum, Admin_Email) VALUES (?, ?, ?, ?, ?)");
	db.stmt->setString(1, Admin_Username);
	db.stmt->setString(2, Admin_Password);
	db.stmt->setString(3, Admin_FullName);
	db.stmt->setString(4, Admin_PhoneNum);
	db.stmt->setString(5, Admin_Email);
	db.QueryStatement();
	db.~DBConnection();
}
void Admin::updateAd() {
	DBConnection db;
	db.prepareStatement("UPDATE Admin SET Admin_Username=?, Admin_Password=?, Admin_FullName=?, Admin_PhoneNum=?, Admin_Email=? WHERE AdminID=?");
	db.stmt->setString(1, Admin_Username);
	db.stmt->setString(2, Admin_Password);
	db.stmt->setString(3, Admin_FullName);
	db.stmt->setString(4, Admin_PhoneNum);
	db.stmt->setString(5 ,Admin_Email);
	db.stmt->setInt(6, AdminID);
	db.QueryStatement();
	db.~DBConnection();
}
void Admin::removeAd() {
	DBConnection db;
	db.prepareStatement("DELETE FROM Admin WHERE AdminID=?");
	db.stmt->setInt(1, AdminID);
	db.QueryStatement();
	db.~DBConnection();
}

std::string Admin::getMaskedInput(const std::string& prompt)
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
Admin::Admin(sql::ResultSet* data)
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM Admin");
	AdminID = data->getInt("AdminID");
	Admin_Username = data->getString("Admin_Username");
	Admin_Password = data->getString("Admin_Password");
	Admin_FullName = data->getString("Admin_FullName");
	Admin_PhoneNum = data->getString("Admin_PhoneNum");
	Admin_Email = data->getString("Admin_Email");
}

Admin::~Admin()
{
}

Admin Admin::viewAdmin(Admin admins)
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM Admin");
	db.QueryResult();

	Admin result;
	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
		{
			Admin found(db.res);
			result = found;
		}
	}
	db.~DBConnection();
	return result;
}

