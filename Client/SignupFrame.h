#include<wx/wx.h>
#include <wx/spinctrl.h>

#include <wx/gbsizer.h>
#include <wx/file.h>
#include <wx/filename.h>
#include <wx/filedlg.h>

#include <vector>
#include "bufferedbitmap.h"
class MyFrame;

class SignupFrame:public wxFrame
{
private:
	wxTextCtrl* nameTextCtrl;
	wxTextCtrl* emailTextCtrl;
	wxComboBox* userRoleTextCtrl;
	wxSpinCtrl* ageSpinCtrl;
	wxTextCtrl* usernameTextCtrl=NULL;
	wxButton* openButton;
	wxTextCtrl* passwordTextCtrl;
	void OnSubmitButtonClicked(wxCommandEvent& evt);
	void OnLoginButtonClicked(wxCommandEvent& evt);
	void OnOpenButtonClicked(wxCommandEvent& evt);
	void OnUsernameTextChanged(wxCommandEvent& evt);


public:
	SignupFrame(const wxString& title);
	friend class MyFrame;
	friend wxString gettingusername();
};


