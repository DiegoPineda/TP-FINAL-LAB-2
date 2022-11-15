#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"
#include "comidas.h"
#include "pedidos.h"







int main()
{
      CatComida Categorias[10];
    int validos = leerArvchivoComidas(Categorias, 10);
//    mostrarArregloComidas(Categorias, validos);
//    system("PAUSE");
//    system("CLS");
    pedidoCelda *lista=inicLista();

    lista=hacerPedido(Categorias,validos,lista);

//    mostrarListaPedidos(lista);


//    validos = ingresarNvaComida(Categorias,validos, 10);
//    mostrarArregloComidas(Categorias, validos);
//    system("PAUSE");
//    system("CLS");
//    cambiarPrecioComida(Categorias, validos);
//    mostrarArregloComidas(Categorias, validos);
//    system("PAUSE");
//    system("CLS");
//    BorrarUnaComida(Categorias, validos);
//    mostrarArregloComidas(Categorias, validos);
    return 0;
}
