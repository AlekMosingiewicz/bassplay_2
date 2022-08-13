//
// Created by aleksander on 04.07.22.
//

#include "SongInfoFrame.h"

namespace Bassplay::Ui {
    void SongInfoFrame::BuildInfoWindow() {
        m_mainPanel = new wxPanel(this);
        m_mainInfo = new wxNotebook;
        m_generalInfo = new wxNotebookPage;
        m_sampleInfo = new wxNotebookPage;
        m_messageInfo = new wxNotebookPage;

        m_mainInfo->InsertPage(infoPages::infoPageMessage, m_messageInfo, wxString(m_song->GetMessage()));
        m_mainInfo->InsertPage(infoPages::infoPageSample, m_sampleInfo, wxString(m_song->GetHumanReadableSamples()));
    }
} // Bassplay