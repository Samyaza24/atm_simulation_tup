#pragma once
#include <wx/wx.h>
#include "classes.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
	
private:
	Account adminAccount;
	Bank bank;

	void CreateControls();
	void SetupSizers();
	void BindEventHandlers();

	void OnTimer(wxTimerEvent& evt);
	void OnFlashDriveInserted();

	bool IsFlashDriveInserted(char driveLetter);
	
	void ShowInsertCardText(bool show);
	void ShowEnterPincode(bool show);
	void ShowRegistrationControls(bool show);
	void ShowTransactionControls(bool show);

	void OnBalanceInquiryButtonClicked(wxCommandEvent& evt);

	wxPanel* panel;
	wxTimer* timer;

	wxStaticText* insertCardText;

	wxStaticText* enterPincodeText;
	wxTextCtrl* pincodeInputField;
	wxButton* enterPincodeButton;

	wxStaticText* registrationText;
	wxTextCtrl* accountNameInputField;
	wxTextCtrl* birthdayInputField;
	wxTextCtrl* contactNumberInputField;
	wxTextCtrl* pinCodeInputField;
	wxButton* registerButton;
	
	wxStaticText* transactionText;
	wxButton* balanceInquiryButton; 
	wxButton* withdrawButton;
	wxButton* depositButton;
	wxButton* fundTransferButton; 
	wxButton* changePinButton; 

	wxStatusBar* statusBar;

	// Balance Inquiry
	wxStaticText* balanceText;
	
};

