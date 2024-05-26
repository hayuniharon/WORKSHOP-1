#include "Appointment.h"
#include "Customer.h"
#include "Treatment.h"
#include "Pet.h"
#include "Sale.h"
#include <vector>
#include "DBConnection.h"
using namespace std;


Appointment::Appointment() {
	AppointmentID = 0;
	TreatmentID = 0;
	PetID = 0;
	Booking_Date = "";
	Booking_Time = "";
	status = "";


}

Appointment::Appointment(int AppointmentID, int TreatmentID, int PetID, std::string Booking_Date, std::string Booking_Time, std::string status)
{
    this->AppointmentID = AppointmentID;
    this->TreatmentID = TreatmentID;
    this->PetID = PetID;
    this->Booking_Date = Booking_Date;
    this->Booking_Time = Booking_Time;
    this->status = status;
}


Appointment::Appointment(sql::ResultSet* data)
{
    DBConnection db;
    db.prepareStatement("SELECT * FROM Appointment");
	AppointmentID = data->getInt("AppointmentID");
	TreatmentID = data->getInt("TreatmentID");
	PetID = data->getInt("PetID");
	Booking_Date = data->getString("Booking_Date");
	Booking_Time = data->getString("Booking_Time");
	status = data->getString("status");
}

Appointment::~Appointment() 
{

}

void Appointment::insertAppt()
{
	DBConnection db;
	db.prepareStatement("INSERT into Appointment (PetID, TreatmentID, Booking_Date, Booking_Time) VALUES (?,?,?,?)");
	db.stmt->setInt(1, PetID);
	db.stmt->setInt(2, TreatmentID);
	db.stmt->setString(3, Booking_Date);
	db.stmt->setString(4, Booking_Time);
	db.QueryStatement();
	db.~DBConnection();
}

void Appointment::updateAppt()
{
	DBConnection db;
	db.prepareStatement("UPDATE Appointment SET status =? WHERE AppointmentID=?");
	db.stmt->setString(1, status);
	db.stmt->setInt(2, AppointmentID);
	db.QueryStatement();
	db.~DBConnection();
}

void Appointment::removeBook() {
	DBConnection db;
	db.prepareStatement("DELETE FROM Appointment WHERE AppointmentID=?");
	db.stmt->setInt(1, AppointmentID);
	db.QueryStatement();
	db.~DBConnection();
}


bool Appointment::Booking_DateExists(const std::string& Booking_Date)
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM Appointment WHERE Booking_Date= ?");
	db.stmt->setString(1, Booking_Date);
	db.QueryResult();
	return (db.res->rowsCount() > 0);
}


bool Appointment::Booking_TimeExists(const std::string& Booking_Time)
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM Appointment WHERE Booking_Time= ?");
	db.stmt->setString(1, Booking_Time);
	db.QueryResult();
	return (db.res->rowsCount() > 0);
}

vector<Appointment> Appointment::findBook (string Booking_Date, int TreatmentID, int PetID, bool ascending)
{
    string query = "SELECT * FROM Appointment WHERE AppointmentID != 0";

    // Check if any other conditions are provided
    if (!Booking_Date.empty() || TreatmentID != 0 || PetID != 0)
    {
        query += " AND";

        if (!Booking_Date.empty())
            query += " Booking_Date LIKE ?";
        if (TreatmentID != 0)
        {
            if (!Booking_Date.empty()) query += " AND";
            query += " TreatmentID = ?";
        }
        if (PetID != 0)
        {
            if (!Booking_Date.empty() || TreatmentID != 0 ) query += " AND";
            query += " PetID = ?";
        }
    }

    query += " ORDER BY Booking_Date ";

    if (ascending)
    {
        query += "ASC";
    }
    else
    {
        query += "DESC";
    }

    DBConnection db;
    db.prepareStatement(query);

    int parameterIndex = 1;
    if (!Booking_Date.empty()) db.stmt->setString(parameterIndex++, "%" + Booking_Date + "%");
    if (TreatmentID != 0) db.stmt->setInt(parameterIndex++, TreatmentID);
    if (PetID != 0) db.stmt->setInt(parameterIndex++, PetID);

    vector<Appointment> book;

    db.QueryResult();

    if (db.res->rowsCount() > 0)
    {
        while (db.res->next())
        {
            Appointment tmpBook(db.res);
            book.push_back(tmpBook);
        }
        db.~DBConnection();
        return book;
    }
}


vector<Appointment> Appointment::history(int PetID, int AppointmentID, bool ascending)
{
    string query = "SELECT * FROM Appointment WHERE PetID = ?";

    // Correct the ORDER BY syntax
    query += " ORDER BY Booking_Date ";
    if (!ascending)
    {
        query += " DESC"; // Add space before DESC
    }

    DBConnection db;
    db.prepareStatement(query);
    db.stmt->setInt(1, PetID);

    vector<Appointment> book;

    db.QueryResult();

    if (db.res->rowsCount() > 0)
    {
        while (db.res->next())
        {
            Appointment tmpBook(db.res);
            book.push_back(tmpBook);
        }
    }

    return book;
}






