#pragma once
#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/listctrl.h>
#include "./NieRHook/Source/ConsoleApplication1/NierHook.hpp"

class Main : public wxFrame, public wxThreadHelper
{
public:
	Main();
	~Main();
public:
	NieRHook* hook = nullptr;

	//UI Thread Timer
	wxTimer* m_Timer = nullptr;

	//HOOK STATUS
	wxStaticText* m_hooked = nullptr;
	wxStaticText* m_status = nullptr;
	wxStaticText* m_version = nullptr;
	wxStaticText* m_github = nullptr;

	//Tabs
	wxNotebook* notebook = nullptr;
	wxPanel* Player = nullptr;
	wxPanel* Inventory = nullptr;
	wxPanel* Weapons = nullptr;
	wxPanel* Misc = nullptr;

protected:
	void updateComponents(void);
	void startTimer(void);
	void stopTimer(void);
	void OnTimer(wxTimerEvent&);
	virtual wxThread::ExitCode Entry();
	void OnThreadUpdate(wxThreadEvent& evt);
	void OnClose(wxCloseEvent& evt);
	void StartHook(void);
	wxDECLARE_EVENT_TABLE();
};

