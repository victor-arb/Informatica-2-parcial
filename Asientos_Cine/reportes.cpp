#include "reportes.h"

Reportes::Reportes()
{
    cont_id = 0;
}
Reportes::~Reportes()
{
}
void Reportes::generarReporteVentas()               //Imprime el reporte de ventas de los usuarios y lo guarda en un archivo
{
    string reporte_ventas;
    string totalCompra;
    map<int,Ventas>::iterator iter;
    for (iter=reporteVentas.begin(); iter!= reporteVentas.end();iter++) {
        reporte_ventas += iter->second.getNombreUsuario() + ":";      //Añade el nombre del usuario
        totalCompra = to_string(iter->second.getTotalCompra());
        reporte_ventas += totalCompra + ",";                     //Añade el total comprado por el usuario
    }

    cout<<reporte_ventas<<endl;


    //Guarda en el archivo
    ofstream fileVentas;

    fileVentas.open(ArchivoVentas.c_str(),ios::app);//Añade una linea nueva
    if (fileVentas.fail()){
        cout<<"El archivo con el reporte de ventas no se pudo abrir."<<endl;
        exit(1);
    }

    fileVentas << reporte_ventas<<endl;
    fileVentas.close();

}

void Reportes::generarReporteTotales()          //Imprime el reporte de ventas totales por genero y lo guarda en un archivo
{
    string reporte_totales;
    updateTotal();                                  //Actuliza el total de todas las ventas
    map<int,Ventas>::iterator iter;
    for (iter=reporteVentas.begin(); iter!= reporteVentas.end();iter++) {
        reporte_totales += "General 2D:"+to_string(total_gener2d)+";"+to_string(cont_gener2d)+"- ventas\n";
        reporte_totales += "General 3D:"+to_string(total_gener3d)+";"+to_string(cont_gener3d)+"- ventas\n";
        reporte_totales += "vibroSound 2D:"+to_string(total_vibro2d)+";"+to_string(cont_vibro2d)+"- ventas\n";
        reporte_totales += "vibroDound 3D:"+to_string(total_vibro3d)+";"+to_string(cont_vibro3d)+"- ventas\n";
        reporte_totales += "Total:" + to_string(total);
    }

    cout<<reporte_totales<<endl;


    //Guardar en el archivo
    ofstream fileTotales;

    fileTotales.open(ArchivoTotales.c_str(),ios::out);
    if (fileTotales.fail()){
        cout<<"El archivo con el reporte de Totales no se pudo abrir."<<endl;
        exit(1);
    }

    fileTotales << reporte_totales <<endl;
    fileTotales.close();
}

//Metodos setters
void Reportes::setReporteVentas(Ventas _ventas)
{
    reporteVentas.insert(make_pair(cont_id, _ventas));
    cont_id++;
}

//Asignan la direccion de los archivos para los reportes
void Reportes::setArchivoVentas(string _direccion_archivo)
{
    ArchivoVentas = _direccion_archivo;
}
void Reportes::setArchivoTotales(string _direccion_archivo)
{
    ArchivoTotales = _direccion_archivo;
}


//Guardan y actualizan el registro de la compra segun el formato
void Reportes::compraGeneral3d(int _valor)                //Guardan el registro de la compra segun el formato
{
    updateContGener3d();
    updateTotalGener3d(_valor);
}
void Reportes::compraGeneral2d(int _valor)
{
    updateContGener2d();
    updateTotalGener2d(_valor);
}
void Reportes::compraVibro3d(int _valor)
{
    updateContVibro3d();
    updateTotalVibro3d( _valor);
}
void Reportes::compraVibro2d(int _valor)
{
    updateContVibro2d();
    updateTotalVibro2d(_valor);
}
void Reportes::updateContGener3d()
{
    cont_gener3d++;
}
void Reportes::updateContGener2d()
{
    cont_gener2d++;
}
void Reportes::updateContVibro3d()
{
    cont_vibro3d++;
}
void Reportes::updateContVibro2d()
{
    cont_vibro2d++;
}


//Actualizan los totales segun los formatos
void Reportes::updateTotalGener3d(int _total_gener3d)
{
    total_gener3d += _total_gener3d;
}
void Reportes::updateTotalGener2d(int _total_gener2d)
{
    total_gener2d += _total_gener2d;
}
void Reportes::updateTotalVibro3d(int _total_vibro3d)
{
    total_vibro3d += _total_vibro3d;
}
void Reportes::updateTotalVibro2d(int _total_vibro2d)
{
    total_vibro2d += _total_vibro2d;
}

void Reportes::updateTotal()
{
    total = total_gener2d + total_gener3d + total_vibro2d + total_vibro3d;
}
