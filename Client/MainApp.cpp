
#include "MainApp.h"
#include"MainFrame.h"
#include<wx/wx.h>
#include"./client.h"
wxIMPLEMENT_APP(MainApp);
CustomClient client;
bool MainApp::OnInit() {
	client.Connect("192.168.209.57", 60000);
	MainFrame* mainFrame = new MainFrame("Convo+Connect");
	

	mainFrame->SetClientSize(800, 600);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}