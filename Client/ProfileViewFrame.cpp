#include "ProfileViewFrame.h"
std::string image_path = "./Assets/test.png";
ProfileFrame::ProfileFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) {

    wxBoxSizer* nameSizer = new wxBoxSizer(wxHORIZONTAL);

    uppernameLabel = new wxStaticText(this, wxID_ANY, "Name:", wxDefaultPosition, wxSize(60, -1));
    nameSizer->Add(uppernameLabel, 0, wxALL, 10);

    nameLabel = new wxStaticText(this, wxID_ANY, "John Doe", wxDefaultPosition, wxSize(60, -1));
    nameSizer->Add(nameLabel, 0, wxALL, 10);

    editNameButton = new wxButton(this, wxID_ANY, "Edit");
    nameSizer->AddStretchSpacer(1);
    nameSizer->Add(editNameButton, 0, wxALIGN_RIGHT | wxALL, 10);

    mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(nameSizer, 0, wxEXPAND);

    wxBoxSizer* emailSizer = new wxBoxSizer(wxHORIZONTAL);
    
    upperemailLabel = new wxStaticText(this, wxID_ANY, "Email:", wxDefaultPosition, wxSize(60, -1));
    emailSizer->Add(upperemailLabel, 0, wxALL, 10);

    emailLabel = new wxStaticText(this, wxID_ANY, "@gmail.com", wxDefaultPosition, wxSize(200, -1));
    emailSizer->Add(emailLabel, 0, wxALL, 10);

    editEmailButton = new wxButton(this, wxID_ANY, "Edit");
    emailSizer->AddStretchSpacer(1);
    emailSizer->Add(editEmailButton, 0, wxALIGN_RIGHT | wxALL, 10);

    
    mainSizer->Add(emailSizer, 0, wxEXPAND);




    wxBoxSizer* ageSizer = new wxBoxSizer(wxHORIZONTAL);

    upperageLabel = new wxStaticText(this, wxID_ANY, "Age:", wxDefaultPosition, wxSize(60, -1));
    ageSizer->Add(upperageLabel, 0, wxALL, 10);

    ageLabel = new wxStaticText(this, wxID_ANY, "19", wxDefaultPosition, wxSize(60, -1));
    ageSizer->Add(ageLabel, 0, wxALL, 10);

    editAgeButton = new wxButton(this, wxID_ANY, "Edit");
    ageSizer->AddStretchSpacer(1);
    ageSizer->Add(editAgeButton, 0, wxALIGN_RIGHT | wxALL, 10);

    mainSizer->Add(ageSizer, 0, wxEXPAND);

    
    wxImage image;
    if (image.LoadFile(image_path, wxBITMAP_TYPE_ANY)) {
        // Resize the image if needed
        wxSize imageSize(100, 100); // Adjust the dimensions as needed
        image.Rescale(imageSize.x, imageSize.y, wxIMAGE_QUALITY_HIGH);

        wxBitmap bitmap(image);
        photoBitmap = new wxStaticBitmap(this, wxID_ANY, bitmap);

        photoLabel = new wxStaticText(this, wxID_ANY, "Photo:", wxDefaultPosition, wxSize(60, -1));

        editPhotoButton = new wxButton(this, wxID_ANY, "Edit");
        mainSizer->Add(photoLabel, 0, wxALL, 10);
        mainSizer->Add(photoBitmap, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        mainSizer->Add(editPhotoButton, 0, wxALIGN_RIGHT | wxALL, 10);

        // Bind event handler for the Edit button
        editPhotoButton->Bind(wxEVT_BUTTON, &ProfileFrame::OnEditPhotoButtonClicked, this);
    }

    //editPhotoButton = new wxButton(this, wxID_ANY, "Edit");

  /*  mainSizer->Add(photoLabel, 0, wxALL, 10);
    mainSizer->Add(photoBitmap, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(editPhotoButton, 0, wxALIGN_RIGHT | wxALL, 10);*/

    editNameButton->Bind(wxEVT_BUTTON, &ProfileFrame::OnEditNameButtonClicked, this);
    editEmailButton->Bind(wxEVT_BUTTON, &ProfileFrame::OnEditEmailButtonClicked, this);
    editAgeButton->Bind(wxEVT_BUTTON, &ProfileFrame::OnEditAgeButtonClicked, this);
    //editPhotoButton->Bind(wxEVT_BUTTON, &ProfileFrame::OnEditPhotoButtonClicked, this);

    SetSizerAndFit(mainSizer);
}


void ProfileFrame::OnEditNameButtonClicked(wxCommandEvent& event) {
    if (isEditingName) {
        wxString newName = nameTextCtrl->GetValue();
        nameLabel->SetLabel(newName);
        editNameButton->SetLabel("Edit");
        mainSizer->Detach(nameTextCtrl);
        nameTextCtrl->Destroy();
    }
    else {
        isEditingName = true;
        editNameButton->SetLabel("Save");
        nameTextCtrl = new wxTextCtrl(this, wxID_ANY, nameLabel->GetLabelText());
        mainSizer->Insert(0, nameTextCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        nameTextCtrl->SetFocus();
    }

    Layout();
}

void ProfileFrame::OnEditEmailButtonClicked(wxCommandEvent& event) {
    if (isEditingEmail) {
        wxString newEmail = emailTextCtrl->GetValue();
        emailLabel->SetLabel( newEmail);
        editEmailButton->SetLabel("Edit");
        mainSizer->Detach(emailTextCtrl);
        emailTextCtrl->Destroy();
    }
    else {
        isEditingEmail = true;
        editEmailButton->SetLabel("Save");
        emailTextCtrl = new wxTextCtrl(this, wxID_ANY, emailLabel->GetLabelText());
        mainSizer->Insert(2, emailTextCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        emailTextCtrl->SetFocus();
    }

    Layout();
}

void ProfileFrame::OnEditAgeButtonClicked(wxCommandEvent& event) {
    if (isEditingAge) {
        wxString newAge = ageTextCtrl->GetValue();
        ageLabel->SetLabel( newAge);
        editAgeButton->SetLabel("Edit");
        mainSizer->Detach(ageTextCtrl);
        ageTextCtrl->Destroy();
    }
    else {
        isEditingAge = true;
        editAgeButton->SetLabel("Save");
        ageTextCtrl = new wxTextCtrl(this, wxID_ANY, ageLabel->GetLabelText());
        mainSizer->Insert(4, ageTextCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        ageTextCtrl->SetFocus();
    }

    Layout();
}

void ProfileFrame::OnEditPhotoButtonClicked(wxCommandEvent& event) {
    if (isEditingPhoto) {
        editPhotoButton->SetLabel("Edit");
        mainSizer->Detach(photoBitmap);
        mainSizer->Detach(photoLabel);
        photoBitmap->Destroy();
    }
    else {
        isEditingPhoto = true;
        editPhotoButton->SetLabel("Save");

        wxString wildcard = "Image files (*.png;*.jpg;*.jpeg)|*.png;*.jpg;*.jpeg|All files (*.*)|*.*";
        wxString imagePath = wxFileSelector("Select an image file", wxEmptyString, wxEmptyString, wxEmptyString, wildcard, wxFD_OPEN);
        image_path = imagePath.ToStdString();
        if (!imagePath.empty()) {
           // Update the image_path
            wxImage image(imagePath, wxBITMAP_TYPE_ANY);
            if (image.IsOk()) {
                // Resize the image to the desired dimensions
                wxSize imageSize(100, 100); // Adjust the dimensions as needed
                image.Rescale(imageSize.x, imageSize.y, wxIMAGE_QUALITY_HIGH);

                // If the image already exists, destroy it
                if (photoBitmap) {
                    photoBitmap->Destroy();
                }

                wxBitmap bitmap(image);
                photoBitmap = new wxStaticBitmap(this, wxID_ANY, bitmap);

                mainSizer->Insert(6, photoLabel, 0, wxALL, 10);
                mainSizer->Insert(7, photoBitmap, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
            }
        }
    }

    Layout();
}


 

wxBEGIN_EVENT_TABLE(ProfileFrame, wxFrame)
// Add event handling entries here
wxEND_EVENT_TABLE()
