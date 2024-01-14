#include <iostream>
#define wxUSE_UNICODE_WCHAR 1
#include "app/BassplayApp.h"
#include "play/serializer/SerializableStringList.h"

wxBEGIN_EVENT_TABLE(Bassplay::Ui::PlayerFrame, wxFrame)
                EVT_MENU(wxID_EXIT,  Bassplay::Ui::PlayerFrame::OnExit)
                EVT_MENU(wxID_ABOUT, Bassplay::Ui::PlayerFrame::OnAbout)
                EVT_MENU(wxID_OPEN,  Bassplay::Ui::PlayerFrame::OnOpen)
                EVT_MENU(wxID_INFO,  Bassplay::Ui::PlayerFrame::OnInfo)
                EVT_BUTTON(playerButtonPlay, Bassplay::Ui::PlayerFrame::OnPlay)
                EVT_BUTTON(playerButtonPause, Bassplay::Ui::PlayerFrame::OnPause)
                EVT_BUTTON(playerButtonStop, Bassplay::Ui::PlayerFrame::OnStop)
                EVT_BUTTON(playerButtonVolume, Bassplay::Ui::PlayerFrame::OnVolumeButtonPress)
wxEND_EVENT_TABLE()

IMPLEMENT_APP(Bassplay::App::BassplayApp)