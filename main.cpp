#include <iostream>
#define wxUSE_UNICODE_WCHAR 1
#include "app/BassplayApp.h"

wxBEGIN_EVENT_TABLE(Bassplay::Ui::PlayerFrame, wxFrame)
                EVT_MENU(wxID_EXIT,  Bassplay::Ui::PlayerFrame::OnExit)
                EVT_MENU(wxID_ABOUT, Bassplay::Ui::PlayerFrame::OnAbout)
                EVT_MENU(wxID_OPEN,  Bassplay::Ui::PlayerFrame::OnOpen)
wxEND_EVENT_TABLE()

IMPLEMENT_APP(Bassplay::App::BassplayApp)