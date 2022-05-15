#include "InventoryPanel.hpp"
#include "defines.h"

wxBEGIN_EVENT_TABLE(InventoryPanel, wxPanel) wxEND_EVENT_TABLE()

    int InventoryPanel::getItemID(wxString name, wxString category)
{
    std::map<wxString, int>::iterator it;
    std::map<wxString, int>::iterator end;

    if (category == wxString("Restorative"))
    {
        it = _Restorative.begin();
        end = _Restorative.end();
    }
    else if (category == wxString("Enhancement"))
    {
        it = _Enhancement.begin();
        end = _Enhancement.end();
    }
    else if (category == wxString("Support"))
    {
        it = _Support.begin();
        end = _Support.end();
    }
    else if (category == wxString("Key"))
    {
        it = _Key.begin();
        end = _Key.end();
    }
    else if (category == wxString("Materials"))
    {
        it = _Materials.begin();
        end = _Materials.end();
    }

    for (; it != end; it++)
    {
        if (it->first == name)
        {
            return it->second;
        }
    }
    return -1;
}
wxArrayString InventoryPanel::getItems(wxString category)
{
    std::map<wxString, int>::iterator it;
    std::map<wxString, int>::iterator end;
    wxArrayString choices;
    if (category == wxString("Restorative"))
    {
        it = _Restorative.begin();
        end = _Restorative.end();
    }
    else if (category == wxString("Enhancement"))
    {
        it = _Enhancement.begin();
        end = _Enhancement.end();
    }
    else if (category == wxString("Support"))
    {
        it = _Support.begin();
        end = _Support.end();
    }
    else if (category == wxString("Key"))
    {
        it = _Key.begin();
        end = _Key.end();
    }
    else if (category == wxString("Materials"))
    {
        it = _Materials.begin();
        end = _Materials.end();
    }

    for (; it != end; it++)
    {
        choices.Add(it->first);
    }
    return choices;
}
InventoryPanel::InventoryPanel(wxNotebook* parent, NieRHook* hook) : wxPanel(parent, wxID_ANY)
{
    this->hook = hook;

    // Load Restorative map
    _Restorative.insert(std::pair<wxString, int>(wxString("Small Recovery"), 0));
    _Restorative.insert(std::pair<wxString, int>(wxString("Medium Recovery"), 1));
    _Restorative.insert(std::pair<wxString, int>(wxString("Large Recovery"), 2));
    _Restorative.insert(std::pair<wxString, int>(wxString("Full Recovery"), 3));
    _Restorative.insert(std::pair<wxString, int>(wxString("Visual Cure"), 60));
    _Restorative.insert(std::pair<wxString, int>(wxString("Aural Cure"), 70));
    _Restorative.insert(std::pair<wxString, int>(wxString("Cure Manipulation"), 75));
    _Restorative.insert(std::pair<wxString, int>(wxString("Cure All Status"), 80));
    _Restorative.insert(std::pair<wxString, int>(wxString("Cure All + Heal All"), 90));

    // Load Enhancement
    _Enhancement.insert(std::pair<wxString, int>(wxString("Melee Attack Up (S)"), 100));
    _Enhancement.insert(std::pair<wxString, int>(wxString("Melee Attack Up (L)"), 102));
    _Enhancement.insert(std::pair<wxString, int>(wxString("Melee Defense Up (S)"), 120));
    _Enhancement.insert(std::pair<wxString, int>(wxString("Melee Defense Up (L)"), 122));
    _Enhancement.insert(std::pair<wxString, int>(wxString("Ranged Attack UP (S)"), 110));
    _Enhancement.insert(std::pair<wxString, int>(wxString("Ranged Attack UP (L)"), 112));
    _Enhancement.insert(std::pair<wxString, int>(wxString("Ranged Defense UP (S)"), 130));
    _Enhancement.insert(std::pair<wxString, int>(wxString("Ranged Defense Up (L)"), 132));
    _Enhancement.insert(std::pair<wxString, int>(wxString("Volt-Proof Salve"), 50));
    _Enhancement.insert(std::pair<wxString, int>(wxString("Skill Salve (S)"), 140));
    _Enhancement.insert(std::pair<wxString, int>(wxString("Skill Salve (L)"), 142));
    _Enhancement.insert(std::pair<wxString, int>(wxString("Impact Bracer (S)"), 150));
    _Enhancement.insert(std::pair<wxString, int>(wxString("Impact Bracer (L)"), 152));
    _Enhancement.insert(std::pair<wxString, int>(wxString("Popola's Booze"), 170));

    // Load Support Items
    _Support.insert(std::pair<wxString, int>(wxString("Speed Salve (S)"), 160));
    _Support.insert(std::pair<wxString, int>(wxString("Speed Salve (L)"), 162));
    _Support.insert(std::pair<wxString, int>(wxString("Animal Bait"), 300));
    _Support.insert(std::pair<wxString, int>(wxString("Small G Luck+"), 330));
    _Support.insert(std::pair<wxString, int>(wxString("Large G Luck+"), 332));
    _Support.insert(std::pair<wxString, int>(wxString("E-Drug"), 400));
    // TODO _Support.insert(std::pair< wxString, int>(wxString("Forbidden Fruit"), 410));

    // Load Materials
    _Materials.insert(std::pair<wxString, int>(wxString("Amber"), 633));
    _Materials.insert(std::pair<wxString, int>(wxString("Ancient Mask"), 682));
    _Materials.insert(std::pair<wxString, int>(wxString("Beast Hide"), 510));
    _Materials.insert(std::pair<wxString, int>(wxString("Black Pearl"), 639));
    _Materials.insert(std::pair<wxString, int>(wxString("Boar Meat"), 517));
    _Materials.insert(std::pair<wxString, int>(wxString("Broken Battery"), 545));
    _Materials.insert(std::pair<wxString, int>(wxString("Broken Circuit"), 646));
    _Materials.insert(std::pair<wxString, int>(wxString("Broken Key"), 540));
    _Materials.insert(std::pair<wxString, int>(wxString("Copper Ore"), 600));
    _Materials.insert(std::pair<wxString, int>(wxString("Clean Nut"), 560));
    _Materials.insert(std::pair<wxString, int>(wxString("Complex Gadget"), 582));
    _Materials.insert(std::pair<wxString, int>(wxString("Crushed Nut"), 636));
    _Materials.insert(std::pair<wxString, int>(wxString("Crystal"), 680));
    _Materials.insert(std::pair<wxString, int>(wxString("Drab Bracelet"), 641));
    _Materials.insert(std::pair<wxString, int>(wxString("Dented Plate"), 610));
    _Materials.insert(std::pair<wxString, int>(wxString("Dented Socket"), 645));
    _Materials.insert(std::pair<wxString, int>(wxString("Dye"), 631));
    _Materials.insert(std::pair<wxString, int>(wxString("Eagle Eggs"), 638));
    _Materials.insert(std::pair<wxString, int>(wxString("Elaborate Gadget"), 581));
    _Materials.insert(std::pair<wxString, int>(wxString("Filler Metal"), 630));
    _Materials.insert(std::pair<wxString, int>(wxString("Giant Egg"), 637));
    _Materials.insert(std::pair<wxString, int>(wxString("Gold Ore"), 603));
    _Materials.insert(std::pair<wxString, int>(wxString("Iron Ore"), 601));
    _Materials.insert(std::pair<wxString, int>(wxString("Large Battery"), 546));
    _Materials.insert(std::pair<wxString, int>(wxString("Large Gear"), 526));
    _Materials.insert(std::pair<wxString, int>(wxString("Lovely Choker"), 681));
    _Materials.insert(std::pair<wxString, int>(wxString("Machine Arm"), 570));
    _Materials.insert(std::pair<wxString, int>(wxString("Machine Core"), 690));
    _Materials.insert(std::pair<wxString, int>(wxString("Machine Head"), 573));
    _Materials.insert(std::pair<wxString, int>(wxString("Machine Leg"), 571));
    _Materials.insert(std::pair<wxString, int>(wxString("Machine Oil"), 628));
    _Materials.insert(std::pair<wxString, int>(wxString("Machine Torso"), 572));
    _Materials.insert(std::pair<wxString, int>(wxString("Memory Alloy"), 536));
    _Materials.insert(std::pair<wxString, int>(wxString("Meteorite"), 588));
    _Materials.insert(std::pair<wxString, int>(wxString("Meteorite Shard"), 531));
    _Materials.insert(std::pair<wxString, int>(wxString("Moldavite"), 687));
    _Materials.insert(std::pair<wxString, int>(wxString("Moose Meat"), 518));
    _Materials.insert(std::pair<wxString, int>(wxString("Mushroom"), 626));
    _Materials.insert(std::pair<wxString, int>(wxString("Natural Rubber"), 634));
    _Materials.insert(std::pair<wxString, int>(wxString("New Bolt"), 555));
    _Materials.insert(std::pair<wxString, int>(wxString("Pearl"), 686));
    _Materials.insert(std::pair<wxString, int>(wxString("Plant Seed"), 621));
    _Materials.insert(std::pair<wxString, int>(wxString("Popola's Booze"), 170));
    _Materials.insert(std::pair<wxString, int>(wxString("Powerup Part L"), 585));
    _Materials.insert(std::pair<wxString, int>(wxString("Powerup Part M"), 584));
    _Materials.insert(std::pair<wxString, int>(wxString("Powerup Part S"), 583));
    _Materials.insert(std::pair<wxString, int>(wxString("Precious Earrings"), 683));
    _Materials.insert(std::pair<wxString, int>(wxString("Pristine Cable"), 551));
    _Materials.insert(std::pair<wxString, int>(wxString("Pristine Screw"), 521));
    _Materials.insert(std::pair<wxString, int>(wxString("Pure Water"), 623));
    _Materials.insert(std::pair<wxString, int>(wxString("Pyrite"), 632));
    _Materials.insert(std::pair<wxString, int>(wxString("Rusted Clump"), 530));
    _Materials.insert(std::pair<wxString, int>(wxString("Rusty Bolt"), 635));
    _Materials.insert(std::pair<wxString, int>(wxString("Severed Cable"), 550));
    _Materials.insert(std::pair<wxString, int>(wxString("Shattered Earrings"), 640));
    _Materials.insert(std::pair<wxString, int>(wxString("Silver Ore"), 602));
    _Materials.insert(std::pair<wxString, int>(wxString("Simple Gadget"), 580));
    _Materials.insert(std::pair<wxString, int>(wxString("Small Gear"), 525));
    _Materials.insert(std::pair<wxString, int>(wxString("Stretched Coil"), 644));
    _Materials.insert(std::pair<wxString, int>(wxString("Stripped Screw"), 520));
    _Materials.insert(std::pair<wxString, int>(wxString("Sturdy Socket"), 642));
    _Materials.insert(std::pair<wxString, int>(wxString("Tanning Agent"), 629));
    _Materials.insert(std::pair<wxString, int>(wxString("Tech Manual"), 684));
    _Materials.insert(std::pair<wxString, int>(wxString("Thick Dictionary"), 685));
    _Materials.insert(std::pair<wxString, int>(wxString("Titanium Alloy"), 535));
    _Materials.insert(std::pair<wxString, int>(wxString("Torn Book"), 627));
    _Materials.insert(std::pair<wxString, int>(wxString("Tree Sap"), 622));
    _Materials.insert(std::pair<wxString, int>(wxString("Tree Seed"), 624));
    _Materials.insert(std::pair<wxString, int>(wxString("Viscous Oil"), 852));
    _Materials.insert(std::pair<wxString, int>(wxString("Volt-Proof Salve"), 50));
    _Materials.insert(std::pair<wxString, int>(wxString("Warped Wire"), 643));

    // Load Key Items
    _Key.insert(std::pair<wxString, int>(wxString("Sachet"), 920));
    _Key.insert(std::pair<wxString, int>(wxString("Quality Sachet"), 921));
    _Key.insert(std::pair<wxString, int>(wxString("Choice Sachet"), 922));
    _Key.insert(std::pair<wxString, int>(wxString("Sound Data 1"), 930));
    _Key.insert(std::pair<wxString, int>(wxString("Sound Data 2"), 931));
    _Key.insert(std::pair<wxString, int>(wxString("Sound Data 3"), 932));
    _Key.insert(std::pair<wxString, int>(wxString("Sound Data 4"), 933));
    _Key.insert(std::pair<wxString, int>(wxString("Sound Data 5"), 934));
    _Key.insert(std::pair<wxString, int>(wxString("Sound Data 6"), 935));
    _Key.insert(std::pair<wxString, int>(wxString("Sound Data 7"), 936));
    _Key.insert(std::pair<wxString, int>(wxString("Grimoire Weiss"), 951));
    _Key.insert(std::pair<wxString, int>(wxString("Play System Pod"), 950));
    _Key.insert(std::pair<wxString, int>(wxString("Blue Ribbon"), 874));
    _Key.insert(std::pair<wxString, int>(wxString("Pink Ribbon"), 873));
    _Key.insert(std::pair<wxString, int>(wxString("Alien Mask"), 996));
    _Key.insert(std::pair<wxString, int>(wxString("Lunar Tear"), 992));
    _Key.insert(std::pair<wxString, int>(wxString("Plug-in Chip"), 841));
    _Key.insert(std::pair<wxString, int>(wxString("Rusty Music Box"), 750));
    _Key.insert(std::pair<wxString, int>(wxString("Stamp"), 833));
    _Key.insert(std::pair<wxString, int>(wxString("Stamp Card"), 834));
    _Key.insert(std::pair<wxString, int>(wxString("Letter for Sartre / Jean-Paul"), 700));
    _Key.insert(std::pair<wxString, int>(wxString("Beautiful Glass"), 701));
    _Key.insert(std::pair<wxString, int>(wxString("Memory Chip"), 715));
    _Key.insert(std::pair<wxString, int>(wxString("Man's Journal"), 716));
    _Key.insert(std::pair<wxString, int>(wxString("Machine Fossil"), 702));
    _Key.insert(std::pair<wxString, int>(wxString("Toothbrush"), 793));
    _Key.insert(std::pair<wxString, int>(wxString("Sartre's / Jean-Paul's Letter"), 703));
    _Key.insert(std::pair<wxString, int>(wxString("Dietary Goods"), 795));
    _Key.insert(std::pair<wxString, int>(wxString("Writing Implement"), 796));
    _Key.insert(std::pair<wxString, int>(wxString("Medical Journal"), 797));
    _Key.insert(std::pair<wxString, int>(wxString("Data Chip A"), 720));
    _Key.insert(std::pair<wxString, int>(wxString("Data Chip B"), 721));
    _Key.insert(std::pair<wxString, int>(wxString("Data Chip C"), 722));
    _Key.insert(std::pair<wxString, int>(wxString("Data Chip D"), 723));
    _Key.insert(std::pair<wxString, int>(wxString("Data Chip E"), 724));
    _Key.insert(std::pair<wxString, int>(wxString("Elevator Key"), 845));
    _Key.insert(std::pair<wxString, int>(wxString("Broken Toy"), 780));
    _Key.insert(std::pair<wxString, int>(wxString("Accounting Book"), 781));
    _Key.insert(std::pair<wxString, int>(wxString("Small Shoe"), 782));
    _Key.insert(std::pair<wxString, int>(wxString("Machine Part"), 832));
    _Key.insert(std::pair<wxString, int>(wxString("Heavy Armor A"), 981));
    _Key.insert(std::pair<wxString, int>(wxString("Heavy Armor B"), 982));
    _Key.insert(std::pair<wxString, int>(wxString("Camouflage Goggles"), 871));
    _Key.insert(std::pair<wxString, int>(wxString("A2 Wig"), 872));
    _Key.insert(std::pair<wxString, int>(wxString("Adam's Glasses"), 995));
    _Key.insert(std::pair<wxString, int>(wxString("Emil mask"), 993));
    _Key.insert(std::pair<wxString, int>(wxString("Emil's head"), 991));
    _Key.insert(std::pair<wxString, int>(wxString("Revealing Outfit"), 983));
    _Key.insert(std::pair<wxString, int>(wxString("Young Man's Outfit"), 984));
    _Key.insert(std::pair<wxString, int>(wxString("Destroyer Outfit"), 985));
    _Key.insert(std::pair<wxString, int>(wxString("CEO Bullets"), 961));
    _Key.insert(std::pair<wxString, int>(wxString("Dress Module"), 980));
    _Key.insert(std::pair<wxString, int>(wxString("Machine Mask"), 990));
    _Key.insert(std::pair<wxString, int>(wxString("Sand Mask"), 994));
    _Key.insert(std::pair<wxString, int>(wxString("Valve: Left Eye"), 997));
    _Key.insert(std::pair<wxString, int>(wxString("Valve: Right Eye"), 998));
    _Key.insert(std::pair<wxString, int>(wxString("Valve: Both Eyes"), 999));
    _Key.insert(std::pair<wxString, int>(wxString("Valve: Head"), 870));
    _Key.insert(std::pair<wxString, int>(wxString("Musamune Mask"), 876));
    _Key.insert(std::pair<wxString, int>(wxString("Matsuda Mask"), 877));
    _Key.insert(std::pair<wxString, int>(wxString("Sato Mask"), 878));
    _Key.insert(std::pair<wxString, int>(wxString("White Hair"), 880));
    _Key.insert(std::pair<wxString, int>(wxString("Black Hair"), 881));
    _Key.insert(std::pair<wxString, int>(wxString("Brown Hair"), 882));
    _Key.insert(std::pair<wxString, int>(wxString("Red Hair"), 883));
    _Key.insert(std::pair<wxString, int>(wxString("Blue Hair"), 884));
    _Key.insert(std::pair<wxString, int>(wxString("Green Hair"), 885));
    _Key.insert(std::pair<wxString, int>(wxString("Purple Hair"), 886));
    _Key.insert(std::pair<wxString, int>(wxString("Ash Grey Hair"), 887));
    _Key.insert(std::pair<wxString, int>(wxString("Golden Hair"), 888));
    _Key.insert(std::pair<wxString, int>(wxString("Pastel Pink Hair"), 889));
    _Key.insert(std::pair<wxString, int>(wxString("Light Blue Hair"), 890));
    _Key.insert(std::pair<wxString, int>(wxString("Lime Green Hair"), 891));
    _Key.insert(std::pair<wxString, int>(wxString("Light Purple Hair"), 892));
    _Key.insert(std::pair<wxString, int>(wxString("Neon White Hair"), 893));
    _Key.insert(std::pair<wxString, int>(wxString("Neon Yellow Hair"), 894));
    _Key.insert(std::pair<wxString, int>(wxString("Neon Pink Hair"), 895));
    _Key.insert(std::pair<wxString, int>(wxString("Neon Blue Hair"), 896));
    _Key.insert(std::pair<wxString, int>(wxString("Neon Green Hair"), 897));
    _Key.insert(std::pair<wxString, int>(wxString("Neon Purple Hair"), 898));

    // Panel Components
    wxArrayString* ItemCategories = new wxArrayString();
    ItemCategories->Add("Restorative", 1);
    ItemCategories->Add("Enhancement", 1);
    ItemCategories->Add("Support", 1);
    ItemCategories->Add("Materials", 1);
    ItemCategories->Add("Key", 1);
    m_ItemCategoryComboBox = new wxComboBox(this, wxID_ANY, "", wxPoint(20, 20), wxSize(315, 25), *ItemCategories, 0,
                                            wxDefaultValidator, wxComboBoxNameStr);
    delete ItemCategories;
    m_ItemCategoryComboBox->Bind(wxEVT_COMBOBOX, &InventoryPanel::onChangeItemCategory, this);

    wxArrayString choices = getItems("Restorative");
    m_Items = new wxListBox(this, wxID_ANY, wxPoint(20, 60), wxSize(315, 300), choices, 0, wxDefaultValidator,
                            wxListBoxNameStr);

    // Buttons
    m_AddItems = new wxButton(this, wxID_ANY, wxString("Add Item"), wxPoint(20, 400), wxDefaultSize, 0,
                              wxDefaultValidator, wxButtonNameStr);
    m_AddItems->Bind(wxEVT_BUTTON, &InventoryPanel::onAddItemPress, this);

    m_RemoveItems = new wxButton(this, wxID_ANY, wxString("Remove Item"), wxPoint(245, 400), wxDefaultSize, 0,
                                 wxDefaultValidator, wxButtonNameStr);
    m_RemoveItems->Bind(wxEVT_BUTTON, &InventoryPanel::onRemoveItemPress, this);

    m_Quantity =
        new wxTextCtrl(this, wxID_ANY, "1", wxPoint(100, 400), wxDefaultSize, 0, wxDefaultValidator, wxTextCtrlNameStr);

    this->SetBackgroundColour(foregroundColor);
    m_ItemCategoryComboBox->SetSelection(0);
}

InventoryPanel::~InventoryPanel()
{
}

void InventoryPanel::onAddItemPress(wxCommandEvent& evt)
{
    if (wxNOT_FOUND == m_Items->GetSelection())
    {
        wxMessageBox("Please select an item");
        return;
    }
    int ID = getItemID(m_Items->GetString(m_Items->GetSelection()), m_ItemCategoryComboBox->GetValue());
    if (ID < 0)
    {
        wxMessageBox("Could not add the item");
        return;
    }
    long quantity;
    m_Quantity->GetValue().ToLong(&quantity);
    if (quantity < 1 || quantity > 99)
    {
        quantity = quantity < 1 ? 1 : 99;
    }
    m_Quantity->SetValue(wxString::Format(wxT("%i"), quantity));
    hook->addItem(ID, quantity);
}

void InventoryPanel::onRemoveItemPress(wxCommandEvent& evt)
{
    if (wxNOT_FOUND == m_Items->GetSelection())
    {
        wxMessageBox("Please select an item");
        return;
    }
    int ID = getItemID(m_Items->GetString(m_Items->GetSelection()), m_ItemCategoryComboBox->GetValue());
    if (ID < 0)
    {
        wxMessageBox("Could not remove the item");
        return;
    }
    hook->removeItem(ID);
}

void InventoryPanel::onChangeItemCategory(wxCommandEvent& evt)
{
    wxArrayString choices = getItems(m_ItemCategoryComboBox->GetValue());
    m_Items->Clear();
    m_Items->InsertItems(choices, 0);
}