//
// Created by aleksander on 04.07.22.
//

#include "SongInfoFrame.h"

namespace Bassplay::Ui {
    void SongInfoFrame::BuildInfoWindow() {
        m_mainPanel = new wxPanel(this);
        m_mainInfo = new wxNotebook(m_mainPanel, wxID_ANY, wxPoint(0, 0), wxSize(600, 600));

        m_sampleInfo = new wxTextCtrl(m_mainInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
                                      wxTE_READONLY|wxTE_MULTILINE
        );
        m_messageInfo = new wxTextCtrl(m_mainInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
                                       wxTE_READONLY|wxTE_MULTILINE
        );
        m_instrumentInfo = new wxTextCtrl(m_mainInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
                                          wxTE_READONLY|wxTE_MULTILINE
        );

        m_mainInfo->AddPage(m_messageInfo, wxString("Message"));
        m_mainInfo->AddPage(m_sampleInfo, wxString("Samples"));
        m_mainInfo->AddPage(m_instrumentInfo, wxString("Instruments"));

        if (m_song != nullptr) {
            SetInfoPages();
        }
    }


    void SongInfoFrame::RemovePage(wxNotebookPage *page, size_t index) {
        if (m_mainInfo != nullptr) {
            m_mainInfo->RemovePage(index);
            page->Destroy();
        }
    }

    void SongInfoFrame::SetInfoPages() {
        //m_generalInfo = new wxNotebookPage(m_mainInfo, wxID_ANY);
        m_sampleInfo->Clear();
        m_instrumentInfo->Clear();
        m_messageInfo->Clear();

        std::string samples = m_song->GetHumanReadableSamples();
        std::string instruments = m_song->GetHumanReadableInstruments();
        std::string message = m_song->GetMessage();

        wxString wxSamples = wxString(samples);
        wxString wxInstruments = wxString(instruments);
        wxString wxMessage = wxString(message);

        m_sampleInfo->WriteText(wxSamples);
        m_instrumentInfo->WriteText(wxInstruments);
        m_messageInfo->WriteText(wxMessage);
    }

    void SongInfoFrame::SetSong(Play::Song *t_song) {
        m_song = t_song;
        SetInfoPages();
    }
} // Bassplay