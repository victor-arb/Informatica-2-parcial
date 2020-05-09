#include "cartelera.h"

Cartelera::Cartelera()
{
}
Cartelera::~Cartelera()
{
}
void Cartelera::setCartelera(int _id, Pelicula _pelicula)
{
    cartelera.insert(make_pair(_id, _pelicula));
}

map<int, Pelicula> Cartelera::getCartelera()
{
    return cartelera;
}

//Muestra la cartelera de peliculas
void Cartelera::showCartelera()
{
    map<int, Pelicula>::iterator iter;
    string aux(100, '-');
    cout<<aux<<endl;
    cout<<" |  ID  |             Nombre             |    Genero    |   Duracion   |   Sala  |  Hora  |  Asientos Disponibles  | Clas. | Formato | ";
    cout<<aux<<endl;
    for(iter= cartelera.begin(); iter != cartelera.end();iter++){
        cout<<" |  "<<iter->first<<"  | "<<iter->second.getNombre()<<" | "<<iter->second.getGenero()
            <<" | "<<iter->second.getDuracion()<<" | "<<iter->second.getSala()<<" | "<<iter->second.getHora()
            <<" | "<<iter->second.getAsientDisponible()<<"/"<<iter->second.getAsientTotal()<<" |  "<<iter->second.getClasificacion()
            <<"  |  "<<iter->second.getFormato()<<"  |"<<endl;
    }
}

//Elimina la pelicula seleccionada de acuerdo al id
void Cartelera::deletePelicula(int _id)
{
    map<int, Pelicula>::iterator iter;
    for(iter= cartelera.begin(); iter != cartelera.end();iter++){
        if(iter->first == _id){
            cartelera.erase(_id);
        }
    }
}
