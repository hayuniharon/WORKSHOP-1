#include "Payment.h"
#include "Pet.h"
#include <string>
#include "Sale.h"
#include "Appointment.h"
using namespace std;
using namespace sql;

Payment::Payment()
{
	PetID = 0;
	TreatmentID = 0;
	PaymentID = 0;	
	Total_Payment = 0.0;
	Payment_Date = "";
	Payment_Status = "";

}

Payment::Payment(int PaymentID, int PetID, int TreatmentID, float Total_Payment, string Payment_Date, string Payment_Status)
{
	this->PaymentID = PaymentID;
	this->PetID = PetID;
	this->TreatmentID = TreatmentID;
	this->Total_Payment = Total_Payment;
	this->Payment_Date = Payment_Date;
	this->Payment_Status = Payment_Status;
}


Payment::Payment(ResultSet* data)
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM Payment");
	TreatmentID = data->getInt("TreatmentID");
	PetID = data->getInt("PetID");
	Total_Payment = data->getDouble("Total_Payment");
	Payment_Date = data->getString("Payment_Date");
	Payment_Status = data->getString("Payment_Status");
	
																																																				
}

void Payment::insertPayment() {
	DBConnection db;
	db.prepareStatement("Insert into Payment (TreatmentID, PetID, Total_Payment ) VALUES (?,?, ?)");

	db.stmt->setInt(1, TreatmentID);
	db.stmt->setInt(2, PetID);
	db.stmt->setDouble(3, Total_Payment);
	db.QueryStatement();
	db.~DBConnection();
}

void Payment::updatePayment()
{
	DBConnection db;
	db.prepareStatement("UPDATE Payment SET TreatmentID=?, PetID=?, Total_Payment=?, Payment_Date=?, Payment_Status=? WHERE PaymentID=?");
	db.stmt->setInt(1, TreatmentID);
	db.stmt->setInt(2, PetID);
	db.stmt->setDouble(3, Total_Payment);
	db.stmt->setString(4, Payment_Date);
	db.stmt->setString(5, Payment_Status);
	db.stmt->setInt(6, PaymentID);
	db.QueryStatement();
	db.~DBConnection();

}

double Payment::total()
{
	double total = 0;
	for (int i = 0; i < items.size(); i++)
	{
		total += items[i].first.Price * items[i].second;
	}
	return total;
}

int Payment::count()
{
	int count = 0;
	for (int i = 0; i < items.size(); i++)
	{
		count += items[i].second;
	}
	return count;
}

void Payment::addTreatment(Treatment treatment, int quantity)
{
	items.push_back({ treatment, quantity });
}



 std::vector<Payment> Payment::Report(const std::string& start, const std::string& end, bool ascending)
{
	string query = "SELECT * FROM Payment p "
		" WHERE p.Payment_Date BETWEEN ? AND ? "
		" ORDER BY TreatmentID ";
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
	db.stmt->setString(1, start);
	db.stmt->setString(2, end);


	vector<Payment> pay;
	db.QueryResult();

	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			Payment tmpPay(db.res);
			pay.push_back(tmpPay);
		}
	}

	db.~DBConnection();
	return pay;
}

 






