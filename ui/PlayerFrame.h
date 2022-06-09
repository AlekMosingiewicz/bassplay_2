//
// Created by aleksander on 09.06.22.
//

#ifndef BASSPLAY_2_PLAYERFRAME_H
#define BASSPLAY_2_PLAYERFRAME_H


#include <wx/frame.h>
#include <wx/string.h>
#include <wx/gdicmn.h>
#include <wx/msgdlg.h>
#include <wx/menu.h>
#include <wx/gtk/filedlg.h>
#include "../play/Player.h"

namespace Bassplay::Ui {

    class PlayerFrame: public wxFrame {
    public:
        PlayerFrame(const wxString& title, const wxPoint& pos, const wxSize& size, Bassplay::Play::Player* musicPlayer);
    private:
        //dependencies
        Bassplay::Play::Player* player;
        //ui elements
        wxMenuBar* mainMenuBar;
        wxMenu* menuFile;
        wxMenu* menuHelp;
        //ui building
        void BuildMainMenu();
        //events
        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        wxDECLARE_EVENT_TABLE();
    };

} // Bassplay

#endif //BASSPLAY_2_PLAYERFRAME_H
