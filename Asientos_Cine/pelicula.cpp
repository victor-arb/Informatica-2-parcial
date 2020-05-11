#include "pelicula.h"

Pelicula::Pelicula(string _nombre, string _genero, int _sala, string _hora, int _nfil, int _ncol,string _duracion, string _clasificacion, string _formato)
{
    nombre = _nombre;
    genero = _genero;
    sala = _sala;
    hora = _hora;
    nfil = _nfil;
    ncol = _ncol;
    duracion = _duracion;
    setAsientTotal();                       //Crea los asientos totales
    asien_disponible = asien_total;         //Asientos totales = filas * columnas
    setAsientosSala();                      //Crea la sala con los asientos en modo disponibles;
    clasificacion = _clasificacion;
    formato = _formato;
}
Pelicula::~Pelicula()
{
}

//Metodos setters
void Pelicula::setNombre(string _nombre)
{
    nombre = _nombre;
}
void Pelicula::setGenero(string _genero)
{
    genero = _genero;
}
void Pelicula::setSala(int _sala)
{
    sala = _sala;
}
void Pelicula::setHora(string _hora)
{
    hora = _hora;
}
void Pelicula::setAsientDisponible(int _asien_disponible)
{
    asien_disponible = _asien_disponible;
}
void Pelicula::setAsientTotal()
{
   asien_total = nfil*ncol;
}
void Pelicula::setClasificacion(string _clasificacion)
{
    clasificacion = _clasificacion;
}
void Pelicula::setFilas_Colum(int _nfil, int _ncol)
{
    nfil = _nfil;
    ncol = _ncol;
}

//Crea los asientos en modo disponible, con el caracter "+"
void Pelicula::setAsientosSala()
{
//    asientos_sala = new string *[nfil];
//    for (int i=0;i < nfil; i++) {
//        asientos_sala[i] =  new string [ncol];

//    }
    //Llena la matriz
    for (int i = 0; i < nfil; i++) {
        for (int j=0; j< ncol; j++) {
            asientos_sala[i][j] = "+";
        }
    }
    showSala();
}

//Metodos getters
string Pelicula::getNombre()
{
    return nombre;
}
string Pelicula::getGenero()
{
    return genero;
}
string Pelicula::getDuracion()
{
    return duracion;
}
int Pelicula::getSala()
{
    return sala;
}
string Pelicula::getHora()
{
    return hora;
}
int Pelicula::getAsientDisponible()
{
    return asien_disponible;
}
int Pelicula::getAsientTotal()
{
    return asien_total;
}
string Pelicula::getClasificacion()
{
    return clasificacion;
}
string Pelicula::getFormato()
{
    return formato;
}
int Pelicula::getFila()
{
    return nfil;
}
int Pelicula::getColumna()
{
    return ncol;
}

//Mostrar la sala con los asientos disponibles
void Pelicula::showSala()
{
    cout<<"Los asientos disponibles se simbolizan con '+' y los ocupados con '-': "<<endl<<endl;
    string aux(unsigned(ncol)*7, '-');
    cout<<aux<<endl;
    cout<<"   ";
    for (int i = 1; i <= ncol; i++) {
        if (i < 10){
            cout<<" |   "<<i;
        }
        else if (i == 10) cout << " | "<<i;
        else if (i<100) {
            cout<<"  | "<<i;
        }
    }
    cout<< "  |"<<endl;
    cout<<aux<<endl;
    string auxLetra = "A";
    auxLetra[0] += (nfil-1);        //Variable auxiliar para imprimir la letra a la que pertenece la fila
    for (int i = 0; i<nfil ; i++) {
        cout <<" "<<auxLetra<<" |";
        for (int j = 0; j < ncol; j++) {
            if (j==0){
                cout<<"|  "<<asientos_sala[i][j];
            }
            else {
                cout<<"  |  "<<asientos_sala[i][j];
            }

        }
        if(i == 0 || i == 1 ){
            cout<< "  || "<<auxLetra<<" |  ----> VibroSound "<<formato<<endl;
        }else {
            cout<< "  || "<<auxLetra<<" |  ----> General "<<formato<<endl;
        }
        cout<<aux<<endl;
        auxLetra[0] -= 1;
    }
    cout<<"   ";
    for (int i = 1; i <= ncol; i++) {
        if (i < 10){
            cout<<" |   "<<i;
        }
        else if (i == 10) cout << " | "<<i;
        else if (i<100) {
            cout<<"  | "<<i;
        }
    }
    cout<< "  | ----->> PANTALLA(Ubicacion)"<<endl;
    cout<<aux<<endl;

}

bool Pelicula::validateReservar(string fila,  int col){
    bool reservacion = true;
    string aux = "A";
    int _fila = ((aux[0]+(nfil-1))-fila[0]);     //Numero equivalente de la fila al string ingresado
    for (int i = 0; i < nfil; i++) {
        for (int j=0; j< ncol; j++) {
            if (i == _fila && j==col-1) {
                if(asientos_sala[i][j] == "-"){         //Comprueba si el asiento esta disponible
                    cout<<"El asiento esta ocupado. "<<endl;
                    reservacion = false;
                }

            }

        }
    };
    return reservacion;
}

void Pelicula::reservar(string fila,  int col)
{
    string aux = "A";
    int _fila = ((aux[0]+(nfil-1))-fila[0]);     //Numero equivalente de la fila al string ingresado
    for (int i = 0; i < nfil; i++) {
        for (int j=0; j< ncol; j++) {
            if (i == _fila && j==col-1) {
                asientos_sala[i][j] = "-";    //Realiza la reservacion

            }

        }
    };
    asien_disponible--;
}

