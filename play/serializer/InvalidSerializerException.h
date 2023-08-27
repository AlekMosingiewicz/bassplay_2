//
// Created by aleksander on 29.08.22.
//

#ifndef BASSPLAY_2_INVALIDSERIALIZEREXCEPTION_H
#define BASSPLAY_2_INVALIDSERIALIZEREXCEPTION_H

#include <exception>

namespace Bassplay::Play::Serializer {

    class InvalidSerializerException: public std::exception {

    };

} // Bassplay

#endif //BASSPLAY_2_INVALIDSERIALIZEREXCEPTION_H
