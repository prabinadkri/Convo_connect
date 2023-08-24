#pragma once
#include "ChatPanel.h"
#include "client.h"
#include "ContactListPanel.h"
struct Msg {
    std::string sen;
    std::string rec;
    std::string msg;
    std::string time;
};

std::string reciver;
std::vector<Msg> allmsg;

class TimePicker : public wxPanel {
public:
    TimePicker(wxWindow* parent, wxWindowID id = wxID_ANY)
        : wxPanel(parent, id) {
        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

        // Initialize the time picker with the current system time
        wxDateTime currentTime = wxDateTime::Now();
        int hour = currentTime.GetHour();
        int minute = currentTime.GetMinute();
        bool isPM = hour >= 12;
        hour = hour % 12;
        if (hour == 0) hour = 12;

        hourComboBox = new wxComboBox(this, wxID_ANY, "9",
            wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
        for (int h = 1; h <= 12; ++h) {
            hourComboBox->Append(wxString::Format("%02d", h));
        }

        minuteComboBox = new wxComboBox(this, wxID_ANY, wxString::Format("%02d", minute),
            wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
        for (int m = 0; m <= 59; ++m) {
            minuteComboBox->Append(wxString::Format("%02d", m));
        }

        amPmComboBox = new wxComboBox(this, wxID_ANY, isPM ? "PM" : "AM",
            wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
        amPmComboBox->Append("AM");
        amPmComboBox->Append("PM");

        sizer->Add(hourComboBox, 0, wxALL, 5);
        sizer->Add(minuteComboBox, 0, wxALL, 5);
        sizer->Add(amPmComboBox, 0, wxALL, 5);

        SetSizer(sizer);
    }

    wxDateTime GetSelectedTime() const {
        int hour = wxAtoi(hourComboBox->GetValue());
        int minute = wxAtoi(minuteComboBox->GetValue());
        if (amPmComboBox->GetValue() == "PM" && hour < 12) {
            hour += 12;
        }
        else if (amPmComboBox->GetValue() == "AM" && hour == 12) {
            hour = 0;
        }

        wxDateTime time;
        time.SetHour(hour);
        time.SetMinute(minute);
        time.SetSecond(0);
        return time;
    }

private:
    wxComboBox* hourComboBox;
    wxComboBox* minuteComboBox;
    wxComboBox* amPmComboBox;
};

class DataFetchThread : public wxThread {
public:
    DataFetchThread(ChatPanel* chatPanel)
        : wxThread(wxTHREAD_JOINABLE), chatPanel(chatPanel) {}

protected:
    virtual ExitCode Entry() {
        Msg a;


        while (!TestDestroy()) {
            // Fetch data from a source (replace this with actual data fetching)
            //wxString sender = "John";
            //wxString message = "Hello from background thread";
            //client.Fetchmessage(sender.getUsername(), reciver);
            allmsg.clear();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            while (!client.Incoming().empty())
            {
                auto msg = client.Incoming().front().msg;

                switch (msg.header.id)
                {
                case CustomMsgTypes::Fetchmsg:
                {

                    std::string sendr(msg.sender.begin(), msg.sender.end());
                    std::string rcvr(msg.reciever.begin(), msg.reciever.end());
                    std::string mess(msg.body.begin(), msg.body.end());
                    std::string ti(msg.time.begin(), msg.time.end());

                    a.sen = sendr;
                    a.rec = rcvr;
                    a.msg = mess;
                    a.time = ti;
                    allmsg.push_back(a);
                    client.Incoming().pop_front().msg;

                }break;
                case CustomMsgTypes::RealFetch:
                {

                    std::string sendr(msg.sender.begin(), msg.sender.end());
                    std::string rcvr(msg.reciever.begin(), msg.reciever.end());
                    std::string mess(msg.body.begin(), msg.body.end());
                    std::string ti(msg.time.begin(), msg.time.end());
                    if (rcvr == sender.getUsername() && sendr == reciver)
                    {
                        a.sen = sendr;
                        a.rec = rcvr;
                        a.msg = mess;
                        a.time = ti;
                        allmsg.push_back(a);
                    }
                    client.Incoming().pop_front().msg;
                }break;
               
                }
            }





            // Safely update the UI
            if (allmsg.empty())
            {
                continue;
            }
            wxQueueEvent(chatPanel, new wxThreadEvent(DATA_FETCH_EVENT));

            wxThread::Sleep(1000); // Fetch every 1 seconds
        }

        return (wxThread::ExitCode)0;
    }

private:
    ChatPanel* chatPanel;
};






ChatPanel::ChatPanel(wxWindow* parent, wxWindowID id, wxString other)
    : wxPanel(parent, id) , away(other)
{

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    messagesScrolledWindow = new wxScrolledWindow(this, wxID_ANY);
    messagesScrolledWindow->SetScrollRate(0, 10); // Adjust scroll rate as needed

    messageSizer = new wxBoxSizer(wxVERTICAL);

    mainSizer->Add(messagesScrolledWindow, 1, wxEXPAND);

    messagesScrolledWindow->SetSizer(messageSizer);
    wxPanel* inputPanel = new wxPanel(this);
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

    messageInput = new wxTextCtrl(inputPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(650, 20), wxTE_MULTILINE);
    messageInput->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    

    sendButton = new wxButton(inputPanel, wxID_ANY, "Send");
    sendButton->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    TimePicker* timePicker = new TimePicker(inputPanel);

    inputSizer->Add(messageInput, 1, wxEXPAND | wxTOP, 25);

    inputSizer->Add(sendButton, 0,  wxTOP, 30);
    inputSizer->Add(timePicker, 0, wxTOP, 30);
    inputPanel->SetSizer(inputSizer);
    mainSizer->Add(inputPanel);
    SetSizer(mainSizer);

    Msg a;
    client.Fetchmessage(sender.getUsername(), reciver);
    allmsg.clear();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    while (!client.Incoming().empty())
    {
        auto msg = client.Incoming().pop_front().msg;

        switch (msg.header.id)
        {
        case CustomMsgTypes::Fetchmsg:
        {
            std::string sendr(msg.sender.begin(), msg.sender.end());
            std::string rcvr(msg.reciever.begin(), msg.reciever.end());
            std::string mess(msg.body.begin(), msg.body.end());
            std::string ti(msg.time.begin(), msg.time.end());
            a.sen = sendr;
            a.rec = rcvr;
            a.msg = mess;
            a.time = ti;
            allmsg.push_back(a);
        }break;
        }
    }


    for (const Msg& msg : allmsg)
    {
        AddMessage(msg.sen, msg.msg);

    }


    SetSizerAndFit(mainSizer);

    sendButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        wxString message = messageInput->GetValue();
        if (!message.IsEmpty()) {
            client.Sendmsg(sender.getUsername(), reciver, message.ToStdString());
            AddMessage(sender.getUsername(), message);
            messageInput->Clear();
            messageSizer->Layout();
            // Scroll to the bottom to show the latest message
            int scrollPos = messagesScrolledWindow->GetScrollRange(wxVERTICAL);
            messagesScrolledWindow->Scroll(0, scrollPos);

            // Trigger layout update
            messageSizer->Layout();
        }
        });
    Bind(DATA_FETCH_EVENT, &ChatPanel::OnDataFetchEvent, this);
    dataFetchThread = new DataFetchThread(this);
    dataFetchThread->Create();
    dataFetchThread->Run();


}
//wxBEGIN_EVENT_TABLE(ChatPanel, wxPanel)
//    EVT_COMMAND(wxID_ANY, DATA_FETCH_EVENT, ChatPanel::OnDataFetchEvent)
//wxEND_EVENT_TABLE()

wxDEFINE_EVENT(DATA_FETCH_EVENT, wxThreadEvent);
void ChatPanel::OnDataFetchEvent(wxThreadEvent& event) {
    /* std::vector<Msg> allmsg = event.GetPayload<std::vector<Msg>>();*/

    for (const Msg& msg : allmsg)
    {
        AddMessage(msg.sen, msg.msg);

    }
    messageSizer->Layout();
    // Scroll to the bottom to show the latest message
    int scrollPos = messagesScrolledWindow->GetScrollRange(wxVERTICAL);
    messagesScrolledWindow->Scroll(0, scrollPos);
    
    // Trigger layout update
    messageSizer->Layout();

}
void ChatPanel::AddMessage(const wxString& sender, const wxString& message)
{
  
    MessageBubble* messageBubble = new MessageBubble(messagesScrolledWindow, wxID_ANY, sender, message);
    if (sender == away) {
        messageSizer->Add(messageBubble, 0, wxALIGN_LEFT | wxALL, 5);
        messageBubble->SetBackgroundColour(wxColor(203, 205, 203));

    }
    else {
        messageBubble->SetBackgroundColour(wxColor(0, 106, 255));

        messageSizer->Add(messageBubble, 0, wxALIGN_RIGHT | wxALL, 5);
    }
    messageSizer->Layout();

    // Get the scroll range
    int scrollPos = messagesScrolledWindow->GetScrollRange(wxVERTICAL);

    // Scroll to the bottom to show the latest message
    messagesScrolledWindow->Scroll(0, scrollPos);

    // Refresh the scrolled window to ensure the new message is immediately visible
    messagesScrolledWindow->Refresh();
}

// void ChatPanel::OnCloseButtonClicked(wxCommandEvent &event)
// {
//     // Get the parent sizer
//     wxSizer *parentSizer = GetParent()->GetSizer();

//     // Remove this chat panel from the sizer
//     parentSizer->Detach(this);

//     // Destroy this chat panel
//     Destroy();
// }