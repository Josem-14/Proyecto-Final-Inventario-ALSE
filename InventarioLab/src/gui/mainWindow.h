#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QMessageBox>
#include "inventorymanager.h"
#include "reportgenerator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void cargarTabla();
    void limpiarFormulario();
    void seleccionarFila(int row, int column);

    void onAgregar();
    void onActualizar();
    void onEliminar();
    void onBuscar();
    void onExportar();
    void onExportarUML();

private:
    Ui::MainWindow *ui;
    InventoryManager manager;
    int idSeleccionado = -1;
};

#endif // MAINWINDOW_H

