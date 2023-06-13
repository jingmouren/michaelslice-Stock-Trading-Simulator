#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>
#include<string>

wxIMPLEMENT_APP(App);

// Code to Open the Window
bool App::OnInit() 
{
	MainFrame* mainFrame = new MainFrame("Stock Trading Simulator");
	mainFrame->SetClientSize(900, 450);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}
