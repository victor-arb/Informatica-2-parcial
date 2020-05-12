#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <pelicula.h>
#include <cartelera.h>
#include <ventas.h>
#include <reportes.h>
#include <fstream>

using namespace std;

static string ArchivoVentas;           //Variable global con la direccion del archivo con los reportes de ventas
static string ArchivoTotales;          //Variable global con la direccion del archivo con los reportes totales
static string DirArcivoAdmin = "../Asientos_cine/sudo.txt";             //Variable global con la direccion del archivo de administrador
static string DirArchivoCartelera = "../Asientos_cine/cartelera.txt";
static string DirArchivoPuestos;

Cartelera menuAdmin(Cartelera _cartelera,Reportes& _reporte);          //Menu con las funciones del administrador
bool validateAdmin(string _cont_admin);             //Valida la contraseña del administrador
Cartelera menuUsuario(Cartelera _cartelera, Reportes& _reporte);        //Menu con las funciones del usuario
void pagoUsuario(int valor_precio);                 //Funcion que efectua el pago del usuario

int main()
{
    string option = "";
    Cartelera _cartelera;
    _cartelera.setDirArchivos(DirArchivoCartelera, DirArchivoPuestos);          //Se asigna nombre a los archivos
    Reportes _reporte;
    _reporte.setArchivoVentas(ArchivoVentas);
    _reporte.setArchivoTotales(ArchivoTotales);

    //Menu de entrada
    while(option != "3"){
        cout<<endl<<endl;
        do{
           cout <<" 1 - Ingresar como administrador"<<endl
                <<" 2 - Ingresar como Usuario"<<endl
                <<" 3 - Salir"<<endl;
           cout<<"Ingrese la opcion elegida -> "; cin>>option;
        }while(option < "1"  && option > "3");

        if (option == "1") _cartelera = menuAdmin(_cartelera, _reporte);
        else if (option == "2") _cartelera = menuUsuario(_cartelera, _reporte);
    }

}

//Menu del Administrador
Cartelera menuAdmin(Cartelera _cartelera, Reportes& _reporte){
    cout<<"Bienvenido, Ha ingresado como administrador."<<endl;
    bool val = true;
    do{
        string cont_admin;
        cout<<"Digite su contrasenia de administrador -> "; cin>>cont_admin;
        val = validateAdmin(cont_admin);
        if(val == false) cout<<"Contrasenia incorrecta, vuelve a intentarlo"<<endl;
    }while(val == false);
    string option1="";
    //Menu
    while(option1 != "6"){
        cout<<endl<<endl;
        do{
            cout <<" 1 - Ingresar una pelicula a la cartelera"<<endl
                 <<" 2 - Quitar una pelicula de la cartelera"<<endl
                 <<" 3 - Cargar Cartelera desde un Archivo con los asientos previamente reservados"<<endl
                 <<" 4 - Generar un reporte"<<endl
                 <<" 5 - Guardar cartelera en un archivo."<<endl
                 <<" 6 - Salir"<<endl;
            cout <<"Ingrese la opcion elegida -> "; cin>>option1;
        }while(option1 <"1" && option1 > "5");
        if (option1 == "1"){        //Ingresa la pelicula
            //Atributos para la pelicula
            string nombre, genero, duracion,hora, clasificacion, formato ;
            int sala,fil,col;
            string _id;
            bool idd;           //Mira si se repite el id
            cout<<endl;
            do{
                idd = true;
                cout<<"Ingrese el id(identificacion, un entero que no debe repetirse) de la pelicula: "; cin>>_id;
                map<int,Pelicula>::iterator iter;
                map<int,Pelicula> maptemp = _cartelera.getCartelera();
                for (unsigned int i = 0; i < (_id.size());i++) {        //Valida que sean numeros
                    if (!isdigit(_id[i])){
                        idd=false;
                        break;
                    }

                }
                if(idd == false){
                    cout<<"Debe ingresar numeros enteros. Vuelva a intentarlo"<<endl;
                }else {
                    for (iter=maptemp.begin();iter!=maptemp.end();iter++) {
                        if (iter->first == stoi(_id)){              //Mira que no hallan id iguales
                            idd=false;
                        }
                    }
                    if(idd == false) cout<<"El id ingresado ya existe, vuelva a intentarlo. "<<endl;
                }

            }while(idd == false);

            cout << "Ingrese el nombre de la Pelicula: "; cin>>nombre;
            fflush(stdin);
            cout<< "Ingrese el genero de la Pelicula: "; cin>>genero;
            fflush(stdin);
            cout<< "Ingrese la duracion de la Pelicula: "; cin>>duracion;
            fflush(stdin);
            cout<< "Ingrese el numero de la sala de la pelicula: "; cin>>sala;
            fflush(stdin);
            cout<< "Ingrese la hora de la pelicula: "; cin>>hora;
            fflush(stdin);
            cout<< "Ingrese la clasificacion de la pelicula: "; cin>>clasificacion;
            fflush(stdin);
            cout<<endl<<"La cantidad de asientos disponibles sera numerofilas x numerocolumnas:"<<endl;
            cout<<"Ingrese el numero de filas: "; cin>> fil;
            cout<<"Ingrese el numero de columnas: "; cin>>col;
            fflush(stdin);
            do{
                cout<< "Ingrese el formato de la pelicula (3D o 2D): "; cin>>formato;
                if (formato != "3D" && formato != "2D"){
                    cout<<"Ingreso un Dato erroneo, Debe ser 2D o 3D. Vuelva a intentarlo."<<endl;
                }
            }while (formato != "3D" && formato != "2D");
            fflush(stdin);
            Pelicula peli(nombre,genero,sala,hora,fil,col,duracion,clasificacion,formato);
            _cartelera.setCartelera(stoi(_id), peli);

//            map<int,Pelicula>::iterator iter;
//            map<int,Pelicula> maptemp = _cartelera.getCartelera();
//            for (iter=maptemp.begin();iter!=maptemp.end();iter++) {
//                if (iter->first == stoi(_id)){              //Mira que no hallan id iguales
//                    iter->second.showSala();
//                }
//            }

            cout<<endl<<"Pelicula agregada exitosamente."<<endl;
        }
        else if (option1 == "2") {          //Quitar una pelicula de la cartelera
            if (_cartelera.getCartelera().size()>0){
                string _id ;
                _cartelera.showCartelera();     //Muestra la cartelera
                bool idd;                       //Mira si se repite el id
                //Eliminar

                do{
                    idd = true;
                    cout<<"Ingrese el id(identificacion) de la pelicula que desea eliminar: "; cin>>_id;
                    map<int,Pelicula>::iterator iter;
                    map<int,Pelicula> maptemp = _cartelera.getCartelera();
                    for (unsigned int i = 0; i < (_id.size());i++) {        //Valida que sean numeros
                        if (!isdigit(_id[i])){
                            idd=false;
                            break;
                        }

                    }
                    if(idd == false){
                        cout<<"Debe ingresar numeros enteros. Vuelva a intentarlo"<<endl;
                        idd=true;
                    }else {
                        for (iter=maptemp.begin();iter!=maptemp.end();iter++) {
                            if (iter->first == stoi(_id)){
                                idd=false;
                                _cartelera.deletePelicula(stoi(_id));         //Elimina la pelicula
                                break;
                            }
                        }
                        if(idd == true) cout<<"Debe ingresar un id existente, vuelva a intentarlo. "<<endl;
                    }
                }while(idd == true);

            }
            else {
                cout<<"La cartelera se encuentra vacia."<<endl;
            }
        }

        else if (option1 == "3") {      //Carga la cartelera desde un archivo
            _cartelera.cargarEstadoCartelera();
            _cartelera.cargarPuestos();
            cout<<"Se ha cargado la cartelera y los asientos exitosamente."<<endl;


        }
        else if (option1 == "4"){      //Genera un reporte
            string optionR="";
            do{
                cout<<"1 - Mostrar reporte de Ventas por Usuarios"<<endl
                    <<"2 - Mostrar reporte de Ventas por registros Totales"<<endl;
                cout<<"Ingrese una opcion: "; cin>>optionR;
            }while(optionR < "1" && optionR >"2");

            if (optionR == "1"){
                cout<<endl;
                cout<< "---------------------------------------"<<endl;
                cout<< "            REPORTE DE VENTAS          "<<endl;
                cout<< "---------------------------------------"<<endl;
                _reporte.generarReporteVentas();                    //Genera el reporte de ventas por usuario
            }
            else {
                cout<<endl;
                cout<< "---------------------------------------"<<endl;
                cout<< "       REPORTE DE VENTAS TOTALES       "<<endl;
                cout<< "---------------------------------------"<<endl;
                _reporte.generarReporteTotales();                    //Genera el reporte de ventas por usuario
            }
        }
        else if(option1 == "5") {                          //Sale y guarda la cartelera
            if(remove("C:\\Users\\Mario\\Desktop\\texto.txt") != 0 )
                perror("Error al borrar archivo!.");
//              else
//                puts("El archivo se borro con exito!");
            _cartelera.guardarEstadoCartelera();
            cout<<"Se ha guardado correctamente la cartelera."<<endl;

        }
        else {
            cout<<"Ha salido del perfil de administrador. "<<endl;
        }

    }
    return _cartelera;
}

bool validateAdmin(string _cont_admin)             //Valida la contraseña del administrador
{
    bool vali = false;
    ifstream archivoAdmin;
    string contra;
    archivoAdmin.open(DirArcivoAdmin.c_str(), ios::in);

    if(archivoAdmin.fail()){
        cout<<"No se pudo abrir el archivo de Administrador."<<endl;
        exit(1);
    }

    while(!archivoAdmin.eof()){ //mientras no sea final del archivo, solo va a terminar con el contenido de la linea pedida
        getline(archivoAdmin,contra);
    }
    archivoAdmin.close();
    if (_cont_admin == contra) vali=true;
    return vali;
}

//Menu de Usuario
Cartelera menuUsuario(Cartelera _cartelera, Reportes &_reporte){
    string nombre_usuario;
    cout<<"Ha ingresado como Usuario."<<endl;
    cout<<" Ingrese el nombre del usuario: "; cin >>nombre_usuario;
    cout<<endl<<" Bienvenido "<<nombre_usuario<<endl<<endl<<endl;
    cout<<"A continuacion se muestra la cartelera."<<endl;
    //_cartelera.showCartelera();         //Muestra la cartelera
    Ventas ventas_usuario;
    ventas_usuario.setNombreUsuario(nombre_usuario);        //Registra al usuario que va a comprar
    string option2="";

//    map<int,Pelicula>::iterator iter;
//    map<int,Pelicula> maptemp = _cartelera.getCartelera();
//    for (iter=maptemp.begin();iter!=maptemp.end();iter++) {

//        iter->second.showSala();
//    }
    while(option2 != "2"){
        _cartelera.showCartelera();         //Muestra la cartelera
        cout<<endl<<endl;
        do{
            cout <<" 1 - Reservar asiento"<<endl
                 <<" 2 - Salir"<<endl;
            cout <<"Ingrese la opcion elegida -> "; cin>>option2;
        }while(option2 <"1" && option2 > "2");

        if (option2 == "1") {
            cout<<endl<<endl<< "A continuacion se muestra la tabla de precios: "<<endl;
            char s='n';
            do{
                Ventas().showTablaPrecios();        //Muestra la tabla de precios
                cout<<"Ingrese 's' para continuar: "; cin >> s;
            }while(s != 's');

            int columna;
            string fila, _id;
            bool idd;           //Mira si existe el id
            do{
                idd = true;
                cout<<"Ingrese el id(identificacion) de la pelicula que desea reservar: "; cin>>_id;

                for (unsigned int i = 0; i < (_id.size());i++) {        //Valida que sean numeros
                    if (!isdigit(_id[i])){
                        idd=false;
                        break;
                    }

                }
                if(idd == false){
                    cout<<"Debe ingresar numeros enteros. Vuelva a intentarlo"<<endl;
                    idd=true;
                }else {
                    map<int,Pelicula>::iterator iter;
                    map<int,Pelicula> maptemp = _cartelera.getCartelera();
                    for (iter=maptemp.begin();iter!=maptemp.end();iter++) {
                        if (iter->first == stoi(_id)){
                            idd=false;
                            break;
                        }
                    }
                    if(idd == true) cout<<"Debe ingresar un id existente, vuelva a intentarlo. "<<endl;

                }

            }while(idd == true);

            string entradas;                        //Variable que controla el numero de entradas que va a comprar el usuario
            bool val;
            do{
                val=true;
                cout<<"Ingrese el numero de entradas que desea comprar: "; cin>>entradas;
                for (unsigned int i = 0; i < (entradas.size());i++) {        //Valida que sean numeros
                    if (!isdigit(entradas[i])){
                        val=false;
                        break;
                    }
                }
                if(val==false) cout<<"Debe ingresar numeros enteros. Vuelve a intentarlo."<<endl;
            }while(val == false);
            int count_ent=1;
            while (count_ent <= stoi(entradas) ) {
                do{
                    idd = false;
                    map<int,Pelicula>::iterator iter;
                    map<int,Pelicula> maptemp = _cartelera.getCartelera();
                    for (iter=maptemp.begin();iter!=maptemp.end();iter++) {
                        //cout<<_id<<endl;
                        if (iter->first == stoi(_id)){
                            idd=true;
                            iter->second.showSala();
                            fflush(stdin);
                            cout<<endl<<"A continuacion realice su compra: "<<endl;
                            cout<<"Ingrese la fila del asiento que desea reservar: ";cin>>fila;
                            if ((fila[0]-1) - 'A' <= iter->second.getFila()){       //Mira si la fila existe
                                fflush(stdin);
                                cout<<"Ingrese la columna del asiento que desea reservar: "; cin>>columna;
                                if (columna>0 && columna < iter->second.getColumna()){      //Mira si la columna existe
                                    idd = iter->second.validateReservar(fila,columna);      //Mira si el asiento esta ocupado
                                    if (idd == true){
                                        //Mira a que tipo pertenece el asiento elegido;
                                        int valor_precio=0;
                                        string formato=iter->second.getFormato();
                                        if((('A' +(iter->second.getFila()-1))-fila[0]) <= 2 ){       //Mira si el asiento es vibrosound
                                            if(formato == "3D"){
                                                valor_precio = 11900;
                                                _reporte.compraVibro3d(valor_precio);                   //Guarda el registro de la compra
                                            }
                                            else if (formato == "2D"){
                                                valor_precio = 9900;
                                                _reporte.compraVibro2d(valor_precio);                  //Guarda el registro de la compra
                                            }
                                        }
                                        else{                                                          //Mira si el asiento es general
                                            if(formato == "3D"){
                                                valor_precio = 10800;
                                                _reporte.compraGeneral3d(valor_precio);                 //Guarda el registro de la compra
                                            }
                                            else if (formato == "2D"){
                                                valor_precio = 7900;
                                                _reporte.compraGeneral2d(valor_precio);
                                            }

                                        }

                                        cout<<"El precio del asiento elegido es: $"<<valor_precio<<endl;
                                        pagoUsuario(valor_precio);                          //El usuario realiza el pago

                                        ventas_usuario.setFilaAsiento(fila);
                                        ventas_usuario.setColumnAsiento(columna);
                                        ventas_usuario.setValorCompra(valor_precio);           //Guarda el registro de la compra por Usuario
                                        ventas_usuario.comprarAsientos(_cartelera,stoi(_id));        //Hace la compra del asiento
                                        string puesto = fila + to_string(columna);
                                        _cartelera.setPuestosComprados(stoi(_id), puesto);      //Guarda los puestos comprados para guardarlos en archivo

                                    }
                                    else {
                                        cout<<"Debe ingresar un asiento disponible."<<endl;
                                    }


                                }
                                else {
                                    cout<<"Ingreso una columna incorrecta"<<endl;
                                    idd=false;
                                }
                            }
                            else {
                                cout<<"Ingreso una fila incorrecta"<<endl;
                                idd=false;
                            }
                        }
                    }
                    if(idd == false)cout <<"Ingreso una fila o columna incorrecta, vuelva a intentarlo. "<<endl;
                    //maptemp.clear();
                }while(idd == false);
                count_ent++;

            }
            option2 = "2";
        }
        else {
            _reporte.setReporteVentas(ventas_usuario);          //Se guardan las compras realizadas por el usuario
            cout<<"Ha salido del perfil de Usuario."<<endl;
        }
    }
    return _cartelera;
}

void pagoUsuario(int valor_precio){
    int billetes[] = {50000, 20000, 10000, 5000, 2000, 1000, 500, 200, 100, 50};
    int cantidad[10];
    int resultado, dinero_usuario;
    bool pago;
    do{
        pago = true;
        cout << "Ingrese el dinero a pagar, se le devolvera de ser necesario: "; cin >> dinero_usuario;
        if (dinero_usuario < valor_precio) pago=false;
        if (pago == false) cout<<"No ha pagado el valor requerido, vuelva a intentarlo"<<endl;
    }while(pago == false);

    cout<<endl<<"Pago realizado con exito!"<<endl;
    int devuelta = dinero_usuario-valor_precio;
    resultado = devuelta;

    for (int i = 0; i < 10; ++i) {
        cantidad[i] = resultado / billetes[i];
        resultado = resultado % billetes[i];
        //cout << cantidad[i];
    }
    cout<<"Su devuelta sera: "<<endl;
    for (int i = 0; i < 10; ++i) {
        cout << billetes[i] << " : " << cantidad[i] << endl;
    }

    cout << "Faltante : " << resultado << endl;



}
