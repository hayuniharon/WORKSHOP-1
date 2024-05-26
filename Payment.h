#pragma once
#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <vector>
#include "DBConnection.h"
#include "Treatment.h"
#include "Pet.h"

class Payment
{
public:
	std::string Payment_Date, Payment_Status;
	float Total_Payment;
	int AppointmentID, TreatmentID, PaymentID, PetID, custs;

	Payment();

	Payment(int PaymentID, int PetID, int TreatmentID, float Total_Payment, string Payment_Date, string Payment_Status);

	Payment(sql::ResultSet* data);
	void insertPayment();
	void updatePayment();

	std::vector<std::pair<Treatment, int>> items;


	double total();
	int count();

	void addTreatment(Treatment treatment, int quantity);
	static std::vector<Payment> Report(const std::string& start, const std::string& end, bool ascending);
	~Payment()
	{

	}
	
	
};

#endif
