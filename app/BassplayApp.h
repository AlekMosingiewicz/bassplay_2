//
// Created by aleksander on 09.06.22.
//

#ifndef BASSPLAY_2_BASSPLAYAPP_H
#define BASSPLAY_2_BASSPLAYAPP_H

#include <wx/wxprec.h>
#include <wx/event.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "../play/Player.h"
#include "../ui/PlayerFrame.h"

namespace Bassplay::App {
    class BassplayApp : public wxApp {
    public:
        virtual bool OnInit();
        virtual int OnExit();
    private:
        Play::Player* player;
    };
} // Bassplay::App



#endif //BASSPLAY_2_BASSPLAYAPP_H
