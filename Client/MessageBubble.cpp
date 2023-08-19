#pragma once 

#include "MessageBubble.h"

MessageBubble::MessageBubble(wxWindow *parent, wxWindowID id, const wxString &sender, const wxString &message)
    : wxPanel(parent, id)
{
    sizer = new wxBoxSizer(wxVERTICAL);

    senderLabel = new wxStaticText(this, wxID_ANY, sender);
    messageLabel = new wxStaticText(this, wxID_ANY, message);

    sizer->Add(senderLabel, 0, wxALL, 5);
    sizer->Add(messageLabel, 0, wxALL, 5);

    SetSizerAndFit(sizer);
}
