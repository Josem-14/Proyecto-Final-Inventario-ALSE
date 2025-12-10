#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <QString>
#include <QVector>
#include "component.h"

class ReportGenerator
{
public:
    static bool generateCSV(const QString &path, const QVector<Component> &list);
};

#endif // REPORTGENERATOR_H

