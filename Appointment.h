#pragma once
#ifndef APPOINTMENT_H
#define APPOIMTMENT_H
#include "Appointment.h"
#include <string>
#include <vector>
#include "DBConnection.h"

class Appointment
{

public:
	int AppointmentID, TreatmentID, PetID, CustID;
	std::string Booking_Date, Booking_Time, status;

    Appointment();
	Appointment(int AppointmentID, int TreatmentID, int PetID, std::string Booking_Date, std::string Booking_Time, std::string status);
	Appointment(sql::ResultSet* data);

	~Appointment();
	std::vector<std::pair<Appointment, int>> treatment;

	void insertAppt();
	void updateAppt();
	void removeBook();

	bool Booking_DateExists(const std::string& Booking_Date);
	bool Booking_TimeExists(const std::string& Booking_Time);

	static std::vector<Appointment> findBook(std::string Booking_Date, int TreatmentID, int PetID, bool ascending);
	static std::vector<Appointment> history(int PetID, int AppointmentID, bool ascending);
	
	
};


#endif
