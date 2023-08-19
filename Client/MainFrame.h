#include<wx/wx.h>

class MainFrame:public wxFrame
{
private:
	wxTextCtrl* usernameTextCtrl;
	wxTextCtrl* passwordTextCtrl;
	void OnLoginButtonClicked(wxCommandEvent& evt);
	void OnSignupButtonClicked(wxCommandEvent& evt);

public:
	MainFrame(const wxString& title);
	
};
