//
// Created by m3t4l on 1/31/26.
//

#ifndef SIMPLEDB_DOCUMENTDB_H
#define SIMPLEDB_DOCUMENTDB_H
#include <map>
#include <memory>
#include <string>

#include "Collection.h"


class DocumentDB {
private:
    std::map<std::string, std::shared_ptr<Collection> > collections;
    std::string basePath;

public:
    DocumentDB(const std::string &basePath);

    std::shared_ptr<Collection> getCollection(const std::string &name);

    std::vector<std::string> listCollections();

    bool dropCollection(const std::string &name);
};


#endif //SIMPLEDB_DOCUMENTDB_H
