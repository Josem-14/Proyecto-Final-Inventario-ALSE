#include "reportgenerator.h"
#include <QFile>
#include <QTextStream>

bool ReportGenerator::generateCSV(const QString &path, const QVector<Component> &list)
{
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);

    out << "ID,Nombre,Tipo,Cantidad,Ubicacion,FechaCompra\n";

    for (const Component &c : list) {
        out << c.getId() << ","
            << c.getName() << ","
            << c.getType() << ","
            << c.getQuantity() << ","
            << c.getLocation() << ","
            << c.getPurchaseDate() << "\n";
    }

    return true;
}