#ifndef REPORTES_H
#define REPORTES_H
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <ventas.h>
#include <fstream>

using namespace std;

class Reportes
{
public:
    Reportes();
    ~Reportes();

    void generarReporteVentas();
    //void guardarReporteVentas();

    void generarReporteTotales();
    //void guardarReporteTotales();

    //CargarDatos Archivo.

    void setReporteVentas(Ventas _ventas);
    void setArchivoVentas(string _direccion_archivo);
    void setArchivoTotales(string _direccion_archivo);

    //Guardan y actualizan el registro de la compra segun el formato
    void compraGeneral3d(int _valor);         //Guardan el registro de la compra segun el formato
    void compraGeneral2d(int _valor);
    void compraVibro3d(int _valor);
    void compraVibro2d(int _valor);

    //Actualizan la cantidad de ventas segun el formato de la pelicula
    void updateContGener3d();
    void updateContGener2d();
    void updateContVibro3d();
    void updateContVibro2d();

    //Actualizan el total de las ventas segun el formtao de la  pelicula
    void updateTotalGener3d(int _total_gener3d);
    void updateTotalGener2d(int _total_gener2d);
    void updateTotalVibro3d(int _total_vibro3d);
    void updateTotalVibro2d(int _total_vibro2d);

    void updateTotal();

private:
    int cont_gener3d;
    int cont_gener2d;
    int cont_vibro3d;
    int cont_vibro2d;

    int total_gener3d;
    int total_gener2d;
    int total_vibro3d;
    int total_vibro2d;

    int total;                  //Guarda el total de todas las compras;
    string ArchivoVentas;       //Variable que contiene la direccion del archivo donde se guardan los reportes de ventas
    string ArchivoTotales;       //Variable que contiene la direccion del archivo donde se guardan los reportes de los totales

    int cont_id;      //Determine automaticamente el id para la informacion del reporte
    map<int,Ventas> reporteVentas;          //Tiene las ventas hechas a cada usuario

};

#endif // REPORTES_H
