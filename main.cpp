#include <iostream>
#include <windows.h>  // For GetDriveType function
#include <fstream>
#include <string>

#include "classes.h"

using namespace std;

bool isFlashDriveInserted(char driveLetter) 
{
    wstring drivePath = wstring(1, driveLetter) + L":\\";

    UINT driveType = GetDriveType(drivePath.c_str());

    // DRIVE_REMOVABLE represents removable drives like USB flash drives
    return (driveType == DRIVE_REMOVABLE);
}


int main() {    
    char driveLetter = 'D';  // Replace 'D' with the letter assigned to your flash drive

    while (true) {
        if (isFlashDriveInserted(driveLetter)) {
            cout << "Flash drive " << driveLetter << ": is inserted!" << endl;
            break;  
        }
        else {
            cout << "Waiting for flash drive " << driveLetter << ":..." << endl;
        }

        // Wait for 2 seconds before checking again
        Sleep(2000);
    }

    // TESTING by FORD
    cout << "This is Testing by Ford" << endl;
    system("pause");

    

    cout << "Declared 3 accounts and used add method. The following accounts were added to the Linked List" << endl;
    C::Account adminAccount("00001", "Ford Torion", "123456", "09-28-2004", "+63 909-090-9090", 5000);
    C::Account account1;
    C::Account account2("00003", "Clifford Roy", "111111", "09-09-0909", "+63 909-090-9090", 5000);
    C::Bank TUPBank(adminAccount);

    TUPBank.retrieveAllAccounts();

    /*TUPBank.add(adminAccount);
    TUPBank.add(account1);
    TUPBank.add(account2);*/

    TUPBank.displayAllAccounts();

    system("pause");
    system("cls");

    cout << "Saving to allAccounts.csv" << endl;

    TUPBank.save_all_accounts();


    return 0;
}