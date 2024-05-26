#include "Staff.h"
#include <ctime>
#include <vector>
#include "DBConnection.h"
#include <iomanip>
#include <conio.h>

using namespace std;


Staff::Staff()
{
	// initialize
	StaffID = 0;
	Staff_Username = "";
	Staff_Password = "";
	Staff_FullName = "";
	Staff_PhoneNum = "";
	Staff_Email = "";
	Staff_Address = "";
	Staff_Position = "";
}

Staff::Staff(int StaffID, string Staff_Username, string Staff_Password, string Staff_FullName, string Staff_PhoneNum, string Staff_Email, string Staff_Address, string Staff_Position)
{
	this->StaffID = StaffID;
	this->Staff_Username = Staff_Username;
	this->Staff_Password = Staff_Password;
	this->Staff_FullName = Staff_FullName;
	this->Staff_PhoneNum = Staff_PhoneNum;
	this->Staff_Email = Staff_Email;
	this->Staff_Address = Staff_Address;
	this->Staff_Position = Staff_Position;
}

bool Staff::loginStaff()
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM Staff WHERE Staff_Username=? AND Staff_Password=?");
	db.stmt->setString(1, Staff_Username);
	db.stmt->setString(2, Staff_Password);
	db.QueryResult();
	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
		{
			StaffID = db.res->getInt("StaffID");
			Staff_Username = db.res->getString("Staff_Username");
			Staff_Password = db.res->getString("Staff_Password");
			Staff_FullName = db.res->getString("Staff_FullName");
			Staff_PhoneNum = db.res->getString("Staff_PhoneNum");
			Staff_Email = db.res->getString("Staff_Email");
			Staff_Address = db.res->getString("Staff_Address");
			Staff_Position = db.res->getString("Staff_Position");
		}
		db.~DBConnection();
		return true;
	}
	else {
		db.~DBConnection();
		return false;
	}
}
void Staff::insertStaff() {
	DBConnection db;
	db.prepareStatement("Insert into Staff (Staff_Username, Staff_Password, Staff_FullName, Staff_PhoneNum, Staff_Email, Staff_Address, Staff_Position) VALUES (?, ?, ?, ?, ?, ?, ?)");
	db.stmt->setString(1, Staff_Username);
	db.stmt->setString(2, Staff_Password);
	db.stmt->setString(3, Staff_FullName);
	db.stmt->setString(4, Staff_PhoneNum);
	db.stmt->setString(5, Staff_Email);
	db.stmt->setString(6, Staff_Address);
	db.stmt->setString(7, Staff_Position);
	db.QueryStatement();
	db.~DBConnection();
}
void Staff::updateStaff() {
	DBConnection db;
	db.prepareStatement("UPDATE Staff SET Staff_Username=?, Staff_Password=?, Staff_FullName=?, Staff_PhoneNum=?, Staff_Email=?, Staff_Address=?, Staff_Position=? WHERE StaffID=?");
	db.stmt->setString(1, Staff_Username);
	db.stmt->setString(2, Staff_Password);
	db.stmt->setString(3, Staff_FullName);
	db.stmt->setString(4, Staff_PhoneNum);
	db.stmt->setString(5, Staff_Email);
	db.stmt->setString(6, Staff_Address);
	db.stmt->setString(7, Staff_Position);
	db.stmt->setInt(8, StaffID);
	db.QueryStatement();
	db.~DBConnection();
}
void Staff::removeStaff()
{
	DBConnection db;
	db.prepareStatement("DELETE FROM Staff WHERE StaffID=?");
	db.stmt->setInt(1, StaffID);
	db.QueryStatement();
	db.~DBConnection();
}

std::string Staff::getMaskedInputS(const std::string& prompt)
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

Staff::Staff(sql::ResultSet* data)
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM Staff");
	StaffID = data->getInt("StaffID");
	Staff_Username = data->getString("Staff_Username");
	Staff_Password = data->getString("Staff_Password");
	Staff_FullName = data->getString("Staff_FullName");
	Staff_PhoneNum = data->getString("Staff_PhoneNum");
	Staff_Email = data->getString("Staff_Email");
	Staff_Address = data->getString("Staff_Address");
	Staff_Position = data->getString("Staff_Position");
}

bool Staff::usernameExists(const string& Staff_Username)
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM Staff WHERE Staff_Username = ? ");
	db.stmt->setString(1, Staff_Username);
	db.QueryResult();
	return (db.res->rowsCount() > 0);
}

//bool Staff::displayStaff()
//{
//	DBConnection db;
//	db.prepareStatement("SELECT * FROM Staff");
//	db.QueryResult();
//	cout << "-------------------------------------------\n";
//	cout << "\tStaff Account\n";
//	cout << "-------------------------------------------\n";
//	if (db.res->rowsCount() != 0)
//	{
//		while (db.res->next())
//		{
//			StaffID = db.res->getInt("ID");
//			Staff_Username = db.res->getString("Username");
//			Staff_Password = db.res->getString("Password");
//			Staff_FullName = db.res->getString("FullName");
//			Staff_PhoneNum = db.res->getString("Phone Number");
//			Staff_Email = db.res->getString("Email");
//			Staff_Address = db.res->getString("Address");
//			Staff_Position = db.res->getString("Position");
//
//			cout << "\n>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<\n";
//			cout << endl << "ID   : " << " " << StaffID << endl << " Username  : " << " " << Staff_Username << endl << " Password  : " << " " << Staff_Password << endl << " FullName  : " << " " << Staff_FullName << endl
//				<< " Phone Number  : " << " " << Staff_PhoneNum << endl << " Email  :" << " " << Staff_Email << endl << " Address  : " << " " << Staff_Address << endl << " Position  : " << " " << Staff_Position << endl;
//		}
//
//		cout << "\n>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<\n";
//		db.~DBConnection();
//		_getch();
//		return true;
//	}
//	else
//	{
//		db.~DBConnection();
//		return false;
//	
//	}
//}

// staff.cpp

vector<Staff> Staff::searchStaff(string Staff_FullName, string Staff_Position, bool ascending)
{
	string query = "SELECT * FROM Staff WHERE"
		" Staff_FullName LIKE ? AND Staff_Position LIKE ?"
		" ORDER BY StaffID ";

	if (ascending)
	{
		query += " ASC";
	}
	else
	{
		query += " DESC";
	}

	DBConnection db;
	db.prepareStatement(query);
	db.stmt->setString(1, "%" + Staff_FullName + "%");
	db.stmt->setString(2, "%" + Staff_Position + "%");

	vector<Staff> staffs;

	db.QueryResult();

	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			Staff tmpStaff(db.res);
			staffs.push_back(tmpStaff);
		}
	}

	return staffs;
}


Staff Staff::findStaff(int StaffID)
{
	return Staff();
	DBConnection db;
	db.prepareStatement("SELECT * FROM Staff WHERE StaffID=?");
	db.stmt->setInt(1, StaffID);
	db.QueryResult();

	Staff result;
	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
		{
			Staff found(db.res);
			result = found;
		}
	}
	db.~DBConnection();
	return result;
}

Staff::~Staff()
{
}


	


