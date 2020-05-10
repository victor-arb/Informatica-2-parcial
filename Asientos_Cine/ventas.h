#ifndef VENTAS_H
#define VENTAS_H
#include <string>
#include <iostream>
#include <map>
#include <vector>

using namespace std;


class Ventas
{
public:
    Ventas();
    ~Ventas();

    void showTablaPrecios();        //Muestra la tabla de precios
    //Metodos setters
    void setNombreUsuario(string _nombre_usuario);
    void setValorCompra(int _valor_compra);
    void setFormatoPel(string _formato_pel);
    void setFilaAsiento(string _fila_asiento);
    void setColumnAsiento(int _col_asiento);

    //Metodos getters
    string getNombreUsuario();
    int getValorCompra();
    string getFormatoPel();
    string getFilaAsiento();
    int getColumnAsiento();

private:
    string nombre_usuario;
    int valor_compra;           //Valor de la compra de acuerdo al tipo de silla
    string formato_pel;
    string fila_asiento;        //Fila del asiento que se compro
    int col_asiento;            //Columna del asiento que se compro
};

#endif // VENTAS_H
