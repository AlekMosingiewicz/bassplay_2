//
// Created by aleksander on 09.06.22.
//

#ifndef BASSPLAY_2_BASSEXCEPTION_H
#define BASSPLAY_2_BASSEXCEPTION_H

#include <exception>

namespace Bassplay {

    class BassException : public std::exception {
    private:
        int code;
    public:
        BassException(int errorCode) : code(errorCode) {}
        int GetCode() { return code; }
    };

} // Bassplay

#endif //BASSPLAY_2_BASSEXCEPTION_H
