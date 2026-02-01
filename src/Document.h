//
// Created by m3t4l on 1/31/26.
//

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
