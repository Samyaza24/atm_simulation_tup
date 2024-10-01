#include "MainFrame.h"
#include "classes.h"
#include <windows.h>
#include <filesystem>
#include <fstream>
#include <string>

using namespace std;

MainFrame::MainFrame(const wxString& title) 
    : wxFrame(nullptr, wxID_ANY, title), 
    adminAccount("00000", "admin", "123456", "09-28-2004", "+63 909-320-5093", 1000000),
    bank(adminAccount)
{
    CreateControls();
    SetupSizers();
    BindEventHandlers();
}

void MainFrame::CreateControls()
{
    wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
    wxFont mainFont(wxFontInfo(wxSize(0, 20)));

    panel = new wxPanel(this);
    panel->SetFont(mainFont);

    timer = new wxTimer(this, wxID_ANY);
    timer->Start(2000);
    
    insertCardText = new wxStaticText(panel, wxID_ANY, "Please insert card...");
    insertCardText->SetFont(headlineFont);

    // Enter PIN Code Field
    enterPincodeText = new wxStaticText(panel, wxID_ANY, "Enter PIN Code");
    enterPincodeText->SetFont(headlineFont);
    pincodeInputField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    enterPincodeButton = new wxButton(panel, wxID_ANY, "Enter PIN Code", wxDefaultPosition, wxDefaultSize);

    // Registration Controls
    registrationText = new wxStaticText(panel, wxID_ANY, "Register for an Account");
    registrationText->SetFont(headlineFont);
    accountNameInputField = new wxTextCtrl(panel, wxID_ANY, "Name", wxDefaultPosition, wxDefaultSize);
    birthdayInputField = new wxTextCtrl(panel, wxID_ANY, "Birthday (12-31-2000)", wxDefaultPosition, wxDefaultSize);
    contactNumberInputField = new wxTextCtrl(panel, wxID_ANY, "Contact Number (+63 909-123-456)", wxDefaultPosition, wxDefaultSize);
    pinCodeInputField = new wxTextCtrl(panel, wxID_ANY, "PIN Code (123456)", wxDefaultPosition, wxDefaultSize);
    registerButton = new wxButton(panel, wxID_ANY, "Register");
  
    // Transaction Controls
    transactionText = new wxStaticText(panel, wxID_ANY, "Choose a Transaction");
    transactionText->SetFont(headlineFont);
    balanceInquiryButton = new wxButton(panel, wxID_ANY, "Balance Inquiry");
    withdrawButton = new wxButton(panel, wxID_ANY, "Withdraw");
    depositButton = new wxButton(panel, wxID_ANY, "Deposit");
    fundTransferButton = new wxButton(panel, wxID_ANY, "Fund Transfer");
    changePinButton = new wxButton(panel, wxID_ANY, "Change PIN Code");

    ShowInsertCardText(true);
    ShowEnterPincode(false);
    ShowRegistrationControls(false);
    ShowTransactionControls(false);

    statusBar = CreateStatusBar();
    statusBar->SetDoubleBuffered(true);
}

void MainFrame::SetupSizers()
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    mainSizer->Add(insertCardText, wxSizerFlags().Center());

    // Add a Box Sizer for PIN Code field and button
    wxBoxSizer* inputPinSizer = new wxBoxSizer(wxHORIZONTAL);
    inputPinSizer->Add(pincodeInputField, wxSizerFlags().Proportion(1));
    inputPinSizer->AddSpacer(5);
    inputPinSizer->Add(enterPincodeButton);

    mainSizer->Add(enterPincodeText, wxSizerFlags().CenterHorizontal());
    mainSizer->Add(inputPinSizer, wxSizerFlags().Expand());
    
    // Add Registration Controls to Sizer
    mainSizer->Add(registrationText, wxSizerFlags().CenterHorizontal());
    mainSizer->Add(accountNameInputField, wxSizerFlags().Expand());
    mainSizer->Add(birthdayInputField, wxSizerFlags().Expand());
    mainSizer->Add(contactNumberInputField, wxSizerFlags().Expand());
    mainSizer->Add(pinCodeInputField, wxSizerFlags().Expand());
    mainSizer->Add(registerButton, wxSizerFlags().Expand());
    
    // Add Transaction Controls to Sizer
    mainSizer->Add(transactionText, wxSizerFlags().CenterHorizontal());
    mainSizer->Add(balanceInquiryButton, wxSizerFlags().Expand());
    mainSizer->Add(withdrawButton, wxSizerFlags().Expand());
    mainSizer->Add(depositButton, wxSizerFlags().Expand());
    mainSizer->Add(fundTransferButton, wxSizerFlags().Expand());
    mainSizer->Add(changePinButton, wxSizerFlags().Expand());

    // Outer Sizer for Border 
    wxGridSizer* outerSizer = new wxGridSizer(1);
    outerSizer->Add(mainSizer, wxSizerFlags(1).Border(wxALL, 25).Expand());

    panel->SetSizer(outerSizer);
    outerSizer->SetSizeHints(this);
}

void MainFrame::BindEventHandlers()
{
    this->Bind(wxEVT_TIMER, &MainFrame::OnTimer, this);
}

void MainFrame::OnTimer(wxTimerEvent& evt)
{
    if (IsFlashDriveInserted('D'))
    {
        OnFlashDriveInserted();
    }
    else
    {
        ShowInsertCardText(true);
        ShowEnterPincode(false);
        ShowRegistrationControls(false);
        ShowTransactionControls(false);
        panel->Layout();
    }
}

void MainFrame::OnFlashDriveInserted()
{
    if (bank.isCardRegistered())
    {
        ShowEnterPincode(true);
        ShowInsertCardText(false);
        ShowRegistrationControls(false);
        ShowTransactionControls(false);
    }
    else
    {
        ShowRegistrationControls(true);
        ShowInsertCardText(false);
        ShowEnterPincode(false);
        ShowTransactionControls(false);
    }
    panel->Layout();
}

bool MainFrame::IsFlashDriveInserted(char driveLetter)
{
    wstring drivePath = wstring(1, driveLetter) + L":\\";

    UINT driveType = GetDriveType(drivePath.c_str());

    // DRIVE_REMOVABLE represents removable drives like USB flash drives
    return (driveType == DRIVE_REMOVABLE);
}

void MainFrame::ShowInsertCardText(bool show)
{
    insertCardText->Show(show);
}

void MainFrame::ShowEnterPincode(bool show)
{
    enterPincodeText->Show(show);
    pincodeInputField->Show(show);
    enterPincodeButton->Show(show);
}

void MainFrame::ShowRegistrationControls(bool show)
{
    registrationText->Show(show);
    accountNameInputField->Show(show);
    birthdayInputField->Show(show);
    contactNumberInputField->Show(show);
    pinCodeInputField->Show(show);
    registerButton->Show(show);
}

void MainFrame::ShowTransactionControls(bool show)
{
    transactionText->Show(show);
    balanceInquiryButton->Show(show);
    withdrawButton->Show(show);
    depositButton->Show(show);
    fundTransferButton->Show(show);
    changePinButton->Show(show);
}
