// CheatsPanel.cpp
#include "CheatsPanel.hpp"
#include "defines.h"

wxBEGIN_EVENT_TABLE(CheatsPanel, wxPanel) EVT_CHECKBOX(wxID_ANY, CheatsPanel::OnNoClipCheckBox)
    EVT_CHECKBOX(wxID_ANY, CheatsPanel::OnInfiniteDoubleJumpCheckBox)
        EVT_CHECKBOX(wxID_ANY, CheatsPanel::OnNoCooldownCheckBox)
            EVT_CHECKBOX(wxID_ANY, CheatsPanel::OnInfiniteAirDashCheckBox)
                EVT_CHECKBOX(wxID_ANY, CheatsPanel::OnIgnoreUpgradeMaterialsCheckBox)
    // EVT_CHECKBOX(wxID_ANY, CheatsPanel::OnFreeCameraCheckBox)
    EVT_CHECKBOX(wxID_ANY, CheatsPanel::OnInfiniteItemUsageCheckBox)
        EVT_CHECKBOX(wxID_ANY, CheatsPanel::OnSetA2DashCheckBox)
            EVT_CHECKBOX(wxID_ANY, CheatsPanel::OnSet2BDashCheckBox)
                EVT_CHECKBOX(wxID_ANY, CheatsPanel::OnInfiniteBuffDurationCheckBox)
                    EVT_CHECKBOX(wxID_ANY, CheatsPanel::OnSaveAnywhereCheckBox)
                        EVT_CHECKBOX(wxID_ANY, CheatsPanel::OnInfiniteConsumableItemsCheckBox) wxEND_EVENT_TABLE()

                            CheatsPanel::CheatsPanel(wxWindow* parent, NieRHook* hook)
    : wxPanel(parent, wxID_ANY)
{
    this->hook = hook;

    // Checkboxes for cheats
    m_NoClipCheckBox = new wxCheckBox(this, wxID_ANY, "No Clip", wxDefaultPosition, wxDefaultSize, 0,
                                      wxDefaultValidator, wxCheckBoxNameStr);
    m_NoClipCheckBox->Bind(wxEVT_CHECKBOX, &CheatsPanel::OnNoClipCheckBox, this);
    m_InfiniteDoubleJumpCheckBox = new wxCheckBox(this, wxID_ANY, "Infinite Double Jump", wxDefaultPosition,
                                                  wxDefaultSize, 0, wxDefaultValidator, wxCheckBoxNameStr);
    m_InfiniteDoubleJumpCheckBox->Bind(wxEVT_CHECKBOX, &CheatsPanel::OnInfiniteDoubleJumpCheckBox, this);
    m_NoCooldownCheckBox = new wxCheckBox(this, wxID_ANY, "No Cooldown", wxDefaultPosition, wxDefaultSize, 0,
                                          wxDefaultValidator, wxCheckBoxNameStr);
    m_NoCooldownCheckBox->Bind(wxEVT_CHECKBOX, &CheatsPanel::OnNoCooldownCheckBox, this);
    m_InfiniteAirDashCheckBox = new wxCheckBox(this, wxID_ANY, "Infinite Air Dash", wxDefaultPosition, wxDefaultSize, 0,
                                               wxDefaultValidator, wxCheckBoxNameStr);
    m_InfiniteAirDashCheckBox->Bind(wxEVT_CHECKBOX, &CheatsPanel::OnInfiniteAirDashCheckBox, this);
    m_IgnoreUpgradeMaterialsCheckBox = new wxCheckBox(this, wxID_ANY, "Ignore Upgrade Materials", wxDefaultPosition,
                                                      wxDefaultSize, 0, wxDefaultValidator, wxCheckBoxNameStr);
    m_IgnoreUpgradeMaterialsCheckBox->Bind(wxEVT_CHECKBOX, &CheatsPanel::OnIgnoreUpgradeMaterialsCheckBox, this);
    // m_FreeCameraCheckBox = new wxCheckBox(this, wxID_ANY, "Free Camera", wxDefaultPosition, wxDefaultSize, 0,
    //                                       wxDefaultValidator, wxCheckBoxNameStr);
    // m_FreeCameraCheckBox->Bind(wxEVT_CHECKBOX, &CheatsPanel::OnFreeCameraCheckBox, this);
    m_InfiniteItemUsageCheckBox = new wxCheckBox(this, wxID_ANY, "Infinite Item Usage", wxDefaultPosition,
                                                 wxDefaultSize, 0, wxDefaultValidator, wxCheckBoxNameStr);
    m_InfiniteItemUsageCheckBox->Bind(wxEVT_CHECKBOX, &CheatsPanel::OnInfiniteItemUsageCheckBox, this);
    m_SetA2DashCheckBox = new wxCheckBox(this, wxID_ANY, "Set A2 Dash", wxDefaultPosition, wxDefaultSize, 0,
                                         wxDefaultValidator, wxCheckBoxNameStr);
    m_SetA2DashCheckBox->Bind(wxEVT_CHECKBOX, &CheatsPanel::OnSetA2DashCheckBox, this);
    m_Set2BDashCheckBox = new wxCheckBox(this, wxID_ANY, "Set 2B Dash", wxDefaultPosition, wxDefaultSize, 0,
                                         wxDefaultValidator, wxCheckBoxNameStr);
    m_Set2BDashCheckBox->Bind(wxEVT_CHECKBOX, &CheatsPanel::OnSet2BDashCheckBox, this);
    m_InfiniteBuffDurationCheckBox = new wxCheckBox(this, wxID_ANY, "Infinite Buff Duration", wxDefaultPosition,
                                                    wxDefaultSize, 0, wxDefaultValidator, wxCheckBoxNameStr);
    m_InfiniteBuffDurationCheckBox->Bind(wxEVT_CHECKBOX, &CheatsPanel::OnInfiniteBuffDurationCheckBox, this);
    m_SaveAnywhereCheckBox = new wxCheckBox(this, wxID_ANY, "Save Anywhere", wxDefaultPosition, wxDefaultSize, 0,
                                            wxDefaultValidator, wxCheckBoxNameStr);
    m_SaveAnywhereCheckBox->Bind(wxEVT_CHECKBOX, &CheatsPanel::OnSaveAnywhereCheckBox, this);
    m_InfiniteConsumableItemsCheckBox = new wxCheckBox(this, wxID_ANY, "Infinite Consumable Items", wxDefaultPosition,
                                                       wxDefaultSize, 0, wxDefaultValidator, wxCheckBoxNameStr);
    m_InfiniteConsumableItemsCheckBox->Bind(wxEVT_CHECKBOX, &CheatsPanel::OnInfiniteConsumableItemsCheckBox, this);

    // Sizer for layout
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_NoClipCheckBox, 0, wxALL, 5);
    sizer->Add(m_InfiniteDoubleJumpCheckBox, 0, wxALL, 5);
    sizer->Add(m_NoCooldownCheckBox, 0, wxALL, 5);
    sizer->Add(m_InfiniteAirDashCheckBox, 0, wxALL, 5);
    sizer->Add(m_IgnoreUpgradeMaterialsCheckBox, 0, wxALL, 5);
    // sizer->Add(m_FreeCameraCheckBox, 0, wxALL, 5);
    sizer->Add(m_InfiniteItemUsageCheckBox, 0, wxALL, 5);
    sizer->Add(m_SetA2DashCheckBox, 0, wxALL, 5);
    sizer->Add(m_Set2BDashCheckBox, 0, wxALL, 5);
    sizer->Add(m_InfiniteBuffDurationCheckBox, 0, wxALL, 5);
    sizer->Add(m_SaveAnywhereCheckBox, 0, wxALL, 5);
    sizer->Add(m_InfiniteConsumableItemsCheckBox, 0, wxALL, 5);
    hook->InfiniteDoubleJump(true);

    this->SetSizer(sizer);
    this->SetBackgroundColour(foregroundColor);
}

CheatsPanel::~CheatsPanel()
{
}

void CheatsPanel::OnNoClipCheckBox(wxCommandEvent& event)
{
    hook->NoCLip(m_NoClipCheckBox->IsChecked());
}
void CheatsPanel::OnInfiniteDoubleJumpCheckBox(wxCommandEvent& event)
{
    hook->InfiniteDoubleJump(m_InfiniteDoubleJumpCheckBox->IsChecked());
}

void CheatsPanel::OnNoCooldownCheckBox(wxCommandEvent& event)
{
    hook->NoCooldown(m_NoCooldownCheckBox->IsChecked());
}

void CheatsPanel::OnInfiniteAirDashCheckBox(wxCommandEvent& event)
{
    hook->InfiniteAirDash(m_InfiniteAirDashCheckBox->IsChecked());
}

void CheatsPanel::OnIgnoreUpgradeMaterialsCheckBox(wxCommandEvent& event)
{
    hook->IgnoreUpgradeMaterials(m_IgnoreUpgradeMaterialsCheckBox->IsChecked());
}

// void CheatsPanel::OnFreeCameraCheckBox(wxCommandEvent& event)
// {
//     hook->FreeCamera(m_FreeCameraCheckBox->IsChecked());
// }

void CheatsPanel::OnInfiniteItemUsageCheckBox(wxCommandEvent& event)
{
    hook->InfiniteItemUsage(m_InfiniteItemUsageCheckBox->IsChecked());
}

void CheatsPanel::OnSetA2DashCheckBox(wxCommandEvent& event)
{
    hook->SetA2Dash(m_SetA2DashCheckBox->IsChecked());
}

void CheatsPanel::OnSet2BDashCheckBox(wxCommandEvent& event)
{
    hook->Set2BDash(m_Set2BDashCheckBox->IsChecked());
}

void CheatsPanel::OnInfiniteBuffDurationCheckBox(wxCommandEvent& event)
{
    hook->InfiniteBuffDuration(m_InfiniteBuffDurationCheckBox->IsChecked());
}

void CheatsPanel::OnSaveAnywhereCheckBox(wxCommandEvent& event)
{
    hook->SaveAnywhere(m_SaveAnywhereCheckBox->IsChecked());
}

void CheatsPanel::OnInfiniteConsumableItemsCheckBox(wxCommandEvent& event)
{
    hook->InfiniteConsumableItems(m_InfiniteConsumableItemsCheckBox->IsChecked());
}