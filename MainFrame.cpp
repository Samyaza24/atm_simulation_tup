#include "MainFrame.h"
#include "classes.h"
#include <windows.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

MainFrame::MainFrame(const wxString& title) 
    : wxFrame(nullptr, wxID_ANY, title), 
    adminAccount("00000", "admin", "123456", "09-28-2004", "+63 909-320-5093", 1000000.0),
    bank(adminAccount) 
{ 
    /*wxMessageBox(wxString::Format("Admin Balance: %f", adminAccount.balance), "Balance Inquiry", wxOK | wxICON_INFORMATION);
    wxMessageBox(wxString::Format("Current Account Balance: %f", bank.currentAccount.balance), "Balance Inquiry", wxOK | wxICON_INFORMATION);*/

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


    //                  INSIDE TRANS
    // Balance Inquiry Controls
    //BalanceText = new wxStaticText(panel, wxID_ANY, "Current Balance");

    // balance
    BalanceText = new wxStaticText(panel, wxID_ANY, "Current Balance");
    BalanceText->SetFont(headlineFont);
    ConfirmBalanceInquiryButton = new wxButton(panel, wxID_ANY, "Confirm");

    //withraw Controls
    WithrawText = new wxStaticText(panel, wxID_ANY, "Withraw Transaction", wxPoint(0, 22), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
    WithrawText->SetFont(headlineFont);
    WithrawInputField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    ConfirmWithrawButton = new wxButton(panel, wxID_ANY, "Confirm");

    //  DEPOSIT CONTROLS
    DepositText = new wxStaticText(panel, wxID_ANY, "Deposit Transaction", wxPoint(0, 22), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
    DepositText->SetFont(headlineFont);
    DepositInputField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    ConfirmDepositButton = new wxButton(panel, wxID_ANY, "Confirm");


    ShowInsertCardText(true);
    ShowEnterPincode(false);
    ShowRegistrationControls(false);
    ShowTransactionControls(false);
    ShowBalanceInquiryControls(false);
    ShowWithrawTransactionControls(false);
    ShowDepositTransactionControls(false);

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

    // Add Balance Inquiry Controls to Sizer
    mainSizer->Add(BalanceText, wxSizerFlags().CenterHorizontal());
    mainSizer->Add(ConfirmBalanceInquiryButton, wxSizerFlags().Expand().Border(wxALL, 10));

    mainSizer->Add(WithrawText, wxSizerFlags().CenterHorizontal());
    mainSizer->Add(WithrawInputField, wxSizerFlags().Expand());
    mainSizer->Add(ConfirmWithrawButton, wxSizerFlags().Expand().Border(wxALL, 10));

    mainSizer->Add(DepositText, wxSizerFlags().CenterHorizontal());
    mainSizer->Add(DepositInputField, wxSizerFlags().Expand());
    mainSizer->Add(ConfirmDepositButton, wxSizerFlags().Expand().Border(wxALL, 10));


    // Outer Sizer for Border 
    wxGridSizer* outerSizer = new wxGridSizer(1);
    outerSizer->Add(mainSizer, wxSizerFlags(1).Border(wxALL, 25).Expand());

    panel->SetSizer(outerSizer);
    outerSizer->SetSizeHints(this);
}

void MainFrame::BindEventHandlers()
{
    this->Bind(wxEVT_TIMER, &MainFrame::OnTimer, this);

    balanceInquiryButton->Bind(wxEVT_BUTTON, &MainFrame::OnBalanceInquiryButtonClicked, this);
    withdrawButton->Bind(wxEVT_BUTTON, &MainFrame::OnWithrawButtonClicked, this);
    depositButton->Bind(wxEVT_BUTTON, &MainFrame::OnDepositButtonClicked, this);


    ConfirmBalanceInquiryButton->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmBalanceInquiryButtonClicked, this);
    ConfirmWithrawButton->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmWithrawButtonClicked, this);
    ConfirmDepositButton->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmDepositButtonClicked, this);


}

void MainFrame::OnTimer(wxTimerEvent& evt)
{
    timer->Stop();
    if(true)
    //if (IsFlashDriveInserted('D'))
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
        ShowEnterPincode(false);
        ShowInsertCardText(false);
        ShowRegistrationControls(false);
        ShowTransactionControls(true);
    }
    else
    {
        ShowRegistrationControls(false);
        //ShowRegistrationControls(true);
        ShowInsertCardText(false);
        ShowEnterPincode(false);
        //ShowTransactionControls(false);
        ShowTransactionControls(true);

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

    ShowBalanceInquiryControls(false);
    ShowWithrawTransactionControls(false);



    if (show) {
        panel->Layout();
    }
}

void MainFrame::ShowBalanceInquiryControls(bool show)
{
    BalanceText->Show(show);
    ConfirmBalanceInquiryButton->Show(show);
}

void MainFrame::ShowWithrawTransactionControls(bool show)
{
    WithrawText->Show(show);
    WithrawInputField->Show(show);
    ConfirmWithrawButton->Show(show);
}

void MainFrame::ShowDepositTransactionControls(bool show)
{
    DepositText->Show(show);
    DepositInputField->Show(show);
    ConfirmDepositButton->Show(show);
}

void MainFrame::OnBalanceInquiryButtonClicked(wxCommandEvent& evt)
{
    ShowTransactionControls(false);
    ShowBalanceInquiryControls(true);
    double balance = bank.currentAccount.balance;

    BalanceText->SetLabel(wxString::Format("Current Balance: %.2f", balance));

    BalanceText->Show(true);
    panel->Layout();
}

void MainFrame::OnConfirmBalanceInquiryButtonClicked(wxCommandEvent& evt)
{
    ShowBalanceInquiryControls(false);
    ShowTransactionControls(true);
    panel->Layout();
}

void MainFrame::OnWithrawButtonClicked(wxCommandEvent& evt) {
    ShowTransactionControls(false);
    ShowWithrawTransactionControls(true);
    panel->Layout();
}

void MainFrame::OnConfirmWithrawButtonClicked(wxCommandEvent& evt) {

    long amount = 0;

    if (WithrawInputField->GetValue().ToLong(&amount) && amount > 0) {
        bool result = bank.withraw(static_cast<int>(amount));

        if (result) {
            wxMessageBox(wxString::Format("You Withrew %ld", amount), "Transaction Successful", wxOK | wxICON_INFORMATION);
        }
        else {
            wxMessageBox("Failed Transaction");
        }
    }
    else {
        wxMessageBox("Invalid amount", "ERROR", wxOK | wxICON_ERROR);
    }

    WithrawInputField->Clear();
    ShowTransactionControls(true);

}

void MainFrame::OnDepositButtonClicked(wxCommandEvent& evt)
{
    ShowTransactionControls(false);
    ShowDepositTransactionControls(true);
    panel->Layout();
}

void MainFrame::OnConfirmDepositButtonClicked(wxCommandEvent& evt)
{
    ShowDepositTransactionControls(false);
    long amount = 0;
    if (DepositInputField->GetValue().ToLong(&amount) && amount > 0) {
        bool result = bank.deposit(static_cast<int>(amount));

        if (result) {
            wxMessageBox(wxString::Format("Deposited %ld", amount), "Transaction Successful", wxOK | wxICON_INFORMATION);
        }
        else {
            wxMessageBox(wxString::Format("Failed Transaction"), "ERROR", wxOK | wxICON_ERROR);
        }
    }
    else {
        wxMessageBox("Invalid Amount. Please enter a positive number.", "ERROR", wxOK | wxICON_ERROR);
    }
    DepositInputField->Clear();
    ShowTransactionControls(true);
}
