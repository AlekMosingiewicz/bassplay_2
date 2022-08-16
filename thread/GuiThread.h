//
// Created by aleksander on 18.06.22.
//

#ifndef BASSPLAY_2_GUITHREAD_H
#define BASSPLAY_2_GUITHREAD_H

#include "../common/wx.h"
#include "../ui/PlayerFrame.h"

namespace Bassplay::Thread {
    class GuiThread: public wxThread {
    public:
        GuiThread(Ui::PlayerFrame* t_playerFrame): wxThread(wxTHREAD_DETACHED), m_playerFrame(t_playerFrame) {};
    private:
        Ui::PlayerFrame* m_playerFrame = nullptr;
    protected:
        ExitCode Entry() override;
    };
}



#endif //BASSPLAY_2_GUITHREAD_H
