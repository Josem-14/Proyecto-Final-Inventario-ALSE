#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

using namespace std;

/**
 * @brief Estructura del inventario.
 */
struct Component {
    int id;              ///< Numero de identificacion 
    string name;         ///< Nombre del componente
    string type;         ///< Tipo o categoría
    int quantity;        ///< Cantidad en stock
    string location;     ///< Ubicación 
    string purchaseDate; ///< Fecha de compra (AÑO-MES-DIA)
};

#endif
