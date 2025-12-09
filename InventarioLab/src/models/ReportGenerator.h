#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <string>
#include <vector>
#include "Component.h"

using namespace std;

/**
 * @brief Clase encargada de generar reportes del inventario.
 * 
 * Realiza el reporte en texto o en CSV.
 */
class ReportGenerator {
public:

    /**
     * @brief Genera un reporte en texto plano con los componentes.
     * @param components Vector con los datos a reportar.
     * @param filepath Ruta del archivo .txt a generar.
     * @return true si se generó correctamente.
     */
    static bool generateTextReport(const vector<Component>& components,
                                   const string& filepath);

    /**
     * @brief Genera un archivo CSV con los componentes.
     * @param components Vector con los datos.
     * @param filepath Ruta del archivo .csv a generar.
     * @return true si se generó correctamente.
     */
    static bool generateCSV(const vector<Component>& components,
                            const string& filepath);
};

#endif


