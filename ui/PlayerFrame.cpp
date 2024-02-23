//
// Created by aleksander on 09.06.22.
//

#include <wx/wx.h>
#include <wx/stdpaths.h>

#include "PlayerFrame.h"

namespace Bassplay::Ui {

    void PlayerFrame::OnExit(wxCommandEvent &event) {
        Close(true);
    }

    void PlayerFrame::OnAbout(wxCommandEvent &event) {
        wxMessageBox("This is a Bass-based mod music player created by Alek Mosingiewicz",
                     "Bassplay 2.0", wxOK | wxICON_INFORMATION);
    }

    void PlayerFrame::OnOpen(wxCommandEvent &event) {
        wxFileDialog fileDialog(this, "Open music file", m_player->GetCurrentDirectory(), "",
                                "Mod files (*.it,*.xm,*.mod,*.s3m,*.mo3,*.mptm)|*.it;*.IT;*.xm;*.XM;*.mod;*.MOD;*.s3m;*.S3M;*.mo3;*.mptm",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        if (fileDialog.ShowModal() == wxID_CANCEL)
            return;
        wxString path = fileDialog.GetPath();
        std::string stdPath = std::string(path.mb_str());
        OpenSong(stdPath);
    }

    void PlayerFrame::OpenSong(std::string &path) {
        try {
            m_player->LoadSong(path);
            ResetPositionSlider();
            m_player->PlaySong();
            if (FindWindowById(playerInfoWindow, this) == nullptr) {
                m_songInfoFrame = nullptr;
            }
            if (m_songInfoFrame != nullptr) {
                m_songInfoFrame->SetSong(m_player->GetSong());
            }
            UpdateGUI();
            BuildHistory();
        } catch (BassplayException &exception) {
            wxMessageBox(wxString::Format("Error code %d", exception.GetCode()),
                         "Error loading song!",
                         wxOK | wxICON_ERROR
            );
        }
    }

    void PlayerFrame::BuildMainMenu() {
        m_menuFile = new wxMenu;

        BuildFileMenu();

        m_menuHelp = new wxMenu;
        m_menuHelp->Append(wxID_ABOUT);

        m_mainMenuBar = new wxMenuBar;
        m_mainMenuBar->Append(m_menuFile, "&File");
        m_mainMenuBar->Append(m_menuHelp, "&Help");

        SetMenuBar(m_mainMenuBar);
        CreateStatusBar();
        SetStatusText("Bassplay 2.0");
    }

    void PlayerFrame::BuildFileMenu() {
        m_menuFile->Append(wxID_OPEN, wxEmptyString, wxString("Load music module"));
        m_menuFile->Append(wxID_INFO, wxEmptyString, wxString("Module info"));
        m_menuFile->AppendSeparator();
        BuildHistory();
        m_menuFile->AppendSeparator();
        m_menuFile->Append(wxID_EXIT);
        Bind(wxEVT_MENU, &PlayerFrame::OnMenu, this);
    }

    void PlayerFrame::OnMenu(wxCommandEvent &event) {
        auto id = event.GetId();
        switch (id) {
            case wxID_EXIT:
                OnExit(event);
                return;
            case wxID_OPEN:
                OnOpen(event);
                return;
            case wxID_ABOUT:
                OnAbout(event);
                return;
            case wxID_INFO:
                OnInfo(event);
                return;
        }
        auto history = m_player->GetHistory()->GetSongs();
        auto iterator = history.begin();
        for (int i = 0; i < id - 100; i++) {
            iterator++;
        }
        std::string path = (*iterator)->GetPath();
        OpenSong(path);
    }

    void PlayerFrame::BuildHistory() {
        if (m_menuFile == nullptr) {
            return;
        }

        for (auto j = 100; j < 200; j++) {
            if (m_menuFile->FindItem(j) != nullptr) {
                m_menuFile->Delete(j);
            }
        }

        auto history = m_player->GetHistory();
        int i = 100;
        for (auto song: history->GetSongs()) {
            auto id = i++;
            m_menuFile->Insert((i - 98), id, wxString(song->GetTitle()));
        }
        this->Refresh();
        this->Update();
    }

    void PlayerFrame::BuildPlayerPanel() {
        m_playerPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(150, 100));
        wxSizer *horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
        wxSizer *verticalSizer = new wxBoxSizer(wxVERTICAL);
        m_timeLabel = new wxStaticText(this, wxID_ANY, wxString("00:00/00:00"), wxDefaultPosition, wxDefaultSize,
                                       wxST_NO_AUTORESIZE);
        m_songNameLabel = new wxStaticText(this, wxID_ANY, wxString("No song loaded"), wxDefaultPosition,
                                           wxSize(300, 0), wxST_NO_AUTORESIZE | wxALIGN_CENTRE_HORIZONTAL);
        mVolumeLabel = new wxStaticText(this, wxID_ANY, wxString("Volume:"), wxDefaultPosition, wxSize(300, 0),
                                        wxST_NO_AUTORESIZE | wxALIGN_LEFT);

        m_positionSlider = new wxSlider(this, playerPositionSlider, 0, 0, 100, wxDefaultPosition, wxSize(300, 0));
        Connect(playerPositionSlider, wxEVT_SCROLL_THUMBRELEASE,
                wxScrollEventHandler(PlayerFrame::OnPositionSliderDragged));
        Connect(playerVolumeSlider, wxEVT_SCROLL_THUMBRELEASE,
                wxScrollEventHandler(PlayerFrame::OnVolumeSliderDragged));

        m_volumeSlider = new wxSlider(this, playerVolumeSlider, 100, 0, 100, wxDefaultPosition, wxSize(300, 0));
        m_volumeSlider->SetValue((float) (m_player->GetVolume() * 100));

        wxString imagedir = wxStandardPaths::Get().GetUserConfigDir() + "/.bassplay/img/";
        m_playButton = new wxBitmapButton(
                this,
                playerButtonPlay,
                wxBitmap(wxImage(imagedir + "211876_play_icon.png", wxBITMAP_TYPE_PNG)),
                wxDefaultPosition,
                wxSize(45, 45)
        );
        m_pauseButton = new wxBitmapButton(
                this,
                playerButtonPause,
                wxBitmap(wxImage(imagedir + "211871_pause_icon.png", wxBITMAP_TYPE_PNG)),
                wxDefaultPosition,
                wxSize(45, 45)
        );
        m_stopButton = new wxBitmapButton(
                this,
                playerButtonStop,
                wxBitmap(wxImage(imagedir + "2203518_block_cube_music_square_stop_icon.png", wxBITMAP_TYPE_PNG)),
                wxDefaultPosition,
                wxSize(45, 45)
        );
        mControlsButton = new wxBitmapButton(
                this,
                playerButtonControls,
                wxBitmap(wxImage(imagedir + "3516631_audio_control_gauge_media_play_icon.png", wxBITMAP_TYPE_PNG)),
                wxDefaultPosition,
                wxSize(45, 45)
        );

        horizontalSizer->Add(m_playButton, 2, wxALL, 5);
        horizontalSizer->Add(m_pauseButton, 2, wxALL, 5);
        horizontalSizer->Add(m_stopButton, 2, wxALL, 5);
        horizontalSizer->Add(mControlsButton, 2, wxALL, 5);
        horizontalSizer->AddSpacer(5);
        horizontalSizer->RecalcSizes();

        verticalSizer->Add(m_songNameLabel, 3, wxALIGN_CENTER, 3);
        verticalSizer->Add(m_timeLabel, 3, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 10);
        verticalSizer->Add(m_positionSlider, 5, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 1);
        verticalSizer->Add(horizontalSizer, 0, wxALIGN_CENTER_HORIZONTAL);
        verticalSizer->Add(mVolumeLabel, 3, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 1);
        verticalSizer->Add(m_volumeSlider, 5, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 1);

        m_playerPanel->SetSizerAndFit(verticalSizer);

        m_playerPanel->Show(true);
        m_volumeSlider->Hide();
        mVolumeLabel->Hide();
    }

    PlayerFrame::PlayerFrame(const wxString &title,
                             const wxPoint &pos,
                             const wxSize &size,
                             Bassplay::Play::Player *musicPlayer) : DpiAwareFrame(NULL, wxID_ANY, title, pos, wxDefaultSize,
                                                                            wxDEFAULT_FRAME_STYLE ^ wxRESIZE_BORDER),
                                                                    m_player(musicPlayer) {
        BuildMainMenu();
        BuildPlayerPanel();
        SetClientSize(this->CalculateRealSize(const_cast<wxSize&>(size)));
    }

    void PlayerFrame::UpdateGUI() {
        if (m_player->GetState() == Play::player_state_playing) {
            UpdateTimeLabel();
        }
        if (m_player->GetState() == Play::player_state_stopped && m_positionSlider->GetValue() > 0) {
            StopAndReset();
        }
        if (m_player->GetState() == Play::player_state_stopped || m_player->GetState() == Play::player_state_paused) {
            m_volumeSlider->SetValue(m_player->GetVolume() * 100);
        }
        UpdatePlayLabel();
        UpdatePositionSlider();
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
        StopAndReset();
    }

    void PlayerFrame::StopAndReset() {
        m_player->StopSong();
        UpdatePlayLabel();
        UpdateTimeLabel();
        ResetPositionSlider();

    }

    void PlayerFrame::UpdateTimeLabel() {
        wxString timeLabel = wxString(m_player->GetCurrentPlaybackTime());
        if (m_timeLabel->GetLabel() != timeLabel) {
            m_timeLabel->SetLabel(timeLabel);
        }
    }

    void PlayerFrame::ResetPositionSlider() {
        m_positionSlider->SetRange(0, static_cast < int > (m_player->GetSong()->GetLength()));
        m_positionSlider->SetValue(0);
    }

    void PlayerFrame::UpdatePositionSlider() {
        if (m_player->HasSong() && m_player->GetState() == Play::player_state_playing) {
            m_positionSlider->SetValue(m_player->GetPlaybackTimeInSeconds());
        }
    }

    void PlayerFrame::OnPositionSliderDragged(wxScrollEvent &event) {
        double position = m_positionSlider->GetValue();
        m_player->JumpToPosition(position);
        UpdateGUI();
        UpdateTimeLabel();
    }

    void PlayerFrame::OnVolumeSliderDragged(wxScrollEvent &event) {
        double volume = m_volumeSlider->GetValue();
        m_player->SetVolume((float) (volume / 100));
    }

    void PlayerFrame::ShowInfoFrame() {
        if (FindWindowById(playerInfoWindow, this) == nullptr) {
            m_songInfoFrame = nullptr;
        }
        if (m_songInfoFrame != nullptr) {
            m_songInfoFrame->Hide();
            m_songInfoFrame->Destroy();
        }
        m_songInfoFrame = new SongInfoFrame(m_player->GetSong(), this, playerInfoWindow);
        m_songInfoFrame->Show();
    }

    void PlayerFrame::OnInfo(wxCommandEvent &event) {
        if (!m_player->HasSong()) {
            wxMessageBox("No module loaded");
            return;
        }
        ShowInfoFrame();
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
        m_songNameLabel->SetLabel(wxString(stateLabel + ": " + titleLabel));
    }

    void PlayerFrame::OnVolumeButtonPress(wxCommandEvent &event) {
        wxSize size = GetSize();
        if (mVolumeVisible) {
            size.SetHeight(size.GetHeight() - 50);
            mVolumeLabel->Hide();
            m_volumeSlider->Hide();
        } else {
            size.SetHeight(size.GetHeight() + 50);
            mVolumeLabel->Show(true);
            m_volumeSlider->Show(true);
        }
        SetSize(size);
        mVolumeVisible = !mVolumeVisible;
        m_playerPanel->Show(true);

        this->Refresh();
        this->Update();
    }

} // Bassplay