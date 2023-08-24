#include "MessageBubble.h"

MessageBubble::MessageBubble(wxWindow* parent, wxWindowID id, const wxString& sender, const wxString& message)
    : wxPanel(parent, id)
{
    this->SetBackgroundColour(wxColor(135, 206, 235));
    wxBoxSizer* containerSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* messageText = new wxStaticText(this, wxID_ANY, message);
    messageText->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    messageText->SetForegroundColour(wxColour(255,255 ,255)); // White text color
    containerSizer->Add(messageText, 1, wxEXPAND |wxALL, 6);
    
    SetSizer(containerSizer);
}
