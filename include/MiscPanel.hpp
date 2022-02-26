#pragma once
#include "NierHook.hpp"
#include <wx/notebook.h>
#include <wx/wx.h>
class MiscPanel : public wxPanel
{
  public:
    MiscPanel(wxNotebook* parent, NieRHook* hook);
    ~MiscPanel();

  protected:
    void OnSavePressed(wxCommandEvent& evt);
    wxDECLARE_EVENT_TABLE();

  private:
    NieRHook* hook = nullptr;

    // Graphics
    wxStaticBox* graphics = nullptr;
    wxSlider* HUDOpacity = nullptr;
    wxStaticText* HUD = nullptr;

    wxStaticText* R = nullptr;
    wxSlider* RSlider = nullptr;
    wxStaticText* G = nullptr;
    wxSlider* GSlider = nullptr;
    wxStaticText* B = nullptr;
    wxSlider* BSlider = nullptr;

    // Sound
    wxStaticBox* sound = nullptr;

    wxButton* Save = nullptr;
};