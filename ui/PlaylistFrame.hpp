//
// Created by aleksander on 06.07.25.
//

#ifndef BASSPLAY_2_PLAYLISTFRAME_HPP
#define BASSPLAY_2_PLAYLISTFRAME_HPP

#include <wx/wx.h>
#include "DpiAwareFrame.hpp"
#include "../play/playlist/Manager.hpp"
#include "playlist/BassplayPlaylist.hpp"
#include "../play/Player.hpp"
#include "../play/Song.hpp"
#include <map>

namespace Bassplay::Ui {
    using Bassplay::Play::Playlist::Manager;
    using Bassplay::Play::Playlist::BassplayPlaylist;
    using Bassplay::Play::Player;
    using Bassplay::Play::Song;

    class PlaylistFrame: public DpiAwareFrame {
    private:
        // UI elements
        wxPanel *m_playlistPanel = nullptr;
        wxListBox *m_playlistListBox = nullptr;
        wxListBox *m_songListBox = nullptr;
        wxButton *m_createButton = nullptr;
        wxButton *m_removeButton = nullptr;
        wxButton *m_playButton = nullptr;
        wxButton *m_addToPlaylistButton = nullptr;
        Manager *m_playlistManager = nullptr;
        wxSizer *m_sizer = nullptr;
        wxSizer *m_buttonSizer = nullptr;
        Player *m_player = nullptr;


        // Helper fields
        BassplayPlaylist *m_currentPlaylist = nullptr;
        Song *m_currentSong = nullptr;
        std::map<int, BassplayPlaylist *> m_indexedPlaylists;

        // Methods
        void BuildPlaylistWindow();
        void OnCreatePlaylist(wxCommandEvent &event);
        void OnAddToPlaylist(wxCommandEvent &event);
        void OnRemoveFromPlaylist(wxCommandEvent &event);
        void OnPlaylistSelected(wxCommandEvent &event);
        void PopulatePlaylistListBox();
        void PopulateSongListBox(BassplayPlaylist *playlist);
        void OnSongSelected(wxCommandEvent &event);
        void OnPlayButtonClicked(wxCommandEvent &event);
        BassplayPlaylist *GetSelectedPlaylist();
    public:
        PlaylistFrame(const wxString &title, const wxPoint &pos, const wxSize &size,
                      Manager *playlistManager, Player *player)
                : DpiAwareFrame(nullptr, wxID_ANY, title, pos, size, wxCLOSE_BOX | wxMINIMIZE_BOX),
                  m_playlistManager(playlistManager),
                  m_player(player) {
            BuildPlaylistWindow();
        }
        ~PlaylistFrame() override {
            delete m_playlistPanel;
            delete m_playlistListBox;
            delete m_createButton;
            delete m_removeButton;
            delete m_playButton;
            delete m_sizer;
            delete m_playlistManager;
            delete m_addToPlaylistButton;
            delete m_playlistManager;
            delete m_buttonSizer;
        }
    };
} // Bassplay


#endif //BASSPLAY_2_PLAYLISTFRAME_HPP
