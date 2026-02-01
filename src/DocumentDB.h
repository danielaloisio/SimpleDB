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
