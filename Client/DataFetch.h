#pragma once
#include <wx/wx.h>

std::string reciver;

struct Msg {
    std::string sen;
    std::string rec;
    std::string msg;
    std::string time;
};


class DataFetchThread : public wxThread {
public:
    DataFetchThread(ChatPanel* chatPanel)
        : wxThread(wxTHREAD_JOINABLE), chatPanel(chatPanel) {}

protected:
    virtual ExitCode Entry() {
        Msg a;
        std::vector<Msg> allmsg;
        while (!TestDestroy()) {
            // Fetch data from a source (replace this with actual data fetching)
            //wxString sender = "John";
            //wxString message = "Hello from background thread";
            client.Fetchmessage(sender.getUsername(), reciver);

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





            // Safely update the UI
            wxQueueEvent(chatPanel, new DataFetchEvent(allmsg));

            wxThread::Sleep(5000); // Fetch every 5 seconds
        }

        return (wxThread::ExitCode)0;
    }

private:
    ChatPanel* chatPanel;
};