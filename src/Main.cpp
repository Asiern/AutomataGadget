#include "Main.h"
#include "InventoryPanel.hpp"
#include "PlayerPanel.hpp"
#include "SettingsPanel.hpp"
#include "WeaponPanel.hpp"
#include "defines.h"

wxBEGIN_EVENT_TABLE(Main, wxFrame) EVT_CLOSE(Main::OnClose) wxEND_EVENT_TABLE()

    Main::Main()
    : wxFrame(nullptr, wxID_ANY, "NieR:Automata Gadget", wxDefaultPosition, windowSize)
{
    // Icon
    this->SetIcon(wxICON(AAAA));

    // Hook Thread bind
    Bind(wxEVT_THREAD, &Main::OnThreadUpdate, this);

    // Frame style
    this->SetMaxSize(windowSize);
    this->SetMinSize(windowSize);
    this->SetBackgroundColour(backgroundColor);
    wxFont font = wxFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);

    // Initialize hook
    hook = new NieRHook();

    // Create Notebook
    notebook = new wxNotebook(this, wxID_ANY, wxPoint(margin, margin * 6), wxSize(width, 495), 0, wxNotebookNameStr);
    Player = new PlayerPanel(notebook, hook);
    Inventory = new InventoryPanel(notebook, hook);
    Weapons = new WeaponPanel(notebook, hook);
    // Settings = new SettingsPanel(notebook, hook);
    notebook->AddPage(Player, wxT("Player"), false, 0);
    notebook->AddPage(Inventory, wxT("Items"), false, 1);
    notebook->AddPage(Weapons, wxT("Weapons"), false, 2);
    // notebook->AddPage(Settings, wxT("Settings"), false, 3);

    // Timer
    m_Timer = new wxTimer();
    m_Timer->Bind(wxEVT_TIMER, &Main::OnTimer, this);

    // Hook status text
    m_hooked =
        new wxStaticText(this, wxID_ANY, "Hooked: No", wxPoint(margin, margin), wxDefaultSize, 0, wxStaticTextNameStr);
    m_hooked->SetForegroundColour(redColor);
    m_hooked->SetFont(font);
    m_status = new wxStaticText(this, wxID_ANY, "Process: None", wxPoint(margin, margin * 3), wxDefaultSize, 0,
                                wxStaticTextNameStr);
    m_status->SetFont(font);
    m_version = new wxStaticText(this, wxID_ANY, "Version: 2.1.0", wxPoint(width - margin * 6, margin), wxDefaultSize,
                                 0, wxStaticTextNameStr);
    m_version->SetFont(font);
    m_gameVer = new wxStaticText(this, wxID_ANY, "Game Version: None", wxPoint(width - margin * 9, margin * 3),
                                 wxDefaultSize, 0, wxStaticTextNameStr);
    m_gameVer->SetFont(font);

    Weapons->Enable(false);
    Player->Enable(false);
    Inventory->Enable(false);
    // Settings->Enable(false);

    StartHook();  // start hook thread
    startTimer(); // start ui thread
}

Main::~Main()
{
}

void Main::updateComponents(void)
{
    if (hook->isHooked())
    {
        m_hooked->SetForegroundColour(greenColor);
        m_hooked->SetLabelText("Hooked: Yes");
        m_status->SetLabel("Process: " + wxString::Format(wxT("%i"), hook->getProcessID()));
        switch (hook->getVersion())
        {
        case 0:
            m_gameVer->SetLabel("Game Version: ");
            break;
        case 1:
            m_gameVer->SetLabel("Game Version: 1.0.1");
            break;
        case 2:
            m_gameVer->SetLabel("Game Version: 1.0.2");
            break;
        }
        if (hook->isSavefileLoaded())
            enableUI();
        else
            disableUI();
    }
    else
    {
        m_hooked->SetForegroundColour(redColor);
        m_hooked->SetLabelText("Hooked: No");
        m_gameVer->SetLabel("Game Version: None");
        m_status->SetLabel("Process: None");
        disableUI();
    }
}

void Main::startTimer(void)
{
    if (!m_Timer->IsRunning())
    {
        m_Timer->Start(1000, wxTIMER_CONTINUOUS);
    }
    else
    {
        wxLogError("Timer already running");
        return;
    }
}

void Main::stopTimer(void)
{
    if (m_Timer->IsRunning())
    {
        m_Timer->Stop();
    }
    else
    {
        wxLogError("Timer not running");
        return;
    }
}

// Timer to update the UI thread
void Main::OnTimer(wxTimerEvent&)
{
    updateComponents();
}

void Main::OnThreadUpdate(wxThreadEvent& evt)
{
}

void Main::StartHook()
{
    // Start Hook thread
    if (CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR)
    {
        wxLogError("Could not create the Hook thread");
        return;
    }
    if (GetThread()->Run() != wxTHREAD_NO_ERROR)
    {
        wxLogError("Could not run the Hook thread");
        return;
    }
}

void Main::disableUI(void)
{
    Weapons->Enable(false);
    Player->Enable(false);
    Inventory->Enable(false);
    // Settings->Enable(false);
}

void Main::enableUI(void)
{
    Weapons->Enable(true);
    Player->Enable(true);
    Inventory->Enable(true);
    // Settings->Enable(true);
}

wxThread::ExitCode Main::Entry()
{
    while (!GetThread()->TestDestroy())
    {
        hook->hookStatus(); // Update status
        if (!hook->isHooked())
        {
            hook->start(); // Start hook
        }
        else
        {
            hook->update(); // Update hook
        }
    }
    return (wxThread::ExitCode)0;
}

void Main::OnClose(wxCloseEvent&)
{
    hook->stop();
    m_Timer->Stop();
    if (hook->isHooked())
    {
        GetThread()->TestDestroy();
        GetThread()->Delete();
    }
    delete m_Timer;
    delete hook;
    Destroy();
}
