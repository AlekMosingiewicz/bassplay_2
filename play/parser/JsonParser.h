
//
// Created by aleksander on 11.06.23.
//

#ifndef BASSPLAY_2_JSONPARSER_H
#define BASSPLAY_2_JSONPARSER_H

#include <unordered_map>
#include <string>
#include <vector>

namespace Bassplay::Play::Parser {

    class JsonParser {
    public:
        JsonParser() = default;
        void Parse(const std::string &json);
        void Parse(const char* json) { Parse(std::string(json)); }
        std::vector<std::unordered_map<std::string,std::string >> GetData() { return m_data; }
    private:
        std::vector<std::unordered_map<std::string,std::string >> m_data;
        std::vector<std::unordered_map<std::string,std::string >> ParseArray(const std::string &arrayString);
        std::unordered_map<std::string, std::string> ParseElement(const std::string &elementString);
    };

} // Bassplay

#endif //BASSPLAY_2_JSONPARSER_H
