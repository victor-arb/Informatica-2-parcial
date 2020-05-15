#include "reportes.h"

Reportes::Reportes()
{
    cont_id = 1;
    cont_gener3d=0;
    cont_gener2d=0;
    cont_vibro3d=0;
    cont_vibro2d=0;

    total_gener3d=0;
    total_gener2d=0;
    total_vibro3d=0;
    total_vibro2d=0;

    total=0;
    ArchivoVentas ="";
    ArchivoTotales ="";
}
Reportes::~Reportes()
{
}

void Reportes::generarReporteVentas(int option)               //Imprime el reporte de ventas de los usuarios y lo guarda en un archivo
{
    ofstream fileVentas;

    fileVentas.open(ArchivoVentas.c_str(),ios::app);//Añade una linea nueva
    if (fileVentas.fail()){
        cout<<"El archivo con el reporte de ventas no se pudo abrir."<<endl;
        exit(1);
    }
    string reporte_ventas;
    string totalCompra;
    //unsigned int contmap = 1;
    map<int,Ventas>::iterator iter;
    for (iter=reporteVentas.begin(); iter!= reporteVentas.end();iter++) {
        reporte_ventas += iter->second.getNombreUsuario() + ":";      //Añade el nombre del usuario
        totalCompra = to_string(iter->second.getTotalCompra());
        reporte_ventas += totalCompra;    //Añade el total comprado por el usuario

        if (option == 1){
            fileVentas << reporte_ventas <<endl;           //Guarda en el archivo
            reporte_ventas = "";
        }
        else if (option == 2) {
            reporte_ventas += "\n";

        }


    }
    //cout<<reporte_ventas<<endl;
    if (option == 2)    //Imprime el reporte
    {
        cout<<reporte_ventas<<endl;
    }
    else {
        reporteVentas.clear();          //Limpia el mapa
        cont_id = 1;
    }



    //cout<<endl<<"Se ha guardado el reporte con exito."<<endl;
    fileVentas.close();

}
//Carga el reporte de ventas guardado previamente
void Reportes::cargarReporteVentas()
{
    string nomuser ;
    int totalcompra;
    ifstream fileVentas;
    fileVentas.open(ArchivoVentas.c_str(), ios::in);
    if (fileVentas.fail()){
        cout<<"No se pudo abrir el archivo con las ventas."<<endl;
        exit(1);
    }
    string linea;
    while(!fileVentas.eof()){ //mientras no sea final del archivo.
           getline(fileVentas,linea);
           if(linea != ""){                 //Comprueba que la linea no este vacia
               unsigned int pos = linea.find(":");  //Toma la posicion entre el inicio y el ";" como el id de la pelicula
               nomuser = linea.substr(0,pos);
               totalcompra = stoi(linea.substr(pos+1));
               Ventas venta_temp;
               venta_temp.setNombreUsuario(nomuser);
               venta_temp.setTotalCompra(totalcompra);
               setReporteVentas(venta_temp);
           }

       }
}

void Reportes::generarReporteTotales(int _option)          //Imprime el reporte de ventas totales por genero y lo guarda en un archivo
{
    string reporte_totales;
    updateTotal();                                  //Actuliza el total de todas las ventas

    reporte_totales += "General 2D:"+to_string(total_gener2d)+";"+to_string(cont_gener2d)+"- ventas\n";
    reporte_totales += "General 3D:"+to_string(total_gener3d)+";"+to_string(cont_gener3d)+"- ventas\n";
    reporte_totales += "vibroSound 2D:"+to_string(total_vibro2d)+";"+to_string(cont_vibro2d)+"- ventas\n";
    reporte_totales += "vibroDound 3D:"+to_string(total_vibro3d)+";"+to_string(cont_vibro3d)+"- ventas\n";
    reporte_totales += "Total:" + to_string(total);

    if (_option == 2){
        cout<<reporte_totales<<endl;
    }else if (_option == 1) {
        //Guardar en el archivo
        ofstream fileTotales;

        fileTotales.open(ArchivoTotales.c_str(),ios::out);
        if (fileTotales.fail()){
            cout<<"El archivo con el reporte de Totales no se pudo abrir."<<endl;
            exit(1);
        }

        fileTotales << reporte_totales <<endl;
        cout<<"Se ha guardado el reporte con exito."<<endl;
        fileTotales.close();
    }




}
//Carga el reporte de totales si existe
void Reportes::cargarReporteTotales()
{
    int total1 = 0, contformat = 0;
    ifstream filetotal;
    filetotal.open(ArchivoTotales.c_str(), ios::in);
    if (filetotal.fail()){
        cout<<"No se pudo abrir el archivo con las ventas."<<endl;
        exit(1);
    }
    string linea;
    int contlinea = 0;
    while(!filetotal.eof()){ //mientras no sea final del archivo.
           getline(filetotal,linea);
           contlinea++;
           if(linea != ""){                 //Comprueba que la linea no este vacia
               if (contlinea == 1){     //General 2d
                   unsigned int pos = linea.find(":");
                   unsigned int pos2 = linea.find(";");
                   total1 = stoi(linea.substr(pos+1, pos2-(pos+1)));//toma entre dos puntos y ; el total de general 2d
                   pos = linea.find("-");
                   contformat = stoi(linea.substr(pos2+1,pos-(pos+1)));//toma entre ; y - el contador de general 2d
                   cont_gener2d = contformat;
                   total_gener2d = total1;

               }
               else if (contlinea == 2){        //General 3d
                   unsigned int pos = linea.find(":");
                   unsigned int pos2 = linea.find(";");
                   total1 = stoi(linea.substr(pos+1, pos2-(pos+1)));//toma entre dos puntos y ; el total de general 3d
                   pos = linea.find("-");
                   contformat = stoi(linea.substr(pos2+1,pos-(pos+1)));//toma entre ; y - el contador de general 3d
                   cont_gener3d += contformat;
                   total_gener3d = total1;

               }
               else if (contlinea == 3) {   //vibrosound 2d
                   unsigned int pos = linea.find(":");
                   unsigned int pos2 = linea.find(";");
                   total1 = stoi(linea.substr(pos+1, pos2-(pos+1)));//toma entre dos puntos y ; el total de vibrosound 2d
                   pos = linea.find("-");
                   contformat = stoi(linea.substr(pos2+1,pos-(pos+1)));//toma entre ; y - el contador de vibrosound 2d
                   cont_vibro2d += contformat;
                   total_vibro2d = total1;
               }
               else if (contlinea == 4) {       //vibrosound 3d
                   unsigned int pos = linea.find(":");
                   unsigned int pos2 = linea.find(";");
                   total1 = stoi(linea.substr(pos+1, pos2-(pos+1)));//toma entre dos puntos y ; el total de vibrosound 3d
                   pos = linea.find("-");
                   contformat = stoi(linea.substr(pos2+1,pos-(pos+1)));//toma entre ; y - el contador de vibrosound 3d
                   cont_vibro3d += contformat;
                   total_vibro3d = total1;
               }
               else if (contlinea == 5) {
                   updateTotal();
               }



           }

       }
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
