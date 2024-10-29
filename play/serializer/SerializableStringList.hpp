//
// Created by aleksander on 24.07.22.
//

#ifndef BASSPLAY_2_SERIALIZABLESTRINGLIST_HPP
#define BASSPLAY_2_SERIALIZABLESTRINGLIST_HPP

#include "ISerializable.hpp"
#include <string>
#include <vector>
#include <list>

namespace Bassplay::Play::Serializer {

    class SerializableStringList : public ISerializable {
    private:
        std::list<std::string> m_strings;
    public:
        SerializableStringList() = default; //default constructor
        SerializableStringList(std::list<std::string> &t_strings): m_strings(t_strings) {}
        std::string serialize() override;
        void add(std::basic_string<char> p_string) { m_strings.emplace_back(p_string); }
        void remove(std::string &p_string) { m_strings.remove(p_string); }
        std::list<std::string> getList() { return m_strings; }
    };

} // Bassplay

#endif //BASSPLAY_2_SERIALIZABLESTRINGLIST_HPP
