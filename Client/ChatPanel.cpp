#pragma once
#include "ChatPanel.h"
#include "client.h"
std::string reciver;
ChatPanel::ChatPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id)
{
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    messagesScrolledWindow = new wxScrolledWindow(this, wxID_ANY);
    messagesScrolledWindow->SetScrollRate(10, 10); // Adjust scroll rate as needed

    messageSizer = new wxBoxSizer(wxVERTICAL);

    mainSizer->Add(messagesScrolledWindow, 1, wxEXPAND);

    messagesScrolledWindow->SetSizer(messageSizer);

    messageInput = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    sendButton = new wxButton(this, wxID_ANY, "Send");

    mainSizer->Add(messageInput, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(sendButton, 0, wxALIGN_RIGHT | wxALL, 5);


    SetSizerAndFit(mainSizer);

    sendButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event) {
        wxString message = messageInput->GetValue();
        if (!message.IsEmpty()) {
            client.Sendmsg("abcd", reciver, message.ToStdString());
            AddMessage("You", message);
            messageInput->Clear();
        }
    });
}

void ChatPanel::AddMessage(const wxString &sender, const wxString &message)
{
    MessageBubble *messageBubble = new MessageBubble(messagesScrolledWindow, wxID_ANY, sender, message);
    messageSizer->Add(messageBubble, 0, wxEXPAND | wxALL, 5);
    messageSizer->Layout();

    // Scroll to the bottom to show the latest message
    int scrollY = messagesScrolledWindow->GetVirtualSize().y - messagesScrolledWindow->GetSize().y;
    if (scrollY > 0) {
        messagesScrolledWindow->Scroll(0, scrollY);
    }
}

// void ChatPanel::OnCloseButtonClicked(wxCommandEvent &event)
// {
//     // Get the parent sizer
//     wxSizer *parentSizer = GetParent()->GetSizer();

//     // Remove this chat panel from the sizer
//     parentSizer->Detach(this);

//     // Destroy this chat panel
//     Destroy();
// }
