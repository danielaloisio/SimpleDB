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

#ifndef SIMPLEDB_DOCUMENT_H
#define SIMPLEDB_DOCUMENT_H
#include <map>
#include <string>
#include <sstream>


class Document {
private:
    std::map<std::string, std::string> fields;
    int id;

public:
    Document(int id);

    void set(const std::string &key, const std::string &value);

    std::string get(const std::string &key) const;

    int getId() const;

    bool matches(const std::string &key, const std::string &value) const;

    std::string toString() const;

    std::string toJSON() const;

    const std::map<std::string, std::string> &getFields() const;
};


#endif //SIMPLEDB_DOCUMENT_H
