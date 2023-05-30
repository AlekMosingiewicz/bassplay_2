//
// Created by aleksander on 29.08.22.
//

#ifndef BASSPLAY_2_SONGCOLLECTION_H
#define BASSPLAY_2_SONGCOLLECTION_H

#include "../serializer/ISerializable.h"
#include "../Song.h"
#include "../serializer/ISongCollectionSerializer.h"
#include <list>
#include <unordered_map>

namespace Bassplay::Play::Serializer {
    class ISongCollectionSerializer;
}

namespace Bassplay::Play::Collection {

    class SongCollection {
    protected:
        std::unordered_map<std::string, Song*> m_songs;
    public:
        SongCollection() = default;
        [[nodiscard]] std::list<Song*> GetSongs() const;
        void AddSong(Song* t_song);
        void RemoveSong(const std::string &name);
        void RemoveAllSongs();
    };

} // Bassplay

#endif //BASSPLAY_2_SONGCOLLECTION_H
