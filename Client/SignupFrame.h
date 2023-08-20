#pragma once
#include<wx/wx.h>
#include <wx/spinctrl.h>

class SignupFrame:public wxFrame
{
private:
	wxTextCtrl* nameTextCtrl;
	wxTextCtrl* emailTextCtrl;
	wxComboBox* userRoleTextCtrl;
	wxSpinCtrl* ageSpinCtrl;
	wxTextCtrl* usernameTextCtrl;
	wxTextCtrl* passwordTextCtrl;
	void OnSubmitButtonClicked(wxCommandEvent& evt);
	void OnLoginButtonClicked(wxCommandEvent& evt);

public:
	SignupFrame(const wxString& title);
};
