#include "cApp.h"
#include "Main.h"
#include <iostream>

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{
}

cApp::~cApp()
{
}


bool cApp::OnInit()
{
	m_frame = new Main();
	m_frame->Show();
	return true;
}
