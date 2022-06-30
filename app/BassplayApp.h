//
// Created by aleksander on 09.06.22.
//

#ifndef BASSPLAY_2_BASSPLAYAPP_H
#define BASSPLAY_2_BASSPLAYAPP_H

#include "../common/wx.h"

#include <vector>
#include "../play/Player.h"
#include "../ui/PlayerFrame.h"
#include "../thread/GuiThread.h"

namespace Bassplay::App {
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
    };
} // Bassplay::App



#endif //BASSPLAY_2_BASSPLAYAPP_H
