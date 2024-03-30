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
    std::map<std::string, JsonNode*> m_children;
    void *m_value;
    JsonNode *m_parent = nullptr;

    JsonNode(std::string name, void *value, JsonNode *parent = nullptr) : m_name(std::move(name)), m_value(value),
                                                                          m_parent(parent) {}

    void AddChild(JsonNode *child) { m_children.insert({child->m_name, child}); child->m_parent = this; }
    void RemoveChild(const std::string &name) {
        if (m_children.find(name) == m_children.end()) {
            return;
        }
        m_children.erase(name);
    }

};

#endif //BASSPLAY_2_JSONNODE_H
