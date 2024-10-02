#include <iostream>
#include "classes.h"
#include <string>

using namespace std;

void Bank::balanceInquiry() {
	cout << "Your Current Balance:" << currentAccount.balance << endl;
}

void Bank::withdraw() {
	int amount;

	cout << "Enter Amount to Withraw:"; cin >> amount;

	if (amount > currentAccount.balance) {
		cout << "Insufficient Funds!";
	}
	else if (amount <= 0) {
		cout << "Invalid Withrawal!";
	}
	else {
		currentAccount.balance -= amount;
		cout << "Withrawal Successful!";
	}
}

void Bank::deposit() {
	int ammount;

	cout << "Enter Amount to Deposit:"; cin >> ammount;

	if (ammount > 1000000000000) {
		cout << "Ammount to be Deposit Exceeded Maximum Capacity!";
	}
	else if (ammount <= 0) {
		cout << "Invalid Ammount!";
	}
	else {
		currentAccount.balance += ammount;
		cout << "Transaction Successful!";
	}

}

void Bank::fundTransfer() {
	string recieverAccount;
	int ammount;

	Node* temp = head;

	do {
		cout << "Enter Recipient Number:"; cin >> recieverAccount;

		if (recieverAccount == currentAccount.accountNumber) {
			cout << "You Cannot Transfer Funds to Your Account.\nPlease Try Again";
			system("pause");
		}
	} while (recieverAccount == currentAccount.accountNumber);

	//To find the reciever
	while (temp != NULL && temp->account.accountNumber != recieverAccount) {
		temp = temp->next;
	}

	if (temp == NULL) {
		cout << "Recipient Not Found!";
		return;
	}

	do {
		cout << "Enter Amount To Transfer:"; cin >> ammount;

		if (ammount <= 0) {
			cout << "Ammount must be greater than 0.";
			system("pause");
		}
		else if (ammount > currentAccount.balance) {
			cout << "Insuffecient Funds. You Only Have " << currentAccount.balance << endl;
			system("pause");
		}
	} while ((ammount <= 0) || (ammount > currentAccount.balance));

	currentAccount.balance -= ammount;
	temp->account.balance += ammount;

	cout << "Transaction Successful!";

}

void Bank::changePincode() {
	string oldP, newP, confirmP;
	bool isValid;

	cout << "Enter the Old PinCode:"; cin >> oldP;

	if (oldP != currentAccount.pincode) {
		cout << "Incorrect Old PinCode!";
		system("pause");
		return;
	}

	do {
		isValid = true;
		cout << "Enter New PinCode:"; cin >> newP;

		if (newP.length() != 6) {
			cout << "PinCode must be exactly 6 digits long!";
			isValid = false;
			continue;
		}

		for (char c : newP) {
			if (isdigit(c)) {
				isValid = false;
				break;
			}
		}

		if (isValid) {
			cout << "Confirm New PinCode:"; cin >> newP;

			if (newP != confirmP) {
				cout << "PinCodes do not match!";
				isValid = false;
			}
			else if (newP == oldP)
			{
				cout << "You have already used that PinCode. Please Choose a different one.";
				isValid = false;
			}
		}
	} while (isValid);

	currentAccount.pincode = newP;
	cout << "Successfully Changed PinCode.";
	system("pause");
}