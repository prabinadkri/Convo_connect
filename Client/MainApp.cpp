
#include "MainApp.h"
#include"MainFrame.h"
#include<wx/wx.h>

wxIMPLEMENT_APP(MainApp);

bool MainApp::OnInit() {
	MainFrame* mainFrame = new MainFrame("Convo+Connect");
	mainFrame->SetClientSize(800, 600);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}