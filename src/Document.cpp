//
// Created by m3t4l on 1/31/26.
//

#include "Document.h"


Document::Document(int id) : id(id) {
}

void Document::set(const std::string &key, const std::string &value) {
    fields[key] = value;
}

std::string Document::get(const std::string &key) const {
    auto it = fields.find(key);
    return (it != fields.end()) ? it->second : "";
}

int Document::getId() const { return id; }

bool Document::matches(const std::string &key, const std::string &value) const {
    auto it = fields.find(key);
    return (it != fields.end() && it->second == value);
}

std::string Document::toString() const {
    std::stringstream ss;
    ss << "{ _id: " << id;
    for (const auto &pair: fields) {
        ss << ", " << pair.first << ": \"" << pair.second << "\"";
    }
    ss << " }";
    return ss.str();
}

std::string Document::toJSON() const {
    std::stringstream ss;
    ss << "{\"_id\":" << id;
    for (const auto &pair: fields) {
        ss << ",\"" << pair.first << "\":\"" << pair.second << "\"";
    }
    ss << "}";
    return ss.str();
}

const std::map<std::string, std::string> &Document::getFields() const {
    return fields;
}
