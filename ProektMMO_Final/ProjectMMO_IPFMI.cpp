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
void Registration(fstream& Users)

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
void Registration(fstream& Users)
{
	int level = 1;
	string username;
	string password;
	string hashed_password;
	hash<string> hash_obj;
	int number_counter = 0;
	int upleter_counter = 0;
	int lowleter_counter = 0;
	int symbol_counter = 0;
	int error_pass_counter = 0;
	bool isValidPass = false;
	bool isValidUsername = false;
	int correct_username_counter = 0;
	int error_username_counter = 0;
	cout << "Plese enter username which has only latin letters and numbers:\n";
	cin >> username;
	for (int i = 0; i < username.size(); i++)
	{
		if (username[i] >= 48 && username[i] <= 57)
		{
			correct_username_counter++;
		}
		else if (username[i] >= 97 && username[i] <= 122)
		{
			correct_username_counter++;
		}
		else if (username[i] >= 65 && username[i] <= 90)
		{
			correct_username_counter++;
		}
		else
		{
			error_username_counter++;
		}
	}
	if (correct_username_counter == username.size() && username.size() >= 5)
	{
		isValidUsername = true;
	}
	else
	{
		cout << "Incorect username!\n";
		Registration(Users);
	}
	cout << "Plese enter password using only latin letters,numbers and (!@#$%^&*) symbols :\n";
	cout << "Be sure you have at least 1 uper letter,1 lower letter, 1 number and 1 symbol! \n";
	cin >> password;

	for (int i = 0; i < password.size(); i++)
	{
		if (password[i] >= 48 && password[i] <= 57)
		{
			number_counter++;
		}
		else if (password[i] >= 65 && password[i] <= 90)
		{
			upleter_counter++;
		}
		else if (password[i] >= 97 && password[i] <= 122)
		{
			lowleter_counter++;
		}
		else if (password[i] == 33 || password[i] == 64 || password[i] == 42 || password[i] == 94)
		{
			symbol_counter++;
		}
		else if (password[i] >= 35 && password[i] <= 38)
		{
			symbol_counter++;
		}
		else
		{
			error_pass_counter++;
		}
	}
	if (number_counter >= 1 && upleter_counter >= 1 && lowleter_counter >= 1 && symbol_counter >= 1 && password.size() >= 5)
	{
		isValidPass = true;
		hashed_password = to_string(hash_obj(password));
	}
	else
	{
		cout << "Incorect password!\n";
		Registration(Users);
	}
	bool flag = true;
	string buffer;
	string buffer_username;
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
			if (username == buffer_username)
			{
				flag = false;
				break;
			}
			buffer_username = "";
		}
	}
	Users.close();
	if (flag == false)
	{
		cout << "There is already user with that name!\nPlease try another username!" << endl;
		Registration(Users);
	}

	if (isValidPass == true && isValidUsername == true)
	{
		Users.open("users.txt", fstream::out | fstream::app);
		Users << username << ":" << hashed_password << ":" << level << endl;
		Users.close();
		Menu2(Users, username, hashed_password, level);
	}
}