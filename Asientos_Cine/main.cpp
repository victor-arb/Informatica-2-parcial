#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <pelicula.h>
#include <cartelera.h>
#include <ventas.h>
using namespace std;

Cartelera menuAdmin(Cartelera _cartelera);          //Menu con las funciones del administrador
bool validateAdmin(string _cont_admin);             //Valida la contraseña del administrador
Cartelera menuUsuario(Cartelera _cartelera);        //Menu con las funciones del usuario
void pagoUsuario(int valor_precio);                 //Funcion que efectua el pago del usuario
int main()
{
    string option = "";
    Cartelera _cartelera;
    while(option != "3"){
        do{
           cout <<" 1 - Ingresar como administrador"<<endl
                <<" 2 - Ingresar como Usuario"<<endl
                <<" 3 - Salir"<<endl;
           cout<<"Ingrese la opcion elegida -> "; cin>>option;
        }while(option < "1"  && option > "3");

        if (option == "1") menuAdmin(_cartelera);
        else if (option == "2") _cartelera = menuUsuario(_cartelera);
    }

}

//Menu del Administrador
Cartelera menuAdmin(Cartelera _cartelera){
    cout<<"Bienvenido, Ha ingresado como administrador."<<endl;
    bool val = true;
    do{
        string cont_admin;
        cout<<"Digite su contraseña de administrador -> "; cin>>cont_admin;
        val = validateAdmin(cont_admin);
    }while(val == false);
    string option1="";
    //Menu
    while(option1 != "4"){
        do{
            cout <<" 1 - Ingresar una pelicula a la cartelera"<<endl
                 <<" 2 - Quitar una pelicula de la cartelera"<<endl
                 <<" 3 - Cargar Cartelera desde un Archivo con los asientos previamente reservados"
                 <<" 4 - Generar un reporte"<<endl
                 <<" 5 - Salir y guardar cartelera en un archivo."<<endl;
            cout <<"Ingrese la opcion elegida -> "; cin>>option1;
        }while(option1 <"1" && option1 > "4");
        if (option1 == "1"){        //Ingresa la pelicula
            //Atributos para la pelicula
            string nombre, genero, duracion,hora, clasificacion, formato ;
            int sala,fil,col, _id;
            bool idd;           //Mira si se repite el id
            do{
                idd = true;
                cout<<"Ingrese el id(identificacion, un entero que no debe repetirse) de la pelicula: "; cin>>_id;
                map<int,Pelicula>::iterator iter;
                for (iter=_cartelera.getCartelera().begin();iter!=_cartelera.getCartelera().end();iter++) {
                    if (iter->first == _id){
                        idd=false;
                    }
                }
                if(idd == false) cout<<"El id ingresado ya existe, vuelva a intentarlo. ";
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
            cout<<"El numero de Asientos disponibles de la sala sera el numero de filas* numero de columnas: "<<endl;
            cout<< "Ingrese el numero de filas que contiene la sala: "; cin>>fil;
            cout<< "Ingrese el numero de columnas que contiene la sala: "; cin>>col;
            cout<< "Ingrese el formato de la pelicula (3D o 2D): "; cin>>formato;
            Pelicula peli(nombre,genero,sala,hora,fil,col,clasificacion,formato);
            _cartelera.setCartelera(_id, peli);
        }
        else if (option1 == "2") {          //Quitar una pelicula de la cartelera
            int _id ;
            _cartelera.showCartelera();     //Muestra la cartelera
            bool idd;                       //Mira si se repite el id
            //Eliminar
            do{
                idd = false;
                cout<<"Ingrese el id(identificacion) de la pelicula que desea eliminar: "; cin>>_id;
                map<int,Pelicula>::iterator iter;
                for (iter=_cartelera.getCartelera().begin();iter!=_cartelera.getCartelera().end();iter++) {
                    if (iter->first == _id){
                        idd=false;
                        _cartelera.deletePelicula(_id);         //Elimina la pelicula
                        break;
                    }
                }
                if(idd == true) cout<<"Debe ingresar un id existente, vuelva a intentarlo. ";
            }while(idd == true);
        }
        else if (option1 == "3") {      //Genera un reporte


        }
        else {
            cout<<"Ha salido del perfil de administrador. "<<endl;
        }

    }
    return _cartelera;
}

//Menu de Usuario
Cartelera menuUsuario(Cartelera _cartelera){
    string nombre_usuario;
    cout<<"Ha ingresado como Usuario."<<endl;
    cout<<" Ingrese el nombre del usuario: "<<nombre_usuario;
    cout<<" Bienvenido "<<nombre_usuario<<endl<<"A continuacion se muestra la cartelera.";
    _cartelera.showCartelera();         //Muestra la cartelera
    Ventas ventas_usuario;
    ventas_usuario.setNombreUsuario(nombre_usuario);        //Registra al usuario que va a comprar
    string option2="";
    while(option2 != "3"){
        do{
            cout <<" 1 - Mostrar tabla de precios segun el formato de la pelicula"<<endl
                 <<" 2 - Reservar asiento"<<endl
                 <<" 3 - Salir"<<endl;
            cout <<"Ingrese la opcion elegida -> "; cin>>option2;
        }while(option2 <"1" && option2 > "3");
        if (option2 == "1"){
            Ventas().showTablaPrecios();        //Muestra la tabla de precios
        }
        else if (option2 == "2") {
            int _id, columna;
            string fila;
            bool idd;           //Mira si existe el id
            do{
                idd = false;
                cout<<"Ingrese el id(identificacion) de la pelicula de la que desea hacer una reservacion: "; cin>>_id;
                map<int,Pelicula>::iterator iter;
                for (iter=_cartelera.getCartelera().begin();iter!=_cartelera.getCartelera().end();iter++) {
                    if (iter->first == _id){
                        idd=true;
                        iter->second.showSala();
                        cout<<"Ingrese la fila del asiento que desea reservar: ";cin>>fila;
                        if (fila[0] - 'A' <= iter->second.getFila()){       //Mira si la fila existe
                            cout<<"Ingrese la columna del asiento que desea reservar: "; cin>>columna;
                            if (columna>0 && columna < iter->second.getColumna()){      //Mira si la columna existe
                                idd = iter->second.validateReservar(fila,columna);      //Mira si el asiento esta ocupado
                                if (idd == true){
                                    //Mira a que tipo pertenece el asiento elegido;
                                    int valor_precio=0;
                                    string formato=iter->second.getFormato();
                                    if(((fila[0]+(iter->second.getFila()-1))-fila[0]) <= 2 ){       //Mira si el asiento es vibrosound
                                        if(formato == "3D") valor_precio = 11900;
                                        else if (formato == "2D") valor_precio = 9900;
                                    }
                                    else{                                                          //Mira si el asiento es general
                                        if(formato == "3D") valor_precio = 10800;
                                        else if (formato == "2D") valor_precio = 7900;
                                    }

                                    cout<<"El precio del asiento elegido es: $"<<valor_precio<<endl;
                                    pagoUsuario(valor_precio);                          //El usuario realiza el pago

                                    ventas_usuario.setFilaAsiento(fila);
                                    ventas_usuario.setColumnAsiento(columna);
                                    ventas_usuario.setValorCompra(valor_precio);           //Guarda el registro de la compra
                                    ventas_usuario.comprarAsientos(_cartelera,_id);        //Hace la compra del asiento


                                    //Se añade al registro los asientos comprados







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
                if(idd == false) cout<<"El id ingresado no existe o ingreso una fila o columna incorrecta, vuelva a intentarlo. ";
            }while(idd == false);

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
