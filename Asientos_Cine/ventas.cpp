#include "ventas.h"

Ventas::Ventas()
{

}
Ventas::~Ventas()       //Destructor
{
}

//Metodos setters
void Ventas::setNombreUsuario(string _nombre_usuario)
{
    nombre_usuario=_nombre_usuario;
}
void Ventas::setValorCompra(int _valor_compra)
{
    valor_compra=_valor_compra;
}
void Ventas::setFormatoPel(string _formato_pel)
{
    formato_pel=_formato_pel;
}
void Ventas::setFilaAsiento(string _fila_asiento)
{
    fila_asiento=_fila_asiento;
}
void Ventas::setColumnAsiento(int _col_asiento)
{
    col_asiento=_col_asiento;
}

//Metodos getters
string Ventas::getNombreUsuario()
{
    return  nombre_usuario;
}
int Ventas::getValorCompra()
{
    return valor_compra;
}
string Ventas::getFormatoPel()
{
    return formato_pel;
}
string Ventas::getFilaAsiento()
{
    return fila_asiento;
}
int Ventas::getColumnAsiento()
{
    return col_asiento;
}


//Muestra la tabla de precios
void Ventas::showTablaPrecios()
{
    string aux(47, '-');
    cout<<aux<<endl;
    cout<<" | TABLA DE PRECIOS POR FORMATO DE PELICULA |"<<endl;
    cout<<aux<<endl;
    cout<<" |   Tipo   |   Clasificacion   |   Costo   |"<<endl<<aux<<endl
        <<" |     1    |     General 2D    |   $7900   |"<<endl<<aux<<endl
        <<" |     2    |     General 3D    |   $10800  |"<<endl<<aux<<endl
        <<" |     3    |  VibroSound 2D    |   $9900   |"<<endl<<aux<<endl
        <<" |     4    |  VibroSound 3D    |   $11900  |"<<endl<<aux<<endl;

}
