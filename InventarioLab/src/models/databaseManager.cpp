#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QDebug>

DatabaseManager::DatabaseManager() {
    openDatabase();
    createTables();
}

bool DatabaseManager::openDatabase() {
    QDir().mkpath("database");

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database/inventario.db");

    if (!db.open()) {
        qDebug() << "Error abriendo BD:" << db.lastError();
        return false;
    }
    return true;
}

void DatabaseManager::createTables() {
    QSqlQuery query;
    query.exec(
        "CREATE TABLE IF NOT EXISTS components ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT,"
        "type TEXT,"
        "quantity INTEGER,"
        "location TEXT,"
        "purchase_date TEXT)"
        );
}

bool DatabaseManager::addComponent(const Component &c) {
    QSqlQuery query;
    query.prepare("INSERT INTO components (name, type, quantity, location, purchase_date) "
                  "VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(c.getName());
    query.addBindValue(c.getType());
    query.addBindValue(c.getQuantity());
    query.addBindValue(c.getLocation());
    query.addBindValue(c.getPurchaseDate());
    return query.exec();
}

bool DatabaseManager::updateComponent(const Component &c) {
    QSqlQuery query;
    query.prepare("UPDATE components SET name=?, type=?, quantity=?, location=?, purchase_date=? WHERE id=?");
    query.addBindValue(c.getName());
    query.addBindValue(c.getType());
    query.addBindValue(c.getQuantity());
    query.addBindValue(c.getLocation());
    query.addBindValue(c.getPurchaseDate());
    query.addBindValue(c.getId());
    return query.exec();
}

bool DatabaseManager::deleteComponent(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM components WHERE id=?");
    query.addBindValue(id);
    return query.exec();
}

QVector<Component> DatabaseManager::getAllComponents() const {
    QVector<Component> list;
    QSqlQuery query("SELECT * FROM components");

    while (query.next()) {
        list.append(Component(
            query.value("id").toInt(),
            query.value("name").toString(),
            query.value("type").toString(),
            query.value("quantity").toInt(),
            query.value("location").toString(),
            query.value("purchase_date").toString()
            ));
    }
    return list;
}

QVector<Component> DatabaseManager::searchComponents(const QString &keyword) const {
    QVector<Component> list;
    QSqlQuery query;
    query.prepare("SELECT * FROM components WHERE name LIKE ? OR type LIKE ?");
    query.addBindValue("%" + keyword + "%");
    query.addBindValue("%" + keyword + "%");
    query.exec();

    while (query.next()) {
        list.append(Component(
            query.value("id").toInt(),
            query.value("name").toString(),
            query.value("type").toString(),
            query.value("quantity").toInt(),
            query.value("location").toString(),
            query.value("purchase_date").toString()
            ));
    }
    return list;
}
