//
// Created by aleksander on 09.06.22.
//

#include <wx/wx.h>
#include "PlayerFrame.h"

namespace Bassplay::Ui {

    void PlayerFrame::OnExit(wxCommandEvent &event) {
        Close(true);
    }

    void PlayerFrame::OnAbout(wxCommandEvent &event) {
        wxMessageBox("Bassplay 2.0",
                     "This is a Bass-based mod music m_player created by Alek Mosingiewicz", wxOK | wxICON_INFORMATION);
    }

    void PlayerFrame::OnOpen(wxCommandEvent &event) {
        wxFileDialog fileDialog(this, "Open music file", m_player->GetCurrentDirectory(), "",
                                "Mod files (*.it,*.xm,*.mod)|*.it;*.xm",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        if (fileDialog.ShowModal() == wxID_CANCEL)
            return;
        wxString path = fileDialog.GetPath();
        std::string stdPath = std::string(path.mb_str());
        try {
            m_player->LoadSong(stdPath);
            wxString name = wxString(m_player->GetSong()->GetTitle());
            GetStatusBar()->PushStatusText(name);
            m_player->PlaySong();
            UpdatePlayLabel();
        } catch (BassplayException &exception) {
            wxMessageBox(wxString::Format("Error code %d", exception.GetCode()),
                         "Error loading song!",
                         wxOK | wxICON_ERROR
            );
        }
    }

    void PlayerFrame::BuildMainMenu() {
        m_menuFile = new wxMenu;
        m_menuFile->Append(wxID_OPEN);
        m_menuFile->AppendSeparator();
        m_menuFile->Append(wxID_EXIT);

        m_menuHelp = new wxMenu;
        m_menuHelp->Append(wxID_ABOUT);

        m_mainMenuBar = new wxMenuBar;
        m_mainMenuBar->Append(m_menuFile, "&File");
        m_mainMenuBar->Append(m_menuHelp, "&Help");

        SetMenuBar(m_mainMenuBar);
        CreateStatusBar();
        SetStatusText("Bassplay 2.0");
    }

    void PlayerFrame::BuildPlayerPanel() {
        m_playerPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(150, 100));
        wxSizer* horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
        wxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);
        m_timeLabel = new wxStaticText(this, wxID_ANY, wxString("00:00/00:00"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE);
        m_songNameLabel = new wxStaticText(this, wxID_ANY, wxString("No song loaded"));

        m_playButton = new wxButton(this, playerButtonPlay, "Play");
        m_pauseButton = new wxButton(this, playerButtonPause, "Pause");
        m_stopButton = new wxButton(this, playerButtonStop, "Stop");

        horizontalSizer->Add(m_playButton, 3, wxALL, 5);
        horizontalSizer->Add(m_pauseButton, 3, wxALL, 5);
        horizontalSizer->Add(m_stopButton, 3, wxALL, 5);
        horizontalSizer->AddSpacer(3);
        horizontalSizer->RecalcSizes();

        verticalSizer->Add(m_songNameLabel, 3, wxALIGN_CENTER, 3);
        verticalSizer->Add(m_timeLabel, 3, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 10);
        verticalSizer->Add(horizontalSizer);

        m_playerPanel->SetSizerAndFit(verticalSizer);

        m_playerPanel->Show(true);
    }

    PlayerFrame::PlayerFrame(const wxString &title, const wxPoint &pos, const wxSize &size,
                             Bassplay::Play::Player *musicPlayer)
            : wxFrame(NULL, wxID_ANY, title, pos, size) {
        m_player = musicPlayer;
        BuildMainMenu();
        BuildPlayerPanel();
    }

    void PlayerFrame::UpdateGUI() {
        if (m_player->GetState() == Play::player_state_playing) {
            UpdateTimeLabel();
        }
    }

    void PlayerFrame::OnPlay(wxCommandEvent &event) {
        m_player->PlaySong();
        UpdatePlayLabel();
    }

    void PlayerFrame::OnPause(wxCommandEvent &event) {
        m_player->PauseSong();
        UpdatePlayLabel();
    }

    void PlayerFrame::OnStop(wxCommandEvent &event) {
        m_player->StopSong();
        UpdatePlayLabel();
    }

    void PlayerFrame::UpdateTimeLabel() {
        wxString timeLabel = wxString(m_player->GetCurrentPlaybackTime());
        if (m_timeLabel->GetLabel() != timeLabel) {
            m_timeLabel->SetLabel(timeLabel);
        }
    }

    void PlayerFrame::UpdatePlayLabel() {
        wxString stateLabel;
        wxString titleLabel;

        switch (m_player->GetState()) {
            case Play::player_state::player_state_stopped:
                stateLabel = wxString("Stopped");
                break;
            case Play::player_state::player_state_playing:
                stateLabel = wxString("Playing");
                break;
            case Play::player_state::player_state_paused:
                stateLabel = wxString("Paused");
                break;
        }

        titleLabel = m_player->GetSong() != nullptr ? wxString(m_player->GetSong()->GetTitle()) : "No song loaded";
        m_songNameLabel->SetLabel(wxString(stateLabel + ":" + titleLabel));
    }

} // Bassplay