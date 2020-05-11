#include "cartelera.h"

Cartelera::Cartelera()
{
}
Cartelera::~Cartelera()
{
}

//Ingresa peliculas a la cartelera
void Cartelera::setCartelera(int _id, Pelicula _pelicula)
{
    cartelera.insert(make_pair(_id, _pelicula));
}

//Retorna la cartelara con las peliculas
map<int, Pelicula> Cartelera::getCartelera()
{
    return cartelera;
}

//Muestra la cartelera de peliculas
void Cartelera::showCartelera()
{
    map<int, Pelicula>::iterator iter;
    string aux(100, '-');
    string aux1(100, '*');
    /*
    cout<<aux<<endl;
    cout<<" |  ID  |             Nombre             |    Genero    |   Duracion   |   Sala  |  Hora  |  Asientos Disponibles  | Clas. | Formato | ";
    cout<<aux<<endl;
    for(iter= cartelera.begin(); iter != cartelera.end();iter++){
        cout<<" |  "<<iter->first<<"  | "<<iter->second.getNombre()<<" | "<<iter->second.getGenero()
            <<" | "<<iter->second.getDuracion()<<" | "<<iter->second.getSala()<<" | "<<iter->second.getHora()
            <<" | "<<iter->second.getAsientDisponible()<<"/"<<iter->second.getAsientTotal()<<" |  "<<iter->second.getClasificacion()
            <<"  |  "<<iter->second.getFormato()<<"  |"<<endl;
    }
    */
    cout<<aux<<endl<<" |          CARTELERA            | "<<endl;
    cout<<aux<<endl<<endl;
    cout<<aux1<<endl<<endl;
    for (iter = cartelera.begin(); iter != cartelera.end();iter++) {
        cout<<aux<<endl;
        cout<<" |             ID               |  "<<iter->first<<"  |"<<endl<<aux<<endl
            <<" |           Nombre             |  "<<iter->second.getNombre()<<"  |"<<endl<<aux<<endl
            <<" |           Genero             |  "<<iter->second.getGenero()<<"  |"<<endl<<aux<<endl
            <<" |          Duracion            |  "<<iter->second.getDuracion()<<"  |"<<endl<<aux<<endl
            <<" |            Sala              |  "<<iter->second.getSala()<<"  |"<<endl<<aux<<endl
            <<" |            Hora              |  "<<iter->second.getHora()<<"  |"<<endl<<aux<<endl
            <<" | Asientos Disponibles/Totales |  "<<iter->second.getAsientDisponible()<<"/"<<iter->second.getAsientTotal()<<"  |"<<endl<<aux<<endl
            <<" |         Clasificacion        |  "<<iter->second.getClasificacion()<<"  |"<<endl<<aux<<endl
            <<" |            Formato           |  "<<iter->second.getFormato()<<"  |"<<endl<<aux<<endl;

        cout<<endl<<endl;
        cout<<aux1<<endl;
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
