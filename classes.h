#pragma once
#include <iostream>
#include <string>

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
		Account* next;
		Node() : next(nullptr) {}
		Node(Account _account) : account(_account), next(nullptr) {}
	};

	class Bank
	{
	private:
		Node* head;
		Account& currentAccount;
	public:
		Bank(Account admin) : head(nullptr), currentAccount(admin) {}

		void retrieve()
		{

		}

		void save()
		{

		}

		void add(Account account)
		{

		}
	};
}