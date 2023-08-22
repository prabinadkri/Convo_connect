#pragma once
#include "ChatPanel.h"
#include "client.h"
struct Msg {
    std::string sen;
    std::string rec;
    std::string msg;
    std::string time;
};

std::string reciver;
std::vector<Msg> allmsg;



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
                auto msg = client.Incoming().pop_front().msg;

                switch (msg.header.id)
                {
                case CustomMsgTypes::Fetchmsg:
                {
                   
                    std::string sendr(msg.sender.begin(), msg.sender.end());
                    std::string rcvr(msg.reciever.begin(), msg.reciever.end());
                    std::string mess(msg.body.begin(), msg.body.end());
                    std::string ti(msg.time.begin(), msg.time.end());
                    if (rcvr == sender.getUsername())
                    {
                        a.sen = sendr;
                        a.rec = rcvr;
                        a.msg = mess;
                        a.time = ti;
                        allmsg.push_back(a);
                    }
                    
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






ChatPanel::ChatPanel(wxWindow* parent, wxWindowID id)
    : wxPanel(parent, id)
{
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    messagesScrolledWindow = new wxScrolledWindow(this, wxID_ANY);
    messagesScrolledWindow->SetScrollRate(10, 10); // Adjust scroll rate as needed

    messageSizer = new wxBoxSizer(wxVERTICAL);

    mainSizer->Add(messagesScrolledWindow, 1, wxEXPAND);

    messagesScrolledWindow->SetSizer(messageSizer);

    messageInput = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    sendButton = new wxButton(this, wxID_ANY, "Send");

    mainSizer->Add(messageInput, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(sendButton, 0, wxALIGN_RIGHT | wxALL, 5);


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

}
void ChatPanel::AddMessage(const wxString& sender, const wxString& message)
{
    MessageBubble* messageBubble = new MessageBubble(messagesScrolledWindow, wxID_ANY, sender, message);
    messageSizer->Add(messageBubble, 0, wxEXPAND | wxALL, 5);
    messageSizer->Layout();

    // Scroll to the bottom to show the latest message
    int scrollY = messagesScrolledWindow->GetVirtualSize().y - messagesScrolledWindow->GetSize().y;
    if (scrollY > 0) {
        messagesScrolledWindow->Scroll(0, scrollY);
    }
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
