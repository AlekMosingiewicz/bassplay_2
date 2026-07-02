//
// Created by aleksander on 23.10.2025.
//

#ifndef BASSPLAY_2_PLAYLISTLISTENER_HPP
#define BASSPLAY_2_PLAYLISTLISTENER_HPP

#include "../event/IBassplayEventHandler.hpp"
#include "../ui/PlaylistFrame.hpp"
#include "../event/BassplayGuiEvent.hpp"
#include "../play/Player.hpp"
#include <typeinfo>

namespace Bassplay::Listener {

    using namespace Event;
    using namespace Ui;
    using namespace Play;

    class PlaylistListener: public IBassplayEventHandler {
    public:
        PlaylistListener() = default;
        explicit PlaylistListener(PlaylistFrame *pFrame, Player *pPlayer): m_playlistFrame(pFrame), m_player(pPlayer) {}

        void SetPlayer(Player *player) { m_player = player; }
        void SetPlaylistFrame(PlaylistFrame *playlistFrame) { m_playlistFrame = playlistFrame; }

        void Handle(Event::BassplayEvent &event) override;
    private:
        void HandlePlaybackEvent(Event::BassplayPlaybackEvent &event);
        void HandleGuiEvent(Event::BassplayGuiEvent &event);

        PlaylistFrame *m_playlistFrame;
        Player *m_player;
    };
}


#endif //BASSPLAY_2_PLAYLISTLISTENER_HPP
