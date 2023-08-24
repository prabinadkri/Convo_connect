#include "SignupFrame.h"
#include"main.h"
#include<wx/wx.h>
#include <wx/spinctrl.h>
#include<thread>
#include"MainFrame.h"
#include "./client.h"
wxString usernameValue = "";


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
    usernameTextCtrl->Bind(wxEVT_TEXT, &SignupFrame::OnUsernameTextChanged, this);

	wxStaticText* passwordLabel = new wxStaticText(panel, wxID_ANY, "Password", wxPoint(250, 420));
	passwordTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(320, 420), wxSize(200, -1), wxTE_PASSWORD);

	openButton = new wxButton(panel, wxID_ANY, " ADD A Profile Pic", wxPoint(320, 445), wxSize(100, 35));
	openButton->Bind(wxEVT_BUTTON, &SignupFrame::OnOpenButtonClicked, this);


	wxButton* submitButton = new wxButton(panel, wxID_ANY, "Signup", wxPoint(250, 480), wxSize(100, 35));
	wxButton* loginButton = new wxButton(panel, wxID_ANY, "Login", wxPoint(355, 480), wxSize(100, 35));

	submitButton->Bind(wxEVT_BUTTON, &SignupFrame::OnSubmitButtonClicked, this);
	loginButton->Bind(wxEVT_BUTTON, &SignupFrame::OnLoginButtonClicked, this);



	CreateStatusBar();
}
void SignupFrame::OnUsernameTextChanged(wxCommandEvent& evt) {
    
    usernameValue = usernameTextCtrl->GetValue();
    
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
	std::this_thread::sleep_for(std::chrono::seconds(1));
	while (!client.Incoming().empty())
	{
		auto msg = client.Incoming().pop_front().msg;

		switch (msg.header.id)
		{
		case CustomMsgTypes::Signup:
		{
			std::string a(msg.body.begin(), msg.body.end());
			wxMessageBox(a, "Login Info", wxOK | wxICON_INFORMATION);
		}break;
		}
	}
	
	wxLogStatus(username);
}
void SignupFrame::OnLoginButtonClicked(wxCommandEvent& evt) {
	Close();
	MainFrame* mainf = new MainFrame("Convo-Connect");
	mainf->SetClientSize(800, 600);
	mainf->Center();
	mainf->Show();
	
}







class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
};





MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    const auto margin = FromDIP(10);

    auto mainSizer = new wxBoxSizer(wxVERTICAL);
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    this->SetBackgroundColour(panel->GetBackgroundColour());

    auto sizer = new wxGridBagSizer(margin, margin);

    auto nameLabel = new wxStaticText(panel, wxID_ANY, "File Name:");
    auto kindLabel = new wxStaticText(panel, wxID_ANY, "Kind:");
    auto sizeLabel = new wxStaticText(panel, wxID_ANY, "Size:");
    auto dimensionsLabel = new wxStaticText(panel, wxID_ANY, "Dimensions:");

    auto kindValue = new wxStaticText(panel, wxID_ANY, "PNG");
    auto sizeValue = new wxStaticText(panel, wxID_ANY, "1.2 MB");
    auto dimensionsValue = new wxStaticText(panel, wxID_ANY, "1024x768");

    auto nameText = new wxTextCtrl(panel, wxID_ANY);
    nameText->SetEditable(false);

    auto loadButton = new wxButton(panel, wxID_ANY, "Load...");

    auto nameFormSizer = new wxBoxSizer(wxHORIZONTAL);
    nameFormSizer->Add(nameText, 1, wxEXPAND | wxRIGHT, margin);
    nameFormSizer->Add(loadButton, 0, wxALIGN_CENTER_VERTICAL);

    auto bitmap = new BufferedBitmap(panel, wxID_ANY, wxBitmap(wxSize(1, 1)), wxDefaultPosition, FromDIP(wxSize(400, 200)));

    sizer->Add(nameLabel, { 0, 0 }, { 1, 1 }, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    sizer->Add(kindLabel, { 1, 0 }, { 1, 1 }, wxALIGN_RIGHT);
    sizer->Add(sizeLabel, { 2, 0 }, { 1, 1 }, wxALIGN_RIGHT);
    sizer->Add(dimensionsLabel, { 3, 0 }, { 1, 1 }, wxALIGN_RIGHT);

    sizer->Add(kindValue, { 1, 1 }, { 1, 1 }, wxEXPAND);
    sizer->Add(sizeValue, { 2, 1 }, { 1, 1 }, wxEXPAND);
    sizer->Add(dimensionsValue, { 3, 1 }, { 1, 1 }, wxEXPAND);

    sizer->Add(nameFormSizer, { 0, 1 }, { 1, 3 }, wxEXPAND);
    sizer->Add(bitmap, { 1, 2 }, { 3, 2 }, wxEXPAND);
    auto saveButton = new wxButton(panel, wxID_ANY, "Save...");
    sizer->Add(saveButton, { 0, 4 }, { 1, 1 }, wxEXPAND);

    sizer->AddGrowableRow(3);
    sizer->AddGrowableCol(2);

    panel->SetSizer(sizer);

    mainSizer->Add(panel, 1, wxEXPAND | wxALL, margin);
    this->SetSizerAndFit(mainSizer);

    saveButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
        {
            // No need to use the saveFileDialog for name, use usernameValue directly
            wxString savePath = "C:\\Users\\acer\\Desktop\\TS\\C++\\Convo_connect - Copy\\assets\\" + usernameValue + ".png";

            // Save the image to the chosen path
            if (bitmap->GetBitmap().IsOk())
            {
                wxImage imageToSave = bitmap->GetBitmap().ConvertToImage();
                if (imageToSave.SaveFile(savePath, wxBITMAP_TYPE_PNG))
                {
                    wxMessageBox("Image saved successfully.", "Success", wxICON_INFORMATION | wxOK, this);
                }
                else
                {
                    wxMessageBox("Failed to save the image.", "Error", wxICON_ERROR | wxOK, this);
                }
            }
            else
            {
                wxMessageBox("No image to save.", "Error", wxICON_ERROR | wxOK, this);
            }
        });


    wxInitAllImageHandlers();

    loadButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
        {
            wxFileDialog openFileDialog(this, "Open Image", "", "", "Image files (*.png;*.jpg;*.jpeg;*.bmp)|*.png;*.jpg;*.jpeg;*.bmp", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

            if (openFileDialog.ShowModal() == wxID_CANCEL)
            {
                return;
            }

            wxImage image;
            if (!image.LoadFile(openFileDialog.GetPath()))
            {
                wxMessageBox("Failed to load image");
                return;
            }

            // set bitmap
            bitmap->SetBitmap(wxBitmap(image));
            nameText->SetValue(openFileDialog.GetPath());

            wxFile file(openFileDialog.GetPath());

            kindValue->SetLabel(wxFileName(openFileDialog.GetPath()).GetExt().Upper());
            sizeValue->SetLabel(wxString::Format("%d KB", static_cast<int>(file.Length() / 1024)));

            dimensionsValue->SetLabel(wxString::Format("%d x %d", image.GetWidth(), image.GetHeight()));

            this->Layout();
            this->Fit(); });
}

void SignupFrame::OnOpenButtonClicked(wxCommandEvent& evt) {

	MyFrame* frame = new MyFrame("Hello World", wxDefaultPosition, wxDefaultSize);
	frame->Show(true);
	

}