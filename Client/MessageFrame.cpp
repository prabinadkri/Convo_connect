#include "MessageFrame.h"
#include "ContactListPanel.h" 
#include "./client.h"
#include "MainFrame.h"


wxString usernamePath = "default";
MessageFrame::MessageFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), currentChatPanel(nullptr)
{
    SetupUI();
}

void MessageFrame::SetupUI()
{
    scrolledWindow = new wxPanel(this, wxID_ANY);

    // Create the main sizer for the frame
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL); // Change to VERTICAL

    // Create the navigation bar
    navBar = new wxPanel(scrolledWindow, wxID_ANY, wxDefaultPosition, wxSize(-1, 80), wxBORDER_NONE);
    navBar->SetBackgroundColour(wxColour(0, 190, 242));

    wxBoxSizer* navBarSizer = new wxBoxSizer(wxHORIZONTAL);
    wxPanel* logoPanel = new RoundedPhotoPanel(navBar, "C:\\Users\\acer\\Desktop\\TS\\C++\\Convo_connect - Copy\\Assets\\Logo.png", usernamePath
    );
    navBarSizer->Add(logoPanel, 0, wxALIGN_CENTER_VERTICAL);
    // Add title text
    wxStaticText* titleText = new wxStaticText(navBar, wxID_ANY, "WHERE YOU CAN CONNECT ", wxDefaultPosition, wxDefaultSize, 0); // Remove wxALIGN_CENTER
    titleText->SetForegroundColour(wxColour(255, 255, 255));
    navBarSizer->Add(titleText, 1, wxALIGN_CENTER_VERTICAL); // Set proportion to 1
   
    // Create buttons with color and hovering effect
    wxButton* homeButton = new wxButton(navBar, wxID_ANY, "Log out", wxDefaultPosition, wxDefaultSize, wxBORDER_NONE | wxBU_EXACTFIT);
    homeButton->SetForegroundColour(wxColour(255, 255, 255));
    homeButton->SetBackgroundColour(wxColour(66, 0, 145));
    homeButton->Bind(wxEVT_ENTER_WINDOW, [homeButton](wxMouseEvent& event) {
        homeButton->SetBackgroundColour(wxColour(0, 0, 200));
        homeButton->Refresh();
        });
    homeButton->Bind(wxEVT_LEAVE_WINDOW, [homeButton](wxMouseEvent& event) {
        homeButton->SetBackgroundColour(wxColour(0, 0, 255));
        homeButton->Refresh();
        });
    navBarSizer->Add(homeButton, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 20);

    navBar->SetSizer(navBarSizer);
    homeButton->Bind(wxEVT_BUTTON, &MessageFrame::OnLogoutButtonClicked, this);
   
    mainSizer->Add(navBar, 0, wxEXPAND); // Set proportion to 0 to avoid taking extra space
    bottomPanel = new wxPanel(scrolledWindow);
    //wxPanel* profilePanel = new wxPanel(bottomPanel);

    profilePhotoPanel = new RoundedPhotoPanel(bottomPanel, "C:\\Users\\acer\\Desktop\\TS\\C++\\Convo_connect - Copy\\Assets\\default.png",usernamePath);
    

    //RoundedPhotoPanel* profilePanel = new RoundedPhotoPanel(bottomPanel, "C:\\Users\\acer\\Desktop\\TS\\C++\\Convo_connect - Copy\\Assets\\"+ usernamePath+".png");
    // Create a horizontal sizer for contact list and chat panel
    contactAndChatSizer = new wxBoxSizer(wxHORIZONTAL);

    // Create the contact list panel
    contactListPanel = new ContactListPanel(bottomPanel, wxID_ANY);
    contactListPanel->SetBackgroundColour(wxColor(238, 245, 252));
    contactAndChatSizer->Add(contactListPanel, 20, wxEXPAND| wxALL, 5);

    // Create the chat panels sizer
    chatPanelsSizer = new wxBoxSizer(wxVERTICAL);
    contactAndChatSizer->Add(chatPanelsSizer, 60, wxEXPAND | wxALL, 5);
    contactAndChatSizer->Add(profilePhotoPanel, 20, wxEXPAND|wxALL, 5);
    bottomPanel->SetSizer(contactAndChatSizer);

    // Add the contact and chat sizer to the main sizer
    mainSizer->Add(bottomPanel, 1, wxEXPAND);

    // Set the main sizer for the scrolled window
    scrolledWindow->SetSizer(mainSizer);

    // Create the outer sizer for the frame
    wxBoxSizer* outerSizer = new wxBoxSizer(wxHORIZONTAL);
    outerSizer->Add(scrolledWindow, 1, wxEXPAND);

    // Set the outer sizer for the frame
    SetSizerAndFit(outerSizer);



    // Bind events for list box selection
    wxListBox* listBox = contactListPanel->GetContactListBox();
    listBox->Bind(wxEVT_LISTBOX, &MessageFrame::OnContactListBoxSelection, this);
    
}

void MessageFrame::CreateChatPanel(const wxString &contactName)
{
    ChatPanel *chatPanel = new ChatPanel(bottomPanel, wxID_ANY , contactName);
    chatPanel->SetBackgroundColour(wxColor(254, 255, 254));
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
    usernamePath = contactName;
    //profilePanel = new RoundedPhotoPanel(bottomPanel, "C:\\Users\\acer\\Desktop\\TS\\C++\\Convo_connect - Copy\\Assets\\" + usernamePath + ".png");
    auto iter = chatPanelsMap.find(contactName);
    reciver = contactName.ToStdString();
    UpdateProfilePhoto("C:\\Users\\acer\\Desktop\\TS\\C++\\Convo_connect - Copy\\Assets\\" + contactName + ".png",contactName);

    //if (iter != chatPanelsMap.end()) {
    //    // Chat panel already exists, show it
    //    ChatPanel *existingChatPanel = iter->second;
    //    existingChatPanel->Show(); // Show the existing chat panel
    //    existingChatPanel->GetParent()->Layout(); // Update parent layout
    //} else {
        // Chat panel doesn't exist, create and show it
        CreateChatPanel(contactName);
  /*  }*/
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
        chatPanel->Close();
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

void MessageFrame::UpdateProfilePhoto(const wxString& photoPath,wxString title)
{
    if (profilePhotoPanel)
    {
        // Remove the old panel
        contactAndChatSizer->Detach(profilePhotoPanel);
        profilePhotoPanel->Destroy();

        // Create and add the new panel
        profilePhotoPanel = new RoundedPhotoPanel(bottomPanel, photoPath, title);
        contactAndChatSizer->Add(profilePhotoPanel, 20, wxEXPAND | wxALL, 5);
        bottomPanel->Layout();
    }
}



void MessageFrame::OnLogoutButtonClicked(wxCommandEvent& evt) {
    Close();
    MainFrame* mainfr = new MainFrame("Convo-Connect");
    mainfr->SetClientSize(800, 600);
    mainfr->Center();
    mainfr->Show();

}