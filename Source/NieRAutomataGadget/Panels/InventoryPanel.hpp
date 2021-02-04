#pragma once
#include <wx/wx.h>
#include <wx/notebook.h>
#include "../NierHook.hpp"
class InventoryPanel : public wxPanel
{
public:
	wxComboBox* m_ItemCategoryComboBox = nullptr;
	wxListBox* m_Items = nullptr;
	wxButton* m_AddItems = nullptr;
	InventoryPanel(wxNotebook* parent, NieRHook* hook);
	~InventoryPanel();
protected:
	void onAddItemPress(wxCommandEvent& evt);
	void onChangeItemCategory(wxCommandEvent& evt);
	wxDECLARE_EVENT_TABLE();
};

