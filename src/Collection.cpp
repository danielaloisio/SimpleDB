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

#include "Collection.h"


Collection::Collection(const std::string &name, const std::string &basePath)
    : name(name), nextId(1), dataPath(basePath + name + ".json") {
    loadFromFile();
}

void Collection::saveToFile() {
    std::ofstream file(dataPath);
    if (!file.is_open()) {
        std::cerr << "Error open file: " << dataPath << std::endl;
        return;
    }

    file << "{\"name\":\"" << name << "\",\"nextId\":" << nextId << ",\"documents\":[";
    for (size_t i = 0; i < documents.size(); ++i) {
        file << documents[i]->toJSON();
        if (i < documents.size() - 1) file << ",";
    }
    file << "]}";
    file.close();
    std::cout << "[DISC] Collection '" << name << "' save in " << dataPath << std::endl;
}

std::string Collection::extractValue(const std::string &json, const std::string &key) {
    std::string searchKey = "\"" + key + "\":";
    size_t pos = json.find(searchKey);
    if (pos == std::string::npos) return "";

    pos += searchKey.length();
    if (json[pos] == '"') {
        size_t start = pos + 1;
        size_t end = json.find("\"", start);
        return json.substr(start, end - start);
    } else {
        size_t end = json.find_first_of(",}", pos);
        return json.substr(pos, end - pos);
    }
}

void Collection::loadFromFile() {
    std::ifstream file(dataPath);
    if (!file.is_open()) {
        std::cout << "[DISC] File not found, create new collection: " << name << std::endl;
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();

    std::string nextIdStr = extractValue(content, "nextId");
    if (!nextIdStr.empty()) {
        nextId = std::stoi(nextIdStr);
    }

    size_t docStart = content.find("\"documents\":[");
    if (docStart != std::string::npos) {
        docStart += 13;
        size_t docEnd = content.find("]}", docStart);
        std::string docsStr = content.substr(docStart, docEnd - docStart);

        size_t pos = 0;
        while ((pos = docsStr.find("{", pos)) != std::string::npos) {
            size_t end = docsStr.find("}", pos);
            std::string docStr = docsStr.substr(pos, end - pos + 1);

            std::string idStr = extractValue(docStr, "_id");
            if (!idStr.empty()) {
                int id = std::stoi(idStr);
                auto doc = std::make_shared<Document>(id);

                size_t fieldPos = 0;
                while ((fieldPos = docStr.find("\"", fieldPos)) != std::string::npos) {
                    size_t keyStart = fieldPos + 1;
                    size_t keyEnd = docStr.find("\"", keyStart);
                    std::string key = docStr.substr(keyStart, keyEnd - keyStart);

                    if (key == "_id") {
                        fieldPos = keyEnd + 1;
                        continue;
                    }

                    size_t valueStart = docStr.find("\"", keyEnd + 2) + 1;
                    size_t valueEnd = docStr.find("\"", valueStart);
                    std::string value = docStr.substr(valueStart, valueEnd - valueStart);

                    doc->set(key, value);
                    fieldPos = valueEnd + 1;
                }

                documents.push_back(doc);
            }
            pos = end + 1;
        }
    }

    std::cout << "[DISC] Collection '" << name << "' loaded with "
            << documents.size() << " documents" << std::endl;
}

int Collection::insert(const std::map<std::string, std::string> &data) {
    auto doc = std::make_shared<Document>(nextId++);
    for (const auto &pair: data) {
        doc->set(pair.first, pair.second);
    }
    documents.push_back(doc);
    saveToFile();
    return doc->getId();
}

std::vector<std::shared_ptr<Document> > Collection::find(const std::string &key, const std::string &value) {
    std::vector<std::shared_ptr<Document> > results;
    for (const auto &doc: documents) {
        if (doc->matches(key, value)) {
            results.push_back(doc);
        }
    }
    return results;
}

std::vector<std::shared_ptr<Document> > Collection::findAll() {
    return documents;
}

std::shared_ptr<Document> Collection::findById(int id) {
    auto it = std::find_if(documents.begin(), documents.end(),
                           [id](const std::shared_ptr<Document> &doc) {
                               return doc->getId() == id;
                           });
    return (it != documents.end()) ? *it : nullptr;
}

bool Collection::update(int id, const std::string &key, const std::string &value) {
    auto doc = findById(id);
    if (doc) {
        doc->set(key, value);
        saveToFile();
        return true;
    }
    return false;
}

bool Collection::remove(int id) {
    auto it = std::find_if(documents.begin(), documents.end(),
                           [id](const std::shared_ptr<Document> &doc) {
                               return doc->getId() == id;
                           });
    if (it != documents.end()) {
        documents.erase(it);
        saveToFile();
        return true;
    }
    return false;
}

std::string Collection::getName() const { return name; }
size_t Collection::count() const { return documents.size(); }
