//
// Created by aleksander on 18.06.22.
//

#include "GuiThread.h"

namespace Bassplay::Thread {
    wxThread::ExitCode GuiThread::Entry() {
        while (!TestDestroy()) {
            m_playerFrame->UpdateGUI();
            This()->Sleep(500);
        }
        return nullptr;
    }
}
