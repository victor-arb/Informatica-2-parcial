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
    Pelicula(string _nombre, string _genero, int _sala, string _hora, int _nfil, int _ncol, string _clasificacion, string _formato);
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

    string** asientos_sala;             //Matriz con el estado de los asientos de la sala de cine
    int nfil, ncol;
};

#endif // PELICULA_H
