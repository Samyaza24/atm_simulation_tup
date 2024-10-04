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

