#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <pelicula.h>
#include <cartelera.h>
#include <ventas.h>
#include <reportes.h>
#include <fstream>
#include <login.h>

using namespace std;

static string ArchivoVentas = "../Asientos_cine/ventas.txt";           //Variable global con la direccion del archivo con los reportes de ventas
static string ArchivoTotales = "../Asientos_cine/totales.txt";          //Variable global con la direccion del archivo con los reportes totales
static string DirArcivoAdmin = "../Asientos_cine/sudo.txt";             //Variable global con la direccion del archivo de administrador
static string DirArchivoUsers = "../Asientos_cine/users.txt";
static string DirArchivoCartelera = "../Asientos_cine/cartelera.txt";
static string DirArchivoPuestos = "../Asientos_cine/puestos.txt";

Cartelera menuAdmin(Cartelera _cartelera,Reportes& _reporte, Login& _login);          //Menu con las funciones del administrador
Cartelera menuUsuario(Cartelera _cartelera, Reportes& _reporte, string nomuser);        //Menu con las funciones del usuario

template <typename t>
void pagoUsuario(t valor_precio);   //efectua el pago del usuario


int main()
{
    string option = "";
    Cartelera _cartelera;
    _cartelera.setDirArchivos(DirArchivoCartelera, DirArchivoPuestos);          //Se asigna nombre a los archivos
    Reportes _reporte;
    _reporte.setArchivoVentas(ArchivoVentas);                                   //Se asigna nombre a los archivos
    _reporte.setArchivoTotales(ArchivoTotales);                                 //Sea asigna nombre a los archivos
    Login _login;
    _login.setArchivos(DirArcivoAdmin, DirArchivoUsers);                        //Se asigna nombre a los archivos
    _login.cargarUsers();           //Carga los usuarios registrados

    //Menu de entrada
    while(option != "3"){
        cout<<endl<<endl;
        do{
           cout <<" 1 - Ingresar como administrador"<<endl
                <<" 2 - Entrar como Usuario"<<endl
                <<" 3 - Salir(Guarda la cartelera y los puestos reservados, tenga en cuenta\n"
                  "           que si tiene datos previamente en el archivo que no han sido cargados a la cartelera\n"
                  "           seran reemplazados por la cartelera actual)"<<endl;
           cout<<"Ingrese la opcion elegida -> "; cin>>option;
        }while(option < "1"  && option > "3");

        if (option == "1") _cartelera = menuAdmin(_cartelera, _reporte, _login);
        else if (option == "2"){
            string optionsign="";
            while(optionsign != "3"){
                do{
                   cout<<endl<<endl;
                   cout <<" 1 - Registrarse( si no tiene una cuenta )"<<endl
                        <<" 2 - Ingresar "<<endl
                        <<" 3 - Salir"<<endl;
                   cout<<"Ingrese la opcion elegida -> "; cin>>optionsign;
                }while(optionsign < "1"  && optionsign > "3");
                if (optionsign == "1"){             //Opcion registro
                    string nom_user, cont_user;
                    bool reg = true;
                    do{
                        cout<< "Realice el siguiente registro: "<<endl;
                        cout<<endl<<"Ingrese el nombre de usuario: "; cin>>nom_user;
                        cout<<endl<<"Ingrese la contrasenia: "; cin>>cont_user;

                        reg = _login.setUsuarios(nom_user, cont_user);    //Mira si el nombre de usuario ya existe y si no lo guarda

                    }while(reg == true);        //Hace el registro si el nombre de usuario no se
                    _login.guardarUsers(nom_user, cont_user);       //Guarda el nombre en el archivo
                    cout<<endl<<"Registro realizado exitosamente."<<endl<<endl;
                }
                else if(optionsign == "2"){             //Opcion ingresar
                    string nom_user, cont_user;
                    bool vali = false;
                    do{
                        cout<<"A continuacion, Inicie sesion: "<<endl;
                        cout<<"Ingrese el nombre de usuario: "; cin>>nom_user;
                        cout<<"Ingrese la contrasenia: "; cin >>cont_user;
                        vali = _login.validateUser(nom_user, cont_user);
                    }while(vali == false);
                    _cartelera = menuUsuario(_cartelera, _reporte, nom_user);
                    optionsign = "3";       //Sale al primer menu;
                }
                else if (optionsign == "3"){
                    cout<<"Ha salido del perfil de usuario."<<endl;
                }

            }

        }
        else if (option == "3"){        //Sale del programa y guarda el estado

            //Guarda en archivos el estado del programa (la cartelera y los puestos reservados
            string dirtemp = "../Asientos_cine/temp.txt";

            if (_cartelera.getCartelera().empty()){
                cout<<"No se ha guardado ningun dato, la cartelera se encuentra vacia."<<endl;
            }
            else {
                ofstream archivotemp (dirtemp.c_str());     //Archivo temporal para borrar el de cartelera y volverlo a llenar con la nueva
                archivotemp.close();
                if(remove(DirArchivoCartelera.c_str()) != 0 )
                    perror("Error al borrar archivo cartelera.");
                else {

                    rename(dirtemp.c_str(), DirArchivoCartelera.c_str());
                    _cartelera.guardarEstadoCartelera();
                    cout<<"Se ha guardado el estado de la cartelera."<<endl;
                }
                ofstream archivotemp1 (dirtemp.c_str());
                archivotemp.close();
                if(remove(DirArchivoPuestos.c_str()) != 0 )
                    perror("Error al borrar archivo puestos.");
                else {
                    rename(dirtemp.c_str(), DirArchivoPuestos.c_str());
                     _cartelera.guardarPuestos();
                     cout<<"Se ha guardado el estado de los puestos reservados."<<endl;
                }
            }



        }
    }

}

//Menu del Administrador
Cartelera menuAdmin(Cartelera _cartelera, Reportes& _reporte, Login& _login){
    cout<<"Bienvenido, Ha ingresado como administrador."<<endl;
    bool val = true;
    do{
        string cont_admin;
        cout<<"Digite su contrasenia de administrador -> "; cin>>cont_admin;
        val = _login.validateAdmin(cont_admin);             //Valida que la contraseña sea correcta
        if(val == false) cout<<"Contrasenia incorrecta, vuelve a intentarlo"<<endl;
    }while(val == false);
    string option1="";
    _cartelera.cargarEstadoCartelera();             //Carga la cartelera previamente guardada si existe
    _cartelera.cargarPuestos();                     //Carga los puestos previamente guardados si existe
    cout<<endl<<endl<<"Se han cargado los datos de los archivos de cartelera y puestos."<<endl;

    //Menu con las opciones de Administrador
    while(option1 != "4"){
        cout<<endl<<endl;
        do{
            cout <<" 1 - Ingresar una pelicula a la cartelera"<<endl
                 <<" 2 - Quitar una pelicula de la cartelera"<<endl
                 <<" 3 - Generar un reporte"<<endl
                 <<" 4 - Salir"<<endl;
            cout <<"Ingrese la opcion elegida -> "; cin>>option1;
        }while(option1 <"1" && option1 > "4");

        if (option1 == "1"){        //Ingresa la pelicula
            //Atributos para la pelicula
            string nombre, genero, duracion,hora, clasificacion, formato ;
            int sala,fil,col;
            string _id;
            bool idd;           //Mira si se repite el id
            cout<<endl;
            do{                                     //Valida que no se repita el id de la pelicula
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


            //LLena los atributos para la pelicula
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
            //Se valida que las filas y las columnas sean maximo 15 para que la sala se muestre correctamente
            do{
                cout<<"Ingrese el numero de filas(max 15): "; cin>> fil;
                if(fil>15) cout<<"Ha sobrepasado el maximo permitido, vuelva a intentar."<<endl;
            }while(fil > 15);
            do{
                cout<<"Ingrese el numero de columnas(max 15): "; cin>>col;
                if(col>15) cout<<"Ha sobrepasado el maximo permitido, vuelva a intentar."<<endl;
            }while(col > 15);


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

        else if (option1 == "3"){      //Genera un reporte
            string optionR="";
            do{
                cout<<"1 - Mostrar reporte de Ventas por Usuarios"<<endl
                    <<"2 - Mostrar reporte de Ventas por registros Totales"<<endl;
                cout<<"Ingrese una opcion: "; cin>>optionR;
            }while(optionR < "1" && optionR >"2");

            if (optionR == "1"){
                _reporte.cargarReporteVentas();         //Carga el reporte desde el archivo al mapa para despues mostrarlo
                cout<<endl;
                cout<< "------------------------------------------------------"<<endl;
                cout<< "            REPORTE DE VENTAS(Por cada compra)        "<<endl;
                cout<< "------------------------------------------------------"<<endl;
                _reporte.generarReporteVentas(2);                    //Genera el reporte de ventas por usuario
            }
            else if (optionR == "2"){
                _reporte.cargarReporteTotales();        //Carga el reporte desde un archivo si existe y lo suma con el actual
                cout<<endl;
                cout<< "---------------------------------------"<<endl;
                cout<< "       REPORTE DE VENTAS TOTALES       "<<endl;
                cout<< "---------------------------------------"<<endl;
                _reporte.generarReporteTotales(2);                    //Genera el reporte de ventas por usuario y lo imprime
            }
        }
        else if (option1 == "4") {          //Sale del menu
            cout<<"Ha salido del perfil de administrador. "<<endl;
        }

    }
    return _cartelera;
}


//Menu de Usuario
Cartelera menuUsuario(Cartelera _cartelera, Reportes &_reporte, string nomuser){
    string nombre_usuario = nomuser;
    cout<<endl<<" Bienvenido "<<nomuser<<endl<<endl<<endl;
    cout<<"A continuacion se muestra la cartelera."<<endl;
    //_cartelera.showCartelera();         //Muestra la cartelera
    Ventas ventas_usuario;
    ventas_usuario.setNombreUsuario(nombre_usuario);        //Registra al usuario que va a comprar
    string option2="";

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
                if (val == true){       //valida que no compre mas de los asientos disponibles
                    map<int,Pelicula>::iterator iter;
                    map<int,Pelicula> maptemp = _cartelera.getCartelera();
                    for (iter=maptemp.begin();iter!=maptemp.end();iter++) {
                        if (iter->first == stoi(_id)){
                            if(stoi(entradas) < 0 || stoi(entradas) > iter->second.getAsientDisponible()){
                                val= false;
                            }
                            if(val == false) cout<<"No puede comprar mas de los asientos disponibles. vuelve a intentarlo"<<endl;
                            break;
                        }
                    }

                }

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
                            do{             //Verifica que el usuario ingrese una letra
                                cout<<"Ingrese la fila del asiento que desea reservar: ";cin>>fila;
                                if (!isalpha(fila[0]) || fila.size() > 1) cout<<"Debe ingrear una letra. vuelve a intentarlo"<<endl;
                            }while(!isalpha(fila[0]));

                            if (('A' +(iter->second.getFila()-1))-fila[0] >= 0 && ('A' +(iter->second.getFila()-1))-fila[0] <= iter->second.getFila()){       //Mira si la fila existe
                                fflush(stdin);
                                cout<<"Ingrese la columna del asiento que desea reservar: "; cin>>columna;
                                if (columna>0 && columna < iter->second.getColumna()){      //Mira si la columna existe
                                    idd = iter->second.validateReservar(fila,columna);      //Mira si el asiento esta ocupado
                                    if (idd == true){
                                        //Mira a que tipo pertenece el asiento elegido;
                                        int valor_precio=0;
                                        string formato=iter->second.getFormato();
                                        if((('A' +(iter->second.getFila()-1))-fila[0]) <= 1 ){       //Mira si el asiento es vibrosound
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
                                        _cartelera = ventas_usuario.comprarAsientos(_cartelera,stoi(_id));        //Hace la compra del asiento
                                        string puesto = fila +":"+ to_string(columna);
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
            _reporte.setReporteVentas(ventas_usuario);          //Se guardan las compras realizadas por el usuario
            _reporte.generarReporteVentas(1);                   //Guarda el reporte con las ventas que se hicieron
            _reporte.generarReporteTotales(1);
        }
        else if (option2 == "2") {

            cout<<"Ha salido del perfil de Usuario."<<endl;
        }
    }
    return _cartelera;
}

template <typename t>
void pagoUsuario(t valor_precio){   //efectua el pago del usuario
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
    cout<<"Su devuelta sera: "<< devuelta <<endl;
    for (int i = 0; i < 10; ++i) {
        cout << billetes[i] << " : " << cantidad[i] << endl;
    }

    cout << "Faltante : " << resultado << endl;



}
