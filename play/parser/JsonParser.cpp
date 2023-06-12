//
// Created by aleksander on 11.06.23.
//

#include "JsonParser.h"

namespace Bassplay::Play::Parser {
    void JsonParser::Parse(const std::string &json) {
        //find beginning and end of array
        size_t array_begin = json.find('[', 0);
        size_t array_end = json.find(']', array_begin);

        m_data = ParseArray(json.substr(array_begin, array_end));
    }

    std::vector<std::unordered_map<std::string,std::string >> JsonParser::ParseArray(const std::string &arrayString) {
        std::vector<std::string> elements_string;
        std::vector<std::unordered_map<std::string,std::string >> parsedElements;
        size_t pointer = 0;
        size_t beginning;
        size_t ending;

        while (pointer < arrayString.length()) {
            pointer = arrayString.find('{', pointer);

            if (pointer == std::string::npos) {
                break;
            }

            beginning = pointer;
            pointer = arrayString.find('}', pointer);
            ending = pointer;
            elements_string.push_back(arrayString.substr(0,ending));
        }

        parsedElements.reserve(elements_string.size());

        for(const std::string& elementString: elements_string) {
            parsedElements.push_back(ParseElement(elementString));
        }

        return parsedElements;
    }

    std::unordered_map<std::string, std::string> JsonParser::ParseElement(const std::string &elementString) {
        std::unordered_map<std::string,std::string> parameters;
        size_t pos = 0;
        size_t nameStart;
        size_t nameEnd;
        size_t valueStart;
        size_t valueEnd;
        bool endFlag = false;

        while (!endFlag) {
            nameStart = elementString.find('\"', pos) + 1;
            nameEnd = elementString.find(':', nameStart) - 1;
            std::string name(elementString.substr(nameStart, (nameEnd - nameStart)));
            pos = nameEnd+3;
            valueStart = pos;
            valueEnd = elementString.find(',', pos) - 1;

            if (valueEnd > elementString.length()) {
                valueEnd = elementString.find('\"', pos);
                endFlag = true;
            }

            std::string value(elementString.substr(valueStart, (valueEnd - valueStart)));
            parameters[name] = value;
            pos = valueEnd + 1;
        }

        return parameters;
    }
} // Bassplay