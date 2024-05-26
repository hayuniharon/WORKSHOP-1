#include "Menu.h"
#include <iostream>
#include <conio.h>
using namespace std;

Menu::Menu() {
	header = "\n\t";
	footer = "\n\t---------------------------------------------------\n\t---------------------------------------------------\n\n\tSelect option: \n\n\t";
	//bullet = "-";

}
int Menu::prompt() {
	int selected = -1;
	do
	{
		system("cls"); // clear ur concole
		cout << header << endl;
		for (int i = 0; i < options.size(); i++) {//loop through each option 
			cout << "\t\t " << options[i].first;
			if (options[i].second != "") {
				cout << " : " << options[i].second;
			}
			cout << endl;
		}
		cout << footer << endl;

		selected = _getch() - '0';
	} while (selected < 1 || selected > options.size());
	return selected;
}
void Menu::addOption(string option) {
	options.push_back({ option,"" });
}

void Menu::setValue(int index, string value) {
	if (index >= 0 && index < options.size()) {
		options[index].second = value;
	}
}


Menu::~Menu() {
	options.clear();
}