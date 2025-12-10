/**
 * @file inventorymanager.h
 * @brief Declaración de la clase InventoryManager.
 *
 * InventoryManager actúa como una capa intermedia entre la interfaz gráfica (UI)
 * y la base de datos. Se encarga de realizar las operaciones lógicas de:
 *  - Obtener lista de componentes
 *  - Agregar componentes
 *  - Actualizar componentes
 *  - Eliminar componentes
 *  - Buscar componentes
 *
 * Esta clase utiliza internamente a DatabaseManager, quien se encarga de las
 * operaciones directas en SQLite.
 */

#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <QVector>
#include <QString>
#include "component.h"
#include "databasemanager.h"

/**
 * @class InventoryManager
 * @brief Administra el inventario a nivel lógico.
 *
 * InventoryManager se encarga de ofrecer una API amigable para el manejo
 * de los componentes, delegando las tareas de acceso a base de datos hacia
 * DatabaseManager.
 */
class InventoryManager
{
public:
    /**
     * @brief Constructor por defecto.
     */
    InventoryManager();

    /**
     * @brief Obtiene todos los componentes almacenados.
     * @return Lista completa de componentes.
     */
    QVector<Component> getComponents() const;

    /**
     * @brief Realiza una búsqueda de componentes.
     * @param keyword texto a buscar (coincidencia parcial).
     * @return lista filtrada de componentes.
     */
    QVector<Component> search(const QString &keyword) const;

    /**
     * @brief Agrega un nuevo componente.
     */
    bool add(const Component &c);

    /**
     * @brief Actualiza un componente existente.
     */
    bool update(const Component &c);

    /**
     * @brief Elimina un componente.
     */
    bool remove(int id);

private:
    DatabaseManager db;  ///< Manejador de base de datos
};

#endif // INVENTORYMANAGER_H