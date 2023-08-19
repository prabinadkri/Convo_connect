#ifndef MESSAGEBUBBLE_H
#define MESSAGEBUBBLE_H

#include <wx/wx.h>

class MessageBubble : public wxPanel
{
public:
    MessageBubble(wxWindow *parent, wxWindowID id, const wxString &sender, const wxString &message);

private:
    wxStaticText *senderLabel;
    wxStaticText *messageLabel;
    wxBoxSizer *sizer;
};

#endif // MESSAGEBUBBLE_H
