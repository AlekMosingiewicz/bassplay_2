//
// Created by aleksander on 04.07.22.
//

#ifndef BASSPLAY_2_SONGINFOFRAME_H
#define BASSPLAY_2_SONGINFOFRAME_H

#include "../play/Song.h"
#include <wx/wx.h>
#include <wx/notebook.h>

enum infoPages {
    infoPageGeneral,
    infoPageMessage,
    infoPageSample,
    infoPageInstruments
};

namespace Bassplay::Ui {

    class SongInfoFrame: public wxFrame {
    public:
        SongInfoFrame() { BuildInfoWindow(); };
        SongInfoFrame(Play::Song* t_song): m_song(t_song) { BuildInfoWindow(); };
        void SetSong(Play::Song* t_song);
    private:
        //fields
        Play::Song* m_song = nullptr;
        //ui fields
        wxPanel* m_mainPanel = nullptr;
        wxNotebook* m_mainInfo = nullptr;
        wxNotebookPage* m_generalInfo = nullptr;
        wxNotebookPage* m_messageInfo = nullptr;
        wxNotebookPage* m_sampleInfo = nullptr;
        wxNotebookPage* m_instrumentInfo = nullptr;

        //functions
        void BuildInfoWindow();
        void ResetInfoWindow();

        void RemovePage(wxNotebookPage* page, size_t index);
        void SetInfoPages();
    };

} // Bassplay

#endif //BASSPLAY_2_SONGINFOFRAME_H
