#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <pelicula.h>
#include <cartelera.h>

using namespace std;

Cartelera menuAdmin(Cartelera _cartelera);
bool validateAdmin(string _cont_admin);
Cartelera menuUsuario(Cartelera _cartelera);
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
                 <<" 3 - Generar un reporte"<<endl
                 <<" 4 - Salir"<<endl;
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

