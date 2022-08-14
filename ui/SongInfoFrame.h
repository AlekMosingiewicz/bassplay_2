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

        SongInfoFrame(Play::Song *t_song, const wxString &title = "Mod info", const wxPoint &pos = wxPoint(0,0),
                      const wxSize &size = wxSize(600,600)) :
                wxFrame(NULL, wxID_ANY, title, pos, size, wxDEFAULT),
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

        void RemovePage(wxNotebookPage *page, size_t index);

        void SetInfoPages();
    };

} // Bassplay

#endif //BASSPLAY_2_SONGINFOFRAME_H
