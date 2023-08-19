#include<wx/wx.h>
#pragma once

#include "client.h"


// extern CustomClient client;

class MainFrame:public wxFrame
{
private:
	wxTextCtrl* usernameTextCtrl;
	wxTextCtrl* passwordTextCtrl;
	void OnLoginButtonClicked(wxCommandEvent& evt);
	void OnSignupButtonClicked(wxCommandEvent& evt);

public:
	MainFrame(const wxString& title);
	CustomClient client;
	// CustomClient getclient(){
	// 	return client;
	// }
	
};
