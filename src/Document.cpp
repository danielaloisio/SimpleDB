/*
Copyright (C) 2026 M3t4l

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see
<https://www.gnu.org/licenses/>.
*/

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
