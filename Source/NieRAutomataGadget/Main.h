#pragma once
#include "wx/wx.h"
#include "wx/notebook.h"
#include "NierHook.hpp"

class Main : public wxFrame, public wxThreadHelper
{
private:
	float StoredX = 0.000000;
	float StoredY = 0.000000;
	float StoredZ = 0.000000;
	void setStoredPosition(float X, float Y, float Z);
	void toggleComponents(bool enabled);

public:
	Main();
	~Main();
public:
	NieRHook* hook;
	//UI Thread Timer
	wxTimer* m_Timer = nullptr;

	//HOOK STATUS
	wxStaticText* m_hooked = nullptr;
	wxStaticText* m_status = nullptr;
	wxStaticText* m_version = nullptr;

	//Tabs
	wxNotebook* notebook = nullptr;

	//STATS
	wxStaticBox* m_StatsBox = nullptr;
	wxStaticText* m_Health = nullptr;
	wxStaticText* m_Level = nullptr;
	wxStaticText* m_Funds = nullptr;
	wxStaticText* m_EXP = nullptr;

	//CHEATS
	wxStaticBox* m_CheatsBox = nullptr;
	wxCheckBox* m_NoClip = nullptr;
	wxCheckBox* m_SpeedHack = nullptr;
	wxCheckBox* m_InfDoubleJump = nullptr;
	wxCheckBox* m_NoCooldown = nullptr;
	wxCheckBox* m_InfAirDash = nullptr;
	wxCheckBox* m_IgnoreUpgradeMaterials = nullptr;

	//POSITION
	wxStaticBox* m_PositionBox = nullptr;
	wxStaticText* m_XText = nullptr;
	wxStaticText* m_YText = nullptr;
	wxStaticText* m_ZText = nullptr;
	wxStaticText* m_StoredPosText = nullptr;
	wxStaticText* m_CurrentPosText = nullptr;
	wxTextCtrl* m_XposTextCtrl = nullptr;
	wxTextCtrl* m_YposTextCtrl = nullptr;
	wxTextCtrl* m_ZposTextCtrl = nullptr;
	wxTextCtrl* m_XposStoredTextCtrl = nullptr;
	wxTextCtrl* m_YposStoredTextCtrl = nullptr;
	wxTextCtrl* m_ZposStoredTextCtrl = nullptr;
	wxComboBox* m_WarpComboBox = nullptr;
	wxButton* m_WarpButton = nullptr;
	wxButton* m_StorePosition = nullptr;
	wxButton* m_RestorePosition = nullptr;

protected:
	void updateComponents(void);
	void startTimer(void);
	void stopTimer(void);
	void OnTimer(wxTimerEvent&);
	virtual wxThread::ExitCode Entry();
	void onWarpCLicked(wxCommandEvent& evt);
	void SpeedHack(wxCommandEvent& evt);
	void NoClip(wxCommandEvent& evt);
	void InfDoubleJump(wxCommandEvent& evt);
	void NoCooldown(wxCommandEvent& evt);
	void InfAirDash(wxCommandEvent& evt);
	void IgnoreUpgradeMaterials(wxCommandEvent& evt);
	void OnThreadUpdate(wxThreadEvent& evt);
	void OnClose(wxCloseEvent& evt);
	void StartHook(void);
	void StorePosition(wxCommandEvent& evt);
	void RestorePosition(wxCommandEvent& evt);
	wxDECLARE_EVENT_TABLE();
};

