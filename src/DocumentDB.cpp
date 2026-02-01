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

#include "DocumentDB.h"


DocumentDB::DocumentDB(const std::string &basePath) : basePath(basePath) {
    system(("mkdir -p " + basePath).c_str());
}

std::shared_ptr<Collection> DocumentDB::getCollection(const std::string &name) {
    if (collections.find(name) == collections.end()) {
        collections[name] = std::make_shared<Collection>(name, basePath);
    }
    return collections[name];
}

std::vector<std::string> DocumentDB::listCollections() {
    std::vector<std::string> names;
    for (const auto &pair: collections) {
        names.push_back(pair.first);
    }
    return names;
}

bool DocumentDB::dropCollection(const std::string &name) {
    if (collections.erase(name) > 0) {
        std::string filepath = basePath + name + ".json";
        remove(filepath.c_str());
        return true;
    }
    return false;
}
