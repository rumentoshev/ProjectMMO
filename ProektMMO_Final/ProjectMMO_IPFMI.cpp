/**
*
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2021/2022
*
* @author Rumen Toshev
* @idnumber 2MI0600038
* @compiler VC
*
* <MMO Basic game>
*
*/
#include<iostream>
#include<fstream>
#include<string>
#include<functional>
#include<cmath>
using namespace std;

void Home_Menu(fstream& Users);
void Login(fstream& Users);
void Registration(fstream& Users);

int main()
{
	fstream Users;
	Home_Menu(Users);

	return 0;
}
void Home_Menu(fstream& Users)
{
	char choice;
	cout << "Home Menu" << endl;
	cout << "Press L for login." << endl;
	cout << "Press R for registration." << endl;
	cout << "Press Q to quit." << endl;
	cin >> choice;
	if (choice == 'L')
	{
		Login(Users);
	}
	else if (choice == 'R')
	{
		Registration(Users);
	}
	else if (choice == 'Q') {
		return;
	}
	else
	{
		Home_Menu(Users);
	}
}