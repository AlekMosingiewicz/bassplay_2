//
// Created by aleksander on 09.06.22.
//

#include "BassplayApp.h"

namespace Bassplay::App {
    bool BassplayApp::OnInit() {
        std::cout << "Hello, World from bassplay app!" << std::endl;
        Ui::PlayerFrame *playerFrame = new Ui::PlayerFrame("Bassplay 2.0", wxPoint(50, 50), wxSize(450, 340));
        playerFrame->Show(true);
        return true;
    }
} // Bassplay::App