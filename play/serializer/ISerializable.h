//
// Created by aleksander on 22.07.22.
//

#ifndef BASSPLAY_2_ISERIALIZABLE_H
#define BASSPLAY_2_ISERIALIZABLE_H

#include <string>

namespace Bassplay::Play::Serializer {

    class ISerializable {
    public:
        ISerializable() = default;
        virtual ~ISerializable() = default;
        virtual std::string serialize() = 0;
    };

} // Bassplay

#endif //BASSPLAY_2_ISERIALIZABLE_H
