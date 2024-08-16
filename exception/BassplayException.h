//
// Created by aleksander on 09.06.22.
//

#ifndef BASSPLAY_2_BASSPLAYEXCEPTION_H
#define BASSPLAY_2_BASSPLAYEXCEPTION_H

#include <exception>

namespace Bassplay {

    class BassplayException : public std::exception {
    private:
        int code;
    public:
        explicit BassplayException(int errorCode) : code(errorCode) {}
        [[nodiscard]] int GetCode() const { return code; }
    };

} // Bassplay

#endif //BASSPLAY_2_BASSPLAYEXCEPTION_H
