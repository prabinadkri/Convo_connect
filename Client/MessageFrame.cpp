#include "MessageFrame.h"
#include "ContactListPanel.h" 
#include "ProfileViewFrame.h"
#include "MainFrame.h"
MessageFrame::MessageFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), currentChatPanel(nullptr)
{
    SetupUI();
}

void MessageFrame::SetupUI()
{
    SetupMenuBar();
    

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


    wxListBox* listBox = contactListPanel->GetContactListBox(); 
    listBox->Bind(wxEVT_LISTBOX, &MessageFrame::OnContactListBoxSelection, this);}




void MessageFrame::CreateChatPanel(const wxString &contactName)
{
    ChatPanel *chatPanel = new ChatPanel(scrolledWindow, wxID_ANY);
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
        ChatPanel *existingChatPanel = iter->second;
        existingChatPanel->Show(); 
        existingChatPanel->GetParent()->Layout();
    } else {
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
    for (const auto &chatPair : chatPanelsMap)
    {
        ChatPanel *chatPanel = chatPair.second;
        chatPanel->Hide();
    }

    auto iter = chatPanelsMap.find(contactName);
    
    if (iter != chatPanelsMap.end())
    {
        ChatPanel *existingChatPanel = iter->second;
        existingChatPanel->Show();
    }
    else
    {
        CreateChatPanel(contactName);
    }

    scrolledWindow->Layout();
}

void MessageFrame::SetupMenuBar()
{
    menuBar = new wxMenuBar;

    wxMenu* profileMenu = new wxMenu;
    profileMenu->Append(ID_VIEW_PROFILE, "View Profile\tCtrl+P", "View your profile");

    menuBar->Append(profileMenu, "&Profile");

    wxMenu* logoutMenu = new wxMenu;
    logoutMenu->Append(ID_LOGOUT, "Logout\tCtrl+L", "Logout from the application");
    menuBar->Append(logoutMenu, "&Logout");
    Bind(wxEVT_MENU, &MessageFrame::OnLogoutMenuItem, this, ID_LOGOUT);

    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &MessageFrame::OnProfileMenuItem, this, ID_VIEW_PROFILE);
}

void MessageFrame::OnProfileMenuItem(wxCommandEvent& event)
{
    ProfileFrame* frame = new ProfileFrame("User Profile");
    frame->Show(true);
    frame->SetSize(800, 600);
   
}

void MessageFrame::OnLogoutMenuItem(wxCommandEvent& event)
{

    // Implement your logout logic here
    // For example, closing the current frame or opening a login window
    Close(); // Close the current frame
    MainFrame* main_Frame = new MainFrame("Convo+Connect");


    main_Frame->SetClientSize(800, 600);
    main_Frame->Center();
    main_Frame->Show();
}
