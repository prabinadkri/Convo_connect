# pragma once
#include "ContactListPanel.h"
#include "client.h"
#include<thread>
#include <string>


ContactListPanel::ContactListPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id)
{

    searchBar = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

    contactListBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

  
  
    //client.Fetchfriend("niru1");
    //
    //if (!client.Incoming().empty())
    //{
    //    auto msg = client.Incoming().pop_front().msg;
    //    std::string a(msg.sender.begin(), msg.sender.end());
    //    AddContact(a);
    //    //switch (msg.header.id)
    //    //{

    //    //}
    //}

    // Store the original contacts in the contacts collection
    //AddContact(frn);
    AddContact("Bob");
    AddContact("Charlie");

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(searchBar, 0, wxEXPAND | wxALL, 5);
    sizer->Add(contactListBox, 1, wxEXPAND | wxALL, 5);
    SetSizerAndFit(sizer);

    searchBar->Bind(wxEVT_TEXT_ENTER, &ContactListPanel::OnSearchBarEnter, this);
}

void ContactListPanel::AddContact(const wxString &contactName)
{
    contacts.push_back(contactName);

    contactListBox->Append(contactName);
}

void ContactListPanel::OnSearchBarEnter(wxCommandEvent &event)
{
    wxString searchText = searchBar->GetValue();

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