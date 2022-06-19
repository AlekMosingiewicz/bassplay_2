//
// Created by aleksander on 09.06.22.
//

#include "BassplayApp.h"

namespace Bassplay::App {
    bool BassplayApp::OnInit() {
        BASS_Init(-1, 44100, 0, NULL, NULL); //start the BASS library
        m_player = new Play::Player(false);
        m_playerFrame = new Ui::PlayerFrame("Bassplay 2.0", wxPoint(50, 50), wxSize(300, 150), m_player);
        m_playerFrame->Show(true);
        InitThreads();
        return true;
    }
    int BassplayApp::OnExit() {
        delete m_player;
        StopThreads();
        BASS_Free();
        BASS_Stop();
        StopThreads();
        return 0;
    }
    void BassplayApp::StopThread(wxThread *thread) {
        if (thread->Delete() != wxTHREAD_NO_ERROR) {
            std::string errorMessage = "Problem deleting thread " + std::to_string(thread->GetId());
            wxLogError(wxString(errorMessage));
        }
        wxCriticalSectionLocker enter(m_pThreadCS);
    }

    void BassplayApp::StopThreads() {
        for (wxThread* thread:m_threads) {
            if (thread)
                StopThread(thread);
        }
    }

    void BassplayApp::RunThread(wxThread *thread) {
        wxThreadError error = thread->Run();
        if (error != wxTHREAD_NO_ERROR) {
            wxLogError(wxString(std::string("Failed to initiate the thread; error code " + std::to_string(error))));
        }
    }

    void BassplayApp::RunThreads() {
        for (wxThread* thread : m_threads) {
            if (thread)
                RunThread(thread);
        }
    }

    void BassplayApp::InitThreads() {
        AddThread(new Thread::GuiThread(m_playerFrame));
        RunThreads();
    }

} // Bassplay::App