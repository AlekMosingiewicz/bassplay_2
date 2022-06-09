//
// Created by aleksander on 09.06.22.
//

#include <wx/wx.h>
#include "PlayerFrame.h"

namespace Bassplay::Ui {
    void PlayerFrame::OnExit(wxCommandEvent &event) {
        Close (true);
    }
    void PlayerFrame::OnAbout(wxCommandEvent &event) {
        wxMessageBox( "Bassplay 2.0",
                      "This is a Bass-based mod music player", wxOK | wxICON_INFORMATION );
    }
    void PlayerFrame::OnOpen(wxCommandEvent &event) {
        wxFileDialog fileDialog(this, "Open music file", "", "",
                                "Mod files (*.it)|*.it", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        if (fileDialog.ShowModal() == wxID_CANCEL)
            return;
        wxString path = fileDialog.GetPath();
        std::string stdPath = std::string(path.mb_str());
        try {
            player->LoadSong(&stdPath);
        } catch (BassException exception) {
            wxMessageBox(wxString::Format("Error code %d", exception.GetCode()),
                         "Error loading song!",
                         wxOK | wxICON_ERROR
                         );
        }

    }
    void PlayerFrame::BuildMainMenu() {
        menuFile = new wxMenu;
        menuFile->Append(wxID_OPEN);
        menuFile->AppendSeparator();
        menuFile->Append(wxID_EXIT);

        menuHelp = new wxMenu;
        menuHelp->Append(wxID_ABOUT);

        mainMenuBar = new wxMenuBar;
        mainMenuBar->Append(menuFile, "&File" );
        mainMenuBar->Append(menuHelp, "&Help" );

        SetMenuBar(mainMenuBar);
        CreateStatusBar();
        SetStatusText( "Bassplay 2.0" );
    }
    PlayerFrame::PlayerFrame(const wxString &title, const wxPoint &pos, const wxSize &size, Bassplay::Play::Player* musicPlayer)
    : wxFrame(NULL, wxID_ANY, title, pos, size) {
        player = musicPlayer;
        BuildMainMenu();
    }
} // Bassplay