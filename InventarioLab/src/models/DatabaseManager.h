#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <string>
#include <vector>
#include "Component.h"

using namespace std;

/**
 * @brief Clase encargada de gestionar la base de datos del inventario.
 
  Da los métodos para conexión, creación de tablas y operaciones CRUD
  sobre los componentes almacenados.
 */
class DatabaseManager {
private:
    string dbPath;     /// Ruta del archivo de base de datos
    void* dbHandle;    /// Manejador de la conexión (interno, opaco)

public:
    /**
     * @brief Constructor que recibe la ruta del archivo de base de datos.
     * @param path Ruta del archivo .db
     */
    DatabaseManager(const string& path);

    /**
     * @brief Destructor. Cierra la conexión si está activa.
     */
    ~DatabaseManager();

    /**
     * @brief Abre o crea la base de datos.
     * @return true si fue posible abrirl la base de datos.
     */
    bool openDB();

    /**
     * @brief Cierra la conexión a la base de datos.
     */
    void closeDB();

    /**
     * @brief Crea las tablas necesarias del inventario.
     * @return true si se creó correctamente.
     */
    bool initSchema();

    /**
     * @brief Agrega un nuevo componente a la base de datos.
     * @param c Componente sin id asignado aún.
     * @return true si se insertó correctamente.
     */
    bool addComponent(const Component& c);

    /**
     * @brief Actualiza un componente existente.
     * @param c Componente con id válido.
     * @return true si se actualizó.
     */
    bool updateComponent(const Component& c);

    /**
     * @brief Elimina un componente por id.
     * @param id Identificador del componente.
     * @return true si se eliminó correctamente.
     */
    bool deleteComponent(int id);

    /**
     * @brief Obtiene todos los componentes del inventario.
     * @return Vector con todos los componentes registrados.
     */
    vector<Component> getAllComponents();
    /**
     * @brief Busca componentes por nombre (subcadena).
     * @param name_substr Subcadena a buscar en el nombre.
     * @return Vector con los componentes que coinciden.
     */
    vector<Component> findComponentsByName(const string& name_substr);
};

#endif
