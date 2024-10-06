#include "classes.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

// DEFINITION OF METHODS OF 'Bank' CLASS FROM 'classes.h'

bool Bank::isEmpty()
{
	return (head == nullptr);
}

bool Bank::accountExists(const std::string& accountNumber) const
{
	// Loop through the bank's internal account list
	Node* ptr = head;
	while (ptr)
	{
		if (ptr->account.accountNumber == accountNumber)
			return true;
		ptr = ptr->next;
	}
	return false;
}

bool Bank::isCardRegistered()
{
	string filepath = string(1, driveLetter) + ":\\account.txt";

	ifstream inputFile(filepath);
	if (!inputFile.is_open())
		return false;

	else
		return true;
}

void Bank::retrieveAllAccounts()
{
	ifstream inputFile(filename);
	if (!inputFile.is_open())
	{
		return;
	}

	Node* ptr = head;
	string line;
	int maxAccNum = 0; // To track the highest account number
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

		// Extract account number and find max
		maxAccNum = max(maxAccNum, stoi(accountNumber));
	}

	// Update accNumberCounter for the next new account
	accNumberCounter = maxAccNum + 1; // Increment to the next available number
}

void Bank::saveAllAccounts()
{
	ofstream outputFile(filename);

	if (!outputFile.is_open())
	{
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

void Bank::add(Account account)
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