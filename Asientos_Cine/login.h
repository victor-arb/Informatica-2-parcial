#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

using namespace std;


class Login
{
public:
    Login();
    ~Login();
    void setArchivos(string _dir_sudo, string _dir_users);
    bool validateAdmin(string _cont_admin);
    bool setUsuarios(string _nom_user, string _cont);
    bool validateUser(string _nom_user, string _cont);
    void guardarUsers(string nombre, string contra);             //Guarda en un archivo el nombre de usuario y la contraseña de los usuarios
    void cargarUsers();              //Carga la informacion de los usuarios a un mapa


private:
    string dir_sudo;
    string dir_users;
    map<string, string> usuarios;
};

#endif // LOGIN_H
