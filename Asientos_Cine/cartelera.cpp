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
void Cartelera::setPuestosComprados(int _id, string _puestos)
{
    map<int,vector<string>>::iterator iter;
    bool oper = false;          //Mira si el id ya existe en el mapa
    for (iter = puestos_comprados.begin();iter!= puestos_comprados.end();iter++) {
        if(iter->first == _id){
            vector<string> temp = iter->second;
            temp.push_back(_puestos);
            puestos_comprados[_id] = temp;          //Agrega un puesto a una pelicula ya registrada en el papa
            oper = true;
        }
    }
    if (oper == false){
        vector<string> temp;
        temp.push_back(_puestos);
        puestos_comprados.insert(make_pair(_id, temp));     //Agrega una nueva pelicula con nuevos puestos reservados
    }

}
//Iguala otra cartelera modificada
void Cartelera::actualizarCartelera(map<int, Pelicula> _temp)
{
    cartelera = _temp;
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
    cartelera.erase(_id);
    /*
    map<int, Pelicula>::iterator iter;
    for(iter= cartelera.begin(); iter != cartelera.end();iter++){
        if(iter->first == _id){
            cartelera.erase(_id);
        }
    }
    */
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
    //unsigned int cont_map=1;
    map<int, Pelicula>::iterator iter;
    //LLena el string con la informacion que va en el archivo
    for(iter= cartelera.begin(); iter != cartelera.end();iter++){
        peli += to_string(iter->first) + ";" + iter->second.getNombre() + "/" + iter->second.getGenero() + "," + iter->second.getDuracion() + "," +
                to_string(iter->second.getSala()) + "," + iter->second.getHora() + "," + to_string(iter->second.getAsientDisponible()) +
                "," + to_string(iter->second.getAsientTotal()) + "," + iter->second.getClasificacion() + "," + iter->second.getFormato()
                +":" + to_string(iter->second.getFila()) + "." + to_string(iter->second.getColumna()) + ".";

        archivoCartel <<peli<<endl;        //Guarda la informacion en el archivo
        peli = "";

    }

    //cout<<"Se ha guardado la informacion de la cartelera con exito."<<endl;
    archivoCartel.close();

}
void Cartelera::cargarEstadoCartelera()
{
    int idd, sala=0, asien_dispon=0, asien_totales=0, fila = 0, columna = 0 ;
    string nombre, genero, duracion, hora, clasificacion, formato;

    ifstream archivoCar;
    archivoCar.open(archivoCartelera.c_str(), ios::in);
    if (archivoCar.fail()){
        cout<<"No se pudo abrir el archivo con la cartelera."<<endl;
        exit(1);
    }
    string linea;
    while(!archivoCar.eof()){ //mientras no sea final del archivo.
       getline(archivoCar,linea);
       if (linea != ""){            //Comprueba que la linea no este vacia
               unsigned int pos = linea.find(";");
               idd = stoi(linea.substr(0,pos));
               unsigned int postemp = linea.find("/");
               nombre = linea.substr(pos+1,postemp-(pos+1));
               pos = linea.find("/");
               unsigned int i = pos+1;
               int cont_coma = 0, cont_punto = 0;               //Cuenta las ',' y los '.' para establecer los atributos
               while (i < linea.size()){
                   if (linea[i] == ','){
                       unsigned int pos2 = i;
                       cont_coma++;
                       if (cont_coma == 1) genero = linea.substr(pos+1,pos2-(pos+1));
                       else if (cont_coma == 2) duracion = linea.substr(pos+1,pos2-(pos+1));
                       else if (cont_coma == 3) sala = stoi(linea.substr(pos+1,pos2-(pos+1)));
                       else if (cont_coma == 4) hora = linea.substr(pos+1,pos2-(pos+1));
                       else if (cont_coma == 5) asien_dispon = stoi(linea.substr(pos+1,pos2-(pos+1)));
                       else if (cont_coma == 6) asien_totales = stoi(linea.substr(pos+1,pos2-(pos+1)));

                       if (cont_coma == 7){
                           clasificacion = linea.substr(pos+1,pos2-(pos+1));
                           pos = pos2;
                           pos2 = linea.find(":");
                           formato = linea.substr(pos+1,pos2-(pos+1));
                           pos = pos2;
                       }else {
                            pos = i;
                       }

                       i++;
                   }
                   else if (linea[i] == '.') {
                       unsigned int pos2 = i;
                       cont_punto++;
                       if (cont_punto == 1) fila = stoi(linea.substr(pos+1,pos2-(pos+1)));
                       else if (cont_punto == 2) columna = stoi(linea.substr(pos+1,pos2-(pos+1)));
                       pos = i;
                       i++;

                   }
                   else {
                       i++;
                   }
               }
               Pelicula peli_temp (nombre, genero, sala, hora, fila, columna, duracion, clasificacion, formato);
               //peli_temp.setAsientDisponible(asien_dispon);
               cartelera.insert(make_pair(idd, peli_temp));

           }
    }


}


void Cartelera::guardarPuestos()
{
    ofstream archivoPuesto;
    archivoPuesto.open(archivoPuestos.c_str(), ios::app);
    if (archivoPuesto.fail()){
        cout<<"El archivo de la cartelera no se pudo abrir."<<endl;
        exit(1);
    }
    string puestos;
    map<int, vector<string>>::iterator iter;
    //LLena el string con la informacion que va en el archivo
    //unsigned int cont_map = 1;
    for( iter= puestos_comprados.begin(); iter != puestos_comprados.end();iter++){
        puestos += to_string(iter->first) + ";" ;
        for (unsigned int i=0;i<iter->second.size();i++) {
             puestos += iter->second[i] + ",";
        }

        archivoPuesto <<puestos<<endl;        //Guarda la informacion en el archivo
        puestos = "";

    }

    //cout<<"Se ha guardado la informacion de la cartelera con exito."<<endl;
    archivoPuesto.close();
}
void Cartelera::cargarPuestos()
{
    int idd=0, columna=0;
    string fila;

    ifstream archivoPues;
    archivoPues.open(archivoPuestos.c_str(), ios::in);
    if (archivoPues.fail()){
        cout<<"No se pudo abrir el archivo con los puestos reservados."<<endl;
        exit(1);
    }
    string linea;
    while(!archivoPues.eof()){ //mientras no sea final del archivo.
           getline(archivoPues,linea);
           if(linea != ""){                 //Comprueba que la linea no este vacia
               unsigned int pos = linea.find(";");  //Toma la posicion entre el inicio y el ";" como el id de la pelicula
               idd = stoi(linea.substr(0,pos));
               unsigned int i = pos+1;
               while (i < linea.size()){
                   if (linea[i] == ','){

                       unsigned int pos2 = i;
                       string lineatemp = linea.substr(pos+1, pos2-(pos2+1));    //Hace una sublinea con la fila y la conexion
                       unsigned int postemp = lineatemp.find(":");
                       fila = lineatemp.substr(0,postemp);
                       columna = stoi(lineatemp.substr(postemp+1));
                       pos = i;
                       i++;
                       //Reserva la el asiento que va encontrando con fila y columna
                       map<int,Pelicula>::iterator iter;
                       for (iter = cartelera.begin(); iter != cartelera.end();iter++) {
                           if(iter->first == idd){                              //Busca que la pelicula exista
                               iter->second.reservar(fila,columna);             //Hace la reservacion
                               string puesto = fila + ":" + to_string(columna);
                               setPuestosComprados(idd, puesto);            //Guarda el puesto que se cargo como comprado
                           }
                       }

                   }
                   else {
                       i++;
                   }

               }

           }

       }

}
