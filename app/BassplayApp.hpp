//
// Created by aleksander on 09.06.22.
//

#ifndef BASSPLAY_2_BASSPLAYAPP_HPP
#define BASSPLAY_2_BASSPLAYAPP_HPP

#include "../common/wx.hpp"

#include <vector>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <map>
#include "../play/Player.hpp"
#include "../ui/PlayerFrame.hpp"
#include "../thread/GuiThread.hpp"
#include "../play/collection/SongCollection.hpp"
#include "../listener/GuiThreadPauseListener.hpp"
#include "../event/BassplayEventDispatcher.hpp"
#include "../event/BassplayEventType.hpp"
#include "../play/persistence/PlaybackHistoryPersister.hpp"
#include "playlist/BassplayPlaylist.hpp"
#include "../play/history/facade.hpp"
#include "../play/playlist/factory/ManagerFactory.hpp"

namespace Bassplay::App {

    using namespace Bassplay::Play::History;
    using namespace Bassplay::Play::Playlist;
    using Bassplay::Play::Persistence::PlaybackHistoryPersister;
    using Bassplay::Play::Manager;
    using Bassplay::Play::Playlist::Factory::ManagerFactory;

    const int HISTORY_SIZE = 5;
    const std::string DEFAULT_PLAYLIST_FILENAME = "playlists.json";

    class BassplayApp : public wxApp {
    public:
        virtual bool OnInit();
        virtual int OnExit();
    private:
        //fields
        Play::Player* m_player = nullptr;
        Ui::PlayerFrame* m_playerFrame = nullptr;
        Play::Playlist::Manager* m_playlistManager = nullptr;
        std::vector<wxThread*> m_threads;
        wxCriticalSection m_pThreadCS;


        //methods
        void InitThreads();
        void StopThreads();
        void StopThread(wxThread* thread);
        void AddThread(wxThread* thread) { m_threads.push_back(thread); }
        void RunThread(wxThread* thread);
        void RunThreads();
        void InitHistory();
        static void InitHistoryDir();
        void SaveHistory();
        static wxString GetAppDir();
    };
} // Bassplay::App



#endif //BASSPLAY_2_BASSPLAYAPP_HPP
