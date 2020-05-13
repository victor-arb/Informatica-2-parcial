#include "login.h"

Login::Login()
{
}
Login::~Login()
{
}
void Login::setArchivos(string _dir_sudo, string _dir_users)
{
    dir_sudo = _dir_sudo;
    dir_users = _dir_users;
}
//Valida el ingreso como administrador
bool Login::validateAdmin(string _cont_admin)
{
    bool vali = false;
    ifstream archivoAdmin;
    string contra;
    archivoAdmin.open(dir_sudo.c_str(), ios::in);

    if(archivoAdmin.fail()){
        cout<<"No se pudo abrir el archivo de Administrador."<<endl;
        exit(1);
    }

    while(!archivoAdmin.eof()){ //mientras no sea final del archivo, solo va a terminar con el contenido de la linea pedida
        getline(archivoAdmin,contra);
    }
    archivoAdmin.close();
    if (_cont_admin == contra) vali=true;
    return vali;
}
//Valida el ingreso como usuario
bool Login::validateUser(string _nom_user, string _cont)
{
    map<string, string>::iterator iter;
    bool val = false;                   //Valida que el usuario y la contraseña sean correctas
    bool vali_nom = false;                  //Valida solo el nombre de usuario
    for (iter = usuarios.begin();iter != usuarios.end();iter++) {
        if (iter->first == _nom_user ){
            vali_nom = true;
            if(iter->second == _cont){
                val = true;
            }
            else {
                cout<<"Contraseña incorrecta, intente de nuevo"<<endl;
            }
        }
    }
    if (vali_nom == false) cout<<"Nombre de usuario incorrecto. Vuelve a intentarlo"<<endl<<endl;
    if(val == true){
        cout<<"Nombre de usuario y contrasenia correctos."<<endl<<endl;
    }
    return val;
}

//Asigna nombre de usuario y contraseña al mapa de usuario
bool Login::setUsuarios(string _nom_user, string _cont)
{
    map<string,string>::iterator iter;
    bool existente=false;                   //Valida si el nombre de usuario ya existe
    for (iter = usuarios.begin();iter!=usuarios.end();iter++) {
        if(iter->first == _nom_user){
            existente = true;
        }

    }
    if (existente == true){                 //El nombre de usuario existe
        cout<<"El nombre de usuario ya existe, vuelva a intentarlo."<<endl;
    }
    else {
        usuarios.insert(make_pair(_nom_user, _cont));
    }
    return existente;

}

//Guarda en un archivo el nombre de usuario y la contraseña de los usuarios
void Login::guardarUsers(string nombre, string contra)
{
    ofstream fileUser;
    fileUser.open(dir_users.c_str(), ios::app);
    if (fileUser.fail()){
        cout<<"No se pudo abrir el archivo con los usuarios"<<endl;
        exit(1);
    }


    fileUser << nombre <<":"<< contra <<endl;               //Guarda la informacion del usuario en un archivo
    fileUser.close();
}

//Carga la informacion de los usuarios a un mapa
void Login::cargarUsers()
{
    ifstream fileUser;
    fileUser.open(dir_users.c_str(), ios::in);

    if(fileUser.fail()){
        cout<<"No se pudo abrir el archivo con los usuarios"<<endl;
        exit(1);
    }
    string linea, nomuser, contuser;
    while(!fileUser.eof()){         //Mientras no sea el final del archivo
        getline(fileUser,linea);
        if (linea != ""){           //Comprueba que la linea no este vacia
            unsigned int pos = linea.find(":");
            nomuser = linea.substr(0,pos);
            contuser = linea.substr(pos+1);
            usuarios.insert(make_pair(nomuser, contuser));      //Agrega la informacion al mapa de usuarios
        }


    }
    fileUser.close();
}
