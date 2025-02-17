//
// Created by aleksander on 09.06.22.
//

#include "BassplayApp.hpp"

namespace Bassplay::App {
    bool BassplayApp::OnInit() {
        BASS_Init(-1, 44100, 0, NULL, NULL); //start the BASS library
        m_player = new Play::Player(false);
        wxInitAllImageHandlers();
        InitHistory();
        m_playerFrame = new Ui::PlayerFrame("Bassplay 2.0", wxPoint(50, 50), wxSize(23, 7), m_player);
        m_playerFrame->Show(true);
        InitThreads();
        return true;
    }

    int BassplayApp::OnExit() {
        BASS_Free();
        BASS_Stop();
        StopThreads();
        SaveHistory();
        delete m_player;
        return 0;
    }

    void BassplayApp::StopThread(wxThread *thread) {
        int i = 0;
        thread->Pause();
        wxThreadError error = thread->Delete();
        if (error != wxTHREAD_NO_ERROR) {
            std::string errorMessage = "Problem deleting thread " + std::to_string(thread->GetId());
            errorMessage += std::to_string(error);
            wxLogError(wxString(errorMessage));
        }
        while (i++ < 100) {
            wxCriticalSectionLocker enter(m_pThreadCS);
        }
    }

    void BassplayApp::StopThreads() {
        for (wxThread *thread: m_threads) {
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
        for (wxThread *thread: m_threads) {
            if (thread)
                RunThread(thread);
        }
    }

    void BassplayApp::InitThreads() {
        auto *guiThread = new Thread::GuiThread(m_playerFrame);
        Bassplay::Event::BassplayEventDispatcher::Instance().RegisterHandler(
                Event::playbackEvent,
                new Bassplay::Listener::GuiThreadPauseListener(guiThread, m_playerFrame)
        );
        AddThread(guiThread);
        RunThreads();
    }

    void BassplayApp::InitHistory() {
        auto playbackHistory = Facade::InitHistory();
        m_player->SetPlaybackHistory(playbackHistory);
    }

    void BassplayApp::InitHistoryDir() {
        auto dirPath = GetAppDir();
        if (!wxDirExists(dirPath)) {
            wxMkdir(dirPath);
        }
    }

    void BassplayApp::SaveHistory() {
        if (m_player == nullptr) {
            return;
        }
        Facade::SaveHistory(m_player->GetPlaybackHistory());
    }

    wxString BassplayApp::GetAppDir() {
        struct passwd *pw = getpwuid(getuid());
        const char *homedir = pw->pw_dir;
        wxString basePath(homedir);
        basePath += "/.bassplay";
        return basePath;
    }

} // Bassplay::App