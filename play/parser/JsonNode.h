//
// Created by aleksander on 18.03.24.
//

#ifndef BASSPLAY_2_JSONNODE_H
#define BASSPLAY_2_JSONNODE_H

#include <string>
#include <map>
#include <utility>

struct JsonNode {
    std::string m_name;
    std::map<std::string, JsonNode> children;
    void *m_value;

    JsonNode(std::string name, void *value): m_name (std::move(name)), m_value(value) {}
};

#endif //BASSPLAY_2_JSONNODE_H
