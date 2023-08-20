#pragma once
#include "ChatPanel.h"
#include "client.h"

std::string reciver;

struct Msg {
    std::string sen;
    std::string rec;
    std::string msg;
    std::string time;
};


//class DataFetchThread : public wxThread {
//public:
//    DataFetchThread(ChatPanel* chatPanel)
//        : wxThread(wxTHREAD_JOINABLE), chatPanel(chatPanel) {}
//
//protected:
//    virtual ExitCode Entry() {
//        Msg a;
//        std::vector<Msg> allmsg;
//        while (!TestDestroy()) {
//            // Fetch data from a source (replace this with actual data fetching)
//            //wxString sender = "John";
//            //wxString message = "Hello from background thread";
//            client.Fetchmessage(sender.getUsername(),reciver);
//
//            std::this_thread::sleep_for(std::chrono::seconds(1));
//            while (!client.Incoming().empty())
//            {
//                auto msg = client.Incoming().pop_front().msg;
//
//                switch (msg.header.id)
//                {
//                case CustomMsgTypes::Fetchmsg:
//                {
//                    std::string sendr(msg.sender.begin(), msg.sender.end());
//                	std::string rcvr(msg.reciever.begin(), msg.reciever.end());
//                    std::string mess(msg.body.begin(), msg.body.end());
//                    std::string ti(msg.time.begin(), msg.time.end());
//                    a.sen = sendr;
//                    a.rec = rcvr;
//                    a.msg = mess;
//                    a.time = ti;
//                    allmsg.push_back(a);
//                }break;
//                }
//            }
//
//
//
//
//
//            // Safely update the UI
//            wxQueueEvent(chatPanel, new DataFetchEvent(allmsg));
//
//            wxThread::Sleep(5000); // Fetch every 5 seconds
//        }
//
//        return (wxThread::ExitCode)0;
//    }
//
//private:
//    ChatPanel* chatPanel;
//};

//class DataFetchEvent : public wxThreadEvent {
//public:
//    DataFetchEvent(std::vector<Msg>msgs)
//        : wxThreadEvent(wxID_ANY),messages(msgs) {}
//
//    std::vector<Msg> Getmsgs() { return messages; }
//   
//private:
//    std::vector<Msg>messages;
//};
//
//


ChatPanel::ChatPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id)
{
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    messagesScrolledWindow = new wxScrolledWindow(this, wxID_ANY);
    messagesScrolledWindow->SetScrollRate(10, 10); // Adjust scroll rate as needed

    messageSizer = new wxBoxSizer(wxVERTICAL);

    mainSizer->Add(messagesScrolledWindow, 1, wxEXPAND);

    messagesScrolledWindow->SetSizer(messageSizer);

    messageInput = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    sendButton = new wxButton(this, wxID_ANY, "Send");

    mainSizer->Add(messageInput, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(sendButton, 0, wxALIGN_RIGHT | wxALL, 5);


   

    SetSizerAndFit(mainSizer);

    sendButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event) {
        wxString message = messageInput->GetValue();
        if (!message.IsEmpty()) {
            client.Sendmsg(sender.getUsername(), reciver, message.ToStdString());
            AddMessage("You", message);
            messageInput->Clear();
        }
    });

   /* dataFetchThread = new DataFetchThread(this);
    dataFetchThread->Create();
    dataFetchThread->Run();*/


}
//void ChatPanel::OnDataFetchEvent(DataFetchEvent& event) {
//    for (auto it = event.Getmsgs().begin();it != event.Getmsgs().end();it++)
//    {
//        AddMessage(it->sen,it->msg);
//
//    }
//
//}
void ChatPanel::AddMessage(const wxString &sender, const wxString &message)
{
    MessageBubble *messageBubble = new MessageBubble(messagesScrolledWindow, wxID_ANY, sender, message);
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
