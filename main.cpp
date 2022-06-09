#include <iostream>
#include "app/BassplayApp.h"
#include "play/Song.h"

wxBEGIN_EVENT_TABLE(Bassplay::Ui::PlayerFrame, wxFrame)
                EVT_MENU(wxID_EXIT,  Bassplay::Ui::PlayerFrame::OnExit)
                EVT_MENU(wxID_ABOUT, Bassplay::Ui::PlayerFrame::OnAbout)
wxEND_EVENT_TABLE()

IMPLEMENT_APP(Bassplay::App::BassplayApp)