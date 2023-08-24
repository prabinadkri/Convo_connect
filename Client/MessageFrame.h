#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <unordered_map>
#include <wx/wx.h>
#include "ChatPanel.h"
#include "ContactListPanel.h"
//#include "MainFrame.h"
class RoundedPhotoPanel;
class MessageFrame : public wxFrame
{
public:
    MessageFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    void OnSize(wxSizeEvent& event) {
        if (GetSize().GetWidth() < 400 || GetSize().GetHeight() < 400) {
            SetSize(wxSize(400, 400));
        }
        event.Skip();
    }
    void OnLogoutButtonClicked(wxCommandEvent& evt);
private:
    wxPanel* profilePanel;
    wxPanel* bottomPanel;
    wxBoxSizer* contactAndChatSizer;
    wxPanel *scrolledWindow;
    ContactListPanel *contactListPanel;
    wxBoxSizer *chatPanelsSizer; 
    wxPanel* navBar;
    std::unordered_map<wxString, ChatPanel *> chatPanelsMap; // Use std::unordered_map
    ChatPanel *currentChatPanel; // Add this member variable
    RoundedPhotoPanel* profilePhotoPanel;

    // Method to update the profile photo
    void UpdateProfilePhoto(const wxString& photoPath, wxString title = "Profile Name");
    void SetupUI();
    void CreateChatPanel(const wxString &contactName);
    void OnContactSelected(const wxString &contactName);
    void OnContactListBoxSelection(wxCommandEvent &event);
    void OpenChatPanel(const wxString &contactName);

     
};



#endif // MessageFrame

#pragma once
#
class RoundedPhotoPanel : public wxPanel
{
public:
    RoundedPhotoPanel(wxWindow* parent, const wxString& photoPath, wxString title)
        : wxPanel(parent, wxID_ANY)
    {
        wxBoxSizer* profileSizer = new wxBoxSizer(wxHORIZONTAL);


        bool logo = false;
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxBitmap photoBitmap(photoPath, wxBITMAP_TYPE_ANY);
        if (!photoBitmap.IsOk())
        {
            // Handle if photo couldn't be loaded
            return;
        }

        wxImage photoImage = photoBitmap.ConvertToImage();
        if (photoPath == "C:\\Users\\acer\\Desktop\\TS\\C++\\Convo_connect - Copy\\Assets\\Logo.png" ) {
            photoImage.Rescale(85, 60, wxIMAGE_QUALITY_HIGH);
            logo = true;
        }
        else {

            photoImage.Rescale(220, 220, wxIMAGE_QUALITY_HIGH);
        }
   
        wxBitmap roundedPhoto(photoImage);
        roundedPhoto = CreateRoundedBitmap(roundedPhoto);

        wxStaticBitmap* photoStaticBitmap = new wxStaticBitmap(this, wxID_ANY, roundedPhoto);
        sizer->Add(photoStaticBitmap, 0, wxALL, 10);
        if (!logo) {
            wxTextCtrl* titlename = new wxTextCtrl(this, wxID_ANY, title);
            sizer->Add(titlename);
            profileSizer->AddStretchSpacer(); // Add a flexible space to the left
            profileSizer->Add(sizer, 0, wxALIGN_CENTER); // Centered photo panel
            profileSizer->AddStretchSpacer(); // Add a flexible space to the right
            SetSizerAndFit(profileSizer);
        }
        else {
            SetSizerAndFit(sizer);
        }
    }

private:
    wxBitmap CreateRoundedBitmap(const wxBitmap& source)
    {
        wxImage img = source.ConvertToImage();
        wxBitmap bmp(img.GetWidth(), img.GetHeight());
        wxMemoryDC mdc(bmp);

        mdc.SetBrush(wxBrush(wxColour(255, 255, 255)));
        mdc.Clear();
        mdc.SetPen(*wxTRANSPARENT_PEN);
        mdc.DrawRoundedRectangle(0, 0, img.GetWidth(), img.GetHeight(), 50);

        wxBitmap scaledBitmap = wxBitmap(img.Scale(img.GetWidth(), img.GetHeight()));
        mdc.DrawBitmap(scaledBitmap, 0, 0, true);

        return bmp;
    }
};

// Usage

