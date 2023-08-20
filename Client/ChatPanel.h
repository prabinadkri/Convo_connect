#ifndef CHATPANEL_H
#define CHATPANEL_H

#include <wx/wx.h>
#include "MessageBubble.h"
#include <wx/scrolwin.h>
#include <wx/thread.h>
class DataFetchThread;
class DataFetchEvent;
wxDECLARE_EVENT(DATA_FETCH_EVENT, wxThreadEvent);
class ChatPanel : public wxPanel
{
public:
    ChatPanel(wxWindow *parent, wxWindowID id);
    
    // Method to add a new message to the chat
    void AddMessage(const wxString &sender, const wxString &message);
    void OnDataFetchEvent(wxThreadEvent& event);
    // void OnCloseButtonClicked(wxCommandEvent &event);
private:
    wxTextCtrl *messageInput;
    wxButton *sendButton;
    wxScrolledWindow *messagesScrolledWindow; // Add a wxScrolledWindow
    // wxButton *closeButton;
    wxBoxSizer *messageSizer;
    DataFetchThread* dataFetchThread;
protected:
    //wxDECLARE_EVENT_TABLE();
};

#endif // CHATPANEL_H
