#include "PlayerPanel.hpp"
#include "defines.h"

wxBEGIN_EVENT_TABLE(PlayerPanel, wxPanel) wxEND_EVENT_TABLE()

    PlayerPanel::PlayerPanel(wxNotebook* parent, NieRHook* hook)
    : wxPanel(parent, wxID_ANY)
{
    this->hook = hook;

    // Timer
    m_Timer = new wxTimer();
    m_Timer->Bind(wxEVT_TIMER, &PlayerPanel::OnTimer, this);

    // Status
    m_StatsBox = new wxStaticBox(this, wxID_ANY, "Status", wxPoint(margin, margin), wxSize(width - 30, 90), 1,
                                 wxStaticBoxNameStr);
    m_Health = new wxStaticText(this, wxID_ANY, "Health: 0/0", wxPoint(margin * 3, margin + 30), wxDefaultSize, 0,
                                wxStaticTextNameStr);
    m_Level = new wxStaticText(this, wxID_ANY, "Level: 0", wxPoint(margin + (width - 2 * margin) / 2, margin + 30),
                               wxDefaultSize, 0, wxStaticTextNameStr);
    m_Funds = new wxStaticText(this, wxID_ANY, "Funds(G): 0", wxPoint(margin + (width - 2 * margin) / 2, margin + 60),
                               wxDefaultSize, 0, wxStaticTextNameStr);
    m_EXP = new wxStaticText(this, wxID_ANY, "EXP: 0", wxPoint(margin * 3, margin + 60), wxDefaultSize, 0,
                             wxStaticTextNameStr);

    // Cheats
    m_CheatsBox =
        new wxStaticBox(this, wxID_ANY, "Cheats", wxPoint(margin, 110), wxSize(width - 30, 130), 1, wxStaticBoxNameStr);
    m_NoClip = new wxCheckBox(this, wxID_ANY, "No Clip", wxPoint(3 * margin, 140), wxDefaultSize, 0, wxDefaultValidator,
                              wxCheckBoxNameStr);
    m_NoClip->Bind(wxEVT_CHECKBOX, &PlayerPanel::NoClip, this);
    m_SpeedHack = new wxCheckBox(this, wxID_ANY, "2x Speed", wxPoint(3 * margin, 170), wxDefaultSize, 0,
                                 wxDefaultValidator, wxCheckBoxNameStr);
    m_SpeedHack->Bind(wxEVT_CHECKBOX, &PlayerPanel::SpeedHack, this);
    m_InfDoubleJump =
        new wxCheckBox(this, wxID_ANY, "Infinite Double Jump", wxPoint(margin + (width - 2 * margin) / 2, 140),
                       wxDefaultSize, 0, wxDefaultValidator, wxCheckBoxNameStr);
    m_InfDoubleJump->Bind(wxEVT_CHECKBOX, &PlayerPanel::InfDoubleJump, this);
    m_NoCooldown = new wxCheckBox(this, wxID_ANY, "No Cooldown", wxPoint(3 * margin, 200), wxDefaultSize, 0,
                                  wxDefaultValidator, wxCheckBoxNameStr);
    m_NoCooldown->Bind(wxEVT_CHECKBOX, &PlayerPanel::NoCooldown, this);
    m_InfAirDash = new wxCheckBox(this, wxID_ANY, "Infinite Air Dash", wxPoint(margin + (width - 2 * margin) / 2, 170),
                                  wxDefaultSize, 0, wxDefaultValidator, wxCheckBoxNameStr);
    m_InfAirDash->Bind(wxEVT_CHECKBOX, &PlayerPanel::InfAirDash, this);
    m_IgnoreUpgradeMaterials =
        new wxCheckBox(this, wxID_ANY, "Ignore Upgrade Materials", wxPoint(margin + (width - 2 * margin) / 2, 200),
                       wxDefaultSize, 0, wxDefaultValidator, wxCheckBoxNameStr);
    m_IgnoreUpgradeMaterials->Bind(wxEVT_CHECKBOX, &PlayerPanel::IgnoreUpgradeMaterials, this);

    // Position
    wxSize TextCtrlSize = wxSize(80, 20);
    m_PositionBox = new wxStaticBox(this, wxID_ANY, "Position", wxPoint(margin, 250), wxSize(width - 30, 200), 1,
                                    wxStaticBoxNameStr);
    m_XText = new wxStaticText(this, wxID_ANY, "X", wxPoint(20, 303), wxDefaultSize, 0, wxStaticTextNameStr);
    m_YText = new wxStaticText(this, wxID_ANY, "Y", wxPoint(20, 338), wxDefaultSize, 0, wxStaticTextNameStr);
    m_ZText = new wxStaticText(this, wxID_ANY, "Z", wxPoint(20, 373), wxDefaultSize, 0, wxStaticTextNameStr);
    m_XposTextCtrl = new wxTextCtrl(this, wxID_ANY, "0.000000", wxPoint(4 * margin, 300), TextCtrlSize, 0,
                                    wxDefaultValidator, wxTextCtrlNameStr);
    m_YposTextCtrl = new wxTextCtrl(this, wxID_ANY, "0.000000", wxPoint(4 * margin, 335), TextCtrlSize, 0,
                                    wxDefaultValidator, wxTextCtrlNameStr);
    m_ZposTextCtrl = new wxTextCtrl(this, wxID_ANY, "0.000000", wxPoint(4 * margin, 370), TextCtrlSize, 0,
                                    wxDefaultValidator, wxTextCtrlNameStr);
    m_XposStoredTextCtrl = new wxTextCtrl(this, wxID_ANY, "0.000000", wxPoint(width / 2 - 4 * margin, 300),
                                          TextCtrlSize, 0, wxDefaultValidator, wxTextCtrlNameStr);
    m_YposStoredTextCtrl = new wxTextCtrl(this, wxID_ANY, "0.000000", wxPoint(width / 2 - 4 * margin, 335),
                                          TextCtrlSize, 0, wxDefaultValidator, wxTextCtrlNameStr);
    m_ZposStoredTextCtrl = new wxTextCtrl(this, wxID_ANY, "0.000000", wxPoint(width / 2 - 4 * margin, 370),
                                          TextCtrlSize, 0, wxDefaultValidator, wxTextCtrlNameStr);
    m_CurrentPosText =
        new wxStaticText(this, wxID_ANY, "Current", wxPoint(4 * margin, 280), wxDefaultSize, 0, wxStaticTextNameStr);
    m_StoredPosText = new wxStaticText(this, wxID_ANY, "Stored", wxPoint(width / 2 - 4 * margin, 280), wxDefaultSize, 0,
                                       wxStaticTextNameStr);
    m_StorePosition = new wxButton(this, wxID_ANY, "Store", wxPoint(240, 300), wxSize(90, 25), 1, wxDefaultValidator,
                                   wxStaticBoxNameStr);
    m_StorePosition->Bind(wxEVT_BUTTON, &PlayerPanel::StorePosition, this);
    m_RestorePosition = new wxButton(this, wxID_ANY, "Restore", wxPoint(240, 335), wxSize(90, 25), 1,
                                     wxDefaultValidator, wxStaticBoxNameStr);
    m_RestorePosition->Bind(wxEVT_BUTTON, &PlayerPanel::RestorePosition, this);
    m_WarpButton = new wxButton(this, wxID_ANY, "Warp", wxPoint(240, 410), wxSize(90, 25), 1, wxDefaultValidator,
                                wxStaticBoxNameStr);
    m_WarpButton->Bind(wxEVT_BUTTON, &PlayerPanel::onWarpCLicked, this);
    wxArrayString* Locations = new wxArrayString();
    Locations->Add("Amusement (Beauvoir)", 1);
    Locations->Add("Amusement (Coaster)", 1);
    Locations->Add("Amusement (Entrance)", 1);
    Locations->Add("Amusement (Sewers)", 1);
    Locations->Add("City Ruins (Center)", 1);
    Locations->Add("City Ruins (Cave)", 1);
    Locations->Add("City Ruins (Engels Fight)", 1);
    Locations->Add("City Ruins (Near Factory)", 1);
    Locations->Add("City Ruins (Tower)", 1);
    Locations->Add("Copied City", 1);
    Locations->Add("Desert Housing (Adam Pit)", 1);
    Locations->Add("Desert Housing (Complex)", 1);
    Locations->Add("Desert Zone (Entrance)", 1);
    Locations->Add("Desert Zone (Merchant)", 1);
    Locations->Add("Emil's (House)", 1);
    Locations->Add("Emil's (Memories)", 1);
    Locations->Add("Emil's (Underground Cave)", 1);
    Locations->Add("Factory (Entrance)", 1);
    Locations->Add("Factory (Marx 1)", 1);
    Locations->Add("Factory (So-Shi)", 1);
    Locations->Add("Flooded City", 1);
    Locations->Add("Flooded City (Sewers)", 1);
    Locations->Add("Forest Zone (A2)", 1);
    Locations->Add("Forest Zone (Abandoned Mall)", 1);
    Locations->Add("Forest Zone (Castle Entrance)", 1);
    Locations->Add("Forest Zone (Masamune)", 1);
    Locations->Add("Forest Zone (Rainbow Road)", 1);
    Locations->Add("Machine Village", 1);
    Locations->Add("Resistance Camp (Back)", 1);
    Locations->Add("Resistance Camp (Entrance)", 1);
    Locations->Add("Underground Cave (Boss)", 1);
    Locations->Add("Underground Cave (Elevator)", 1);
    Locations->Add("Underground Cave (Entrance)", 1);
    m_WarpComboBox =
        new wxComboBox(this, wxID_ANY, "", wxPoint(4 * margin, 410), wxSize((width - (9 * margin)) * 2 / 3, 20),
                       *Locations, 0, wxDefaultValidator, wxComboBoxNameStr);
    delete Locations;

    this->SetBackgroundColour(wxColor(255, 255, 255));
    m_Timer->Start(1000, wxTIMER_CONTINUOUS);
}

PlayerPanel::~PlayerPanel()
{
    m_Timer->Stop();
    delete m_Timer;
}

void PlayerPanel::OnTimer(wxTimerEvent&)
{
    if (hook->isHooked())
    {
        // Player
        m_Level->SetLabel("Level: " + wxString::Format(wxT("%i"), hook->getLevel()));
        m_Health->SetLabel("Health: " + wxString::Format(wxT("%i"), hook->getHealth()) + "/" +
                           wxString::Format(wxT("%i"), hook->getMaxHealth()));
        m_Funds->SetLabel("Funds(G): " + wxString::Format(wxT("%i"), hook->getFunds()));
        m_EXP->SetLabel("EXP: " + wxString::Format(wxT("%i"), hook->getEXP()));
        // Position
        m_XposTextCtrl->SetLabel(wxString::Format(wxT("%f"), hook->getXPosition()));
        m_YposTextCtrl->SetLabel(wxString::Format(wxT("%f"), hook->getYPosition()));
        m_ZposTextCtrl->SetLabel(wxString::Format(wxT("%f"), hook->getZPosition()));
        switch (hook->getVersion())
        {
        case VER_0_0_1:
            m_WarpButton->Enable(true);
            m_WarpComboBox->Enable(true);
            m_RestorePosition->Enable(true);
            m_NoClip->Enable(true);
            m_IgnoreUpgradeMaterials->Enable(true);
            m_SpeedHack->Enable(true);
            m_NoCooldown->Enable(true);
            break;
        case VER_0_0_2:
            m_WarpButton->Enable(false);
            m_WarpComboBox->Enable(false);
            m_RestorePosition->Enable(false);
            m_NoClip->Enable(false);
            m_IgnoreUpgradeMaterials->Enable(false);
            m_SpeedHack->Enable(false);
            m_NoCooldown->Enable(false);
            break;
        }
    }
    else
    {
    }
}

void PlayerPanel::SpeedHack(wxCommandEvent& evt)
{
    if (m_SpeedHack->IsChecked())
    {
        hook->setGameSpeed(2);
    }
    else
    {
        hook->setGameSpeed(1);
    }
}

void PlayerPanel::NoClip(wxCommandEvent& evt)
{
    if (m_NoClip->IsChecked())
    {
        hook->NoCLip(true);
    }
    else
    {
        hook->NoCLip(false);
    }
}

void PlayerPanel::InfDoubleJump(wxCommandEvent& evt)
{
    if (m_InfDoubleJump->IsChecked())
    {
        hook->InfiniteDoubleJump(true);
    }
    else
    {
        hook->InfiniteDoubleJump(false);
    }
}

void PlayerPanel::NoCooldown(wxCommandEvent& evt)
{
    if (m_NoCooldown->IsChecked())
    {
        hook->NoCooldown(true);
    }
    else
    {
        hook->NoCooldown(false);
    }
}

void PlayerPanel::InfAirDash(wxCommandEvent& evt)
{
    if (m_InfAirDash->IsChecked())
    {
        hook->InfiniteAirDash(true);
    }
    else
    {
        hook->InfiniteAirDash(false);
    }
}

void PlayerPanel::IgnoreUpgradeMaterials(wxCommandEvent& evt)
{
    if (m_IgnoreUpgradeMaterials->IsChecked())
    {
        hook->IgnoreUpgradeMaterials(true);
    }
    else
    {
        hook->IgnoreUpgradeMaterials(false);
    }
}

void PlayerPanel::StorePosition(wxCommandEvent& evt)
{
    m_XposStoredTextCtrl->SetValue(wxString::Format(wxT("%f"), hook->getXPosition()));
    m_YposStoredTextCtrl->SetValue(wxString::Format(wxT("%f"), hook->getYPosition()));
    m_ZposStoredTextCtrl->SetValue(wxString::Format(wxT("%f"), hook->getZPosition()));
    this->setStoredPosition(hook->getXPosition(), hook->getYPosition(), hook->getZPosition());
}

void PlayerPanel::setStoredPosition(float X, float Y, float Z)
{
    this->StoredX = X;
    this->StoredY = Y;
    this->StoredZ = Z;
}

void PlayerPanel::RestorePosition(wxCommandEvent& evt)
{
    hook->setPosition(this->StoredX, this->StoredY, this->StoredZ);
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

void PlayerPanel::onWarpCLicked(wxCommandEvent& evt)
{
    switch (str2int(m_WarpComboBox->GetValue()))
    {
    case str2int("Amusement (Beauvoir)"):
        hook->setPosition(796.61, 21.72, 295.11);
        break;
    case str2int("Amusement (Coaster)"):
        hook->setPosition(756.55, 13.49, 429.83);
        break;
    case str2int("Amusement (Entrance)"):
        hook->setPosition(396.0, -0.18, 294.48);
        break;
    case str2int("Amusement (Sewers)"):
        hook->setPosition(314.30, 0.07, 265.88);
        break;
    case str2int("City Ruins (Cave)"):
        hook->setPosition(182.69, -67.22, 359.33);
        break;
    case str2int("City Ruins (Center)"):
        hook->setPosition(1.15, 3.32, 341.3);
        break;
    case str2int("City Ruins (Engels Fight)"):
        hook->setPosition(-40.72, 52.99, 708.13);
        break;
    case str2int("City Ruins (Near Factory)"):
        hook->setPosition(-69.09, 21.94, 520.71);
        break;
    case str2int("City Ruins (Tower)"):
        hook->setPosition(106.39, 0.8, 98.1);
        break;
    case str2int("Copied City"):
        hook->setPosition(317.2, -116.99, 404.64);
        break;
    case str2int("Desert Housing (Adam Pit)"):
        hook->setPosition(63.62, -84.04, -539.75);
        break;
    case str2int("Desert Housing (Complex)"):
        hook->setPosition(-160.44, -81.5, -798.63);
        break;
    case str2int("Desert Zone (Entrance)"):
        hook->setPosition(-623.32, 6.36, -252.24);
        break;
    case str2int("Desert Zone (Merchant)"):
        hook->setPosition(-162.62, 12.01, 19.76);
        break;
    case str2int("Emil's (House)"):
        hook->setPosition(317.09, -251.37, 390.9);
        break;
    case str2int("Emil's (Memories)"):
        break;
    case str2int("Emil's (Underground Cave)"):
        hook->setPosition(261.23, -10.02, 358.9);
        break;
    case str2int("Factory (Entrance)"):
        hook->setPosition(-446.86, 4.8, 657.10);
        break;
    case str2int("Factory (Marx 1)"):
        hook->setPosition(-644.04, 0, 441.88);
        break;
    case str2int("Factory (So-Shi)"):
        break;
    case str2int("Flooded City"):
        hook->setPosition(389.63, -74.65, 832.08);
        break;
    case str2int("Flooded City (Sewers)"):
        hook->setPosition(473.77, -63.24, 623.68);
        break;
    case str2int("Forest Zone (A2)"):
        hook->setPosition(924.65, 26.05, -333.15);
        break;
    case str2int("Forest Zone (Abandoned Mall)"):
        hook->setPosition(156.46, 1.34, -112.90);
        break;
    case str2int("Forest Zone (Castle Entrance)"):
        hook->setPosition(818.07, -36.3, -272.39);
        break;
    case str2int("Forest Zone (Masamune)"):
        hook->setPosition(1001.20, 3.60, -378.19);
        break;
    case str2int("Forest Zone (Rainbow Road)"):
        hook->setPosition(675.6, -47.04, -254.78);
        break;
    case str2int("Machine Village"):
        hook->setPosition(428.4, 11.03, -34.63);
        break;
    case str2int("Resistance Camp (Back)"):
        hook->setPosition(341.26, 9.48, 678.23);
        break;
    case str2int("Resistance Camp (Entrance)"):
        hook->setPosition(224.4, 10.27, 594.27);
        break;
    case str2int("Underground Cave (Boss)"):
        hook->setPosition(398.7, -99.22, 348.41);
        break;
    case str2int("Underground Cave (Elevator)"):
        hook->setPosition(315.05, -105.59, 406.57);
        break;
    case str2int("Underground Cave (Entrance)"):
        hook->setPosition(213.39, -105.95, 352.27);
        break;
    default:
        wxMessageBox("Could not find location", wxMessageBoxCaptionStr, 0, this, -1, -1);
        break;
    }
}
