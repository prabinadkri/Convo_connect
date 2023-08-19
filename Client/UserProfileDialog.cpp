#pragma once 

#include "UserProfileDialog.h"

UserProfileDialog::UserProfileDialog(wxWindow *parent, wxWindowID id)
    : wxDialog(parent, id, "User Profile", wxDefaultPosition, wxDefaultSize,
               wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *usernameLabel = new wxStaticText(this, wxID_ANY, "Username:");
    usernameInput = new wxTextCtrl(this, wxID_ANY);

    wxStaticText *statusLabel = new wxStaticText(this, wxID_ANY, "Status:");
    statusInput = new wxTextCtrl(this, wxID_ANY);

    saveButton = new wxButton(this, wxID_OK, "Save");
    cancelButton = new wxButton(this, wxID_CANCEL, "Cancel");

    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(saveButton, 0, wxALL, 5);
    buttonSizer->Add(cancelButton, 0, wxALL, 5);

    mainSizer->Add(usernameLabel, 0, wxALL, 5);
    mainSizer->Add(usernameInput, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(statusLabel, 0, wxALL, 5);
    mainSizer->Add(statusInput, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxALL, 5);

    SetSizerAndFit(mainSizer);
}
