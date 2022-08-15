//
// Created by aleksander on 04.07.22.
//

#ifndef BASSPLAY_2_SONGINFOFRAME_H
#define BASSPLAY_2_SONGINFOFRAME_H

#include "../play/Song.h"
#include <wx/wx.h>
#include <wx/notebook.h>

namespace Bassplay::Ui {

    class SongInfoFrame : public wxFrame {
    public:
        SongInfoFrame() { BuildInfoWindow(); };

        SongInfoFrame(Play::Song *t_song, wxWindow *parent = nullptr, wxWindowID = wxID_ANY,
                      const wxString &title = "Mod info", const wxPoint &pos = wxPoint(0, 0),
                      const wxSize &size = wxSize(600, 600)) :
                wxFrame(parent, wxID_ANY, title, pos, size, wxCLOSE_BOX | wxMINIMIZE_BOX),
                m_song(t_song) { BuildInfoWindow(); };

        void SetSong(Play::Song *t_song);

    private:
        //fields
        Play::Song *m_song = nullptr;
        //ui fields
        wxPanel *m_mainPanel = nullptr;
        wxNotebook *m_mainInfo = nullptr;
        wxTextCtrl *m_generalInfo = nullptr;
        wxTextCtrl *m_messageInfo = nullptr;
        wxTextCtrl *m_sampleInfo = nullptr;
        wxTextCtrl *m_instrumentInfo = nullptr;

        //functions
        void BuildInfoWindow();
        void SetInfoPages();
        void SetMainInfoPage();
    };

} // Bassplay

#endif //BASSPLAY_2_SONGINFOFRAME_H
