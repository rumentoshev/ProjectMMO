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
void Login(fstream& Users)
{
	string username;
	string password;
	string buffer;
	string buffer_username;
	string buffer_password;
	string buffer_level;
	string hashed_password;
	hash<string> hash_obj;
	int level;
	bool flag = false;
	cout << "Plese enter your username:\n";
	cin >> username;
	cout << "Plese enter your password:\n";
	cin >> password;
	hashed_password = to_string(hash_obj(password));
	Users.open("users.txt", fstream::in);
	if (Users.is_open())
	{
		while (getline(Users, buffer))
		{
			int i = 0;
			while (i < buffer.size() && buffer[i] != ':')
			{
				buffer_username += buffer[i++];
			}
			i++;
			while (i < buffer.size() && buffer[i] != ':')
			{
				buffer_password += buffer[i++];
			}
			i++;
			while (i < buffer.size())
			{
				buffer_level += buffer[i++];
			}
			level = stoi(buffer_level);
			if ((username == buffer_username) && (hashed_password == buffer_password))
			{
				Users.close();
				flag = true;
				Menu2(Users, username, hashed_password, level);
				break;
			}
			buffer_username = "";
			buffer_password = "";
			buffer_level = "";
		}
		if (flag == false)
		{
			Users.close();
			cout << "Invalid information!Plese try again!" << endl;
			Login(Users);
		}
	}
}