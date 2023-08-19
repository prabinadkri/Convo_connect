#ifndef CONTACTLISTPANEL_H
#define CONTACTLISTPANEL_H

#include <wx/wx.h>
#include <vector>

class ContactListPanel : public wxPanel
{
public:
    ContactListPanel(wxWindow *parent, wxWindowID id);

    // Method to add a contact to the list
    void AddContact(const wxString &contactName);

    wxListBox* GetContactListBox() { return contactListBox; } // Public accessor method
    void OnSearchBarEnter(wxCommandEvent &event);

private:
    wxListBox *contactListBox; // This is of type wxListBox
    wxTextCtrl *searchBar;
    std::vector<wxString> contacts; // Store contact names

    DECLARE_EVENT_TABLE()
};

#endif // CONTACTLISTPANEL_H
