#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

namespace C
{
	struct Account
	{
		string accountNumber;
		string name;
		string pincode;
		string birthday;
		string contactNumber;
		double balance;

		Account() : accountNumber("00000"), name("default"), pincode("123456"), birthday("01-01-1900"), contactNumber("+63 000-000-0000"), balance(5000) {}
		Account(string accNumber, string _name, string pin, string bday, string contact, double _balance) : accountNumber(accNumber), name(_name), pincode(pin), birthday(bday), contactNumber(contact), balance(_balance) {}
	};

	struct Node
	{
		Account account;
		Node* next;
		Node() : next(nullptr) {}
		Node(Account _account) : account(_account), next(nullptr) {}
	};

	class Bank
	{
	private:
		Node* head;
		Account& currentAccount;

		string filename = "allAccounts.csv";
		char driveLetter = 'D';

		bool isEmpty()
		{
			return (head == nullptr);
		}

	public:
		Bank(Account admin) : head(nullptr), currentAccount(admin) {}

		void checkIfRegistered()
		{
			string filepath = string(1, driveLetter) + ":\\account.txt";

			ifstream inputFile(filepath);
			if (!inputFile)
			{
				ofstream outputFile(filepath);
				cout << "Register an account\n";
				string name;

				cout << "Enter name: ";
				getline(cin, name);
				outputFile << name << endl;
				outputFile.close();
			}
			else
			{
				string name;
				getline(inputFile, name);
				cout << "Welcome " << name << endl
					<< "Enter Pin Code\n";
			}
		}

		void retrieveAllAccounts()
		{
			ifstream inputFile(filename);
			if (!inputFile.is_open())
			{
				cout << "Error: could not open " << filename << " for retrieving" << endl;
				return;
			}

			Node* ptr = head;
			string line;
			while (getline(inputFile, line))
			{
				stringstream stream(line);
				string accountNumber, name, pincode, birthday, contactNumber, balanceStr;
				double balance;

				getline(stream, accountNumber, ',');
				getline(stream, name, ',');
				getline(stream, pincode, ',');
				getline(stream, birthday, ',');
				getline(stream, contactNumber, ',');
				getline(stream, balanceStr, ',');

				balance = stod(balanceStr);

				Account account(accountNumber, name, pincode, birthday, contactNumber, balance);
				add(account);
			}

		}

		void save_all_accounts()
		{
			ofstream outputFile(filename);

			if (!outputFile.is_open())
			{
				cout << "Error: Could not open " << filename << " for saving" << endl;
				return;
			}

			Node* ptr = head;

			while (ptr)
			{
				outputFile << ptr->account.accountNumber << ","
					<< ptr->account.name << ","
					<< ptr->account.pincode << ","
					<< ptr->account.birthday << ","
					<< ptr->account.contactNumber << ","
					<< ptr->account.balance << endl;
				ptr = ptr->next;
			}
			outputFile.close();
		}


		void add(Account account)
		{
			Node* newNode = new Node(account);
			if (isEmpty())
			{
				newNode->next = nullptr;
				head = newNode;
			}
			else
			{
				newNode->next = head;
				head = newNode;
			}
		}

		void displayAllAccounts()
		{
			Node* ptr = head;

			cout << "\nALL ACCOUNTS" << endl;
			int i = 1;

			while (ptr)
			{
				cout << i++ << ". " << ptr->account.name << " | Account #: " << ptr->account.accountNumber << endl;
				ptr = ptr->next;
			}

			system("pause");
		}
	};
}