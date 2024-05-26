#include "Treatment.h"
#include <vector>

using namespace std;

Treatment::Treatment()
{
	TreatmentID = 0;
	NameT = "";
	Description = "";
	Price = 0;
}

Treatment::Treatment(sql::ResultSet* data)
{
	TreatmentID = data->getInt("TreatmentID");
	NameT = data->getString("NameT");
	Description = data->getString("Description");
	Price = data->getDouble("Price");
}

Treatment Treatment::searchTreatment(int TreatmentID)
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM treatment WHERE TreatmentID=?");
	db.stmt->setInt(1, TreatmentID);
	db.QueryResult();

	Treatment result;
	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
		{
			Treatment found(db.res);
			result = found;
		}
	}
	db.~DBConnection();
	return result;
}

vector<Treatment> Treatment::findTreatment(int TreatmentID, std::string NameT, std::string Description, int minPrice, int maxPrice, bool ascending)
{
	string query = "SELECT * FROM Treatment WHERE "
		" (NameT LIKE ? OR Description LIKE ?) AND Price >= ? AND Price <= ? "
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
	db.stmt->setString(1, "%" + NameT + "%");
	db.stmt->setString(2, "%" + Description + "%");
	db.stmt->setDouble(3, minPrice);
	db.stmt->setDouble(4, maxPrice);


	vector<Treatment> treatment;
	db.QueryResult();

	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			Treatment tmpTreatment(db.res);
			treatment.push_back(tmpTreatment);
		}
	}

	db.~DBConnection();
	return treatment;
}

void Treatment::updateTreatment()
{
	DBConnection db;
	db.prepareStatement("UPDATE Treatment SET NameT = ?, Description = ? , Price = ? WHERE TreatmentID = ?");
	db.stmt->setString(1, NameT);
	db.stmt->setString(2, Description);
	db.stmt->setDouble(3, Price);
	db.stmt->setInt(4, TreatmentID);
	db.QueryStatement();
	db.~DBConnection();
}

void Treatment::removeTreatment()
{
	DBConnection db;
	db.prepareStatement("DELETE FROM Treatment WHERE TreatmentID=?");
	db.stmt->setInt(1, TreatmentID);
	db.QueryStatement();
	db.~DBConnection();
}

Treatment::~Treatment()
{

}
