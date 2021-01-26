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
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	m_frame = new Main();
	m_frame->Show();
	return true;
}
