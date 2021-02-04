#include "InventoryPanel.hpp"
wxBEGIN_EVENT_TABLE(InventoryPanel, wxPanel)
wxEND_EVENT_TABLE()
InventoryPanel::InventoryPanel(wxNotebook* parent, NieRHook* hook) :wxPanel(parent, wxID_ANY)
{
	wxArrayString* ItemCategories = new wxArrayString();
	ItemCategories->Add("Restorative", 1);
	ItemCategories->Add("Enhancement", 1);
	ItemCategories->Add("Support", 1);
	ItemCategories->Add("Materials", 1);
	ItemCategories->Add("Key", 1);

	m_ItemCategoryComboBox = new wxComboBox(this, wxID_ANY, "", wxPoint(20, 20), wxSize(315, 25), *ItemCategories, 0, wxDefaultValidator, wxComboBoxNameStr);
	m_ItemCategoryComboBox->Bind(wxEVT_COMBOBOX, &InventoryPanel::onChangeItemCategory, this);
	wxArrayString choices;
	choices.Add("Small Recovery");
	choices.Add("Medium Recovery");
	choices.Add("Large Recovery");
	choices.Add("Full Recovery");
	choices.Add("Visual Cure");
	choices.Add("Aural Cure");
	choices.Add("Cure Manipulation");
	choices.Add("Cure All Status");
	choices.Add("Cure All + Heal All");
	m_Items = new wxListBox(this, wxID_ANY, wxPoint(20, 60), wxSize(315, 300), choices, 0, wxDefaultValidator, wxListBoxNameStr);
	m_AddItems = new wxButton(this, wxID_ANY, wxString("Add Selected"), wxPoint(20, 500), wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
	m_AddItems->Bind(wxEVT_BUTTON, &InventoryPanel::onAddItemPress, this);
	delete ItemCategories;

	this->SetBackgroundColour(wxColor(255, 255, 255));
	m_ItemCategoryComboBox->SetSelection(0);
}

InventoryPanel::~InventoryPanel()
{
}

void InventoryPanel::onAddItemPress(wxCommandEvent& evt)
{
	//hook->addItem("Small Recovery", 5);
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}


void InventoryPanel::onChangeItemCategory(wxCommandEvent& evt)
{
	wxArrayString choices;
	switch (str2int(m_ItemCategoryComboBox->GetValue())) {
	case str2int("Restorative"):
		choices.Add("Small Recovery", 1);
		choices.Add("Medium Recovery");
		choices.Add("Large Recovery");
		choices.Add("Full Recovery");
		choices.Add("Visual Cure");
		choices.Add("Aural Cure");
		choices.Add("Cure Manipulation");
		choices.Add("Cure All Status");
		choices.Add("Cure All + Heal All");
		m_Items->Clear();
		m_Items->InsertItems(choices, 0);
		break;
	case str2int("Enhancement"):
		choices.Add("Melee Attack Up (S)");
		choices.Add("Melee Attack Up (L)");
		choices.Add("Melee Defense Up(S)");
		choices.Add("Melee Defense Up (L)");
		choices.Add("Ranged Attack UP (S)");
		choices.Add("Ranged Attack UP (L)");
		choices.Add("Ranged Defense UP (S)");
		choices.Add("Ranged Defense Up (L)");
		choices.Add("Volt-Proof Salve");
		choices.Add("Skill Salve (S)");
		choices.Add("Skill Salve (L)");
		choices.Add("Impact Bracer (S)");
		choices.Add("Impact Bracer (L)");
		choices.Add("Popola's Booze");
		m_Items->Clear();
		m_Items->InsertItems(choices, 0);
		break;
	case str2int("Support"):
		choices.Add("Speed Salve (S)");
		choices.Add("Speed Salve (L)");
		choices.Add("Animal Bait");
		choices.Add("Small G Luck+");
		choices.Add("Large G Luck+");
		choices.Add("E-Drug");
		choices.Add("Forbidden Fruit");
		m_Items->Clear();
		m_Items->InsertItems(choices, 0);
		break;
	case str2int("Materials"):
		m_Items->Clear();
		m_Items->InsertItems(choices, 0);
		break;
	case str2int("Key"):
		choices.Add("Sachet");
		choices.Add("Quality Sachet");
		choices.Add("Choice Sachet");
		choices.Add("Sound Data 1");
		choices.Add("Sound Data 2");
		choices.Add("Sound Data 3");
		choices.Add("Sound Data 4");
		choices.Add("Sound Data 5");
		choices.Add("Grimoire Weiss");
		choices.Add("Play System Pod");
		choices.Add("Blue Ribbon");
		choices.Add("Pink Ribbon");
		choices.Add("Alien Mask");
		choices.Add("Lunar Tear");
		choices.Add("Plug-in Chip");
		choices.Add("Rusty Music Box");
		choices.Add("Stamp");
		choices.Add("Stamp Card");
		choices.Add("Letter for Sartre");
		choices.Add("Beautiful Glass");
		choices.Add("Memory Chip");
		choices.Add("Man's Journal");
		choices.Add("Machine Fossil");
		choices.Add("Toothbrush");
		choices.Add("Sartre's Letter");
		choices.Add("Dietary Goods");
		choices.Add("Writing Implement");
		choices.Add("Medical Journal");
		choices.Add("Data Chip A");
		choices.Add("Data Chip B");
		choices.Add("Data Chip C");
		choices.Add("Data Chip D");
		choices.Add("Data Chip E");
		choices.Add("Elevator Key");
		choices.Add("Broken Toy");
		choices.Add("Accounting Book");
		choices.Add("Small Shoe");
		choices.Add("Machine Part");
		choices.Add("Heavy Armor A");
		choices.Add("Heavy Armor B");
		choices.Add("Camouflage Goggles");
		choices.Add("A2 Wig");
		choices.Add("Adam's Glasses");
		choices.Add("Emil mask");
		choices.Add("Emil's head");
		choices.Add("Letter for Jean-Paul");
		m_Items->Clear();
		m_Items->InsertItems(choices, 0);
		break;
	default:
		m_Items->Clear();
		wxMessageBox("Something went wrong");
		break;
	}


}