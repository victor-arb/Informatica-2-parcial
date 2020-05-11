#ifndef PELICULA_H
#define PELICULA_H

#include <string>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Pelicula
{
public:
    Pelicula(string _nombre="", string _genero="", int _sala=0, string _hora="", int _nfil=10, int _ncol=15,string _duracion="", string _clasificacion="", string _formato="");
    ~Pelicula();
    void setNombre(string _nombre);
    void setGenero(string _genero);
    void setSala(int _sala);
    void setHora(string _hora);
    void setAsientDisponible(int _asien_disponible);
    void setAsientTotal();
    void setClasificacion(string _clasificacion);
    void setFilas_Colum(int _nfil, int _ncol);
    void setAsientosSala();

    string getNombre();
    string getGenero();
    string getDuracion();
    int getSala();
    string getHora();
    int getAsientDisponible();
    int getAsientTotal();
    string getClasificacion();
    string getFormato();
    int getFila();
    int getColumna();

    void showSala();                //Muestra la sala con los asientos disponibles
    void reservar(string fila,  int col);          //Realiza la reserva de una asiento
    bool validateReservar(string fila,  int col);

private:
    //Atributos
    string nombre;
    string genero;
    string duracion;
    int sala;                              //Numero de la sala
    string hora;
    int asien_disponible;
    int asien_total;
    string clasificacion;
    string formato;

    int nfil, ncol;

    string asientos_sala[10][15];             //Matriz con el estado de los asientos de la sala de cine
    //string **asientos_sala;

};

#endif // PELICULA_H
