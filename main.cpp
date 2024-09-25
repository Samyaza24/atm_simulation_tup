#include <iostream>
#include <windows.h>  // For GetDriveType function
#include <fstream>
#include <string>

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

    return 0;
}