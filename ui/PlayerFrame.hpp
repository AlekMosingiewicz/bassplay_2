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

enum playerWidgets {
    playerWidgetsMinimum = 200,
    playerButtonPlay,
    playerButtonPause,
    playerButtonStop,
    playerButtonControls,
    playerPositionSlider,
    playerVolumeSlider,
    playerInfoWindow
};



namespace Bassplay::Ui {

    class UiThread;

    class PlayerFrame: public DpiAwareFrame  {
    public:
        PlayerFrame(const wxString& title, const wxPoint& pos, const wxSize& size, Bassplay::Play::Player* musicPlayer);
        void UpdateGUI(bool withPlayLabelUpdate = true);
        void StopAndReset();
        //info
        void ShowInfoFrame();

    private:
        //dependencies
        Bassplay::Play::Player* m_player;
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
        wxMutex m_playLabelMutex;

        //helper variables
        bool mVolumeVisible = false;

        //external frames
        SongInfoFrame* m_songInfoFrame = nullptr;

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
        void ResetPositionSlider();
        void UpdatePositionSlider();
        void OpenSong(std::string& path);

        wxDECLARE_EVENT_TABLE();
    };

} // Bassplay



#endif //BASSPLAY_2_PLAYERFRAME_HPP
