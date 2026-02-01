//
// Created by m3t4l on 1/31/26.
//

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
