//
// Created by aleksander on 09.06.22.
//
#pragma once

#ifndef BASSPLAY_2_PLAYERFRAME_HPP
#define BASSPLAY_2_PLAYERFRAME_HPP


#include <wx/wx.h>
#include "../play/Player.hpp"
#include "SongInfoFrame.hpp"
#include "DpiAwareFrame.hpp"
#include "PlaylistFrame.hpp"
#include "../play/Song.hpp"
#include "../event/BassplayPlaybackEvent.hpp"
#include "../event/BassplayEventDispatcher.hpp"
#include "../event/BassplayEventType.hpp"
#include "../play/history/facade.hpp"
#include "../play/provider/factory/PlaylistProviderFactory.hpp"
#include "../play/playlist/Manager.hpp"
#include "../play/tools/DirTool.hpp"
#include "../listener/PlaylistListener.hpp"

enum playerWidgets {
    playerWidgetsMinimum = 200,
    playerButtonPlay,
    playerButtonPause,
    playerButtonStop,
    playerButtonControls,
    playerPositionSlider,
    playerVolumeSlider,
    playerInfoWindow,
    playerPlaylistWindow,
};

enum CustomMenuItems {
    bpCUSTOM_MENU_ITEMS_ID_MINIMUM = wxID_HIGHEST + 1,
    bpPLAYLISTS
};


namespace Bassplay::Ui {

    class UiThread;
    using namespace Bassplay::Play;
    using namespace Bassplay::Event;
    using Bassplay::Play::History::Facade;
    using Bassplay::Play::Provider::Factory::PlaylistProviderFactory;
    using Bassplay::Play::Playlist::Manager;
    using Bassplay::Play::Tools::DirTool;

    class PlayerFrame: public DpiAwareFrame  {
    public:
        PlayerFrame(
                const wxString& title,
                const wxPoint& pos,
                const wxSize& size,
                Bassplay::Play::Player* musicPlayer,
                Manager* playlistManager = nullptr
                );
        void UpdateGUI(bool withPlayLabelUpdate = true, bool withHistoryUpdate = false);
        void StopAndReset();
        void ResetPositionSlider();
        //info
        void ShowInfoFrame();

    private:
        //dependencies
        Bassplay::Play::Player* m_player;
        Manager* m_playlistManager = nullptr;

        //ui elements
        wxMenuBar* m_mainMenuBar;
        wxMenu* m_menuFile;
        wxMenu* m_menuHelp;
        wxPanel* m_playerPanel;
        wxStaticText* m_songNameLabel = nullptr;
        wxStaticText* m_timeLabel = nullptr;
        wxStaticText* mVolumeLabel = nullptr;
        wxButton* m_playButton;
        wxButton* m_pauseButton;
        wxButton* m_stopButton;
        wxButton* mControlsButton;
        wxSlider* m_positionSlider;
        wxSlider* m_volumeSlider;

        //multithreading
        wxMutex m_guiUpdateMutex;

        //helper variables
        bool mVolumeVisible = false;

        //playlist-related
        Bassplay::Listener::PlaylistListener m_playlistListener;
        bool m_playlistListenerRegistered = false;

        //external frames
        SongInfoFrame* m_songInfoFrame = nullptr;
        PlaylistFrame* m_playlistFrame = nullptr;

        //ui building
        void BuildMainMenu();
        void BuildPlayerPanel();
        void BuildFileMenu();
        //history handling
        void BuildHistory();
        //events
        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnInfo(wxCommandEvent& event);
        void OnMenu(wxCommandEvent& event);
        void OnPlaylists(wxCommandEvent& event);
        //play controls
        void OnPlay(wxCommandEvent& event);
        void OnPause(wxCommandEvent& event);
        void OnStop(wxCommandEvent& event);
        void OnPositionSliderDragged(wxScrollEvent& event);
        void OnVolumeSliderDragged(wxScrollEvent& event);
        void OnVolumeButtonPress(wxCommandEvent& event);

        //helper methods
        void UpdatePlayLabel();
        void UpdateTimeLabel();

        void UpdatePositionSlider();
        void OpenSong(std::string& path);

        //ui control
        static void ForcePauseGUIUpdates();

        wxDECLARE_EVENT_TABLE();
    };

} // Bassplay



#endif //BASSPLAY_2_PLAYERFRAME_HPP
