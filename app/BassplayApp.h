//
// Created by aleksander on 09.06.22.
//

#ifndef BASSPLAY_2_BASSPLAYAPP_H
#define BASSPLAY_2_BASSPLAYAPP_H

#include "../common/wx.h"

#include <vector>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "../play/Player.h"
#include "../ui/PlayerFrame.h"
#include "../thread/GuiThread.h"
#include "../play/collection/SongCollection.h"
#include "../play/transformer/JsonSongCollectionTransformer.h"
#include "../play/parser/JsonParser.h"
#include "../play/serializer/JsonSongCollectionSerializer.h"
#include "../play/persistence/FileCollectionPersister.h"
#include "../listener/GuiThreadPauseListener.h"
#include "../event/BassplayEventDispatcher.h"
#include "../event/BassplayEventType.h"

namespace Bassplay::App {

    using namespace Bassplay::Play::History;

    const int HISTORY_SIZE = 5;

    class BassplayApp : public wxApp {
    public:
        virtual bool OnInit();
        virtual int OnExit();
    private:
        //fields
        Play::Player* m_player = nullptr;
        Ui::PlayerFrame* m_playerFrame = nullptr;
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



#endif //BASSPLAY_2_BASSPLAYAPP_H
