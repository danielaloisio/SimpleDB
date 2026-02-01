//
// Created by m3t4l on 1/31/26.
//

#ifndef SIMPLEDB_COLLECTION_H
#define SIMPLEDB_COLLECTION_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "Document.h"

class Collection {
private:
    std::string name;
    std::vector<std::shared_ptr<Document> > documents;
    int nextId;
    std::string dataPath;

    void saveToFile();

    std::string extractValue(const std::string &json, const std::string &key);

public:
    Collection(const std::string &name,
               const std::string &basePath);

    void loadFromFile();

    int insert(const std::map<std::string, std::string> &data);

    std::vector<std::shared_ptr<Document> > find(const std::string &key, const std::string &value);

    std::vector<std::shared_ptr<Document> > findAll();

    std::shared_ptr<Document> findById(int id);

    bool update(int id, const std::string &key, const std::string &value);

    bool remove(int id);

    std::string getName() const;

    size_t count() const;
};


#endif //SIMPLEDB_COLLECTION_H
