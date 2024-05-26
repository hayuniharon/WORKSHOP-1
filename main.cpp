#pragma warning(suppress : 4996)
#include <iostream>
#include <fstream>
#include <ctime>
#include <conio.h>
#include <iomanip>
#include <regex>
#include <chrono>
#include <string>
#include <sstream>
#include <windows.h>
#include <mysql/jdbc.h>
#include <stdio.h>

// include class
#include "ArrowMenu.h"
#include "Menu.h"
#include "Admin.h"
#include "Staff.h"
#include "Customer.h"
#include "Pet.h"
#include "Payment.h"
#include "Appointment.h"
#include "Treatment.h"
#include "Sale.h"


using namespace std;


//function for admin
void adminPage();
void loginAdmin();
void homeAdmin(Admin admins); 
Admin adminProfile(Admin admins);
Staff ManageStaff(Staff staffs);
Staff registerStaff(Staff staffs);
int listStaff();
void SaleReportMenu(Admin admins, Cust custs, Payment pay, Treatment treatment);


//function for staff
void staffPage();
void loginStaff(Staff staffs);
void homeStaff(Staff staffs);
Staff profileStaff(Staff staffs);
void deleteStaff(Staff staffs);
int apptList(Staff staffs);

//function for customer
void custPage();
void registerCust(Cust custs);
void loginCust(Pet pets, Cust custs, Appointment Book);
void homeCust(Cust custs);
Cust profileCust(Pet pets,Cust custs);
Cust deleteCust(Cust custs);
int tSelection();
void homePet(Pet pets, Cust custs);
void profilePet(Cust custs);
Pet addPet(Pet pets, Cust custs);
void deletePet(Pet& pets, Cust custs);
Pet petHistory(Pet pets, Cust custs);
int viewPet();
int TreatmentList();
int selectPet(Cust custs);
Cust bookAppt(Cust custs, Pet pets, Treatment treatment, Appointment book, Payment pay);
void doPayment(Cust cust, Pet pets, Treatment treatment, Appointment book, Payment pay);
int slotTime(Appointment book);
bool validateDate(const std::string& date);



int main() {
	//int len = 0, x, y = 240; // 240 = white background, black foreground 
	//system("cls");
	//string text = " HELLO, WELCOME TO PET CARE SYSTEM :) ";
	//len = text.length();
	//cout << endl << endl << endl << "\t\t"; // start 3 down, 2 tabs, right
	//for (x = 0; x < len; x++)
	//{
	//	SetConsoleTextAttribute(console, y); // set color for the next print
	//	cout << text[x];
	//	y++; // add 1 to y, for a new color
	//	if (y > 254) // There are 255 colors. 255 being white on white. Nothing to see. Bypass it
	//		y = 240; // if y > 254, start colors back at white background, black chars
	//	Sleep(250); // Pause between letters 
	//}

	//SetConsoleTextAttribute(console, 15); // set color to black background, white chars
	//WaitKey(); // Program over, wait for a keypress to close program

	Menu mainmenu;  
	mainmenu.header = "\n\n\t ----------- WELCOME TO PET CARE SYSTEM ----------- \n\n\t Choose your role: \n\t";
	
	mainmenu.addOption("Press 1 > Admin");
	mainmenu.addOption("Press 2 > Staff");
	mainmenu.addOption("Press 3 > Customer");
	mainmenu.addOption("Press 4 > Exit");


	while (1)
	{
		switch (mainmenu.prompt())
		{
		case 1:
			adminPage();
			break;
		case 2:
			staffPage();
			break;
		case 3:
			custPage();
		case 4:
			exit(0);
			//return 0;
		/*default:
			break;*/
		}
	}

}

// **** ADMIN ****
void adminPage()
{
	ArrowMenu Rolemenu;            
	Rolemenu.header = "\n\n\t -------------------- ADMIN PAGE ------------------- \n";
	Rolemenu.addOption("Login");
	Rolemenu.addOption("Exit");

	while (1)
	{
		
		switch (Rolemenu.prompt())
		{
		case -1: 
			return;
		case 0:
			loginAdmin();
			break;
		case 1:
			main();
			break;
		}
	}

}

// login for admin
void loginAdmin()
{
	Menu loginAdmin;           
	loginAdmin.header = "\n\n\t ------------------- LOGIN AS ADMIN ------------------ \n\n\t  ";
	loginAdmin.addOption("Press 1 > Username"); 
	loginAdmin.addOption("Press 2 > Password");
	loginAdmin.addOption("Press 3 > Login");
	loginAdmin.addOption("Press 4 > Back");

	Admin admins;
	Appointment book;
	Payment pay;
	string n, p;
	char ch;

	while (1)
	{
	
		switch (loginAdmin.prompt())
		{
		case 1:
			cout << "Insert Username: ";
			getline (cin, admins.Admin_Username);
			loginAdmin.setValue(0, admins.Admin_Username);
			break;
		case 2:
			cout << "Insert Password: ";
			admins.Admin_Password = Admin::getMaskedInput("");
			loginAdmin.setValue(1, std::string(admins.Admin_Password.length(), '*'));
			break;
		case 3:
			if (admins.loginAd())
			{
			     homeAdmin(admins);
			}
			else
			{
				cout << "\n\n\t Invalid Login \n\n\t Press any key to login again. \n\n ";
				_getch();
			}
			break;
		case 4:
			main();
			break;

		}
	}
}

// admin home page
void homeAdmin (Admin admins)
{
	Staff staffs;
	Cust custs;
	Treatment treatment;
	Payment pay;
	ArrowMenu homeAdmin;         
	homeAdmin.header = "\n\n\t ----------------- HOME ADMIN PAGE ----------------- ";
	homeAdmin.addOption(" Your Profile:   ");
	homeAdmin.addOption(" Manage Staff:   ");
	homeAdmin.addOption(" Sale Report:    ");
	homeAdmin.addOption(" Logout          ");
	while (1)
	{
		homeAdmin.header = "\n\n\t Welcome, " + admins.Admin_Username; "\n\n\t ";
		switch (homeAdmin.prompt())
		{
		case -1:
			return;
			break;
		case 0:
		    admins = adminProfile(admins);
			break;
		case 1:
			ManageStaff(staffs);
			break;
		//case 2:
			//TreatmentList();
			//break;
		case 2:
			SaleReportMenu(admins, custs, pay, treatment);
			break;
		case 3:
			main();
			break;
		default:
			break;
		}
	}

}

// admin profile can update details here.
Admin adminProfile(Admin admins) 
{

	Admin temp = admins; // copy the object

	ArrowMenu profileAM;            
	profileAM.header = "\n\n\t ------------------- Your profile -------------------";
	profileAM.addOption("Admin ID     ");
	profileAM.addOption("Username     ");
	profileAM.addOption("Password     ");
	profileAM.addOption("Full Name    ");
	profileAM.addOption("Phone Number ");
	profileAM.addOption("Email        ");;
	profileAM.addOption("Save         ");
	profileAM.addOption("Back         ");

	char confirm; 
	string tmpInput;
	while (1) {
		profileAM.setValue(0, to_string(temp.AdminID));
		profileAM.setValue(1, temp.Admin_Username);
		profileAM.setValue(2, temp.Admin_Password);
		profileAM.setValue(3, temp.Admin_FullName);
		profileAM.setValue(4, temp.Admin_PhoneNum);
		profileAM.setValue(5, temp.Admin_Email);

		switch (profileAM.prompt())
		{
		case -1:
			return 0;
			break;
		case 0:
			cout << "ID cannot change.";
			_getch();
			break;
		case 1:
			cout << "Insert  new username: ";
			getline (cin, temp.Admin_Username);
			break;
		case 2:
			cout << "Insert new password: ";
			cin >> temp.Admin_Password;
			cin >> tmpInput;
			if (tmpInput.length() < 6)
			{
				cout << "\n\n\t Password must be at least 6 character long \n\n\t Press any key to continue.";
				_getch();
			}
			else
			{
				temp.Admin_Password = tmpInput;
			}
			break;
		case 3: 
			cout << "Insert Full Name: ";
			getline (cin, temp.Admin_FullName);
			break;
		case 4:
			cout << "Insert new Phone Number: ";
			cin >> temp.Admin_PhoneNum;
			break;
		case 5:
			cout << "Insert new Email: ";
			cin >> temp.Admin_Email;
			break;
		case 6:
			cout << "\n\n\tUpdate your account? (y/n)";
			char confirm;
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y') {
				admins = temp;
				admins.updateAd();
				cout << "\n\n\tInformation updated.";
				_getch();
			}
			break;
		case 7:
			return admins;
			break;
		default:
			break;
		}
	}
}

// admin access to manage staff page
Staff ManageStaff(Staff staffs)
{
	
	ArrowMenu ManageStaffMenu;                 
	ManageStaffMenu.header = "\n\n\t ------------------- MANAGE STAFF ------------------- \n\n";
	ManageStaffMenu.addOption("Register Staff");
	ManageStaffMenu.addOption("Search Staff");
	ManageStaffMenu.addOption("Back");

	Admin admins;

	while (1)
	{
		switch (ManageStaffMenu.prompt())
		{
		case -1: // prompt returns -1 when esc is pressed
			return 0;
			break;
		case 0:
			staffs = registerStaff(staffs);
			break;
		case 1:
			listStaff();
			break;
		case 2:
			return staffs;
			break;
		default:
			break;
		}
	}
}

// admin access to register staff 
Staff registerStaff(Staff staffs) {
	Staff newacc;
	Menu rgMenu;         
	rgMenu.header = "\n\n\t ------------ REGISTRATION PAGE FOR STAFF ------------ \n\n\t ";
	rgMenu.addOption(" Press 1 > Staff Username   ");
	rgMenu.addOption(" Press 2 > Staff Password   ");
	rgMenu.addOption(" Press 3 > Staff FullName   ");
	rgMenu.addOption(" Press 4 > Staff Email      ");
	rgMenu.addOption(" Press 5 > Staff PhoneNum   ");
	rgMenu.addOption(" Press 6 > Staff Address    ");
	rgMenu.addOption(" Press 7 > Staff Position     ");
	rgMenu.addOption(" Press 8 > Register         ");
	rgMenu.addOption(" Press 9 > Back             ");
	rgMenu.footer = "\n\n\t----------------------------------------------------";
	char confirm;
	string tmpinput;
	bool valid = true;
	while (1) {

		switch (rgMenu.prompt())
		{
		case 1:
			cout << "Insert Username: ";
			getline(cin, newacc.Staff_Username);
			if (newacc.usernameExists(newacc.Staff_Username))
			{
				cout << "\n\n\t Username already exists. Please choose a different username.\n";
				_getch();
				cout << "\n\n\t Insert different Username: ";
				cin >> newacc.Staff_Username;
			}
			rgMenu.setValue(0, newacc.Staff_Username);
			break;
		case 2:
			cout << "Insert Password: ";
			cin >> tmpinput;
			if (tmpinput.length() < 6)
			{
				cout << "\n\n\t Password must be at least 6 character long \n\n\t Press any key to continue.";
				_getch();
			}
			else
			{
				newacc.Staff_Password = tmpinput;
				rgMenu.setValue(1, newacc.Staff_Password);
			}
			break;
		case 3:
			cout << "Insert Full Name: ";
			getline(cin, newacc.Staff_FullName);
			rgMenu.setValue(2, newacc.Staff_FullName);
			break;
		case 4:
			cout << "Insert Email:";
			cin >> newacc.Staff_Email;
			rgMenu.setValue(3, newacc.Staff_Email);
			break;
		case 5:
			cout << "Insert Phone Number:";
			getline(cin, newacc.Staff_PhoneNum);
			rgMenu.setValue(4, newacc.Staff_PhoneNum);
			break;
		case 6:
			cout << "Insert Address:";
			getline(cin, newacc.Staff_Address);
			rgMenu.setValue(5, newacc.Staff_Address);
			break;
		case 7:
			cout << "Insert Position:";
			cin >> newacc.Staff_Position;
			rgMenu.setValue(6, newacc.Staff_Position);
			break;
		case 8:
			cout << "\n\n\t Are you sure want to register staff account? (y/n)";
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y')
			{
				staffs = newacc;
				staffs.insertStaff();
				cout << "\n\n\t Staff account successful registered.";
				_getch();
			}
			break;
		case 9:
			return staffs;
			break;
		default:
			break;
		}
	}
}

// admin access to delete staff
void deleteStaff(Staff staffs)
{
	Admin admins;
	Appointment book;
	Menu deleteSM;
	char confirm;

	deleteSM.header = "\n\n\t ------------------ DELETE STAFF ACCOUNT ------------------ \n\n";

	cout << "\n\n\tAre you sure want to delete your staffs details? (y/n)\n\n";
	confirm = _getch();
	if (confirm == 'Y' || confirm == 'y')
	{
		// Remove the pet using removePet()
		staffs.removeStaff();
		cout << "\n\n\t Your staff account deleted.";
		_getch();
		homeAdmin(admins);
	}
	else
	{
		cout << "\n\n\t Your Staff account saved. \n\n\t Press any key to continue. ";
		_getch();
		homeAdmin(admins);
	}
}

// list of staff
int listStaff()
{
	Admin admins;
	Appointment book;
	Payment pay;
	vector<Staff> staffs;
	Staff searchS;
	string displayS = "";

	int StaffID = 0;
	string Staff_FullName = "", Staff_Position = " ", Staff_Email = " ";
	bool asc = true;

	Menu searchSM;
	searchSM.header = "\n\n\t\tList Staff of Pet Care \n";
	searchSM.addOption(" 1 > View By Name");
	searchSM.addOption(" 2 > View By Position");
	searchSM.addOption(" 3 > View All Staff: ");
	searchSM.addOption(" 4 > Back");
	searchSM.addOption(" 5 > Delete Staff Account");

	while (1)
	{
		if (asc)
		{
			searchSM.setValue(2, "Ascending");
		}
		else
		{
			searchSM.setValue(2, "Descending");
		}
		if (displayS == "")
		{
			displayS = "\n\tResult:\n\n";
			stringstream tmpS;

			tmpS << setw(10) << "\tStaff ID  | " << setw(36) << "\tStaff FullName    | " << setw(16) << "\tStaff Position  | " << setw(26) << "\tStaff Email      | " << "\n "
				<< endl;

			for (int i = 0; i < staffs.size(); i++)
			{
				tmpS << setw(10) << staffs[i].StaffID << "\t  |" << setw(35) << staffs[i].Staff_FullName << "\t  |" << setw(16) << staffs[i].Staff_Position << "\t|" << setw(25) << staffs[i].Staff_Email << "\t |" << endl;
			}
			displayS += tmpS.str();
		}
		searchSM.footer = displayS;

		switch (searchSM.prompt())
		{
		case 1:
			cout << " Insert Staff Name: ";
			cin.ignore(); // Ignore newline character in the buffer
			getline(cin, Staff_FullName);
			searchSM.setValue(0, Staff_FullName);
			staffs = Staff::searchStaff(Staff_FullName, Staff_Position, asc);
			displayS = "";
			break;
		case 2:
			cout << " Insert Position: ";
			cin.ignore(); // Ignore newline character in the buffer
			getline(cin, Staff_Position);
			searchSM.setValue(1, Staff_Position);
			staffs = Staff::searchStaff(Staff_FullName, Staff_Position, asc);
			displayS = "";
			break;
		case 3:
			asc = !asc;
			staffs = Staff::searchStaff("", "", asc); // View all staff, no criteria
			displayS = "";
			break;
		case 4:
			homeAdmin(admins);
			break;
		case 5:
			cout << " Insert Staff ID to delete account: ";
			cin >> StaffID;
			searchSM.setValue(1, to_string(StaffID));
			for (Staff& staffs : staffs) {
				if (staffs.StaffID == StaffID) {
					deleteStaff(staffs);
				}
			}
			break;
			break;
		}
	}
}

// treatment list
int tSelection()
{
	Menu treatM;
	treatM.header = "\n\n\t\t Treatment Category";
	treatM.addOption(" 1 > Basic");
	treatM.addOption(" 2 > Classic");
	treatM.addOption(" 3 > Advance");
	treatM.addOption(" 4 > Extreme");
	while (1)
	{
		return treatM.prompt();
	}
}

// sale report
void SaleReportMenu(Admin admins, Cust custs, Payment pay, Treatment treatment) {

	string start, endDate;

	vector<int> TreatmentID;

	bool sortByDate = true, ascending = true;

	ArrowMenu saleM;
	saleM.addOption("Start");
	saleM.addOption("End");
	saleM.addOption("Treatment");
	saleM.addOption("Sort By");
	saleM.setValue(3, "Date");
	saleM.addOption("Order");
	saleM.setValue(4, "Ascending");
	saleM.addOption("Generate");
	saleM.addOption("Back");

	ofstream outputFile("ReportSale.txt"); // Open a file for Report Sale
	vector<Sale> result; // vector to store the result

	// we declare it like this so that the index matches their id in the database
	string NameT[] = { "","Basic","Classic","Advance","Extreme" };

	//declare outside so that we don't unnecessarily declare new variable in each loop iteration
	string selectedNameT;
	int tmpSelectedTreatmentID;

	vector<int>::iterator iterator; //iterator is declare using what we are iterating, in this case it is vector of integer
	int option = 0;

	while (1)
	{

		selectedNameT = "";
		if (TreatmentID.empty()) {
			selectedNameT = "NONE";
		}
		else {
			for (int i = 0; i < TreatmentID.size(); i++) {
				selectedNameT += NameT[TreatmentID[i]] + ", ";
			}
		}
		saleM.setValue(2, selectedNameT);



		// report display
		stringstream ss;
		// construct our report header
		ss << endl << "\t\t\t--------------------------------- SALES REPORT ---------------------------------\n" << endl << "\t\t\t\t" << "|" << setw(20) << "Date Time" << "|";
		if (!TreatmentID.empty()) {
			// if treatment id not empty we add treatment column
			ss << "\t" << setw(18) << "     Treatment" << "|";
		}
		ss << setw(20) << "Total Payment" << "|";

		ss << "\n\t\t\t--------------------------------------------------------------------------------";

		float Total_Payment = 0;
		// repeat same structure for content of the report
		for (int i = 0; i < result.size(); i++) {
			ss << endl << "\t\t\t\t" << "|" << setw(20) << result[i].Payment_Date.substr(0, 7) << "|";

			if (!TreatmentID.empty()) {
				// if category id not empty we add category column
				ss << setw(20) << result[i].NameT << "|";

			}

			ss << setw(20) << result[i].value << "|";
			Total_Payment += result[i].value;  // calculate total sale 


		}
		ss << "\n\t\t\t--------------------------------------------------------------------------------";
		ss << endl << "\t\t\t\t" << "|" << setw(20) << "Total Sale" << "|";
		if (!TreatmentID.empty()) {
			// if category id not empty we add category column
			ss << setw(20) << "" << " ";
		}
		ss << setw(20) << Total_Payment << "|";

		ss << endl << "\n\t\t\t--------------------------------- END OF REPORT ---------------------------------" << endl;
		saleM.header = ss.str();

		option = saleM.prompt(option);
		switch (option)
		{
		case -1:
			return;
			break;
		case 0:
			cout << "Insert start date (yyyy-mm-dd): ";
			cin >> start;
			saleM.setValue(0, start);
			break;
		case 1:
			cout << "Insert end date (yyyy-mm-dd): ";
			cin >> endDate;
			saleM.setValue(1, endDate);
			break;
		case 2: //toggle category
			tmpSelectedTreatmentID = tSelection();

			//find the selected category id inside our categoryIds vector
			iterator = find(TreatmentID.begin(), TreatmentID.end(), tmpSelectedTreatmentID);

			if (iterator == TreatmentID.end()) {//if the iterator reaches the end means not found
				TreatmentID.push_back(tmpSelectedTreatmentID);
			}
			else {
				TreatmentID.erase(iterator); //if it exist erase it
			}

			break;
		case 3:// sort by
			sortByDate = !sortByDate;
			if (sortByDate)
				saleM.setValue(3, "Date");
			else
				saleM.setValue(3, "Price");
			break;
		case 4:
			ascending = !ascending;
			if (ascending)
				saleM.setValue(4, "Ascending");
			else
				saleM.setValue(4, "Descending");
			break;
		case 5:
			result.clear();
			result = Sale::salesReport(start, endDate, TreatmentID, sortByDate, ascending);
			cout << "Report generated successfully. Check 'ReportSale.txt' for your report details.\n";
			_getch();

			if (outputFile.is_open()) {
				outputFile << "--------------------------------- SALES REPORT ---------------------------------\n\n";
				outputFile << "|" << setw(20) << "Date Time" << "|";

				if (!TreatmentID.empty()) {
					outputFile << setw(18) << "     Treatment" << "|";
				}

				outputFile << setw(20) << "Total Payment" << "|\n";
				outputFile << "--------------------------------------------------------------------------------\n";

				double Total_Payment = 0;

				for (const Sale& sale : result) {
					outputFile << "|" << setw(20) << sale.Payment_Date.substr(0, 7) << "|";

					if (!TreatmentID.empty()) {
						outputFile << setw(20) << sale.NameT << "|";
					}

					outputFile << setw(20) << sale.value << "|\n";

					Total_Payment += sale.value;
				}
				outputFile << "\n--------------------------------------------------------------------------------";
				outputFile << "\n" << "|" << setw(20) << "Total Sale" << "| ";

				if (!TreatmentID.empty()) {
					outputFile << setw(20) << "" << " ";
				}

				outputFile << setw(20) << Total_Payment << "|\n";
				outputFile << "\n--------------------------------- END OF REPORT ---------------------------------\n";
				time_t now = time(0); // get current dat/time with respect to system  
				char* dt = ctime(&now);
				outputFile << "\n********************************************************************************** \n\n The report generated on " << dt << endl;
				cout << "Report generated successfully. Check 'ReportSale.txt' for your report details.\n";
			}
			else {
				cout << "Error opening the file 'ReportSale.txt' for writing.\n";
			}
			break;
		case 6:
			Appointment book;
			homeAdmin(admins);
		}

	}
	outputFile.close();
}

//Treatment
int TreatmentList()
{
	Admin admins; 
	Payment pay;
	Appointment book;
	vector<Treatment> treatment;
	Treatment searchT;
	string displayT = "";

	int TreatmentID = 0;
	string NameT = "", Description = " ";
	double Price = 0.0;
	int minPrice = 0, maxPrice = 999999;
	bool asc = true;
	

	Menu searchTM;
	searchTM.header = "\n\n\t\tSearch Treatment: \n\n";
	searchTM.addOption(" 1 > Name ");
	searchTM.addOption(" 2 > Description");
	searchTM.addOption(" 3 > Minimum price");
	searchTM.addOption(" 4 > Maximum price");
	searchTM.addOption(" 5 > Ordering");
	searchTM.addOption(" 6 > Search");
	searchTM.addOption(" 7 > Select");


	while (1)
	{
		if (asc)
		{
			searchTM.setValue(4, "Ascending");
		}
		else
		{
			searchTM.setValue(4, "Descending");
		}
		if (displayT == "")
		{
			displayT = "\nResult:\n\n";
			stringstream tmpS;

			tmpS << setw(5) << " Treatment ID | " << setw(12) << " Name | " << setw(52) << " Description | " << setw(12) << " Price | " << "\n" << endl;

			for (int i = 0; i < treatment.size(); i++)
			{
				tmpS << setw(13) << treatment[i].TreatmentID << " |" << setw(10) << treatment[i].NameT << " |" << setw(50) << treatment[i].Description << " |" <<  setw(10) << treatment[i].Price << " |" << endl;
			}
			displayT += tmpS.str();

		}
		searchTM.footer = displayT;


		switch (searchTM.prompt())
		{
		case 1:
			cout << " Insert Name: ";
			getline(cin, NameT);
			searchTM.setValue(0, NameT);
			break;
		case 2:
			cout << " Insert Description: ";
			getline(cin, Description);
			searchTM.setValue(1, Description);
			break;
		case 3:
			cout << "Insert Minimum Price: ";
			cin >> minPrice;
			searchTM.setValue(2, to_string(minPrice));
			break;
		case 4:
			cout << "Insert Maximum Price: ";
			cin >> maxPrice;
			searchTM.setValue(3, to_string(maxPrice));
			break;       
		case 5:
			asc = !asc;
			break;
		case 6:
			treatment = Treatment::findTreatment(TreatmentID, NameT, Description, minPrice, maxPrice, asc);
			displayT = "";
			break;
		case 7:
			return 0;
			break;
		}
	}
}

// ***** STAFF *****
void staffPage()
{
	Staff staffs;
	ArrowMenu Rolemenu;       
	Rolemenu.header = "\n\n\t -------------------- STAFF PAGE -------------------- \n\n\t Select Option: ";
	Rolemenu.addOption("Register");
	Rolemenu.addOption("Login");
	Rolemenu.addOption("Exit");

	while (1)
	{
		switch (Rolemenu.prompt())
		{
		case -1: // prompt returns -1 when esc is pressed
			return;
			break;
		case 0:
			cout << "";
			cout << "\n\n\tStaff can't proceed registration by themselves. \n\n\tContact  administrator to register as a staff. \n\n\tPlease press any key to continue.";
			_getch();
			break;
		case 1:
			loginStaff(staffs);
			break;
		case 2:
			return;
		default:
			break;
		}
	}

}

// login for staff
void loginStaff(Staff staffs)
{
	Menu loginStaff;
	loginStaff.header = "\n\n\t ------------------ LOGIN AS STAFF ------------------ \n\n";
	loginStaff.addOption("Press 1 > Username");
	loginStaff.addOption("Press 2 > Password");
	loginStaff.addOption("Press 3 > Login");
	loginStaff.addOption("Press 4 > Back");

	while (1)
	{
		switch (loginStaff.prompt())
		{
		case 1:
			cout << "Insert Username: ";
			getline (cin, staffs.Staff_Username);
			loginStaff.setValue(0, staffs.Staff_Username);
			break;
		case 2:
			cout << "Insert Password: ";
			staffs.Staff_Password = Staff::getMaskedInputS("");
			loginStaff.setValue(1, std::string(staffs.Staff_Password.length(), '*'));
			break;

		case 3:
			if (staffs.loginStaff())
			{
				homeStaff(staffs);
			}
			else
			{
				cout << "\n\n\t\t\t\t\tInvalid Login \n\n\t\t\t\t\tPress any key to login again.";
				_getch();
			}
			break;
		case 4:
			main();
			break;
		/*default:
			break;*/
		}
	}
}

// staff home page
void homeStaff(Staff staffs)
{
	Pet pets;
	Cust custs;
	Payment pay;
	ArrowMenu homeStaff;        
	homeStaff.header = "\n\n\t ----------------- HOME PAGE STAFF ------------------ ";
	homeStaff.addOption(" Your Profile ");
	homeStaff.addOption(" Appointment List "); // DELETE
	homeStaff.addOption(" Pet List ");  // UPDATE PET
	homeStaff.addOption(" Logout");
	while (1)
	{
		homeStaff.header = "\n\n\t Welcome, " + staffs.Staff_Username; "\n\n";
		switch (homeStaff.prompt())
		{
		case -1:
			return;
			break;
		case 0:
			staffs = profileStaff(staffs);
			break;
		case 1:
			apptList(staffs);
			break;
		case 2:
			viewPet();
			break;
		case 3:
			main();
			break;
		default: 
			break;
		}
	}

}

// appointment list to view by staff
 int apptList(Staff staffs)
{
	vector<Appointment> book;
	Pet pets;
	Cust custs;
	string displayB = "";
	Appointment temp;
	int AppointmentID = 0, PetID = 0, TreatmentID = 0;
	string Booking_Date = "", Booking_Time = "", status = "";
	bool asc = true;

	Menu searchB;
	searchB.header = "\n\n\t\tSearch Appointment: ";
	searchB.addOption(" 1 > Search by TreatmentID");
	searchB.addOption(" 2 > Search by PetID");
	searchB.addOption(" 3 > View All Appointment");
	searchB.addOption(" 4 > Back");
	searchB.addOption(" 5 > Update Status ");

	while (1)
	{
		if (asc)
		{
			searchB.setValue(2, "Ascending");
		}
		else
		{
			searchB.setValue(2, "Descending");
		}
		if (displayB == "")
		{
			displayB = "\n\tResult:\n\n";
			stringstream tmpS;

			tmpS << setw(5) << " Appointment ID | " << setw(14) << " Treatment ID  | "   << setw(8) << "Pet ID | " << setw(13) << " Booking Date  | " << setw(13) << " Booking Time | " << setw(20)  << " Status | " << "\n" << endl;

			for (int i = 0; i < book.size(); i++)
			{
				tmpS << setw(15) << book[i].AppointmentID << " |" << setw(15) << book[i].TreatmentID << " |" << setw(7) << book[i].PetID << " |" << setw(15) << book[i].Booking_Date << " |" << setw(14) << book[i].Booking_Time << " |" << setw(18) << book[i].status << " |" << endl;
			}
			displayB += tmpS.str();

		}
		searchB.footer = displayB;


		switch (searchB.prompt())
		{
		case 1:
			cout << " Insert TreatmentID: ";
			cin >> TreatmentID;
			searchB.setValue(0, to_string(TreatmentID));
			book = Appointment::findBook(Booking_Date, TreatmentID, PetID, asc);
			displayB = "";
			break;
		case 2:
			cout << " PetID: ";
			cin >> PetID;
			searchB.setValue(1, to_string(PetID));
			book = Appointment::findBook(Booking_Date, TreatmentID, PetID, asc);
			displayB = "";
			break;
		case 3:
			asc = !asc;
			book = Appointment::findBook(Booking_Date, TreatmentID, PetID, asc);
			displayB = "";
			break;
		case 4:
			homeStaff(staffs);
			break;
	   case 5:
		   // Update Status
		   cout << "Enter Appointment ID to update status: ";
		   cin >> AppointmentID;

		   // Find the appointment with the specified AppointmentID
		   auto it = find_if(book.begin(), book.end(), [AppointmentID](const Appointment& appt) {
			   return appt.AppointmentID == AppointmentID;
			   });

		   if (it != book.end()) {
			   // Appointment found, update the status
			   cout << "Enter new status: ";
			   cin >> status;
			   it->status = status;
			   it->updateAppt();
			   cout << "Status updated successfully." << endl;
		   }
		   else {
			   cout << "Appointment not found." << endl;
			   _getch();
		   }

		   break;
		}
	}
}

// staff can view and update account
Staff profileStaff(Staff staffs)
{

	Staff temp = staffs; // copy the object

	ArrowMenu profileSM ;          
	profileSM.header = "\n\n\t ------------------- Your profile -------------------\n";
	profileSM.addOption("Staff ID     ");
	profileSM.addOption("Username     ");
	profileSM.addOption("Password     ");
	profileSM.addOption("Full Name    ");
	profileSM.addOption("Phone Number ");
	profileSM.addOption("Email        ");
	profileSM.addOption("Address      ");
	profileSM.addOption("Save         ");
	profileSM.addOption("Back         ");

	char confirm;
	string tmpInput;
	while (1) {
		profileSM.setValue(0, to_string(temp.StaffID));
		profileSM.setValue(1, temp.Staff_Username);
		profileSM.setValue(2, temp.Staff_Password);
		profileSM.setValue(3, temp.Staff_FullName);
		profileSM.setValue(4, temp.Staff_PhoneNum);
		profileSM.setValue(5, temp.Staff_Email);
		profileSM.setValue(6, temp.Staff_Address);

		switch (profileSM.prompt())
		{
		case -1: // prompt returns -1 when esc is pressed
			return 0;
			break;
		case 0:
			cout << "ID cannot change.";
			_getch();
			break;
		case 1:
			cout << "Insert  new username: ";
			getline (cin, temp.Staff_Username);
			break;
		case 2:
			cout << "Insert new password: ";
			cin >> temp.Staff_Password;
			cin >> tmpInput;
			if (tmpInput.length() < 6)
			{
				cout << "\n\n\t Password must be at least 6 character long \n\n\t Press any key to continue.";
				_getch();
			}
			else
			{
				temp.Staff_Password = tmpInput;
			}

			break;
		case 3:
			cout << "Insert Full Name: ";
			getline (cin, temp.Staff_FullName);
		
			break;
		case 4:
			cout << "Insert new Phone Number: ";
			cin >> temp.Staff_PhoneNum;
	
			break;
		case 5:
			cout << "Insert new Email: ";
			cin >> temp.Staff_Email;
			
			break;
		case 6:
			cout << "Insert address: ";
			getline (cin, temp.Staff_Address);
		
			break;
		case 7:
			cout << "\n\n\tUpdate your account? (y/n)";
			char confirm;
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y') {
				staffs = temp;
				staffs.updateStaff();
				cout << "\n\n\tInformation updated.";
				_getch();
			}
			
			break;
		case 8:
			return staffs;
		
			break;
		default:
			break;
		}
	}
}

// pet list to view by staff
int viewPet()
{
	
	vector<Pet> pets;
	Staff staffs;
	Cust custs;
	string displayP = "";
	//Pet pets;
	int PetID = 0;
	string Pet_Name = "", Pet_Species = " ", Pet_Status=" ";
	bool asc = true;
	auto it = pets.begin();

	Menu searchP;
	searchP.header = "\n\n\t\tSearch Pet: \n";
	searchP.addOption(" 1 > Search by Pet Name");
	searchP.addOption(" 2 > Search by Pet Species");
	searchP.addOption(" 3 > View all Pet ");
	searchP.addOption(" 4 > Update Pet Status");
	searchP.addOption(" 5 > Back");


	while (1)
	{
		if (asc)
		{
			searchP.setValue(2, "Ascending");
		}
		else
		{
			searchP.setValue(2, "Descending");
		}
		if (displayP == "")
		{
			displayP = "\n\tResult:\n\n";
			stringstream tmpS;

			tmpS << setw(7) << " Pet ID | " << setw(16) << " Customer ID | " << setw(17) << " Pet Name | " << setw(18) << " Pet Species | " << setw(22) <<
				" Pet Breed | " << setw(22) << " Pet Color | " << setw(22) << " Pet Gender | " << setw(22) << " Pet Weight | " << setw(22) << " Pet Status | " << endl;
			tmpS << " ------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \n" << endl;

			for (int i = 0; i < pets.size(); i++)
			{
				tmpS << setw(7) << pets[i].PetID << " |" << setw(14) << pets[i].CustID << " |" << setw(15) << pets[i].Pet_Name << " |" << setw(16) << pets[i].Pet_Species << " |" << setw(20) << 
					pets[i].Pet_Breed << " |" << setw(20) << pets[i].Pet_Color << " |" << setw(20) << pets[i].Pet_Gender << " |" << setw(20) << pets[i].Pet_Weight << " |" << setw(20) << pets[i].Pet_Status  << " |" << endl;
			}
			displayP += tmpS.str();

		}
		searchP.footer = displayP;


		switch (searchP.prompt())
		{
		case 1:
			cout << " Insert Pet Name: ";
			getline(cin, Pet_Name);
			searchP.setValue(0, Pet_Name);
			pets = Pet::searchPet(Pet_Name, Pet_Species, asc);
			displayP = "";
			break;
		case 2:
			cout << " Insert Pet Species: ";
			getline(cin, Pet_Species);
			searchP.setValue(1, Pet_Species);
			pets = Pet::searchPet(Pet_Name, Pet_Species, asc);
			displayP = "";
			break;
		case 3:
			asc = !asc;
			pets = Pet::searchPet(Pet_Name, Pet_Species, asc);
			displayP = "";
			break;
		case 4:
			// Update Status
			cout << "Enter Pet ID to update status: ";
			cin >> PetID;

		     it = find_if(pets.begin(), pets.end(), [PetID](const Pet& pet) {
				return pet.PetID == PetID;
				});

			if (it != pets.end()) {
				// Pet found, update the status
				cout << "Enter new pet current status: ";
				cin >> Pet_Status;
				//searchP.setValue(0, Pet_Status);
				it->Pet_Status = Pet_Status;

				// Update status in the database
				it->updateStatus();

				cout << "Status updated successfully." << endl;
				
			}
			else {
				cout << "Pet ID not found." << endl;
				_getch();

			}
			break;

		case 5:
			homeStaff(staffs);
			break;
		}
	}
}


// ***** CUSTOMER *****
void custPage()
{
	Cust custs;
	Pet pets;
	Appointment Book;
	ArrowMenu Rolemenu;
            
	Rolemenu.header = "\n\n\t ------------------- CUSTOMER PAGE ------------------- \n\n\t Select Option: ";
	Rolemenu.addOption("Register");
	Rolemenu.addOption("Login");
	Rolemenu.addOption("Exit");

	while (1)
	{
		switch (Rolemenu.prompt())
		{
		case -1: // prompt returns -1 when esc is pressed
			return;
			break;
		case 0:
			registerCust(custs);
	
			break;
		case 1:
			loginCust(pets,custs,Book);
		
			break;
		case 2:
			return;
	
		default:
			break;
		}
	}

}

// registration for customer
void registerCust(Cust custs) {
	Pet pets;
	Appointment Book;
	Cust newacc;
	Menu rgMenu;
        
	rgMenu.header = "\n\n\t ---------- REGISTRATION PAGE FOR CUSTOMER ---------- \n\n\t ";
	rgMenu.addOption(" Press 1 > Username");
	rgMenu.addOption(" Press 2 > Password");
	rgMenu.addOption(" Press 3 > FullName");
	rgMenu.addOption(" Press 4 > PhoneNum");
	rgMenu.addOption(" Press 5 > Email");
	rgMenu.addOption(" Press 6 > Address");
	rgMenu.addOption(" Press 7 > Register");
	rgMenu.addOption(" Press 8 > Back");
	rgMenu.footer = "\n\n\t ---------------------------------------------------- \n\n";

	string tmpinput;
	bool valid = true;
	while (1) {

		switch (rgMenu.prompt()) {
		case 1:
			cout << "Insert Username: ";
			getline (cin, newacc.Cust_Username);
			rgMenu.setValue(0, newacc.Cust_Username);
		 
			break;
		case 2:
			cout << "Insert Password: ";
			cin >> tmpinput;
			if (tmpinput.length() < 6)
			{
				cout << "Password must be at least 6 character long";
				_getch();
			}
			else
			{
				newacc.Cust_Password = tmpinput;
				rgMenu.setValue(1, newacc.Cust_Password);
			}
			
			break;
		case 3:
			cout << "Insert Full Name: ";
			getline (cin, newacc.Cust_FullName);
			rgMenu.setValue(2, newacc.Cust_FullName);
		
			break;
		case 4:
			cout << "Insert Phone Number:";
			cin >> newacc.Cust_PhoneNum;
			rgMenu.setValue(3, newacc.Cust_PhoneNum);
		
			break;
		case 5:
			cout << "Insert Email:";
			cin >> newacc.Cust_Email;
			rgMenu.setValue(4, newacc.Cust_Email);
		
			break;
		case 6:
			cout << "Insert Address:";
			getline (cin, newacc.Cust_Address);
			rgMenu.setValue(5, newacc.Cust_Address);
			
			break;
		case 7:
			cout << "\n\n\tAre you sure to proceed the registration? (y/n) \n\n";
			char confirm;
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y')
			{
				valid = true;
				newacc.insertCust();
				cout << "\n\n\t ______ You are successfully registered as Customer ______";
				_getch();
			}
		
			break;
		case 8:
			loginCust(pets, custs,Book);
			break;
		default:
			break;
		}
	}
}

// login for customer
void loginCust(Pet pets, Cust cust, Appointment Book)
{
	Menu loginCust;
	loginCust.header = "\n\n\t ---------------- LOGIN AS CUSTOMER -----------------\n\n\t  ";
	loginCust.addOption("Press 1 For Username");
	loginCust.addOption("Press 2 For Password");
	loginCust.addOption("Press 3 For Login");
	loginCust.addOption("Press 4 For Back");

	Cust custs;

	while (1)
	{
		switch (loginCust.prompt())
		{
		case 1:
			cout << "Insert Username: ";
			getline (cin, custs.Cust_Username);
			loginCust.setValue(0, custs.Cust_Username);
		
			break;
		case 2:
			cout << "Insert Password: ";
			custs.Cust_Password = Cust::getMaskedInput("");
			loginCust.setValue(1, std::string(custs.Cust_Password.length(), '*'));
			break;
		case 3:
			if (custs.loginCust())
			{
				homeCust(custs);
			}
			else
			{
				cout << "\n\n\t Invalid Login \n\n\t Press any key to login again.";
				_getch();
			}
		
			break;
		case 4:
			main();
	
			break;
		/*default:
			break;*/
		}
	}
}

// customer home page
void homeCust(Cust custs)
{
	Pet pets;
	Appointment book;
	Treatment treatment;
	Payment pay;
	ArrowMenu homeCust;
	homeCust.header = "\n\n\t ---------------- HOME PAGE CUSTOMER ---------------- \n";
	homeCust.addOption(" Your Profile");
	homeCust.addOption(" Pet Profile");
	homeCust.addOption(" Book Appointment");
	homeCust.addOption(" Logout");
	homeCust.addOption(" Delete Account");
	while (1)
	{
		homeCust.header = "\n\n\t Welcome, " + custs.Cust_Username + "\n\n";
		switch (homeCust.prompt())
		{
		case -1:
			return;
			break;
		case 0:
			custs = profileCust(pets,custs);
		
			break;
		case 1:
			homePet(pets, custs);
			break;
		case 2:
			bookAppt(custs, pets, treatment,book, pay);
			break;
		case 3:
			main();
			
			break;
		case 4:
			deleteCust(custs);
		default:
			break;
		}
	}

}

// customer can view and update account
Cust profileCust(Pet pets,Cust custs) 
{

    Cust temp = custs; // copy the object

	ArrowMenu profileCM;
	          
	profileCM.header = "\n\n\t ------------------- Your profile -------------------";
	profileCM.addOption("Customer ID   ");
	profileCM.addOption("Username     ");
	profileCM.addOption("Password     ");
	profileCM.addOption("Full Name    ");
	profileCM.addOption("Phone Number ");
	profileCM.addOption("Email        ");
	profileCM.addOption("Address      ");
	profileCM.addOption("Save         ");
	profileCM.addOption("Back         ");

	char confirm;
	string tmpInput;
	while (1) {
		profileCM.setValue(0, to_string(temp.CustID));
		profileCM.setValue(1, temp.Cust_Username);
		profileCM.setValue(2, temp.Cust_Password);
		profileCM.setValue(3, temp.Cust_FullName);
		profileCM.setValue(4, temp.Cust_PhoneNum);
		profileCM.setValue(5, temp.Cust_Email);
		profileCM.setValue(6, temp.Cust_Address);

		switch (profileCM.prompt())
		{
		case -1:
			return custs;
			break;
		case 0:
			cout << "\n\nID cannot change.";
			_getch();
			
			break;
		case 1:
			cout << "Insert  new username: ";
			getline (cin, temp.Cust_Username);
			break;
		case 2:
			cout << "Insert new password: ";
			cin >> temp.Cust_Password;
			cin >> tmpInput;
			if (tmpInput.length() < 6)
			{
				cout << "\n\n\t Password must be at least 6 character long \n\n\t Press any key to continue.";
				_getch();
			}
			else
			{
				temp.Cust_Password = tmpInput;
			}
			break;
		case 3:
			cout << "Insert Full Name: ";
			getline (cin, temp.Cust_FullName);
			break;
		case 4:
			cout << "Insert new Phone Number: ";
			cin >> temp.Cust_PhoneNum;
			break;
		case 5:
			cout << "Insert new Email: ";
			cin >> temp.Cust_Email;
			break;
		case 6:
			cout << "Insert address: ";
			getline (cin, temp.Cust_Address);
			break;
		case 7:
			cout << "\n\n\tUpdate your account? (y/n)";
			char confirm;
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y') {
				custs = temp;
				custs.updateCust();
				cout << "\n\n\tInformation updated.";
				_getch();
			}
			break;
		case 8:
			return custs;
			break;
	    default:
			break;
		}
	}
}

// customer delete account
Cust deleteCust(Cust custs)
{
	Cust temp = custs;
	Menu deleteCM;
	char confirm;
         
    deleteCM.header = "\n\n\t ------------------ DELETE ACCOUNT ------------------ \n\n";
	
	cout << "\n\n\tAre you sure want to delete your account? (y/n)\n\n";
	confirm = _getch();
	if (confirm == 'Y' || confirm == 'y')
	{
		custs = temp;
		custs.removeCust();
		cout << "\n\n\t Customer account deleted.";
		_getch();
		homeCust(custs);
	}
	else
	{
		cout << "\n\n\t Account saved. \n\n\t Press any key to continue. ";
		_getch();
		homeCust(custs);
	}
	return custs;
}

// home page for pet
void homePet(Pet pets, Cust custs)
{

	ArrowMenu homePet;
         
	homePet.header = "\n\n\t --------------------- YOUR PET --------------------- \n";
	homePet.addOption(" Pet Profile");
	homePet.addOption(" Add Pet");
	homePet.addOption(" Appointment History ");
	homePet.addOption(" Logout");
	while (1)
	{
		switch (homePet.prompt())
		{
		case -1:
			return;
			break;
		case 0:
			profilePet(custs);
			break;
		case 1:
			pets = addPet(pets, custs);
			break;
		case 2:
			petHistory(pets,custs);
			break;
		case 3:
			homeCust(custs);
			break;
	
		default:
			break;
		}
	}
}

// view all pet history
Pet petHistory(Pet pets, Cust custs)
{
	vector<Appointment> book;
	string displayHistory = "";
	int PetID = 0, AppointmentID = 0;
	bool ascending = true;
	Menu OPMenu;
	OPMenu.header = "\n\n\t ----------------- Appointment History ----------------- \n";

	OPMenu.addOption(" 1 > Search by PetID ");
	OPMenu.addOption(" 2 > View All History: ");
	OPMenu.addOption(" 3 > Back To Your Page ");

	while (1)
	{
		if (ascending)
		{
			OPMenu.setValue(1, "Ascending");
		}
		else
		{
			OPMenu.setValue(1, "Descending");
		}

		if (displayHistory == "")
		{
			displayHistory = "\n\n\t Your History: ";
			stringstream tmpPet;
			tmpPet << setw(4) << "\t\t Pet ID" << "|" << setw(14) << " Appointment ID" << "|" << setw(13) << " Treatment ID" << "|" << setw(13) << " Date " << "|" << setw(5) << " Time Slot" << "|" << setw(15) << " Comment" << "|" <<endl;
			tmpPet << "\t\t\t\t ----------------------------------------------------------------------------- " << endl;

			for (int i = 0; i < book.size(); i++)
			{
				tmpPet << "\t\t\t\t " << setw(5) << book[i].PetID << " |" << setw(14) << book[i].AppointmentID << " |"
					<< setw(12) << book[i].TreatmentID << " |" << setw(12) << book[i].Booking_Date << " |" << setw(10) << book[i].Booking_Time << "|" << setw(15) << book[i].status << "|" << endl;
			}

			displayHistory += tmpPet.str();
		}

		OPMenu.footer = displayHistory;

		switch (OPMenu.prompt())
		{
		case 1:
			cout << "Insert PetID: ";
			cin >> PetID;
			OPMenu.setValue(0, to_string(PetID));
			book = Appointment::history(PetID, AppointmentID, ascending);
			displayHistory = "";
			break;
		case 2:
			ascending = !ascending;
			book = Appointment::history(PetID, AppointmentID, ascending);
			displayHistory = "";
			break;
		case 3:
			homeCust(custs);
			break;
		}
	}
}

// adding pet
Pet addPet(Pet pets, Cust custs)
{
	
	Pet newpet = pets;
	newpet.CustID = custs.CustID;
	Menu addMenu;        
	addMenu.header = "\n\n\t ------------------- ADD YOUR PET ------------------- \n\n";
	addMenu.addOption(" Press 1 > Pet Name: ");
	addMenu.addOption(" Press 2 > Species: ");
	addMenu.addOption(" Press 3 > Breed: ");
	addMenu.addOption(" Press 4 > Color: ");
	addMenu.addOption(" Press 5 > Gender: ");
	addMenu.addOption(" Press 6 > Weight: ");
	addMenu.addOption(" Press 7 > Add");
	addMenu.addOption(" Press 8 > Back");

	string tmpinput;
	bool valid = true;
	while (1)
	{
		switch (addMenu.prompt())
		{
		case 1:
			cout << "Insert your pet name: ";
			getline (cin, newpet.Pet_Name);
			addMenu.setValue(0, newpet.Pet_Name);
			break;
		case 2:
			cout << "Insert species of pet: ";
			getline (cin, newpet.Pet_Species);
			addMenu.setValue(1, newpet.Pet_Species);
			break;
		case 3:
			cout << "Insert breed of pet: ";
			getline (cin, newpet.Pet_Breed);
			addMenu.setValue(2, newpet.Pet_Breed);
			break;
		case 4:
			cout << "Insert color of pet: ";
			getline (cin, newpet.Pet_Color);
			addMenu.setValue(3, newpet.Pet_Color);
			break;
		case 5:
			cout << "Insert gender of pet: ";
			getline (cin, newpet.Pet_Gender);
			addMenu.setValue(4, newpet.Pet_Gender);
			break;
		case 6:
			cout << "Insert weight of pet (in kg): ";
			cin >> newpet.Pet_Weight;
			addMenu.setValue(5, newpet.Pet_Weight);
			break;
		case 7:
			valid = true;
			newpet.insertPet();
			cout << "\n\n\t ______ You are successfully add your pet! ______";
			_getch();
			break;
		case 8:
			return pets;
		default:
			break;
		}
	}
}

// customer delete their pet
void deletePet(Pet& pet, Cust custs)
{
	Appointment book;
	Menu deletePM;
	char confirm;

	deletePM.header = "\n\n\t ------------------ DELETE YOUR PET ------------------ \n\n";

	cout << "\n\n\tAre you sure want to delete your pet details? (y/n)\n\n";
	confirm = _getch();
	if (confirm == 'Y' || confirm == 'y')
	{
		// Remove the pet using removePet()
		pet.removePet();
		cout << "\n\n\t Your Pet deleted.";
		_getch();
		homeCust(custs);
	}
	else
	{
		cout << "\n\n\t Your Pet saved. \n\n\t Press any key to continue. ";
		_getch();
		homePet(pet, custs);
	}
}

// view pet profile
void profilePet(Cust custs)
{
	vector<Pet> pets;
	Pet temp;
	Pet selPet;
	string displayPet = "";


	int CustID = 0, PetID = 0;
	string Pet_Name = "", Pet_Species = "", Pet_Breed = "", Pet_Color = "", Pet_Weight = "", Pet_Gender = "";
	bool asc = true;
	auto it = find_if(pets.begin(), pets.end(), [PetID](const Pet& pet) {
		return pet.PetID == PetID;
		});
	char confirm;
	Menu OPMenu;
	OPMenu.header = "\n\n\t ----------------- Your Pet profile ----------------- \n";
	//OPMenu.addOption("Customer ID   ");
	OPMenu.addOption(" 1 > Search by CustID ");
	OPMenu.addOption(" 2 > Search by Pet Name ");
	OPMenu.addOption(" 3 > Search by Species ");
	OPMenu.addOption(" 4 > View All Pet ");
	OPMenu.addOption(" 5 > Back To Your Page ");
	//OPMenu.addOption(" 6 > Edit Pet Details ");
	OPMenu.addOption(" 6 > Delete Pet Profile ");

	while (1)
	{
		if (displayPet == "")
		{
			displayPet = "\n\n\t Your Pet: ";
			stringstream tmpPet;
			tmpPet << setw(4) << "\t\t Customer ID" << "|" << setw(8) << " Pet ID" << "|" << setw(20) << "Pet Name" << "|" << setw(20) << "Pet Species" << "|"
				<< setw(20) << "Pet Breed" << "|" << setw(20) << "Pet Color" << "|" << setw(20) << "Pet Gender" << "|" << setw(20) << "Pet Weight" << "|" << endl;
			tmpPet << "\t\t\t\t --------------------------------------------------------------------------------------------------------------------------------------------------- " << endl;

			for (int i = 0; i < pets.size(); i++)
			{
				tmpPet << "\t\t\t\t" << setw(11) << pets[i].CustID << "|" << setw(8) << pets[i].PetID << "|" << setw(20) << pets[i].Pet_Name << "|" << setw(20) << pets[i].Pet_Species
					<< "|" << setw(20) << pets[i].Pet_Breed << "|" << setw(20) << pets[i].Pet_Color << "|" << setw(20) << pets[i].Pet_Gender << "|" << setw(20) << pets[i].Pet_Weight << "|" << endl;
			}

			displayPet += tmpPet.str();
		}
		OPMenu.footer = displayPet;

		switch (OPMenu.prompt())
		{
		case 1:
			cout << " Insert CustID: ";
			cin >> CustID;
			OPMenu.setValue(0, to_string(custs.CustID));
			pets = Pet::ourPet(custs.CustID, Pet_Name, Pet_Species);
			displayPet = "";
			break;
		case 2:
			cout << " Insert Pet Name: ";
			cin.ignore(); // Add this line to clear the input buffer
			getline(cin, Pet_Name);
			OPMenu.setValue(1, Pet_Name);
			pets = Pet::ourPet(custs.CustID, Pet_Name, Pet_Species);
			displayPet = "";
			break;
		case 3:
			cout << " Insert Species: ";
			cin.ignore(); // Add this line to clear the input buffer
			getline(cin, Pet_Species);
			OPMenu.setValue(2, Pet_Species);
			pets = Pet::ourPet(custs.CustID, Pet_Name, Pet_Species);
			displayPet = "";
			break;
		case 4:
			pets = Pet::ourPet(custs.CustID, Pet_Name, Pet_Species);
			displayPet = "";
			break;
		case 5:
			homeCust(custs);
			break;
		//case 6:
		//	int petID;
		//	cout << "Enter the Pet ID you want to edit: ";
		//	cin >> petID;
		//	cin.ignore(); // Add this line to clear the input buffer
		//	if (it != pets.end()) {
		//		editPet(*it);
		//	}
		//	else {
		//		cout << "Pet not found." << endl;
		//	}
		//	break;
		case 6:
			cout << " Insert Pet ID you want to delete: ";
			cin >> PetID;
			OPMenu.setValue(0, to_string(PetID));

			// Find the specific Pet object to delete
			for (Pet& pet : pets) {
				if (pet.PetID == PetID) {
					deletePet(pet, custs);
					break;
				}
			}
			break;
		}
	}
}

// select pet for booking
int selectPet(Cust custs)
{
	vector<Pet> pets;

	Pet temp;
	Pet selPet;
	string displayPet = "";

	int CustID = 0, PetID = 0;
	string Pet_Name = "", Pet_Species = "", Pet_Breed = "", Pet_Color = "", Pet_Weight = "", Pet_Gender = "";
	bool asc = true;
	char confirm;
	Menu OPMenu;
	OPMenu.header = "\n\n\t ----------------- Your Pet profile ----------------- \n";

	OPMenu.addOption(" 1 > My Pet ");
	OPMenu.addOption(" 2 > Select PetID ");

	while (1)
	{
		if (displayPet == "")
		{
			displayPet = "\n\n\t Your Pet: ";
			stringstream tmpPet;
			tmpPet << setw(4) << "\t\t Customer ID" << "|" << setw(8) << " Pet ID" << "|" << setw(20) << "Pet Name" << "|" << setw(20) << "Pet Species" << "|"
				<< setw(20) << "Pet Breed" << "|" << setw(20) << "Pet Color" << "|" << setw(20) << "Pet Gender" << "|" << setw(20) << "Pet Weight" << "|" << endl;
			tmpPet << "\t\t\t\t --------------------------------------------------------------------------------------------------------------------------------------------------- " << endl;

			for (int i = 0; i < pets.size(); i++)
			{
				tmpPet << "\t\t\t\t" << setw(11) << pets[i].CustID << "|" << setw(8) << pets[i].PetID << "|" << setw(20) << pets[i].Pet_Name << "|" << setw(20) << pets[i].Pet_Species
					<< "|" << setw(20) << pets[i].Pet_Breed << "|" << setw(20) << pets[i].Pet_Color << "|" << setw(20) << pets[i].Pet_Gender << "|" << setw(20) << pets[i].Pet_Weight << "|" << endl;
			}

			displayPet += tmpPet.str();
		}
		OPMenu.footer = displayPet;

		switch (OPMenu.prompt())
		{
		case 1:
			pets = Pet::ourPet(custs.CustID, Pet_Name, Pet_Species);
			displayPet = "";
			break;
		case 2:
		return 0;
		break;
		}
	}
}

// list of available time slot
int slotTime(Appointment book)
{
	Menu slotMenu;            
	slotMenu.header = "\n\n\t --------------- SELECT YOUR SLOT TIME --------------- \n";
	slotMenu.addOption("\n\t SLOT 1 : 8:30am");
	slotMenu.addOption("\n\t SLOT 2 : 10:30am");
	slotMenu.addOption("\n\t SLOT 3 : 12:30am");
	slotMenu.addOption("\n\t SLOT 4 : 14:30pm");
	slotMenu.addOption("\n\t SLOT 5 : 16:30pm");
         

	while (1)
	{
		return slotMenu.prompt();
	}
}

// process booking an appointment
Cust bookAppt(Cust custs, Pet pets, Treatment treatment, Appointment book, Payment pay)
{
	
    Appointment temp = book;
	temp.CustID = custs.CustID;
	int PetID = 0, TreatmentID = 0, CustomerID = 0, AppointmentID = 0;
	double Total_Payment = 0.0;
	string displayString = " ", Booking_Date = "", Booking_Time = "";

	Menu apptMenu;
	apptMenu.header = "\n\n\t\tBook Appointment\n\t\t------------------------------------------- \n";
	apptMenu.addOption(" 1 > Enter TreatmentID");
	apptMenu.addOption(" 2 > Select PetID");
	apptMenu.addOption(" 3 > Set Date (yyyy/mm/dd)");
	apptMenu.addOption(" 4 > Set Time (in format 24h. Eg: HHMM (1430)");
	apptMenu.addOption(" 5 > Book");
	apptMenu.addOption(" 6 > Proceed to Payment");
	apptMenu.addOption(" 7 > Back");
	bool valid = true;
	char confirm;

	while (1)
	{
		switch (apptMenu.prompt())
		{
		case 1:
			TreatmentList();
			cout << "Select Treatment ID: ";
			cin >> book.TreatmentID;
			apptMenu.setValue(0, to_string(book.TreatmentID));
			break; 
		case 2:
			selectPet(custs);
			cout << "Enter Pet ID: ";
			cin >> book.PetID;
			apptMenu.setValue(1, to_string(book.PetID));
			break;
		case 3:
			cout << "Set Date For Booking (yyyy/mm/dd): ";
			cin >> book.Booking_Date;
			if (book.Booking_DateExists(book.Booking_Date))
			{
				cout << "\n\n\t Sorry, your booking Date not available.\n\n\t The date choosen already assigned by someone else. \n\n\t Please choose another date. \n";
				_getch();
				cout << "\nSet another Date For Booking (yyyy/mm/dd): ";
				cin >> book.Booking_Date;
			}
			apptMenu.setValue(2, book.Booking_Date);
			break;
		case 4:
			slotTime(book);
			cout << "Set Time For Booking (in 24h format): ";
			cin >> book.Booking_Time;
			if (book.Booking_TimeExists(book.Booking_Time))
			{
				cout << "\n\n\t Sorry, your booking Time slot not available. \n\n\t The time slot choosen already assigned by someone else.\n\n\t Please choose another slot. \n";
				_getch();
				cout << "\nSet another time For Booking (in 24h format): ";
				cin >> book.Booking_Time;
			}
			apptMenu.setValue(3, book.Booking_Time);
			break;
		case 5:
			cout << "Proceed the booking? (y/n): ";
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y')
			{
				book.insertAppt();
				cout << "\nBooking successful.";
				_getch();
			}
			else
				cout << "\nBooking cancelled. ";
			    _getch();
			break;
		case 6:
			doPayment(custs, pets, treatment, book, pay);
			break;
		case 7:
			homeCust(custs);
			break;
		default:
			break;
		}
	}
}

// process of payment
void doPayment(Cust cust, Pet pets, Treatment treatment, Appointment book, Payment pay)
{
	system("cls");
	char confirm;
	Payment temp = pay;
	int AppointmentID = 0;
	temp.AppointmentID = book.AppointmentID;
	cout << " \n\t\t Your appointment details: \n\n\tTreatment ID: " + to_string(book.TreatmentID) + " \n\tPet ID : " + to_string(book.PetID)
		+ " \n\tBooking Date: " + book.Booking_Date + " \n\tBooking Time: " + book.Booking_Time;
	_getch();


	while (book.TreatmentID != 0)
	{

		if (book.TreatmentID == 1)
		{
			temp.Total_Payment = 40 * 1;
			cout << "\n\t Total: RM " + to_string(temp.Total_Payment);
			break;
		}
		else if (book.TreatmentID == 2)
		{
			temp.Total_Payment = 70 * 1;
			cout << "\n\tTotal: RM " + to_string(temp.Total_Payment);
			break;
		}
		else if (book.TreatmentID == 3)
		{
			temp.Total_Payment = 130 * 1;
			cout << "\n\tTotal: RM " + to_string(temp.Total_Payment);
			break;
		}
		else if (book.TreatmentID == 4)
		{
			temp.Total_Payment = 180 * 1;
			cout << "\n\tTotal: RM " + to_string(temp.Total_Payment);
			break;
		}

	}
	pay.TreatmentID = book.TreatmentID;
	book.PetID = pay.PetID;
	cout << "\n\n************************************************************\n";
	cout << "\n\nProceed the payment? (y/n)\n\n Once you enter the confirmation details,\n you will automatically go to transaction.\n You are enable to cancel the booking after the transaction process.\n";
	confirm = _getch();
	if (confirm == 'Y' || confirm == 'y')
	{
		cout << "\nRe-enter Your TreatmentID for confirmation: ";
		cin >> pay.TreatmentID;
		cout << "\nRe-enter Your PetID for confirmation: ";
		cin >> pay.PetID;

		time_t now = time(0); // get current dat/time with respect to system  
		char* dt = ctime(&now); // convert it into string  
		cout << "\nPayment successful. ";
		system("cls");
		cout << "\n\n\t ***************** YOUR RECEIPT ***************** \n\n\t Your booking for treatment " + to_string(pay.TreatmentID) + " has been assigned. \n\n\t Date: " + book.Booking_Date
			+ "\n\n\t Slot Time: " + book.Booking_Time
			+ "\n\n\t Treatment price: RM " + to_string(temp.Total_Payment)
			+ "\n\n\t Tax & Service: RM25  \n\n\t ********************************************* ";


		// calculate total payment ( price + tax & service )
		pay.Total_Payment = temp.Total_Payment + 25;

		cout << "\n\n\t Total Payment: RM " + to_string(pay.Total_Payment);
		pay.insertPayment();
		temp.AppointmentID = book.AppointmentID;
		cout << "\n\n\t ********************************************* \n\n\t The payment was made on " << dt << endl;
		cout << "\n\n\t Show the receipt at the counter, and the staff will guide you. \n\n\t\t Thank You :) ";
	}
	else
		cout << "\nPayment cancelled.";
	    book.removeBook();
	_getch();

	ofstream receiptFile("Receipt.txt");  // Open a file named "Receipt.txt" for writing

	if (receiptFile.is_open()) {
		receiptFile << "\n\n\t ***************** YOUR RECEIPT ***************** \n\n\t Your booking for treatment " + to_string(pay.TreatmentID) + " has been assigned. \n\n\t Date: " + book.Booking_Date
			+ "\n\n\t Slot Time: " + book.Booking_Time
			+ "\n\n\t Treatment price: RM " + to_string(temp.Total_Payment)
			+ "\n\n\t Tax & Service: RM25  \n\n\t ********************************************* ";

		pay.Total_Payment = temp.Total_Payment + 25;
		receiptFile << "\n\n\t Total Payment: RM " + to_string(pay.Total_Payment);
		pay.insertPayment();
		time_t now = time(0); // get current dat/time with respect to system  
		char* dt = ctime(&now);
		receiptFile << "\n\n\t ********************************************* \n\n\t The payment was made on " << dt << endl;
		receiptFile << "\n\n\t Show the receipt at the counter, and the staff will guide you. \n\n\t\t Thank You :) ";

		receiptFile.close();  // Close the file after writing
		cout << "\nReceipt generated successfully. Check 'Receipt.txt' for your receipt details.\n";
	}
	else {
		cout << "\nError opening the file 'Receipt.txt' for writing.\n";
	}
}

bool validateDate(const std::string& date) {
	// Define a regex pattern for YYYY-MM-DD format
	std::regex dateRegex(R"(\d{4}-\d{2}-\d{2})");

	// Check if the date matches the format
	return std::regex_match(date, dateRegex);
}








