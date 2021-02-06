#include "MiscPanel.hpp"

wxBEGIN_EVENT_TABLE(MiscPanel, wxPanel)
wxEND_EVENT_TABLE()

MiscPanel::MiscPanel(wxNotebook* parent, NieRHook* hook) :wxPanel(parent, wxID_ANY)
{
	this->hook = hook;

	graphics = new wxStaticBox(this, wxID_ANY, "Graphics", wxPoint(10, 10), wxSize(335, 150), 0, wxStaticBoxNameStr);
	HUD = new wxStaticText(graphics, wxID_ANY, "HUD Opacity", wxPoint(20, 30), wxDefaultSize, 0, wxStaticTextNameStr);
	HUDOpacity = new wxSlider(graphics, wxID_ANY, 100, 1, 100, wxPoint(120, 28), wxDefaultSize, 0, wxDefaultValidator, wxSliderNameStr);
	//HUDOpacity->Bind(wxEVT_SCROLLBAR, &MiscPanel::OnSlideHUD, this);

	R = new wxStaticText(graphics, wxID_ANY, "Red", wxPoint(20, 60), wxDefaultSize, 0, wxStaticTextNameStr);
	RSlider = new wxSlider(graphics, wxID_ANY, 100, 0, 100, wxPoint(120, 58), wxDefaultSize, 0, wxDefaultValidator, wxSliderNameStr);

	G = new wxStaticText(graphics, wxID_ANY, "Green", wxPoint(20, 90), wxDefaultSize, 0, wxStaticTextNameStr);
	GSlider = new wxSlider(graphics, wxID_ANY, 100, 0, 100, wxPoint(120, 88), wxDefaultSize, 0, wxDefaultValidator, wxSliderNameStr);

	B = new wxStaticText(graphics, wxID_ANY, "Blue", wxPoint(20, 120), wxDefaultSize, 0, wxStaticTextNameStr);
	BSlider = new wxSlider(graphics, wxID_ANY, 100, 0, 100, wxPoint(120, 118), wxDefaultSize, 0, wxDefaultValidator, wxSliderNameStr);

	//sound = new wxStaticBox(this, wxID_ANY, "Sound", wxPoint(10, 180), wxSize(335, 150), 0, wxStaticBoxNameStr);

	Save = new wxButton(this, wxID_ANY, "Save Changes", wxPoint(20, 400), wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
	Save->Bind(wxEVT_BUTTON, &MiscPanel::OnSavePressed, this);

	this->SetBackgroundColour(wxColor(255, 255, 255));
}

MiscPanel::~MiscPanel()
{
}

void MiscPanel::OnSavePressed(wxCommandEvent& evt)
{
	hook->setHUDOpacity((float)HUDOpacity->GetValue() / 100);
	hook->setColor((float)RSlider->GetValue() / 100, (float)GSlider->GetValue() / 100, (float)BSlider->GetValue() / 100);
}
