#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <sstream>

#include "Document.h"
#include "Collection.h"
#include "DocumentDB.h"

int main() {
    std::cout << "=== Data base in disc ===" << std::endl;
    DocumentDB db("YOUR_PATH");

    auto user = db.getCollection("user");

    std::cout << "\n=== Insert documents  ===" << std::endl;
    int id1 = user->insert({{"name", "Kobra1"}, {"age", "30"}, {"city", "Detroit"}});
    int id2 = user->insert({{"name", "Kobra2"}, {"age", "25"}, {"city", "Santiago"}});
    int id3 = user->insert({{"name", "Kobra3"}, {"age", "40"}, {"city", "São Paulo"}});

    std::cout << "Inserted documents with IDs: " << id1 << ", " << id2 << ", " << id3 << std::endl;

    std::cout << "\n=== All documents ===" << std::endl;
    auto findAll = user->findAll();
    for (const auto& doc : findAll) {
        std::cout << doc->toString() << std::endl;
    }

    std::cout << "\n=== Search by city ===" << std::endl;
    auto result = user->find("city", "Detroit");
    for (const auto& doc : result) {
        std::cout << doc->toString() << std::endl;
    }

    std::cout << "\n=== Update document ID " << id1 << " ===" << std::endl;
    user->update(id1, "age", "40");
    auto docUpdated = user->findById(id1);
    if (docUpdated) {
        std::cout << docUpdated->toString() << std::endl;
    }

    return 0;
}
