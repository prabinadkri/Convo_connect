#ifndef CHATPANEL_H
#define CHATPANEL_H

#include <wx/wx.h>
#include "MessageBubble.h"
#include <wx/scrolwin.h>
class ChatPanel : public wxPanel
{
public:
    ChatPanel(wxWindow *parent, wxWindowID id);

    // Method to add a new message to the chat
    void AddMessage(const wxString &sender, const wxString &message);
    // void OnCloseButtonClicked(wxCommandEvent &event);
private:
    wxTextCtrl *messageInput;
    wxButton *sendButton;
    wxScrolledWindow *messagesScrolledWindow; // Add a wxScrolledWindow
    // wxButton *closeButton;
    wxBoxSizer *messageSizer;
};

#endif // CHATPANEL_H
