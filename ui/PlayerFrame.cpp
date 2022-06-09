//
// Created by aleksander on 09.06.22.
//

#include "PlayerFrame.h"

namespace Bassplay::Ui {
    void PlayerFrame::OnExit(wxCommandEvent &event) {
        Close (true);
    }
    void PlayerFrame::OnAbout(wxCommandEvent &event) {
        wxMessageBox( "Bassplay 2.0",
                      "This is a Bass-based mod music player", wxOK | wxICON_INFORMATION );
    }
    PlayerFrame::PlayerFrame(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(NULL, wxID_ANY, title, pos, size) {
        wxMenu* menuFile = new wxMenu;
        menuFile->AppendSeparator();
        menuFile->Append(wxID_EXIT);

        wxMenu *menuHelp = new wxMenu;
        menuHelp->Append(wxID_ABOUT);

        wxMenuBar *menuBar = new wxMenuBar;
        menuBar->Append( menuFile, "&File" );
        menuBar->Append( menuHelp, "&Help" );

        SetMenuBar( menuBar );
        CreateStatusBar();
        SetStatusText( "Bassplay 2.0" );
    }
} // Bassplay