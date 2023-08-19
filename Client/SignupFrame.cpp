#include "SignupFrame.h"
#include"main.h"
#include<wx/wx.h>
#include <wx/spinctrl.h>

#include"MainFrame.h"

SignupFrame::SignupFrame(const wxString& title) :wxFrame(nullptr, wxID_ANY, title) {
	wxPanel* panel = new wxPanel(this);
	
	wxStaticText* NameLabel = new wxStaticText(panel, wxID_ANY, "Name", wxPoint(250, 220));
	nameTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(320, 220), wxSize(200, -1));

	wxStaticText* emailLabel = new wxStaticText(panel, wxID_ANY, "email", wxPoint(250, 255));
	emailTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(320, 255), wxSize(200, -1));

	wxString choices[] = { "Admin", "User"};
	userRoleTextCtrl = new wxComboBox(panel, wxID_ANY, "User", wxPoint(250, 285), wxDefaultSize, 2, choices, wxCB_DROPDOWN);

	wxStaticText* ageLabel = new wxStaticText(panel, wxID_ANY, "age:", wxPoint(250, 325));

	ageSpinCtrl = new wxSpinCtrl(panel, wxID_ANY, "25", wxPoint(320, 325), wxDefaultSize,
                                         wxSP_ARROW_KEYS, 0, 120, 25);


	wxStaticText* usernameLabel = new wxStaticText(panel, wxID_ANY, "Username", wxPoint(250, 355));
	usernameTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(320, 355), wxSize(200, -1));

	wxStaticText* passwordLabel = new wxStaticText(panel, wxID_ANY, "Password", wxPoint(250, 420));
	passwordTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(320, 420), wxSize(200, -1), wxTE_PASSWORD);


	wxButton* submitButton = new wxButton(panel, wxID_ANY, "Signup", wxPoint(250, 440), wxSize(100, 35));
	wxButton* loginButton = new wxButton(panel, wxID_ANY, "Login", wxPoint(355, 440), wxSize(100, 35));

	submitButton->Bind(wxEVT_BUTTON, &SignupFrame::OnSubmitButtonClicked, this);
	loginButton->Bind(wxEVT_BUTTON, &SignupFrame::OnLoginButtonClicked, this);

	CreateStatusBar();
}

void SignupFrame::OnSubmitButtonClicked(wxCommandEvent& evt) {
	wxLogStatus("Button clicked");
	wxString name = nameTextCtrl->GetValue();
    wxString email = emailTextCtrl->GetValue();
    wxString userRole = userRoleTextCtrl->GetValue();
    int age = ageSpinCtrl->GetValue();
    wxString username = usernameTextCtrl->GetValue();
    wxString password = passwordTextCtrl->GetValue();

    std::string nameStr = name.ToStdString();
    std::string emailStr = email.ToStdString();
    std::string userRoleStr = userRole.ToStdString();
    std::string usernameStr = username.ToStdString();
    std::string passwordStr = password.ToStdString();



	User s1(nameStr,emailStr, userRoleStr,usernameStr,passwordStr,age);
	wxLogStatus("User is being created");
	s1.AddUser();
	wxMessageBox("signup successfully", "Login Info", wxOK | wxICON_INFORMATION);
	wxLogStatus(username);
}
void SignupFrame::OnLoginButtonClicked(wxCommandEvent& evt) {
	Close();
	MainFrame* mainf = new MainFrame("Convo-Connect");
	mainf->SetClientSize(800, 600);
	mainf->Center();
	mainf->Show();
	
}