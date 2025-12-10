#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QVector>
#include "component.h"

class DatabaseManager {
public:
    DatabaseManager();

    bool openDatabase();
    void createTables();

    bool addComponent(const Component &c);
    bool updateComponent(const Component &c);
    bool deleteComponent(int id);

    QVector<Component> getAllComponents() const;
    QVector<Component> searchComponents(const QString &keyword) const;

private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H

