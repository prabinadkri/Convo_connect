#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <unordered_map>
#include <wx/wx.h>
#include "ChatPanel.h"
#include "ContactListPanel.h"

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
private:
    wxScrolledWindow *scrolledWindow;
    ContactListPanel *contactListPanel;
    wxBoxSizer *chatPanelsSizer; 

    std::unordered_map<wxString, ChatPanel *> chatPanelsMap; // Use std::unordered_map
    ChatPanel *currentChatPanel; // Add this member variable

    void SetupUI();
    void CreateChatPanel(const wxString &contactName);
    void OnContactSelected(const wxString &contactName);
    void OnContactListBoxSelection(wxCommandEvent &event);
    void OpenChatPanel(const wxString &contactName);

     
};



#endif // MessageFrame
