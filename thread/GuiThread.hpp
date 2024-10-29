//
// Created by aleksander on 18.06.22.
//

#ifndef BASSPLAY_2_GUITHREAD_HPP
#define BASSPLAY_2_GUITHREAD_HPP

#include "../common/wx.hpp"
#include "../ui/PlayerFrame.hpp"

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



#endif //BASSPLAY_2_GUITHREAD_HPP
