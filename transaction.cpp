#include "classes.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

bool Bank::withraw(int amount) {
	if (amount > currentAccount.balance) {
		return false;
	}
	else if (currentAccount.balance - amount <= 0) {
		return false;
	}
	else {
		currentAccount.balance -= amount;
		return true;
	}
}

bool Bank::deposit(int amount) {
	if (amount > 1000000000000) {
		return false;
	}
	else if (amount <= 0) {
		return false;
	}
	else {
		currentAccount.balance += amount;
		return true;
	}
}

bool Bank::fundTransfer(const string& receiverAccountNumber, int amount)
{
	// If valid amount
	if (amount <= 0 || currentAccount.balance <= 0 || amount > currentAccount.balance) {
		return false; 
	}

	// Find the receiver account in the list
	Node* current = head;
	while (current != nullptr) {
		if (current->account.accountNumber == receiverAccountNumber) {
			// Transfer funds
			currentAccount.balance -= amount; // Deduct from current account
			current->account.balance += amount; // Add to receiver's account
			return true; // Transfer successful
		}
		current = current->next;
	}

	return false; // Receiver account not found
}



