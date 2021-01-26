#include "Main.h"
#include "resource.h"

wxBEGIN_EVENT_TABLE(Main, wxFrame)
EVT_CLOSE(Main::OnClose)
wxEND_EVENT_TABLE()

Main::Main() : wxFrame(nullptr, wxID_ANY, "NieR:Automata Gadget", wxPoint(30, 30), wxSize(400, 600))
{
	//Hook Thread bind
	Bind(wxEVT_THREAD, &Main::OnThreadUpdate, this);

	//Frame style
	this->SetIcon(wxICON(IDI_ICON1));
	this->SetMaxSize(wxSize(400, 600));
	this->SetMinSize(wxSize(400, 600));
	this->SetBackgroundColour(wxColor(242, 242, 242));
	wxFont font = wxFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);

	//Const sizes
	const int margin = 10;
	const int width = 365;

	//Create Notebook
	notebook = new wxNotebook(this, wxID_ANY, wxPoint(margin, margin * 6), wxSize(width, 485), 0, wxNotebookNameStr);

	//Timer
	m_Timer = new wxTimer();
	m_Timer->Bind(wxEVT_TIMER, &Main::OnTimer, this);

	//Hook status text
	m_hooked = new wxStaticText(this, wxID_ANY, "Hooked: No", wxPoint(margin, margin), wxDefaultSize, 0, wxStaticTextNameStr);
	m_hooked->SetForegroundColour(wxColor(244, 67, 54));
	m_hooked->SetFont(font);
	m_status = new wxStaticText(this, wxID_ANY, "Process: None", wxPoint(margin, margin * 3), wxDefaultSize, 0, wxStaticTextNameStr);
	m_status->SetFont(font);
	m_version = new wxStaticText(this, wxID_ANY, "Version: 1.0.1", wxPoint(width - margin * 6, margin), wxDefaultSize, 0, wxStaticTextNameStr);
	m_version->SetFont(font);
	/*m_github = new wxStaticText(this, wxID_ANY, "github.com/Asiern", wxPoint(width - margin * 8, margin * 3), wxDefaultSize, 0, wxStaticTextNameStr);
	m_github->SetFont(font);*/

	//PLAYER TAB
	PlayerTab = new wxPanel(notebook, wxID_ANY);
	notebook->AddPage(PlayerTab, wxT("Player"), true, 0);

	//Status
	m_StatsBox = new wxStaticBox(PlayerTab, wxID_ANY, "Status", wxPoint(margin, margin), wxSize(width - 30, 90), 1, wxStaticBoxNameStr);
	m_Health = new wxStaticText(PlayerTab, wxID_ANY, "Health: 0/0", wxPoint(margin * 3, margin + 30), wxDefaultSize, 0, wxStaticTextNameStr);
	m_Level = new wxStaticText(PlayerTab, wxID_ANY, "Level: 0", wxPoint(margin + (width - 2 * margin) / 2, margin + 30), wxDefaultSize, 0, wxStaticTextNameStr);
	m_Funds = new wxStaticText(PlayerTab, wxID_ANY, "Funds(G): 0", wxPoint(margin + (width - 2 * margin) / 2, margin + 60), wxDefaultSize, 0, wxStaticTextNameStr);
	m_EXP = new wxStaticText(PlayerTab, wxID_ANY, "EXP: 0", wxPoint(margin * 3, margin + 60), wxDefaultSize, 0, wxStaticTextNameStr);

	//Cheats
	m_CheatsBox = new wxStaticBox(PlayerTab, wxID_ANY, "Cheats", wxPoint(margin, 110), wxSize(width - 30, 130), 1, wxStaticBoxNameStr);
	m_NoClip = new wxCheckBox(PlayerTab, wxID_ANY, "No Clip", wxPoint(3 * margin, 140), wxDefaultSize, 0, wxDefaultValidator, wxCheckBoxNameStr);
	m_NoClip->Bind(wxEVT_CHECKBOX, &Main::NoClip, this);
	m_SpeedHack = new wxCheckBox(PlayerTab, wxID_ANY, "2x Speed", wxPoint(3 * margin, 170), wxDefaultSize, 0, wxDefaultValidator, wxCheckBoxNameStr);
	m_SpeedHack->Bind(wxEVT_CHECKBOX, &Main::SpeedHack, this);
	m_InfDoubleJump = new wxCheckBox(PlayerTab, wxID_ANY, "Infinite Double Jump", wxPoint(margin + (width - 2 * margin) / 2, 140), wxDefaultSize, 0, wxDefaultValidator, wxCheckBoxNameStr);
	m_InfDoubleJump->Bind(wxEVT_CHECKBOX, &Main::InfDoubleJump, this);
	m_NoCooldown = new wxCheckBox(PlayerTab, wxID_ANY, "No Cooldown", wxPoint(3 * margin, 200), wxDefaultSize, 0, wxDefaultValidator, wxCheckBoxNameStr);
	m_NoCooldown->Bind(wxEVT_CHECKBOX, &Main::NoCooldown, this);
	m_InfAirDash = new wxCheckBox(PlayerTab, wxID_ANY, "Infinite Air Dash", wxPoint(margin + (width - 2 * margin) / 2, 170), wxDefaultSize, 0, wxDefaultValidator, wxCheckBoxNameStr);
	m_InfAirDash->Bind(wxEVT_CHECKBOX, &Main::InfAirDash, this);
	m_IgnoreUpgradeMaterials = new wxCheckBox(PlayerTab, wxID_ANY, "Ignore Upgrade Materials", wxPoint(margin + (width - 2 * margin) / 2, 200), wxDefaultSize, 0, wxDefaultValidator, wxCheckBoxNameStr);
	m_IgnoreUpgradeMaterials->Bind(wxEVT_CHECKBOX, &Main::IgnoreUpgradeMaterials, this);

	//Position
	wxSize TextCtrlSize = wxSize(80, 20);
	m_PositionBox = new wxStaticBox(PlayerTab, wxID_ANY, "Position", wxPoint(margin, 250), wxSize(width - 30, 200), 1, wxStaticBoxNameStr);
	m_XText = new wxStaticText(PlayerTab, wxID_ANY, "X", wxPoint(20, 303), wxDefaultSize, 0, wxStaticTextNameStr);
	m_YText = new wxStaticText(PlayerTab, wxID_ANY, "Y", wxPoint(20, 338), wxDefaultSize, 0, wxStaticTextNameStr);
	m_ZText = new wxStaticText(PlayerTab, wxID_ANY, "Z", wxPoint(20, 373), wxDefaultSize, 0, wxStaticTextNameStr);
	m_XposTextCtrl = new wxTextCtrl(PlayerTab, wxID_ANY, "0.000000", wxPoint(4 * margin, 300), TextCtrlSize, 0, wxDefaultValidator, wxTextCtrlNameStr);
	m_YposTextCtrl = new wxTextCtrl(PlayerTab, wxID_ANY, "0.000000", wxPoint(4 * margin, 335), TextCtrlSize, 0, wxDefaultValidator, wxTextCtrlNameStr);
	m_ZposTextCtrl = new wxTextCtrl(PlayerTab, wxID_ANY, "0.000000", wxPoint(4 * margin, 370), TextCtrlSize, 0, wxDefaultValidator, wxTextCtrlNameStr);
	m_XposStoredTextCtrl = new wxTextCtrl(PlayerTab, wxID_ANY, "0.000000", wxPoint(width / 2 - 4 * margin, 300), TextCtrlSize, 0, wxDefaultValidator, wxTextCtrlNameStr);
	m_YposStoredTextCtrl = new wxTextCtrl(PlayerTab, wxID_ANY, "0.000000", wxPoint(width / 2 - 4 * margin, 335), TextCtrlSize, 0, wxDefaultValidator, wxTextCtrlNameStr);
	m_ZposStoredTextCtrl = new wxTextCtrl(PlayerTab, wxID_ANY, "0.000000", wxPoint(width / 2 - 4 * margin, 370), TextCtrlSize, 0, wxDefaultValidator, wxTextCtrlNameStr);
	m_CurrentPosText = new wxStaticText(PlayerTab, wxID_ANY, "Current", wxPoint(4 * margin, 280), wxDefaultSize, 0, wxStaticTextNameStr);
	m_StoredPosText = new wxStaticText(PlayerTab, wxID_ANY, "Stored", wxPoint(width / 2 - 4 * margin, 280), wxDefaultSize, 0, wxStaticTextNameStr);
	m_StorePosition = new wxButton(PlayerTab, wxID_ANY, "Store", wxPoint(240, 300), wxSize(90, 25), 1, wxDefaultValidator, wxStaticBoxNameStr);
	m_StorePosition->Bind(wxEVT_BUTTON, &Main::StorePosition, this);
	m_RestorePosition = new wxButton(PlayerTab, wxID_ANY, "Restore", wxPoint(240, 335), wxSize(90, 25), 1, wxDefaultValidator, wxStaticBoxNameStr);
	m_RestorePosition->Bind(wxEVT_BUTTON, &Main::RestorePosition, this);
	m_WarpButton = new wxButton(PlayerTab, wxID_ANY, "Warp", wxPoint(240, 410), wxSize(90, 25), 1, wxDefaultValidator, wxStaticBoxNameStr);
	m_WarpButton->Bind(wxEVT_BUTTON, &Main::onWarpCLicked, this);
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
	m_WarpComboBox = new wxComboBox(PlayerTab, wxID_ANY, "", wxPoint(2 * margin, 410), wxSize((width - (6 * margin)) * 2 / 3, 20), *Locations, 0, wxDefaultValidator, wxComboBoxNameStr);

	delete Locations;

	////ITEMS TAB
	//ItemsTab = new wxPanel(notebook, wxID_ANY);
	//notebook->AddPage(ItemsTab, wxT("Items"), false, 1);

	////ITEMS
	//wxArrayString* ItemCategories = new wxArrayString();
	//ItemCategories->Add("Restorative", 1);
	//ItemCategories->Add("Enhancement", 1);
	//ItemCategories->Add("Support", 1);
	//ItemCategories->Add("Materials", 1);
	//ItemCategories->Add("Key", 1);

	//m_ItemCategoryComboBox = new wxComboBox(ItemsTab, wxID_ANY, "", wxPoint(2 * margin, 2 * margin), wxSize(width - (5 * margin), 25), *ItemCategories, 0, wxDefaultValidator, wxComboBoxNameStr);

	//m_Items = new wxListCtrl(ItemsTab, wxID_ANY, wxPoint(2 * margin, 60), wxSize(width - (5 * margin), 300), wxLC_ICON, wxDefaultValidator, wxListCtrlNameStr);

	//delete ItemCategories;

	//Tab styles
	PlayerTab->SetBackgroundColour(wxColor(255, 255, 255));
	//ItemsTab->SetBackgroundColour(wxColor(255, 255, 255));

	toggleComponents(false);//disable components

	//Initialize hook
	hook = new NieRHook();
	StartHook();//start hook thread
	startTimer();//start ui thread
}

void Main::setStoredPosition(float X, float Y, float Z)
{
	this->StoredX = X;
	this->StoredY = Y;
	this->StoredZ = Z;
}

void Main::toggleComponents(bool enabled)
{
	//Status
	m_StatsBox->Enable(enabled);
	m_Health->Enable(enabled);
	m_EXP->Enable(enabled);
	m_Funds->Enable(enabled);
	m_Level->Enable(enabled);

	//Cheats
	m_CheatsBox->Enable(enabled);
	m_NoClip->Enable(enabled);
	m_IgnoreUpgradeMaterials->Enable(enabled);
	m_InfAirDash->Enable(enabled);
	m_InfDoubleJump->Enable(enabled);
	m_SpeedHack->Enable(enabled);
	m_NoCooldown->Enable(enabled);

	//Position
	m_PositionBox->Enable(enabled);
	m_WarpButton->Enable(enabled);
	m_WarpComboBox->Enable(enabled);
	m_StorePosition->Enable(enabled);
	m_RestorePosition->Enable(enabled);
	m_XposTextCtrl->Enable(enabled);
	m_YposTextCtrl->Enable(enabled);
	m_ZposTextCtrl->Enable(enabled);
	m_XposStoredTextCtrl->Enable(enabled);
	m_YposStoredTextCtrl->Enable(enabled);
	m_ZposStoredTextCtrl->Enable(enabled);
	m_CurrentPosText->Enable(enabled);
	m_StoredPosText->Enable(enabled);
	m_XText->Enable(enabled);
	m_YText->Enable(enabled);
	m_ZText->Enable(enabled);
}


Main::~Main()
{
}

void Main::updateComponents(void)
{
	if (hook->isHooked()) {
		toggleComponents(true);
		//Status
		m_hooked->SetForegroundColour(wxColor(76, 175, 80));
		m_hooked->SetLabelText("Hooked: Yes");
		m_status->SetLabel("Process: " + wxString::Format(wxT("%i"), hook->getProcessID()));
		//Player
		m_Level->SetLabel("Level: " + wxString::Format(wxT("%i"), hook->getLevel()));
		m_Health->SetLabel("Health: " + wxString::Format(wxT("%i"), hook->getHealth()) + "/" + wxString::Format(wxT("%i"), hook->getMaxHealth()));
		m_Funds->SetLabel("Funds(G): " + wxString::Format(wxT("%i"), hook->getFunds()));
		m_EXP->SetLabel("EXP: " + wxString::Format(wxT("%i"), hook->getEXP()));
		//Position
		m_XposTextCtrl->SetLabel(wxString::Format(wxT("%f"), hook->getXPosition()));
		m_YposTextCtrl->SetLabel(wxString::Format(wxT("%f"), hook->getYPosition()));
		m_ZposTextCtrl->SetLabel(wxString::Format(wxT("%f"), hook->getZPosition()));
	}
	else {
		toggleComponents(false);
		m_hooked->SetForegroundColour(wxColor(244, 67, 54));
		m_hooked->SetLabelText("Hooked: No");
		m_status->SetLabel("Process: None");
	}
}

void Main::startTimer(void)
{
	if (!m_Timer->IsRunning()) {
		m_Timer->Start(1000, wxTIMER_CONTINUOUS);
	}
	else {
		wxLogError("Timer already running");
		return;
	}
}

void Main::stopTimer(void)
{
	if (m_Timer->IsRunning()) {
		m_Timer->Stop();
	}
	else {
		wxLogError("Timer not running");
		return;
	}
}

//Timer to update the UI thread
void Main::OnTimer(wxTimerEvent&)
{
	updateComponents();
}
constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}
void Main::onWarpCLicked(wxCommandEvent& evt)
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

void Main::SpeedHack(wxCommandEvent& evt)
{
	if (m_SpeedHack->IsChecked()) {
		hook->setGameSpeed(2);
	}
	else {
		hook->setGameSpeed(1);
	}
}

void Main::NoClip(wxCommandEvent& evt)
{
	if (m_NoClip->IsChecked()) {
		hook->NoCLip(true);
	}
	else {
		hook->NoCLip(false);
	}
}

void Main::InfDoubleJump(wxCommandEvent& evt)
{
	if (m_InfDoubleJump->IsChecked()) {
		hook->InfiniteDoubleJump(true);
	}
	else {
		hook->InfiniteDoubleJump(false);
	}
}

void Main::NoCooldown(wxCommandEvent& evt)
{
	if (m_NoCooldown->IsChecked()) {
		hook->NoCooldown(true);
	}
	else {
		hook->NoCooldown(false);
	}
}

void Main::InfAirDash(wxCommandEvent& evt)
{
	if (m_InfAirDash->IsChecked()) {
		hook->InfiniteAirDash(true);
	}
	else {
		hook->InfiniteAirDash(false);
	}
}

void Main::IgnoreUpgradeMaterials(wxCommandEvent& evt)
{
	if (m_IgnoreUpgradeMaterials->IsChecked()) {
		hook->IgnoreUpgradeMaterials(true);
	}
	else {
		hook->IgnoreUpgradeMaterials(false);
	}
}

void Main::OnThreadUpdate(wxThreadEvent& evt)
{
}

void Main::StartHook()
{
	//Start Hook thread
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
void Main::StorePosition(wxCommandEvent& evt)
{
	m_XposStoredTextCtrl->SetValue(wxString::Format(wxT("%f"), hook->getXPosition()));
	m_YposStoredTextCtrl->SetValue(wxString::Format(wxT("%f"), hook->getYPosition()));
	m_ZposStoredTextCtrl->SetValue(wxString::Format(wxT("%f"), hook->getZPosition()));
	this->setStoredPosition(hook->getXPosition(), hook->getYPosition(), hook->getZPosition());
}
void Main::RestorePosition(wxCommandEvent& evt)
{
	hook->setPosition(this->StoredX, this->StoredY, this->StoredZ);
}
wxThread::ExitCode Main::Entry()
{
	while (!GetThread()->TestDestroy())
	{
		hook->hookStatus(); //Update status
		if (!hook->isHooked()) {
			hook->start();//Start hook
		}
		else {
			hook->update(); //Update hook
		}
	}
	return (wxThread::ExitCode)0;
}

void Main::OnClose(wxCloseEvent&)
{
	m_Timer->Stop();
	if (hook->isHooked()) {
		hook->stop();
		GetThread()->TestDestroy();
		GetThread()->Delete();
	}
	delete m_Timer;
	delete hook;
	Destroy();
}

