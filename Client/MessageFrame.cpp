#pragma once 

#include "MessageFrame.h"
#include "ContactListPanel.h" 

MessageFrame::MessageFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), currentChatPanel(nullptr)
{
    SetupUI();
}

void MessageFrame::SetupUI()
{
    
    scrolledWindow = new wxScrolledWindow(this, wxID_ANY);
    scrolledWindow->SetScrollRate(0, 10);

    wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);

    contactListPanel = new ContactListPanel(scrolledWindow, wxID_ANY);
    mainSizer->Add(contactListPanel, 0, wxEXPAND | wxALL, 5);

    chatPanelsSizer = new wxBoxSizer(wxVERTICAL); 
    mainSizer->Add(chatPanelsSizer, 1, wxEXPAND | wxALL, 5);

    scrolledWindow->SetSizer(mainSizer);

    wxBoxSizer *outerSizer = new wxBoxSizer(wxHORIZONTAL);
    outerSizer->Add(scrolledWindow, 1, wxEXPAND);
    SetSizerAndFit(outerSizer);


    wxListBox* listBox = contactListPanel->GetContactListBox(); // Access the list box through the accessor
    listBox->Bind(wxEVT_LISTBOX, &MessageFrame::OnContactListBoxSelection, this);}




void MessageFrame::CreateChatPanel(const wxString &contactName)
{
    ChatPanel *chatPanel = new ChatPanel(scrolledWindow, wxID_ANY);
    chatPanel->GetClientfunc(clientdup);
    chatPanelsMap[contactName] = chatPanel;
    chatPanelsSizer->Add(chatPanel, 1, wxEXPAND | wxALL, 5);
    scrolledWindow->Layout();
}

void MessageFrame::OnContactSelected(const wxString &contactName)
{
    // Hide all other chat panels
    for (const auto &chatPair : chatPanelsMap)
    {
        ChatPanel *chatPanel = chatPair.second;
        chatPanel->Hide();
    }

    auto iter = chatPanelsMap.find(contactName);
    
    if (iter != chatPanelsMap.end()) {
        // Chat panel already exists, show it
        ChatPanel *existingChatPanel = iter->second;
        existingChatPanel->Show(); // Show the existing chat panel
        existingChatPanel->GetParent()->Layout(); // Update parent layout
    } else {
        // Chat panel doesn't exist, create and show it
        CreateChatPanel(contactName);
    }
}




void MessageFrame::OnContactListBoxSelection(wxCommandEvent &event)
{
    wxListBox *contactListBox = dynamic_cast<wxListBox*>(event.GetEventObject());
    if (contactListBox) {
        int selectedIndex = contactListBox->GetSelection();
        if (selectedIndex != wxNOT_FOUND) {
            wxString selectedContactName = contactListBox->GetString(selectedIndex);
            OnContactSelected(selectedContactName);
        }
    }
}


void MessageFrame::OpenChatPanel(const wxString &contactName)
{
    // Hide all other chat panels
    for (const auto &chatPair : chatPanelsMap)
    {
        ChatPanel *chatPanel = chatPair.second;
        chatPanel->Hide();
    }

    auto iter = chatPanelsMap.find(contactName);
    
    if (iter != chatPanelsMap.end())
    {
        // Chat panel already exists, show it
        ChatPanel *existingChatPanel = iter->second;
        existingChatPanel->Show(); // Show the existing chat panel
    }
    else
    {
        // Chat panel doesn't exist, create and show it
        CreateChatPanel(contactName);
    }

    scrolledWindow->Layout(); // Update layout
}
