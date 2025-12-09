#include "DatabaseManager.h"
#include <sqlite3.h>
#include <iostream>
#include <sstream>

using namespace std;

DatabaseManager::DatabaseManager(const string& path)
    : dbPath(path), dbHandle(nullptr) {}

DatabaseManager::~DatabaseManager() {
    closeDB();
}

bool DatabaseManager::openDB() {
    if (dbHandle) return true;

    sqlite3* db = nullptr;
    int rc = sqlite3_open(dbPath.c_str(), &db);

    if (rc != SQLITE_OK) {
        cerr << "Error abriendo la base de datos: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    dbHandle = static_cast<void*>(db);
    return true;
}

void DatabaseManager::closeDB() {
    if (dbHandle) {
        sqlite3_close(static_cast<sqlite3*>(dbHandle));
        dbHandle = nullptr;
    }
}

bool DatabaseManager::initSchema() {
    if (!openDB()) return false;

    sqlite3* db = static_cast<sqlite3*>(dbHandle);
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS components(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            type TEXT,
            quantity INTEGER,
            location TEXT,
            purchase_date TEXT
        );
    )";

    char* errmsg = nullptr;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errmsg);

    if (rc != SQLITE_OK) {
        cerr << "Error creando tabla: " << errmsg << endl;
        sqlite3_free(errmsg);
        return false;
    }

    return true;
}

bool DatabaseManager::addComponent(const Component& c) {
    if (!openDB()) return false;

    sqlite3* db = static_cast<sqlite3*>(dbHandle);

    const char* sql = "INSERT INTO components(name,type,quantity,location,purchase_date) VALUES(?,?,?,?,?)";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, c.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, c.type.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, c.quantity);
    sqlite3_bind_text(stmt, 4, c.location.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, c.purchaseDate.c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

bool DatabaseManager::updateComponent(const Component& c) {
    if (!openDB()) return false;

    sqlite3* db = static_cast<sqlite3*>(dbHandle);

    const char* sql =
        "UPDATE components SET name=?, type=?, quantity=?, location=?, purchase_date=? WHERE id=?";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, c.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, c.type.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, c.quantity);
    sqlite3_bind_text(stmt, 4, c.location.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, c.purchaseDate.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 6, c.id);

    int rc = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

bool DatabaseManager::deleteComponent(int id) {
    if (!openDB()) return false;

    sqlite3* db = static_cast<sqlite3*>(dbHandle);
    const char* sql = "DELETE FROM components WHERE id=?";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);

    int rc = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

vector<Component> DatabaseManager::getAllComponents() {
    vector<Component> components;

    if (!openDB()) return components;

    sqlite3* db = static_cast<sqlite3*>(dbHandle);
    const char* sql = "SELECT * FROM components";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Component c;
        c.id = sqlite3_column_int(stmt, 0);
        c.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        c.type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        c.quantity = sqlite3_column_int(stmt, 3);
        c.location = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        c.purchaseDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

        components.push_back(c);
    }

    sqlite3_finalize(stmt);
    return components;
}

vector<Component> DatabaseManager::findComponentsByName(const string& name_substr) {
    vector<Component> components;

    if (!openDB()) return components;

    sqlite3* db = static_cast<sqlite3*>(dbHandle);

    const char* sql = "SELECT * FROM components WHERE name LIKE ?";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    string pattern = "%" + name_substr + "%";
    sqlite3_bind_text(stmt, 1, pattern.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Component c;
        c.id = sqlite3_column_int(stmt, 0);
        c.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        c.type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        c.quantity = sqlite3_column_int(stmt, 3));
        c.location = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        c.purchaseDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

        components.push_back(c);
    }

    sqlite3_finalize(stmt);
    return components;
}
/**
 * @brief Clase encargada de gestionar la base de datos del inventario.
 *
 * Da los métodos para conexión, creación de tablas y operaciones CRUD
 * sobre los componentes almacenados.
 */class DatabaseManager {
private:
    string dbPath;     /// Ruta del archivo de base de datos    