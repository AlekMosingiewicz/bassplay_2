//
// Created by aleksander on 29.06.25.
//

#ifndef BASSPLAY_2_MANAGER_HPP
#define BASSPLAY_2_MANAGER_HPP

#include <map>
#include "BassplayPlaylist.hpp"
#include "../persistence/BulkPlaylistsPersister.hpp"
#include "../provider/IPlaylistProvider.hpp"
#include <list>
#include <string>
#include <fstream>

namespace Bassplay::Play::Playlist {
    using Bassplay::Play::Persistence::BulkPlaylistsPersister;
    using Bassplay::Play::Provider::IPlaylistProvider;

    class Manager {
    private:
        std::map<std::string, BassplayPlaylist *> *m_playlists;
        IPlaylistProvider *m_playlistProvider = nullptr;
        std::string m_filePath;
    public:
        Manager() = default;

        explicit Manager(IPlaylistProvider *playlistProvider) : m_playlistProvider(playlistProvider) {
            LoadPlaylists();
        }

        Manager(IPlaylistProvider *playlistProvider, std::string filePath)
                : m_playlistProvider(playlistProvider), m_filePath(filePath) {
            LoadPlaylists();
        }

        ~Manager() {
            for (auto &pair: (*m_playlists)) {
                delete pair.second;
            }
        }

        void LoadPlaylists() {
            if (m_playlistProvider) {
                m_playlists = m_playlistProvider->GetPlaylists();
            }
        }

        void SavePlaylists(const std::list<BassplayPlaylist *> &playlists) {
            auto playlistPersistStream = std::fstream(m_filePath, std::ios::out | std::ios::trunc);
            BulkPlaylistsPersister persister(&playlistPersistStream);
            persister.persist(playlists);
        }

        void SavePlaylists() {
            std::list<BassplayPlaylist *> playlists;
            for (auto &pair: (*m_playlists)) {
                playlists.push_back(pair.second);
            }
            SavePlaylists(playlists);
        }

        BassplayPlaylist *GetPlaylist(const std::string &name) {
            return (*m_playlists)[name];
        }

        std::map<std::string, BassplayPlaylist *> *GetPlaylists() {
            if (m_playlists->empty()) {
                LoadPlaylists();
            }
            return m_playlists;
        }

        void AddPlaylist(BassplayPlaylist *playlist) {
            (*m_playlists)[playlist->GetName()] = playlist;
        }

        void RemovePlaylist(const std::string &name) {
            auto it = m_playlists->find(name);
            if (it != m_playlists->end()) {
                for (auto &song: it->second->GetCollection()->GetSongs()) {
                    delete song; // Free memory of songs
                }
                delete it->second; // Free memory
                m_playlists->erase(it);
            }
        }
    };
} // Bassplay

#endif //BASSPLAY_2_MANAGER_HPP
