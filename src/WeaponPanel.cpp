#include "WeaponPanel.hpp"

wxBEGIN_EVENT_TABLE(WeaponPanel, wxPanel)
    wxEND_EVENT_TABLE() WeaponPanel::WeaponPanel(wxNotebook* parent, NieRHook* hook)
    : wxPanel(parent, wxID_ANY)
{
    this->hook = hook;

    // Load Weapons
    _Weapons.insert(std::pair<wxString, int>("Faith", 0x3EB));
    _Weapons.insert(std::pair<wxString, int>("Iron Pipe", 0x3F5));
    _Weapons.insert(std::pair<wxString, int>("Beastbane", 0x3FC));
    _Weapons.insert(std::pair<wxString, int>("Phoenix Dagger", 0x410));
    _Weapons.insert(std::pair<wxString, int>("Ancient Overlord", 0x406));
    _Weapons.insert(std::pair<wxString, int>("Type-40 Sword", 0x41A));
    _Weapons.insert(std::pair<wxString, int>("Type-3 Sword", 0x424));
    _Weapons.insert(std::pair<wxString, int>("Virtuous Contract", 0x42E));
    _Weapons.insert(std::pair<wxString, int>("Cruel Oath", 0x42F));
    _Weapons.insert(std::pair<wxString, int>("YoRHa-issue Blade", 0x438));
    _Weapons.insert(std::pair<wxString, int>("Machine Sword", 0x442));
    _Weapons.insert(std::pair<wxString, int>("Iron Will", 0x4B3));
    _Weapons.insert(std::pair<wxString, int>("Fang of the Twins", 0x4BD));
    _Weapons.insert(std::pair<wxString, int>("Beastlord", 0x4C4));
    _Weapons.insert(std::pair<wxString, int>("Phoenix Sword", 0x4CE));
    _Weapons.insert(std::pair<wxString, int>("Type-40 Blade", 0x4D8));
    _Weapons.insert(std::pair<wxString, int>("Type-3 Blade", 0x4E2));
    _Weapons.insert(std::pair<wxString, int>("Virtuous Treaty", 0x4EC));
    _Weapons.insert(std::pair<wxString, int>("Cruel Blood Oath", 0x4ED));
    _Weapons.insert(std::pair<wxString, int>("Machine Axe", 0x4F6));
    _Weapons.insert(std::pair<wxString, int>("Phoenix Lance", 0x578));
    _Weapons.insert(std::pair<wxString, int>("Beastcurse", 0x58C));
    _Weapons.insert(std::pair<wxString, int>("Dragoon Lance", 0x596));
    _Weapons.insert(std::pair<wxString, int>("Spear of the Usurper", 0x5A0));
    _Weapons.insert(std::pair<wxString, int>("Type-40 Lance", 0x5AA));
    _Weapons.insert(std::pair<wxString, int>("Type-3 Lance", 0x5B4));
    _Weapons.insert(std::pair<wxString, int>("Virtuous Dignity", 0x5BE));
    _Weapons.insert(std::pair<wxString, int>("Cruel Arrogance", 0x5BF));
    _Weapons.insert(std::pair<wxString, int>("Machine Spear", 0x5C8));
    _Weapons.insert(std::pair<wxString, int>("Angel's Folly", 0x688));
    _Weapons.insert(std::pair<wxString, int>("Demon's Cry", 0x65E));
    _Weapons.insert(std::pair<wxString, int>("Type-40 Fists", 0x64A));
    _Weapons.insert(std::pair<wxString, int>("Type-3 Fists", 0x640));
    _Weapons.insert(std::pair<wxString, int>("Virtuous Grief", 0x654));
    _Weapons.insert(std::pair<wxString, int>("Cruel Lament", 0x655));
    _Weapons.insert(std::pair<wxString, int>("Machine Heads", 0x672));
    _Weapons.insert(std::pair<wxString, int>("Engine Blade", 0x753));
    _Weapons.insert(std::pair<wxString, int>("Cypress Stick", 0x754));
    _Weapons.insert(std::pair<wxString, int>("Emil Heads", 0x755));

    wxArrayString weapons;
    std::map<wxString, int>::iterator it = _Weapons.begin();

    for (; it != _Weapons.end(); it++)
    {
        weapons.Add(it->first);
    }
    w_WeaponList = new wxListBox(this, wxID_ANY, wxPoint(20, 20), wxSize(315, 290), weapons, wxLB_NEEDED_SB,
                                 wxDefaultValidator, wxListBoxNameStr);

    // Level
    w_LevelBox =
        new wxStaticBox(this, wxID_ANY, "Weapon Level", wxPoint(20, 330), wxSize(315, 70), 0, wxStaticBoxNameStr);
    w_Level1 = new wxRadioButton(this, wxID_ANY, "Level 1", wxPoint(30, 360), wxDefaultSize, 0, wxDefaultValidator,
                                 wxRadioButtonNameStr);
    w_Level2 = new wxRadioButton(this, wxID_ANY, "Level 2", wxPoint(110, 360), wxDefaultSize, 0, wxDefaultValidator,
                                 wxRadioButtonNameStr);
    w_Level3 = new wxRadioButton(this, wxID_ANY, "Level 3", wxPoint(190, 360), wxDefaultSize, 0, wxDefaultValidator,
                                 wxRadioButtonNameStr);
    w_Level4 = new wxRadioButton(this, wxID_ANY, "Level 4", wxPoint(270, 360), wxDefaultSize, 0, wxDefaultValidator,
                                 wxRadioButtonNameStr);
    // Create
    w_CreateButton =
        new wxButton(this, wxID_ANY, "Add", wxPoint(20, 415), wxSize(90, 25), 0, wxDefaultValidator, wxButtonNameStr);
    w_CreateButton->Bind(wxEVT_BUTTON, &WeaponPanel::OnCreatePress, this);
    // Remove
    w_RemoveButton = new wxButton(this, wxID_ANY, "Remove", wxPoint(120, 415), wxSize(90, 25), 0, wxDefaultValidator,
                                  wxButtonNameStr);
    w_RemoveButton->Bind(wxEVT_BUTTON, &WeaponPanel::OnRemovePress, this);

    w_Status = new wxStaticText(this, wxID_ANY, "", wxPoint(215, 420), wxDefaultSize, 0, wxStaticTextNameStr);

    this->SetBackgroundColour(wxColor(255, 255, 255));
}
WeaponPanel::~WeaponPanel()
{
}
void WeaponPanel::toggleComponents(bool enabled)
{
    w_WeaponList->Enable(enabled);
    w_CreateButton->Enable(enabled);
}
int WeaponPanel::getSelectedRadioBox(void)
{
    if (this->w_Level1->GetValue())
    {
        return 1;
    }
    else if (this->w_Level2->GetValue())
    {
        return 2;
    }
    else if (this->w_Level3->GetValue())
    {
        return 3;
    }
    else if (this->w_Level4->GetValue())
    {
        return 4;
    }
    else
    {
        w_Level1->SetValue(true);
        return 1;
    }
}
void WeaponPanel::OnCreatePress(wxCommandEvent& evt)
{
    if (wxNOT_FOUND == w_WeaponList->GetSelection())
    {
        wxMessageBox("Please select a weapon");
        return;
    }
    std::map<wxString, int>::iterator it = _Weapons.begin();
    int ID = -1;
    for (; it != _Weapons.end(); it++)
    {
        if (it->first == w_WeaponList->GetString(w_WeaponList->GetSelection()))
        {
            ID = it->second;
            break;
        }
    }
    if (ID < 0)
    {
        wxMessageBox("Could not add the item");
        return;
    }
    // Add Weapon
    if (!hook->addWeapon(ID, this->getSelectedRadioBox()))
    {
        wxMessageBox("Could not add selected weapon");
        return;
    }
    w_Status->SetLabel(it->first + " Created");
}
void WeaponPanel::OnRemovePress(wxCommandEvent& evt)
{
    if (wxNOT_FOUND == w_WeaponList->GetSelection())
    {
        wxMessageBox("Please select a weapon");
        return;
    }
    std::map<wxString, int>::iterator it = _Weapons.begin();
    int ID = -1;
    for (; it != _Weapons.end(); it++)
    {
        if (it->first == w_WeaponList->GetString(w_WeaponList->GetSelection()))
        {
            ID = it->second;
            break;
        }
    }
    if (ID < 0)
    {
        wxMessageBox("Could not add the item");
        return;
    }
    // Remove Weapon
    if (!hook->removeWeapon(ID))
    {
        wxMessageBox("Could not remove selected weapon");
        return;
    }
    w_Status->SetLabel(it->first + " Removed");
}
