//
// Created by aleksander on 18.03.24.
//

#ifndef BASSPLAY_2_JSONNODE_H
#define BASSPLAY_2_JSONNODE_H

#include <string>
#include <map>
#include <utility>
#include <list>

namespace Bassplay::Play::Parser {

    enum class JsonNodeType {
        INT_ARRAY,
        FLOAT_ARRAY,
        STRING_ARRAY,
        STRING,
        INTEGER,
        FLOAT,
    };

    struct JsonNode {
        std::map<std::string, JsonNode *> m_children;
        std::string m_stringValue;
        int m_intValue;
        float m_floatValue;
        JsonNodeType m_type;
        JsonNode *m_parent = nullptr;
        std::list<std::string> m_stringArray;
        std::list<int> m_intArray;
        std::list<float> m_floatArray;

        // Constructor overloaded for integer type
        explicit JsonNode(int value, JsonNode *parent = nullptr) : m_intValue(value), m_parent(parent),
                                                                   m_floatValue(0) {
            m_type = JsonNodeType::INTEGER;
        }

        // Constructor overloaded for float type
        explicit JsonNode(float value, JsonNode *parent = nullptr) : m_floatValue(value), m_intValue(0),
                                                                     m_parent(parent) {
            m_type = JsonNodeType::FLOAT;
        }

        // Constructor overloaded for string type
        explicit JsonNode(std::string &value, JsonNode *parent = nullptr) : m_stringValue(std::move(value)),
                                                                            m_intValue(0), m_floatValue(0),
                                                                            m_parent(parent) {
            m_type = JsonNodeType::STRING;
        }

        explicit JsonNode(std::list<int> &value, JsonNode *parent = nullptr) : m_intArray(value), m_intValue(0),
                                                                               m_floatValue(0), m_parent(parent) {
            m_type = JsonNodeType::INT_ARRAY;
        }

        explicit JsonNode(std::list<float> &value, JsonNode *parent = nullptr) : m_floatArray(value), m_intValue(0),
                                                                                 m_floatValue(0), m_parent(parent) {
            m_type = JsonNodeType::FLOAT_ARRAY;
        }

        explicit JsonNode(std::list<std::string> &value, JsonNode *parent = nullptr) : m_stringArray(value),
                                                                                       m_intValue(0), m_floatValue(0),
                                                                                       m_parent(parent) {
            m_type = JsonNodeType::STRING_ARRAY;
        }

        void AddChild(std::string &name, JsonNode *child) {
            m_children.insert({name, child});
            child->m_parent = this;
        }

        void RemoveChild(const std::string &name) {
            if (m_children.find(name) == m_children.end()) {
                return;
            }
            m_children.erase(name);
        }

    };
}
#endif //BASSPLAY_2_JSONNODE_H
