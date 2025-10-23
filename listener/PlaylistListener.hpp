//
// Created by aleksander on 23.10.2025.
//

#ifndef BASSPLAY_2_PLAYLISTLISTENER_HPP
#define BASSPLAY_2_PLAYLISTLISTENER_HPP

#include "../event/IBassplayEventHandler.hpp"
#include "../ui/PlaylistFrame.hpp"
#include "../event/BassplayPlaybackEvent.hpp"
#include "../play/Player.hpp"

namespace Bassplay::Listener {

    using namespace Event;
    using namespace Ui;
    using namespace Play;

    class PlaylistListener: public IBassplayEventHandler {
    public:
        explicit PlaylistListener(PlaylistFrame *pFrame, Player *pPlayer): m_playlistFrame(pFrame), m_player(pPlayer) {}


        void Handle(Event::BassplayEvent &event) override;
    private:
        PlaylistFrame *m_playlistFrame;
        Player *m_player;
    };
}


#endif //BASSPLAY_2_PLAYLISTLISTENER_HPP
