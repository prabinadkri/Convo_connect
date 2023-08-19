#ifndef USERPROFILEDIALOG_H
#define USERPROFILEDIALOG_H

#include <wx/wx.h>

class UserProfileDialog : public wxDialog
{
public:
    UserProfileDialog(wxWindow *parent, wxWindowID id);

private:
    wxTextCtrl *usernameInput;
    wxTextCtrl *statusInput;
    wxButton *saveButton;
    wxButton *cancelButton;
};

#endif // USERPROFILEDIALOG_H
