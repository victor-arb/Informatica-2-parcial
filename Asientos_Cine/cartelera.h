#ifndef CARTELERA_H
#define CARTELERA_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <pelicula.h>
#include <fstream>

using namespace std;


class Cartelera
{
public:
    Cartelera();
    ~Cartelera();

    //Metodos setters
    void setCartelera(int id, Pelicula _pelicula);
    void setPuestosComprados(int _id, vector<string> _puestos);
    void setDirArchivos(string _archivoCartelera, string _archivoPuestos);

    map<int,Pelicula> getCartelera();
    void showCartelera();
    void deletePelicula(int _id);


    //Guardar y cargar archivos
    void guardarEstadoCartelera();          //Guarda en archivos la informacion de la cartelera y los puestos comprados
    void cargarEstadoCartelera();           //Carga la informacion previamente guardada en archivos;
    void guardarPuestos();
    void cargarPuestos();


private:
    map<int,Pelicula> cartelera;
    map<int,vector<string>> puestos_comprados;          //Mapa que guarda la informacion de la id de la pelicula y los puestos comprados
    string archivoCartelera;
    string archivoPuestos;

};

#endif // CARTELERA_H
