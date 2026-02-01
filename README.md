# SimpleDB

SimpleDB is a simple document database written in C++.
It stores collections of documents on disk as JSON files and provides basic operations: insert, find, update and remove.

## Overview

- Language: `C++`
- Build system: `CMake`
- Core classes: `Document`, `Collection`, and `DocumentDB`
- Persistence: each `Collection` is saved to a JSON file inside a base directory (e.g.: `users/`)

## Features

- Insert documents (string key/value pairs)
- Find by field (e.g., find all documents with `city = "Detroit"`)
- Retrieve all documents from a collection
- Find by ID
- Update document fields
- Remove document by ID
- Simple per-collection JSON persistence

## Main code structure

- `Document` — represents a document (ID + map of `string -> string`). Provides string and JSON conversion.
- `Collection` — manages a list of `Document`s, handles reading/writing to disk (`<basePath><collectionName>.json`), tracks `nextId` and implements CRUD operations.
- `DocumentDB` — manages multiple collections and creates the base directory where collection files are stored.

## Requirements

- C++ compiler(e.g., `g++` >= 10, recent `clang++`)
- `CMake` >= 3.10 (the `CMakeLists` specifies 3.31.6, so using `CMake` >= 3.31 is recommended)

## How to build

From the project root (command line):

    mkdir -p build && cd build
    cmake ..
    cmake --build .

This will create the `SimpleDB` executable inside the `build` directory (or according to your `CMake` configuration).

## How to run

From the build directory where the executable was generated:

    ./SimpleDB

The example `main.cpp` creates a `DocumentDB` with base path `users/`, gets the `users` collection, inserts some documents, lists all documents and performs a field search. Running will also create/update the file `users/users.json` with persisted data.

Example approximate output:

    === Data base in disc ===

    === Insert documents ===
    Inserted documents with IDs: 1, 2, 3

    === All documents ===
    { _id: 1, name: "Kobra1", age: "30", city: "Detroit" }
    { _id: 2, name: "Kobra2", age: "25", city: "Santiago" }
    { _id: 3, name: "Kobra3", age: "40", city: "São Paulo" }

    === Search by city ===
    { _id: 1, name: "Kobra1", age: "30", city: "Detroit" }

    === Update document ID 1 ===
    { _id: 1, name: "Kobra1", age: "40", city: "Detroit" }

## Quick usage API (example)

    #include "DocumentDB.h"

    int main() {
        DocumentDB db("users/");
        auto coll = db.getCollection("users");

        // Insert
        int id = coll->insert({{"name","Alice"}, {"city","Lisbon"}});

        // Find all
        auto all = coll->findAll();

        // Find by field
        auto res = coll->find("city", "Lisbon");

        // Update
        coll->update(id, "name", "Alice Silva");

        // Remove
        coll->remove(id);

        return 0;
    }

## Data location

By default `DocumentDB` creates the base directory passed to the constructor (e.g.: `users/`). Each collection is stored in `<basePath><collectionName>.json` (for example `users/users.json`).

## License

Source files include headers indicating GPL (see source files). If desired, add a `LICENSE` file with the full text of the appropriate GPL license.

## Contact

Credits: M3t4l

Contributions and issues are welcome.
