#ifndef CARTELERA_H
#define CARTELERA_H

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <pelicula.h>

using namespace std;


class Cartelera
{
public:
    Cartelera();
    ~Cartelera();


    void setCartelera(int id, Pelicula _pelicula);
    map<int,Pelicula> getCartelera();
    void showCartelera();
    void deletePelicula(int _id);

private:
    map<int,Pelicula> cartelera;
};

#endif // CARTELERA_H
