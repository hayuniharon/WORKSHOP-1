#include "Pet.h"
#include <ctime>
#include <vector>
#include "DBConnection.h"

using namespace std;

Pet::Pet()
{
	// initialize
	PetID = 0;
	CustID = 0;
	Pet_Name = "";
	Pet_Species = "";
	Pet_Breed = "";
	Pet_Color = "";
	Pet_Gender = "";
	Pet_Weight = "";
	Pet_Status = "";
}

Pet::Pet(int PetID, int CustID, string Pet_Name, string Pet_Species, string Pet_Breed, string Pet_Gender, string Pet_Weight, string Pet_Status )
{
	this->PetID = PetID;
	this->CustID = CustID;
	this->Pet_Name = Pet_Name;
	this->Pet_Species = Pet_Species;
	this->Pet_Breed = Pet_Breed;
	this->Pet_Color = Pet_Color;
	this->Pet_Gender = Pet_Gender;
	this->Pet_Weight = Pet_Weight;
	this->Pet_Status = Pet_Status;
}

int Pet::insertPet()
{
	DBConnection db;
	db.prepareStatement("Insert into Pet  (CustID, Pet_Name, Pet_Species, Pet_Breed, Pet_Color, Pet_Gender, Pet_Weight, Pet_Status) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
	db.stmt->setInt(1, CustID);
	db.stmt->setString(2, Pet_Name);
	db.stmt->setString(3, Pet_Species);
	db.stmt->setString(4, Pet_Breed);
	db.stmt->setString(5, Pet_Color);
	db.stmt->setString(6, Pet_Gender);
	db.stmt->setString(7, Pet_Weight);
	db.stmt->setString(8, Pet_Status);
	db.QueryStatement();

	generatedPetID = db.getGeneratedId();
	db.~DBConnection();
	return generatedPetID; 
}

void Pet::updatePet()
{
	DBConnection db;
	db.prepareStatement("UPDATE Pet SET PetID=?, Pet_Name=?, Pet_Species=?, Pet_Breed=?, Pet_Color=?, Pet_Gender=?, Pet_Weight=? WHERE CustID=? AND PetID=?");
	db.stmt->setInt(1, CustID);
	db.stmt->setString(2, Pet_Name);
	db.stmt->setString(3, Pet_Species);
	db.stmt->setString(4, Pet_Breed);
	db.stmt->setString(5, Pet_Color);
	db.stmt->setString(6, Pet_Gender);
	db.stmt->setString(7, Pet_Weight);
	db.stmt->setInt(9, PetID);
	db.QueryStatement();
	db.~DBConnection();
}

void Pet::updateStatus()
{
	DBConnection db;
	db.prepareStatement("UPDATE Pet SET Pet_Status=? WHERE PetID=?");
	db.stmt->setString(1, Pet_Status);
	db.stmt->setInt(2, PetID);
	db.stmt->executeUpdate();
	db.QueryStatement();
	db.~DBConnection();
}


void Pet::removePet()
{
	DBConnection db;
	db.prepareStatement("DELETE FROM Pet WHERE PetID=?");
	db.stmt->setInt(1, PetID);
	db.QueryStatement();
	db.~DBConnection();
}

Pet::Pet(sql::ResultSet* data)
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM Pet");
	PetID = data->getInt("PetID");
	CustID = data->getInt("CustID");
	Pet_Name = data->getString("Pet_Name");
	Pet_Species = data->getString("Pet_Species");
	Pet_Breed = data->getString("Pet_Breed");
	Pet_Color = data->getString("Pet_Color");
	Pet_Gender = data->getString("Pet_Gender");
	Pet_Weight = data->getString("Pet_Weight");
	Pet_Status = data->getString("Pet_Status");
	
}

Pet::~Pet()
{

}

vector<Pet> Pet::searchPet(string Pet_Name, string Pet_Species, bool asc)
{
	string query = "SELECT * FROM Pet WHERE "
		" ( Pet_Name LIKE ? AND Pet_Species LIKE ? ) "
		" ORDER BY PetID";

	DBConnection db;
	db.prepareStatement(query);
	db.stmt->setString(1, "%" + Pet_Name + "%");
	db.stmt->setString(2, "%" + Pet_Species + "%");

	vector<Pet> pets;

	db.QueryResult();

	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			Pet tmpPet(db.res);
			pets.push_back(tmpPet);
		}
	}

	db.~DBConnection();
	return pets;
}

vector<Pet> Pet::ourPet(int CustID, string Pet_Name, string Pet_Species)
{
	DBConnection db;
	string query = "SELECT * FROM Pet WHERE CustID = ?";

	if (!Pet_Name.empty())
		query += " AND Pet_Name LIKE ?";

	if (!Pet_Species.empty())
		query += " AND Pet_Species LIKE ?";

	db.prepareStatement(query);
	db.stmt->setInt(1, CustID);

	if (!Pet_Name.empty())
		db.stmt->setString(2, "%" + Pet_Name + "%");

	if (!Pet_Species.empty())
	{
		if (Pet_Name.empty())
			db.stmt->setString(2, "%" + Pet_Species + "%");
		else
			db.stmt->setString(3, "%" + Pet_Species + "%"); // Use index 3 for the third parameter
	}

	vector<Pet> pets;

	db.QueryResult();

	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			Pet tmpPet(db.res);
			pets.push_back(tmpPet);
		}
	}

	db.~DBConnection();
	return pets;
}


