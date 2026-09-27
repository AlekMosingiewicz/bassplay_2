//
// Created by aleksander on 13.12.2025.
//

#ifndef BASSPLAY_2_PLAYLISTCHOICEDIALOG_HPP
#define BASSPLAY_2_PLAYLISTCHOICEDIALOG_HPP

#include <wx/wx.h>
#include "../play/playlist/Manager.hpp"
#include "../play/Song.hpp"
#include <memory>

namespace Bassplay::Ui {
    using Play::Playlist::Manager;
    using Play::Song;
    using Play::Playlist::BassplayPlaylist;

    class PlaylistChoiceDialog : public wxDialog {
    public:
        PlaylistChoiceDialog(wxWindow *parent,
                             Manager *playlistManager,
                             std::shared_ptr<Song> songToAdd,
                             const wxString &title = wxString("Select Playlist"),
                             const wxPoint &pos = wxDefaultPosition,
                             const wxSize &size = wxDefaultSize,
                             long style = wxDEFAULT_DIALOG_STYLE) : wxDialog(parent, wxID_ANY, title, pos, size, style),
                                                                    m_playlistManager(playlistManager),
                                                                    m_songToAdd(songToAdd) {
            BuildDialog();
        }

    private:
        // data elements
        std::shared_ptr<Song> m_songToAdd;
        BassplayPlaylist *m_selectedPlaylist = nullptr;

        // gui elements
        Manager *m_playlistManager;
        wxButton *m_createPlaylistButton;
        wxButton *m_addToPlaylistButton;

        //procedures
        void BuildDialog();

        //event handling
        void OnCreatePlaylist(wxCommandEvent &event);
        void OnSelectPlaylist(wxCommandEvent &event);
        void OnAddToPlaylist(wxCommandEvent &event);
    };
}
#endif //BASSPLAY_2_PLAYLISTCHOICEDIALOG_HPP
