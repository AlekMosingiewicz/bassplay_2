//
// Created by aleksander on 04.07.22.
//

#include "SongInfoFrame.h"

namespace Bassplay::Ui {
    void SongInfoFrame::BuildInfoWindow() {
        m_mainPanel = new wxPanel(this);
        m_mainInfo = new wxNotebook;
        m_mainPanel->AddChild(m_mainInfo);
        if (m_song != nullptr) {
            SetInfoPages();
        }
    }

    void SongInfoFrame::ResetInfoWindow() {
        if (m_generalInfo != nullptr) {
            this->RemovePage(m_generalInfo, infoPages::infoPageGeneral);
        }
        if (m_sampleInfo != nullptr) {
            this->RemovePage(m_sampleInfo, infoPages::infoPageSample);
        }
        if (m_messageInfo != nullptr) {
            this->RemovePage(m_messageInfo, infoPages::infoPageMessage);
        }
        if (m_instrumentInfo != nullptr) {
            this->RemovePage(m_instrumentInfo, infoPages::infoPageInstruments);
        }
    }

    void SongInfoFrame::RemovePage(wxNotebookPage *page, size_t index) {
        m_mainInfo->RemovePage(index);
        page->Destroy();
        page = nullptr;
    }

    void SongInfoFrame::SetInfoPages() {
        m_generalInfo = new wxNotebookPage;
        m_sampleInfo = new wxNotebookPage;
        m_messageInfo = new wxNotebookPage;
        m_instrumentInfo = new wxNotebookPage;

        m_mainInfo->InsertPage(infoPages::infoPageMessage, m_messageInfo, wxString(m_song->GetMessage()));
        m_mainInfo->InsertPage(infoPages::infoPageSample, m_sampleInfo, wxString(m_song->GetHumanReadableSamples()));
        m_mainInfo->InsertPage(infoPages::infoPageInstruments, m_instrumentInfo, wxString(m_song->GetHumanReadableInstruments()));

    }

    void SongInfoFrame::SetSong(Play::Song *t_song) {
        m_song = t_song;
        ResetInfoWindow();
        SetInfoPages();
    }
} // Bassplay