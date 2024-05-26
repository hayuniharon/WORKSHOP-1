#include "Sale.h"
using namespace std;
using namespace sql;

Sale::Sale(ResultSet* data) {

	value = data->getDouble("value");
	Payment_Date = data->getString("date");
	NameT = data->getString("name");


}

vector<Sale> Sale::salesReport(string start, string end, vector <int> TreatmentID, bool sortByDate, bool ascending) {


	string NameTString = "";
	if (TreatmentID.size() > 0) {
		NameTString = " AND t.TreatmentID IN (";
		for (int i = 0; i < TreatmentID.size(); i++) {
			NameTString += "?,";
		}

		NameTString.erase(NameTString.size() - 1);
		NameTString += ") ";

	}


	string sql = " SELECT p.Payment_Date as date, t.NameT as name, SUM(p.Total_Payment) as value "
		" FROM Payment p "
		" JOIN Treatment t ON p.TreatmentID = t.TreatmentID "
		+ NameTString;


	sql += " WHERE p.Payment_Date >= ? AND p.Payment_Date <= ? ";

	sql += "GROUP BY ";
	if (!TreatmentID.empty()) {

		sql += "t.NameT , ";
	}

	sql += " CAST(MONTH(p.Payment_Date) AS VARCHAR(2)) + '-' + CAST(YEAR(p.Payment_Date) AS VARCHAR(4)) ";

	sql += " ORDER BY ";
	if (sortByDate) {

		sql += " p.Payment_Date";
	}
	else {

		sql += " value ";
	}


	if (ascending) {
		sql += " ASC ";
	}
	else {
		sql += " DESC ";
	}

	vector <Sale> salesReport;

	DBConnection db;

	db.prepareStatement(sql);

	int index = 1;

	while (index <= TreatmentID.size()) {

		db.stmt->setInt(index, TreatmentID[index - 1]);
		index++;

	}

	db.stmt->setString(index, start);
	index++;
	db.stmt->setString(index, end);
	db.QueryResult();

	if (db.res->rowsCount() > 0) {

		while (db.res->next()) {
			Sale tmpSale(db.res);
			salesReport.push_back(tmpSale);
		}
	}

	db.~DBConnection();
	return salesReport;



}