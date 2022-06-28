//
// Created by aleksander on 09.06.22.
//
#pragma once

#ifndef BASSPLAY_2_PLAYERFRAME_H
#define BASSPLAY_2_PLAYERFRAME_H


#include <wx/wx.h>
#include "../play/Player.h"

enum playerWidgets {
    playerWidgetsMinimum = 100,
    playerButtonPlay,
    playerButtonPause,
    playerButtonStop,
    playerPositionSlider
};



namespace Bassplay::Ui {

    class UiThread;

    class PlayerFrame: public wxFrame  {
    public:
        PlayerFrame(const wxString& title, const wxPoint& pos, const wxSize& size, Bassplay::Play::Player* musicPlayer);
        void UpdateGUI();
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
        wxButton* m_playButton;
        wxButton* m_pauseButton;
        wxButton* m_stopButton;
        wxSlider* m_positionSlider;

        //ui building
        void BuildMainMenu();
        void BuildPlayerPanel();
        //events
        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        //play controls
        void OnPlay(wxCommandEvent& event);
        void OnPause(wxCommandEvent& event);
        void OnStop(wxCommandEvent& event);
        void OnSliderDragged(wxScrollEvent& event);
        //helper methods
        void UpdatePlayLabel();
        void UpdateTimeLabel();
        void ResetPositionSlider();
        void UpdatePositionSlider();
        wxDECLARE_EVENT_TABLE();
    };

} // Bassplay



#endif //BASSPLAY_2_PLAYERFRAME_H
