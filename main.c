#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comida.h"
#include "pedido.h"
#include "postres.h"
#include "bebidas.h"

int main()
{
      CatComida Categorias[10];
      CeldaPostre Categoriaspos[10];
      CeldaBebida CategoriasBeb[10];
      int validos = leerArvchivoComidas(Categorias, 10);
      //int validosBebida = leerArvchivoBebida(CategoriasBeb, 10);
      //int validosPostres = leerArvchivoPostres(Categoriaspos, 10)
      //validos = menuComidas(Categorias, validos);
      //validosBebida = menuBebida(CategoriasBeb, validosBebida);
      //validosPostre = menuPostre(Categoriaspos, validosPos);


    pedidoCelda *lista=inicLista();

    lista=hacerPedido(Categorias,validos,lista);

//    mostrarListaPedidos(lista);

    return 0;
}
