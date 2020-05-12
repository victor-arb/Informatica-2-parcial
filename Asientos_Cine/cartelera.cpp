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

//Guarda la informacion de los puestos comprados para luego guardarla en un archivo
void Cartelera::setPuestosComprados(int _id, vector<string> _puestos)
{
    puestos_comprados.insert(make_pair(_id, _puestos));
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

//Ingresa el nombre de los archivos donde se guarda el estado de la cartelera
void Cartelera::setDirArchivos(string _archivoCartelera, string _archivoPuestos)
{
    archivoCartelera = _archivoCartelera;
    archivoPuestos = _archivoPuestos;
}

//Guarda en archivos la informacion de la cartelera y los puestos comprados
void Cartelera::guardarEstadoCartelera()
{
    ofstream archivoCartel;
    archivoCartel.open(archivoCartelera.c_str(), ios::app);
    if (archivoCartel.fail()){
        cout<<"El archivo de la cartelera no se pudo abrir."<<endl;
        exit(1);
    }
    string peli;
    map<int, Pelicula>::iterator iter;
    //LLena el string con la informacion que va en el archivo
    for(iter= cartelera.begin(); iter != cartelera.end();iter++){
        peli += to_string(iter->first) + ";" + iter->second.getNombre() + "," + iter->second.getGenero() + "," +
                to_string(iter->second.getSala()) + "," + iter->second.getHora() + "," + to_string(iter->second.getAsientDisponible()) +
                "," + to_string(iter->second.getAsientTotal()) + "," + iter->second.getClasificacion() + "," + iter->second.getFormato()
                +":" + to_string(iter->second.getFila()) + "." + to_string(iter->second.getColumna()) + ".";

       archivoCartel <<peli;        //Guarda la informacion en el archivo

    }

    cout<<"Se ha guardado la informacion de la cartelera con exito."<<endl;
    archivoCartel.close();

}
void Cartelera::cargarEstadoCartelera()
{

}


void Cartelera::guardarPuestos()
{
    ofstream archivoPuesto;
    archivoPuesto.open(archivoPuestos.c_str(), ios::app);
    if (archivoPuesto.fail()){
        cout<<"El archivo de la cartelera no se pudo abrir."<<endl;
        exit(1);
    }
    string peli;
    map<int, vector<string>>::iterator iter;
    //LLena el string con la informacion que va en el archivo
    for( iter= puestos_comprados.begin(); iter != puestos_comprados.end();iter++){
        peli += to_string(iter->first) + ";" ;
        for (unsigned int i=0;i<iter->second.size();i++) {
             peli += iter->second[i] + ",";
        }


       archivoPuesto <<peli;        //Guarda la informacion en el archivo

    }

    cout<<"Se ha guardado la informacion de la cartelera con exito."<<endl;
    archivoPuesto.close();
}
void Cartelera::cargarPuestos()
{

}
