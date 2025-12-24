//
// Created by aleksander on 13.12.2025.
//

#include "PlaylistChoiceDialog.hpp"

namespace Bassplay::Ui {
    void PlaylistChoiceDialog::BuildDialog() {
        auto sizer = new wxBoxSizer(wxVERTICAL);
        auto playlistListBox = new wxListBox(this, wxID_ANY);

        for (const auto &[fst, snd]: *m_playlistManager->GetPlaylists()) {
            playlistListBox->Append(fst);
        }

        sizer->Add(playlistListBox, 1, wxEXPAND | wxALL, 10);

        auto *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
        m_createPlaylistButton = new wxButton(this, wxID_ANY, "Create New Playlist");
        m_createPlaylistButton->Bind(wxEVT_BUTTON, &PlaylistChoiceDialog::OnCreatePlaylist, this);
        playlistListBox->Bind(wxEVT_COMMAND_LISTBOX_SELECTED, &PlaylistChoiceDialog::OnSelectPlaylist, this);

        m_addToPlaylistButton = new wxButton(this, wxID_ANY, "Add");
        m_addToPlaylistButton->Bind(wxEVT_BUTTON, &PlaylistChoiceDialog::OnAddToPlaylist, this);

        buttonSizer->Add(m_createPlaylistButton, 2, wxALL, 5);
        buttonSizer->Add(m_addToPlaylistButton, 2, wxALL, 5);

        sizer->Add(buttonSizer, 0, wxALIGN_CENTER);

        SetSizerAndFit(sizer);
    }

    void PlaylistChoiceDialog::OnCreatePlaylist(wxCommandEvent &event) {
        wxTextEntryDialog dialog(this, "Enter playlist name:", "Create Playlist");
        if (dialog.ShowModal() == wxID_OK) {
            std::string playlistName = dialog.GetValue().ToStdString();
            if (!playlistName.empty()) {
                auto newPlaylist = new BassplayPlaylist(playlistName);
                newPlaylist->AddSong(m_songToAdd);
                m_playlistManager->AddPlaylist(newPlaylist);
                wxMessageBox("Song added to new playlist: " + dialog.GetValue(), "Success", wxOK | wxICON_INFORMATION);
                Close();
            } else {
                wxMessageBox("Playlist name cannot be empty.", "Error", wxOK | wxICON_ERROR);
            }
        }
    }

    void PlaylistChoiceDialog::OnSelectPlaylist(wxCommandEvent &event) {
        wxString selectedPlaylistName = event.GetString();
        m_selectedPlaylist = m_playlistManager->GetPlaylist(selectedPlaylistName.ToStdString());
    }

    void PlaylistChoiceDialog::OnAddToPlaylist(wxCommandEvent &event) {
        if (m_selectedPlaylist != nullptr) {
            m_selectedPlaylist->AddSong(m_songToAdd);
            wxMessageBox("Song added to playlist: " + wxString(m_selectedPlaylist->GetName()), "Success", wxOK | wxICON_INFORMATION);
            Close();
        }
    }
}
