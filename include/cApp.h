#pragma once

#include "Main.h"
#include "wx/wx.h"

class cApp : public wxApp
{
  public:
    cApp();
    ~cApp();

  private:
    Main* m_frame = nullptr;

  public:
    virtual bool OnInit();
};
