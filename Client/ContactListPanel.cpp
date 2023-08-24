# pragma once
#include "ContactListPanel.h"
#include "client.h"
#include<thread>
#include <string>
#include <algorithm> 

ContactListPanel::ContactListPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id)
{

    searchBar = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    
    searchBar->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    contactListBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    contactListBox->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

  
    client.Fetchfriend(sender.getUsername());
    std::this_thread::sleep_for(std::chrono::seconds(1));
    while (!client.Incoming().empty())
    {
        auto msg = client.Incoming().pop_front().msg;
        
        switch (msg.header.id)
        {
        case CustomMsgTypes::Fetchfriend:
        {
            std::string a(msg.body.begin(), msg.body.end());
            AddContact(a);
        }break;
        }
    }

    //// Store the original contacts in the contacts collection
    ////AddContact(frn);
    //AddContact("Bob");
    //AddContact("Charlie");

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(searchBar, 0, wxEXPAND | wxALL, 5);
    sizer->Add(contactListBox, 1, wxEXPAND | wxALL, 5);
    SetSizerAndFit(sizer);

    searchBar->Bind(wxEVT_TEXT_ENTER, &ContactListPanel::OnSearchBarEnter, this);
}

void ContactListPanel::AddContact(const wxString &contactName)
{
    auto iter = std::find(contacts.begin(), contacts.end(), contactName);
    if (iter == contacts.end()) {
        contacts.push_back(contactName);

        contactListBox->Append(contactName);
    }
 
    
}

void ContactListPanel::OnSearchBarEnter(wxCommandEvent &event)
{
    
    wxString searchText = searchBar->GetValue();
   

    if (searchText == "") {

        contactListBox->Clear();
        int sz = contacts.size();
        for (int i = 0;i < sz;i++) {
            contactListBox->Append(contacts[i]);
        }

        return;
        
    }
    contactListBox->Clear();
    client.Finduser(searchText.ToStdString());

    std::this_thread::sleep_for(std::chrono::seconds(1));
    while (!client.Incoming().empty())
    {
        auto msg = client.Incoming().pop_front().msg;

        switch (msg.header.id)
        {
        case CustomMsgTypes::Finduser:
        {
            std::string a(msg.body.begin(), msg.body.end());
         
            AddContact(a);
        }break;
        }
    }
    contactListBox->Clear();


    for (const wxString &contact : contacts)
    {
        if (contact.Lower().Contains(searchText.Lower()))
        {

            contactListBox->Append(contact);
        }
    }
}




BEGIN_EVENT_TABLE(ContactListPanel, wxPanel)
    EVT_TEXT_ENTER(wxID_ANY, ContactListPanel::OnSearchBarEnter)
END_EVENT_TABLE()
