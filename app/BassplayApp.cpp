//
// Created by aleksander on 09.06.22.
//

#include "BassplayApp.h"

namespace Bassplay::App {
    bool BassplayApp::OnInit() {
        BASS_Init(-1, 44100, 0, NULL, NULL); //start the BASS library
        player = new Play::Player(false);
        auto *playerFrame = new Ui::PlayerFrame("Bassplay 2.0", wxPoint(50, 50), wxSize(300, 150), player);
        playerFrame->Show(true);
        return true;
    }
    int BassplayApp::OnExit() {
        delete player;
        return 0;
    }

} // Bassplay::App