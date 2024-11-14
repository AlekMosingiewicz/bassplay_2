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
        auto history_path = GetAppDir() + "/history_stream.json";
        if (!wxFileExists(history_path) || m_player == nullptr) {
            return;
        }
        wxFile historyFile(history_path);
        wxString buffer;
        historyFile.ReadAll(&buffer);
        std::string jsonString = buffer.ToStdString();
        if (jsonString.empty()) {
            return;
        }
        auto playbackHistory = PlaybackHistory::CreateFromJson(jsonString);
        playbackHistory->GetCollection()->SetLimit(HISTORY_SIZE);
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
        InitHistoryDir();
        auto appDir = GetAppDir();
        wxString wxHistoryPath = appDir + "/history_stream.json";
        const char *history_path = wxHistoryPath.c_str();

        std::fstream history_stream(history_path, std::ostream::out);
        if (!history_stream.is_open()) {
            wxLogError(wxString("Failed to open history file for writing"));
            return;
        }

        PlaybackHistoryPersister persister(&history_stream);
        persister.persist(m_player->GetPlaybackHistory());
        history_stream.close();
    }

    wxString BassplayApp::GetAppDir() {
        struct passwd *pw = getpwuid(getuid());
        const char *homedir = pw->pw_dir;
        wxString basePath(homedir);
        basePath += "/.bassplay";
        return basePath;
    }

} // Bassplay::App