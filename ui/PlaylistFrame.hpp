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
#include "../play/tools/DirTool.hpp"
#include "../event/BassplayEventDispatcher.hpp"
#include "../event/BassplayEventType.hpp"
#include "../event/BassplayGuiEvent.hpp"
#include <map>

namespace Bassplay::Ui {
    using Bassplay::Play::Playlist::Manager;
    using Bassplay::Play::Playlist::BassplayPlaylist;
    using Bassplay::Play::Player;
    using Bassplay::Play::Song;
    using Bassplay::Play::Tools::DirTool;
    using Bassplay::Event::BassplayEventDispatcher;
    using Bassplay::Event::BassplayGuiEvent;
    using namespace Bassplay::Event;

    class PlaylistFrame: public DpiAwareFrame {
    private:
        // UI elements
        wxPanel   *m_playlistPanel = nullptr;
        wxListBox *m_playlistListBox = nullptr;
        wxListBox *m_songListBox = nullptr;
        wxButton  *m_createButton = nullptr;
        wxButton  *m_removeButton = nullptr;
        wxButton  *m_removePlaylistButton = nullptr;
        wxButton  *m_playButton = nullptr;
        wxButton  *m_addToPlaylistButton = nullptr;
        Manager   *m_playlistManager = nullptr;
        wxSizer   *m_sizer = nullptr;
        wxSizer   *m_playlistButtonSizer = nullptr;
        wxSizer   *m_songButtonSizer = nullptr;
        Player    *m_player = nullptr;
        bool       m_isHidden = false;


        // Helper fields
        BassplayPlaylist *m_currentPlaylist = nullptr;
        Song *m_currentSong = nullptr;
        std::map<int, BassplayPlaylist *> m_indexedPlaylists;

        // Methods
        void BuildPlaylistWindow();
        void BuildPlaylistPanel();
        void BuildSongsPanel();
        void OnPlaylistSelected(wxCommandEvent &event);
        void PopulatePlaylistListBox();
        void PopulateSongListBox();

        // Event handlers
        void OnSongSelected(wxCommandEvent &event);
        void OnAddToPlaylist(wxCommandEvent &event);
        void OnRemoveFromPlaylist(wxCommandEvent &event);
        void OnCreatePlaylist(wxCommandEvent &event);
        void OnSongDoubleClicked(wxCommandEvent &event);
        void OnPlayButtonClicked(wxCommandEvent &event);
        void OnRemovePlaylist(wxCommandEvent &event);
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
            BassplayGuiEvent event(Bassplay::Event::GuiEventType::playlistWindowClosed);
            BassplayEventDispatcher::Instance().BroadcastEvent(event);
            delete m_playlistPanel;
        }

        void SetCurrentSongIndex(int index) {
            if (m_songListBox != nullptr) {
                m_songListBox->SetSelection(index);
            }
        }

        void OnClose(wxCloseEvent &event) {
            m_isHidden = true;
        }

        bool IsHidden() const {
            return m_isHidden;
        }
    };

} // Bassplay


#endif //BASSPLAY_2_PLAYLISTFRAME_HPP
