// CheatsPanel.hpp
#ifndef CHEATSPANEL_HPP
#define CHEATSPANEL_HPP

#include "NieRHook.hpp" // Include the necessary header for NieRHook or update it if required
#include <wx/wx.h>

class CheatsPanel : public wxPanel
{
  public:
    CheatsPanel(wxWindow* parent, NieRHook* hook);
    ~CheatsPanel();

  private:
    NieRHook* hook;

    // Checkboxes for cheats
    wxCheckBox* m_NoClipCheckBox;
    wxCheckBox* m_InfiniteDoubleJumpCheckBox;
    wxCheckBox* m_NoCooldownCheckBox;
    wxCheckBox* m_InfiniteAirDashCheckBox;
    wxCheckBox* m_IgnoreUpgradeMaterialsCheckBox;
    // wxCheckBox* m_FreeCameraCheckBox;
    wxCheckBox* m_InfiniteItemUsageCheckBox;
    wxCheckBox* m_SetA2DashCheckBox;
    wxCheckBox* m_Set2BDashCheckBox;
    wxCheckBox* m_InfiniteBuffDurationCheckBox;
    wxCheckBox* m_SaveAnywhereCheckBox;
    wxCheckBox* m_InfiniteConsumableItemsCheckBox;

    // Other member functions
    void OnNoClipCheckBox(wxCommandEvent& event);
    void OnInfiniteDoubleJumpCheckBox(wxCommandEvent& event);
    void OnNoCooldownCheckBox(wxCommandEvent& event);
    void OnInfiniteAirDashCheckBox(wxCommandEvent& event);
    void OnIgnoreUpgradeMaterialsCheckBox(wxCommandEvent& event);
    // void OnFreeCameraCheckBox(wxCommandEvent& event);
    void OnInfiniteItemUsageCheckBox(wxCommandEvent& event);
    void OnSetA2DashCheckBox(wxCommandEvent& event);
    void OnSet2BDashCheckBox(wxCommandEvent& event);
    void OnInfiniteBuffDurationCheckBox(wxCommandEvent& event);
    void OnSaveAnywhereCheckBox(wxCommandEvent& event);
    void OnInfiniteConsumableItemsCheckBox(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // CHEATSPANEL_HPP