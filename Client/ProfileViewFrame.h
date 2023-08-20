#pragma once
#pragma once

#include <wx/wx.h>

class ProfileFrame : public wxFrame {
private:
    wxBoxSizer* mainSizer = nullptr;
    wxStaticText* nameLabel = nullptr;
    wxStaticText* uppernameLabel = nullptr;
    wxStaticText* upperemailLabel = nullptr;
    wxButton* editNameButton = nullptr;
    wxStaticText* upperageLabel = nullptr;

    wxStaticText* emailLabel = nullptr;
    wxButton* editEmailButton = nullptr;

    wxStaticText* ageLabel = nullptr;
    wxButton* editAgeButton = nullptr;

    wxStaticText* photoLabel = nullptr;
    wxStaticBitmap* photoBitmap = nullptr;
    wxButton* editPhotoButton = nullptr;

    wxTextCtrl* nameTextCtrl = nullptr;
    wxTextCtrl* emailTextCtrl = nullptr;
    wxTextCtrl* ageTextCtrl = nullptr;

    bool isEditingName = false;
    bool isEditingEmail = false;
    bool isEditingAge = false;
    bool isEditingPhoto = false;

public:
    ProfileFrame(const wxString& title);

private:
    void OnEditNameButtonClicked(wxCommandEvent& event);
    void OnEditEmailButtonClicked(wxCommandEvent& event);
    void OnEditAgeButtonClicked(wxCommandEvent& event);
    void OnEditPhotoButtonClicked(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};
