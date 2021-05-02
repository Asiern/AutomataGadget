#pragma once
#include <wx/wx.h>
#include <wx/notebook.h>
#include "../NieRHook/Source/ConsoleApplication1/NierHook.hpp"
#include <map>

class WeaponPanel : public wxPanel
{
private:
	int getSelectedRadioBox(void);
	std::map<wxString, int> _Weapons;
public:
	WeaponPanel(wxNotebook* parent, NieRHook* hook);
	~WeaponPanel();
	wxListBox* w_WeaponList = nullptr;
	NieRHook* hook = nullptr;
	//Level
	wxStaticBox* w_LevelBox = nullptr;
	wxRadioButton* w_Level1 = nullptr;
	wxRadioButton* w_Level2 = nullptr;
	wxRadioButton* w_Level3 = nullptr;
	wxRadioButton* w_Level4 = nullptr;
	//Create
	wxButton* w_CreateButton = nullptr;
	wxButton* w_RemoveButton = nullptr;
	wxStaticText* w_Status = nullptr;

	//Methods
	void toggleComponents(bool enabled);
protected:
	void OnRemovePress(wxCommandEvent& evt);
	void OnCreatePress(wxCommandEvent& evt);
	wxDECLARE_EVENT_TABLE();
};