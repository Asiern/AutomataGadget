#include "WeaponPanel.hpp"

wxBEGIN_EVENT_TABLE(WeaponPanel, wxPanel)
wxEND_EVENT_TABLE()
WeaponPanel::WeaponPanel(wxNotebook* parent, NieRHook* hook) : wxPanel(parent, wxID_ANY)
{
	this->hook = hook;
	Weapons = new wxArrayString();
	Weapons->Add("Faith", 1);
	Weapons->Add("Iron Pipe", 1);
	Weapons->Add("Beastbane", 1);
	Weapons->Add("Phoenix Dagger", 1);
	Weapons->Add("Ancient Overlord", 1);
	Weapons->Add("Type-40 Sword", 1);
	Weapons->Add("Type-3 Sword", 1);
	Weapons->Add("Virtuous Contract", 1);
	Weapons->Add("Cruel Oath", 1);
	Weapons->Add("YoRHa-issue Blade", 1);
	Weapons->Add("Machine Sword", 1);
	Weapons->Add("Iron Will", 1);
	Weapons->Add("Fang of the Twins", 1);
	Weapons->Add("Beastlord", 1);
	Weapons->Add("Phoenix Sword", 1);
	Weapons->Add("Type-40 Blade", 1);
	Weapons->Add("Type-3 Blade", 1);
	Weapons->Add("Virtuous Treaty", 1);
	Weapons->Add("Cruel Blood Oath", 1);
	Weapons->Add("Machine Axe", 1);
	Weapons->Add("Phoenix Lance", 1);
	Weapons->Add("Beastcurse", 1);
	Weapons->Add("Dragoon Lance", 1);
	Weapons->Add("Spear of the Usurper", 1);
	Weapons->Add("Type-40 Lance", 1);
	Weapons->Add("Type-3 Lance", 1);
	Weapons->Add("Virtuous Dignity", 1);
	Weapons->Add("Cruel Arrogance", 1);
	Weapons->Add("Machine Spear", 1);
	Weapons->Add("Angel's Folly", 1);
	Weapons->Add("Demon's Cry", 1);
	Weapons->Add("Type-40 Fists", 1);
	Weapons->Add("Type-3 Fists", 1);
	Weapons->Add("Virtuous Grief", 1);
	Weapons->Add("Creal Lament", 1);
	Weapons->Add("Machine Heads", 1);
	Weapons->Add("Engine Blade", 1);
	Weapons->Add("Cypress Stick", 1);
	Weapons->Add("Emil Heads", 1);

	w_WeaponList = new wxListBox(this, wxID_ANY, wxPoint(20, 20), wxSize(315, 290), *Weapons, wxLB_NEEDED_SB, wxDefaultValidator, wxListBoxNameStr);
	//Level
	w_LevelBox = new wxStaticBox(this, wxID_ANY, "Weapon Level", wxPoint(20, 330), wxSize(315, 70), 0, wxStaticBoxNameStr);
	w_Level1 = new wxRadioButton(this, wxID_ANY, "Level 1", wxPoint(30, 360), wxDefaultSize, 0, wxDefaultValidator, wxRadioButtonNameStr);
	w_Level2 = new wxRadioButton(this, wxID_ANY, "Level 2", wxPoint(110, 360), wxDefaultSize, 0, wxDefaultValidator, wxRadioButtonNameStr);
	w_Level3 = new wxRadioButton(this, wxID_ANY, "Level 3", wxPoint(190, 360), wxDefaultSize, 0, wxDefaultValidator, wxRadioButtonNameStr);
	w_Level4 = new wxRadioButton(this, wxID_ANY, "Level 4", wxPoint(270, 360), wxDefaultSize, 0, wxDefaultValidator, wxRadioButtonNameStr);
	//Create
	w_CreateButton = new wxButton(this, wxID_ANY, "Create", wxPoint(248, 415), wxSize(90, 25), 0, wxDefaultValidator, wxButtonNameStr);
	w_CreateButton->Bind(wxEVT_BUTTON, &WeaponPanel::OnCreatePress, this);
	w_Status = new wxStaticText(this, wxID_ANY, "", wxPoint(20, 415), wxDefaultSize, 0, wxStaticTextNameStr);

	this->SetBackgroundColour(wxColor(255, 255, 255));
}
WeaponPanel::~WeaponPanel()
{
	delete Weapons;
}
void WeaponPanel::toggleComponents(bool enabled)
{
	w_WeaponList->Enable(enabled);
	w_CreateButton->Enable(enabled);
}
int WeaponPanel::getSelectedRadioBox(void) {
	if (this->w_Level1->GetValue()) {
		return 1;
	}
	else if (this->w_Level2->GetValue()) {
		return 2;
	}
	else if (this->w_Level3->GetValue()) {
		return 3;
	}
	else if (this->w_Level4->GetValue()) {
		return 4;
	}
	else {
		w_Level1->SetValue(true);
		return 1;
	}
}
void WeaponPanel::OnCreatePress(wxCommandEvent& evt)
{
	int Selection = w_WeaponList->GetSelection();
	int SelectionID;
	switch (Selection) {
	case 0:
		SelectionID = 0x000003EB;
		break;
	case 1:
		SelectionID = 0x000003F5;
		break;
	case 2:
		SelectionID = 0x000003FC;
		break;
	case 3:
		SelectionID = 0x00000410;
		break;
	case 4:
		SelectionID = 0x00000406;
		break;
	case 5:
		SelectionID = 0x0000041A;
		break;
	case 6:
		SelectionID = 0x00000424;
		break;
	case 7:
		SelectionID = 0x0000042E;
		break;
	case 8:
		SelectionID = 0x0000042F;
		break;
	case 9:
		SelectionID = 0x00000438;
		break;
	case 10:
		SelectionID = 0x00000442;
		break;
	case 11:
		SelectionID = 0x000004B3;
		break;
	case 12:
		SelectionID = 0x000004BD;
		break;
	case 13:
		SelectionID = 0x000004C4;
		break;
	case 14:
		SelectionID = 0x000004CE;
		break;
	case 15:
		SelectionID = 0x000004D8;
		break;
	case 16:
		SelectionID = 0x000004E2;
		break;
	case 17:
		SelectionID = 0x000004EC;
		break;
	case 18:
		SelectionID = 0x000004ED;
		break;
	case 19:
		SelectionID = 0x000004F6;
		break;
	case 20:
		SelectionID = 0x00000578;
		break;
	case 21:
		SelectionID = 0x0000058C;
		break;
	case 22:
		SelectionID = 0x00000596;
		break;
	case 23:
		SelectionID = 0x000005A0;
		break;
	case 24:
		SelectionID = 0x000005AA;
		break;
	case 25:
		SelectionID = 0x000005B4;
		break;
	case 26:
		SelectionID = 0x000005BE;
		break;
	case 27:
		SelectionID = 0x000005BF;
		break;
	case 28:
		SelectionID = 0x000005C8;
		break;
	case 29:
		SelectionID = 0x00000668;
		break;
	case 30:
		SelectionID = 0x0000065E;
		break;
	case 31:
		SelectionID = 0x0000064A;
		break;
	case 32:
		SelectionID = 0x00000640;
		break;
	case 33:
		SelectionID = 0x00000654;
		break;
	case 34:
		SelectionID = 0x00000655;
		break;
	case 35:
		SelectionID = 0x00000672;
		break;
	case 36:
		SelectionID = 0x00000753;
		break;
	case 37:
		SelectionID = 0x00000754;
		break;
	case 38:
		SelectionID = 0x00000755;
		break;
	default:
		wxMessageBox("Weapon not selected");
		return;
	}
	//Add Weapon
	hook->addWeapon(SelectionID, this->getSelectedRadioBox());
	wxString Level = std::to_string(this->getSelectedRadioBox());
	wxString WeaponName = w_WeaponList->GetString(Selection);
	w_Status->SetLabel(WeaponName + " Lv:" + Level + " Created");
}
