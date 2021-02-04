#pragma once
#include <wx/wx.h>
#include <wx/notebook.h>
#include "../NierHook.hpp"
class WeaponPanel : public wxPanel
{
private:
	int getSelectedRadioBox(void);
public:
	WeaponPanel(wxNotebook* parent, NieRHook* hook);
	~WeaponPanel();
	wxArrayString* Weapons = nullptr;
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
	wxStaticText* w_Status = nullptr;

	//Methods
	void toggleComponents(bool enabled);
protected:
	void OnCreatePress(wxCommandEvent& evt);
	wxDECLARE_EVENT_TABLE();
};