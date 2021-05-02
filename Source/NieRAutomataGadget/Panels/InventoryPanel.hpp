#pragma once
#include <wx/wx.h>
#include <wx/notebook.h>
#include "../NieRHook/Source/ConsoleApplication1/NierHook.hpp"
#include <map>

class InventoryPanel : public wxPanel
{
private:
	NieRHook* hook;
	wxComboBox* m_ItemCategoryComboBox = nullptr;
	wxListBox* m_Items = nullptr;
	wxButton* m_AddItems = nullptr;
	wxButton* m_RemoveItems = nullptr;
	wxTextCtrl* m_Quantity = nullptr;
	std::map<wxString, int> _Restorative;
	std::map<wxString, int> _Enhancement;
	std::map<wxString, int> _Key;
	std::map<wxString, int> _Support;
	std::map<wxString, int> _Materials;
	int getItemID(wxString name, wxString category);
	wxArrayString getItems(wxString category);
public:
	InventoryPanel(wxNotebook* parent, NieRHook* hook);
	~InventoryPanel();
protected:
	void onAddItemPress(wxCommandEvent& evt);
	void onRemoveItemPress(wxCommandEvent& evt);
	void onChangeItemCategory(wxCommandEvent& evt);
	wxDECLARE_EVENT_TABLE();
};

