//
// Created by aleksander on 06.07.25.
//

#include "PlaylistFrame.hpp"

namespace Bassplay::Ui {

    void PlaylistFrame::BuildPlaylistWindow() {
        m_playlistPanel = new wxPanel(this);
        m_playlistListBox = new wxListBox(m_playlistPanel, wxID_ANY);
        m_createButton = new wxButton(m_playlistPanel, wxID_ANY, "Create");
        m_removeButton = new wxButton(m_playlistPanel, wxID_ANY, "Remove");
        m_playButton = new wxButton(m_playlistPanel, wxID_ANY, "Play");
        m_addToPlaylistButton = new wxButton(m_playlistPanel, wxID_ANY, "Add to Playlist");

        // Layout
        BuildPlaylistPanel();
        BuildSongsPanel();

        // Bind events
        m_createButton->Bind(wxEVT_BUTTON, &PlaylistFrame::OnCreatePlaylist, this);
        m_removeButton->Bind(wxEVT_BUTTON, &PlaylistFrame::OnRemoveFromPlaylist, this);
        m_playlistListBox->Bind(wxEVT_COMMAND_LISTBOX_SELECTED , &PlaylistFrame::OnPlaylistSelected, this);
        m_addToPlaylistButton->Bind(wxEVT_BUTTON, &PlaylistFrame::OnAddToPlaylist, this);
        m_playButton->Bind(wxEVT_BUTTON, &PlaylistFrame::OnPlayButtonClicked, this);

        // Populate the playlist list box
        PopulatePlaylistListBox();
        m_sizer->Show(true);
        m_playlistPanel->Show(true);

        m_playlistPanel->SetSizer(m_sizer);
    }

    void PlaylistFrame::BuildPlaylistPanel() {
        m_sizer = new wxBoxSizer(wxHORIZONTAL);
        m_sizer->Add(m_playlistListBox, 1, wxEXPAND | wxALL, 5);

        m_playlistButtonSizer = new wxBoxSizer(wxVERTICAL);
        m_playlistButtonSizer->Add(m_addToPlaylistButton, 0, wxEXPAND | wxALL, 5);
        m_playlistButtonSizer->Add(m_createButton, 0, wxEXPAND | wxALL, 5);
        m_playlistButtonSizer->Add(m_removeButton, 0, wxEXPAND | wxALL, 5);
        m_playlistButtonSizer->Add(m_playButton, 0, wxEXPAND | wxALL, 5);
        m_sizer->Add(m_playlistButtonSizer, 0, wxEXPAND | wxALL, 5);
    }

    void PlaylistFrame::BuildSongsPanel() {
        m_songListBox = new wxListBox(m_playlistPanel, wxID_ANY);
        m_songButtonSizer = new wxBoxSizer(wxVERTICAL);
        m_songButtonSizer->Add(m_addToPlaylistButton, 0, wxEXPAND | wxALL, 5);
        m_songButtonSizer->Add(m_removeButton, 0, wxEXPAND | wxALL, 5);
        m_songButtonSizer->Add(m_playButton, 0, wxEXPAND | wxALL, 5);

        m_sizer->Add(m_songListBox, 1, wxEXPAND | wxALL, 5);
        m_sizer->Add(m_songButtonSizer, 0, wxEXPAND | wxALL, 5);
    }

    void PlaylistFrame::OnAddToPlaylist(wxCommandEvent &event) {
        // Logic to add a song to the playlist
        wxFileDialog fileDialog(this, "Add song to playlist",
                                DirTool::GetSongDirectory(m_player),
                                "",
                                "Mod files (*.it,*.xm,*.mod,*.s3m,*.mo3,*.mptm)|*.it;*.IT;*.xm;*.XM;*.mod;*.MOD;*.s3m;*.S3M;*.mo3;*.mptm",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        if (fileDialog.ShowModal() == wxID_CANCEL)
            return;
        std::string path = fileDialog.GetPath().ToStdString();
        m_currentPlaylist->AddSong(new Play::Song(path));
        m_currentPlaylist->ResetToBeginning();
        PopulateSongListBox();
    }

    void PlaylistFrame::OnRemoveFromPlaylist(wxCommandEvent &event) {
        int selection = m_playlistListBox->GetSelection();
        if (selection != wxNOT_FOUND) {
            m_playlistManager->RemovePlaylist(m_currentPlaylist->GetName());
            m_indexedPlaylists.erase(selection);
            PopulateSongListBox();
        }
    }

    void PlaylistFrame::OnPlaylistSelected(wxCommandEvent &event) {
        m_currentPlaylist = GetSelectedPlaylist();
        PopulateSongListBox();
    }

    void PlaylistFrame::PopulateSongListBox() {
        m_songListBox->Clear();
        if (m_currentPlaylist) {
            for (const auto &song : m_currentPlaylist->GetCollection()->GetSongs()) {
                m_songListBox->AppendString(song->GetName());
            }
        }
        m_songListBox->Bind(wxEVT_COMMAND_LISTBOX_SELECTED, &PlaylistFrame::OnSongSelected, this);
    }

    void PlaylistFrame::OnSongSelected(wxCommandEvent &event) {
        int selection = m_songListBox->GetSelection();
        if (selection != wxNOT_FOUND) {
            m_currentPlaylist->SetCurrentSongIndex(selection);
        }
    }

    void PlaylistFrame::PopulatePlaylistListBox() {
        m_playlistListBox->Clear();
        int counter = 0;
        for (const auto &playlist : (*m_playlistManager->GetPlaylists())) {
            m_indexedPlaylists.insert({counter++, playlist.second});
            m_playlistListBox->AppendString(playlist.second->GetName());
        }
    }

    void PlaylistFrame::OnPlayButtonClicked(wxCommandEvent &event) {
        if (m_player->GetPlaylist() == nullptr) {
            m_player->SetPlaylist(m_currentPlaylist);
            m_songListBox->SetSelection(0); // TODO make dynamic
        }
        m_player->PlayFromPlaylist();
    }

    BassplayPlaylist *PlaylistFrame::GetSelectedPlaylist() {
        int selection = m_playlistListBox->GetSelection();
        auto it = m_indexedPlaylists.find(selection);
        if (it != m_indexedPlaylists.end()) {
            m_currentPlaylist = it->second;
        } else {
            m_currentPlaylist = nullptr;
        }
        return m_currentPlaylist;
    }

    void PlaylistFrame::OnCreatePlaylist(wxCommandEvent &event) {
        wxTextEntryDialog dialog(this, "Enter playlist name:", "Create Playlist");
        if (dialog.ShowModal() == wxID_OK) {
            std::string playlistName = dialog.GetValue().ToStdString();
            if (!playlistName.empty()) {
                auto newPlaylist = new BassplayPlaylist(playlistName);
                m_playlistManager->AddPlaylist(newPlaylist);
                m_indexedPlaylists.insert({m_playlistListBox->GetCount(), newPlaylist});
                m_playlistListBox->AppendString(playlistName);
                m_playlistListBox->Select(m_indexedPlaylists.end()->first - 1);
                m_currentPlaylist = newPlaylist;
            } else {
                wxMessageBox("Playlist name cannot be empty.", "Error", wxOK | wxICON_ERROR);
            }
            PopulatePlaylistListBox();
        }
    }

} // Bassplay}