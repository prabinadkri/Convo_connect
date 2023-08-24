#include "MainFrame.h"
#include"main.h"
#include<wx/wx.h>
#include"SignupFrame.h"
#include "MessageFrame.h"
#include "client.h"
#include <thread>
User sender;
MainFrame::MainFrame(const wxString& title) :wxFrame(nullptr, wxID_ANY, title) {

	
	//client.Sendmsg("asdd", "xyz", "123");
	wxPanel* panel = new wxPanel(this);
	wxStaticText* usernameLabel = new wxStaticText(panel, wxID_ANY, "Username", wxPoint(250,150 ));
	usernameTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(320, 150),wxSize(200,-1));
	wxStaticText* passwordLabel = new wxStaticText(panel, wxID_ANY, "Password", wxPoint(250, 220));
	passwordTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(320, 220), wxSize(200, -1),wxTE_PASSWORD);
	wxButton* submitButton = new wxButton(panel, wxID_ANY, "Login", wxPoint(250, 255), wxSize(100, 35));
	wxButton* signupButton = new wxButton(panel, wxID_ANY, "signup", wxPoint(355, 255), wxSize(100, 35));

	submitButton->Bind(wxEVT_BUTTON, &MainFrame::OnLoginButtonClicked, this);
	signupButton->Bind(wxEVT_BUTTON, &MainFrame::OnSignupButtonClicked, this);
	CreateStatusBar();
}

void MainFrame::OnLoginButtonClicked(wxCommandEvent& evt) {
	wxLogStatus("Button clicked");
	wxString username = usernameTextCtrl->GetValue();
	wxString password = passwordTextCtrl->GetValue();
	std::string Username = username.ToStdString();
	std::string Password = password.ToStdString();


	User s1;
	 sender = s1.AuthenticateUser(Username, Password);
	if (!sender.IsEmpty())
	{
		wxMessageBox("login successfully", "Login Info", wxOK | wxICON_INFORMATION);
		Close();
	wxInitAllImageHandlers();

   MessageFrame* messageFrame = new MessageFrame("Convo_Connect", wxDefaultPosition, wxDefaultSize);
        messageFrame->SetClientSize(800, 600);
        //messageFrame->SetBackgroundColour(wxColor(100, 100, 200));
        messageFrame->SetMinSize(wxSize(400, 400)); // Set the minimum size here
        messageFrame->Bind(wxEVT_SIZE, &MessageFrame::OnSize, messageFrame); // Bind event handler here
		
        messageFrame->Show(true);

	}
	else {
		wxMessageBox("wrong username or password", "Login Info", wxOK | wxICON_INFORMATION);
	}
	
}
void MainFrame::OnSignupButtonClicked(wxCommandEvent& evt) {
	Close();
	SignupFrame* signupFrame = new SignupFrame("Convo+Connect");
	signupFrame->SetClientSize(800, 600);
	signupFrame->Center();
	signupFrame->Show();

}