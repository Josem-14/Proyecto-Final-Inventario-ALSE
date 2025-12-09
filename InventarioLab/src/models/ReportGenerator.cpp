#include "ReportGenerator.h"
#include <fstream>
#include <iostream>

using namespace std;

bool ReportGenerator::generateTextReport(const vector<Component>& components,
                                         const string& filepath) {
    ofstream file(filepath);

    if (!file.is_open()) {
        cerr << "Error creando archivo de reporte: " << filepath << endl;
        return false;
    }

    file << "===== REPORTE DE INVENTARIO =====\n\n";

    for (const auto& c : components) {
        file << "ID: " << c.id << "\n"
             << "Nombre: " << c.name << "\n"
             << "Tipo: " << c.type << "\n"
             << "Cantidad: " << c.quantity << "\n"
             << "Ubicacion: " << c.location << "\n"
             << "Fecha de compra: " << c.purchaseDate << "\n";
        file << "----------------------------------------\n";
    }

    file.close();
    return true;
}

bool ReportGenerator::generateCSV(const vector<Component>& components,
                                  const string& filepath) {
    ofstream file(filepath);

    if (!file.is_open()) {
        cerr << "Error creando archivo CSV: " << filepath << endl;
        return false;
    }

    file << "id,name,type,quantity,location,purchase_date\n";

    for (const auto& c : components) {
        file << c.id << ","
             << c.name << ","
             << c.type << ","
             << c.quantity << ","
             << c.location << ","
             << c.purchaseDate << "\n";
    }

    file.close();
    return true;
}
