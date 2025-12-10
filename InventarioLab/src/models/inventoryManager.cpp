#include "inventorymanager.h"

InventoryManager::InventoryManager()
{
}

QVector<Component> InventoryManager::getComponents() const
{
    return db.getAllComponents();
}

QVector<Component> InventoryManager::search(const QString &keyword) const
{
    return db.searchComponents(keyword);
}

bool InventoryManager::add(const Component &c)
{
    return db.addComponent(c);
}

bool InventoryManager::update(const Component &c)
{
    return db.updateComponent(c);
}

bool InventoryManager::remove(int id)
{
    return db.deleteComponent(id);
}