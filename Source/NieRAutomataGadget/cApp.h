#pragma once

#include "wx/wx.h"
#include "Main.h"

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

