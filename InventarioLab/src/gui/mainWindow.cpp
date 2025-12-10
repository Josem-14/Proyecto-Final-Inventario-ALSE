#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //
    // 🔥 CONEXIONES MANUALES (garantizado que funciona SIEMPRE)
    //
    connect(ui->btnAdd,     &QPushButton::clicked, this, &MainWindow::onAgregar);
    connect(ui->btnUpdate,  &QPushButton::clicked, this, &MainWindow::onActualizar);
    connect(ui->btnDelete,  &QPushButton::clicked, this, &MainWindow::onEliminar);
    connect(ui->btnSearch,  &QPushButton::clicked, this, &MainWindow::onBuscar);
    connect(ui->btnExport,  &QPushButton::clicked, this, &MainWindow::onExportar);
    connect(ui->btnClear,   &QPushButton::clicked, this, &MainWindow::limpiarFormulario);

    // Selección de filas en tabla
    connect(ui->tableInventory, &QTableWidget::cellClicked,
            this, &MainWindow::seleccionarFila);

    cargarTabla();
}

MainWindow::~MainWindow()
{
    delete ui;
}

////////////////////////////////////////////////////
/// Cargar Tabla
////////////////////////////////////////////////////
void MainWindow::cargarTabla()
{
    QVector<Component> lista = manager.getComponents();
    ui->tableInventory->setRowCount(lista.size());

    for (int i = 0; i < lista.size(); i++) {
        const Component &c = lista[i];

        ui->tableInventory->setItem(i, 0, new QTableWidgetItem(QString::number(c.getId())));
        ui->tableInventory->setItem(i, 1, new QTableWidgetItem(c.getName()));
        ui->tableInventory->setItem(i, 2, new QTableWidgetItem(c.getType()));
        ui->tableInventory->setItem(i, 3, new QTableWidgetItem(QString::number(c.getQuantity())));
        ui->tableInventory->setItem(i, 4, new QTableWidgetItem(c.getLocation()));
        ui->tableInventory->setItem(i, 5, new QTableWidgetItem(c.getPurchaseDate()));
    }
}

////////////////////////////////////////////////////
/// Limpiar formulario
////////////////////////////////////////////////////
void MainWindow::limpiarFormulario()
{
    idSeleccionado = -1;

    ui->inputName->clear();
    ui->inputType->clear();
    ui->inputQuantity->setValue(0);
    ui->inputLocation->clear();
    ui->inputDate->setDate(QDate::currentDate());
}

////////////////////////////////////////////////////
/// Seleccionar fila
////////////////////////////////////////////////////
void MainWindow::seleccionarFila(int row, int)
{
    idSeleccionado = ui->tableInventory->item(row, 0)->text().toInt();

    ui->inputName->setText(ui->tableInventory->item(row, 1)->text());
    ui->inputType->setText(ui->tableInventory->item(row, 2)->text());
    ui->inputQuantity->setValue(ui->tableInventory->item(row, 3)->text().toInt());
    ui->inputLocation->setText(ui->tableInventory->item(row, 4)->text());
    ui->inputDate->setDate(QDate::fromString(ui->tableInventory->item(row, 5)->text(), "yyyy-MM-dd"));
}

////////////////////////////////////////////////////
/// AGREGAR
////////////////////////////////////////////////////
void MainWindow::onAgregar()
{
    Component c(0,
                ui->inputName->text(),
                ui->inputType->text(),
                ui->inputQuantity->value(),
                ui->inputLocation->text(),
                ui->inputDate->date().toString("yyyy-MM-dd"));

    if (c.getName().isEmpty() || c.getType().isEmpty()) {
        QMessageBox::warning(this, "Error", "Debe llenar Nombre y Tipo.");
        return;
    }

    manager.add(c);
    cargarTabla();
    limpiarFormulario();
}

////////////////////////////////////////////////////
/// ACTUALIZAR
////////////////////////////////////////////////////
void MainWindow::onActualizar()
{
    if (idSeleccionado == -1) {
        QMessageBox::warning(this, "Error", "Debe seleccionar un registro.");
        return;
    }

    Component c(idSeleccionado,
                ui->inputName->text(),
                ui->inputType->text(),
                ui->inputQuantity->value(),
                ui->inputLocation->text(),
                ui->inputDate->date().toString("yyyy-MM-dd"));

    manager.update(c);
    cargarTabla();
    limpiarFormulario();
}

////////////////////////////////////////////////////
/// ELIMINAR
////////////////////////////////////////////////////
void MainWindow::onEliminar()
{
    if (idSeleccionado == -1) {
        QMessageBox::warning(this, "Error", "Debe seleccionar un registro.");
        return;
    }

    manager.remove(idSeleccionado);
    cargarTabla();
    limpiarFormulario();
}

////////////////////////////////////////////////////
/// BUSCAR
////////////////////////////////////////////////////
void MainWindow::onBuscar()
{
    QString key = ui->searchInput->text();
    QVector<Component> lista = manager.search(key);

    ui->tableInventory->setRowCount(lista.size());

    for (int i = 0; i < lista.size(); i++) {
        const Component &c = lista[i];

        ui->tableInventory->setItem(i, 0, new QTableWidgetItem(QString::number(c.getId())));
        ui->tableInventory->setItem(i, 1, new QTableWidgetItem(c.getName()));
        ui->tableInventory->setItem(i, 2, new QTableWidgetItem(c.getType()));
        ui->tableInventory->setItem(i, 3, new QTableWidgetItem(QString::number(c.getQuantity())));
        ui->tableInventory->setItem(i, 4, new QTableWidgetItem(c.getLocation()));
        ui->tableInventory->setItem(i, 5, new QTableWidgetItem(c.getPurchaseDate()));
    }
}

////////////////////////////////////////////////////
/// EXPORTAR CSV
////////////////////////////////////////////////////
void MainWindow::onExportar()
{
    QString path = QFileDialog::getSaveFileName(this,
                                                "Guardar reporte CSV",
                                                "",
                                                "Archivo CSV (*.csv)");

    if (path.isEmpty())
        return;

    QVector<Component> lista = manager.getComponents();

    if (ReportGenerator::generateCSV(path, lista)) {
        QMessageBox::information(this, "Éxito", "Archivo exportado correctamente.");
    } else {
        QMessageBox::critical(this, "Error", "No se pudo exportar el archivo.");
    }
}

