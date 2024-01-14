//
// Created by aleksander on 09.06.22.
//

#include "BassplayApp.h"

namespace Bassplay::App {
    bool BassplayApp::OnInit() {
        BASS_Init(-1, 44100, 0, NULL, NULL); //start the BASS library
        m_player = new Play::Player(false);
        InitHistory();
        m_playerFrame = new Ui::PlayerFrame("Bassplay 2.0", wxPoint(50, 50), wxSize(380, 200), m_player);
        m_playerFrame->Show(true);
        InitThreads();
        return true;
    }

    int BassplayApp::OnExit() {
        StopThreads();
        BASS_Free();
        BASS_Stop();
        StopThreads();
        SaveHistory();
        delete m_player;
        return 0;
    }

    void BassplayApp::StopThread(wxThread *thread) {
        int i = 0;
        wxThreadError error = thread->Delete();
        if (error != wxTHREAD_NO_ERROR) {
            std::string errorMessage = "Problem deleting thread " + std::to_string(thread->GetId());
            errorMessage += error;
            wxLogError(wxString(errorMessage));
        }
        while (i++ < 100) {
            wxCriticalSectionLocker enter(m_pThreadCS);
            if (!thread) break;
        }
        thread->Kill();
    }

    void BassplayApp::StopThreads() {
        for (wxThread *thread: m_threads) {
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
        for (wxThread *thread: m_threads) {
            if (thread)
                RunThread(thread);
        }
    }

    void BassplayApp::InitThreads() {
        AddThread(new Thread::GuiThread(m_playerFrame));
        RunThreads();
    }

    void BassplayApp::InitHistory() {
        auto history_path = GetAppDir() + "/history_stream.json";
        if (!wxFileExists(history_path) || m_player == nullptr) {
            return;
        }
        Bassplay::Play::Parser::JsonParser parser;
        Bassplay::Play::Transformer::JsonSongCollectionTransformer transformer(&parser);
        wxFile historyFile(history_path);
        wxString buffer;
        historyFile.ReadAll(&buffer);
        auto collection = transformer.Transform(buffer.c_str());
        collection->SetLimit(HISTORY_SIZE);
        m_player->SetHistory(collection);
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
        const char* history_path = wxHistoryPath.c_str();

        Bassplay::Play::Serializer::JsonSongSerializer serializer;
        Bassplay::Play::Serializer::JsonSongCollectionSerializer songCollectionSerializer(&serializer);
        std::fstream history_stream(history_path, std::ostream::out);

        Bassplay::Play::Persistence::FileCollectionPersister persister(&history_stream, &songCollectionSerializer);
        persister.PersistCollection(*(m_player->GetHistory()));
    }

    wxString BassplayApp::GetAppDir() {
        struct passwd *pw = getpwuid(getuid());
        const char *homedir = pw->pw_dir;
        wxString basePath(homedir);
        basePath+="/.bassplay";
        return basePath;
    }

} // Bassplay::App