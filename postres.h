#ifndef POSTRES_H_INCLUDED
#define POSTRES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nombre[20];
    float precio;
    int id_categoria;
    char nombre_cat[20];
} stDatosPostres;

typedef struct
{
    int id;
    char nombre[20];
    float precio;
} postre;

typedef struct
{
    postre dato;
    struct nodoPostre* anterior;
    struct nodoPostre* siguiente;
} nodoPostre;

typedef struct
{
    int id_categoria;
    char nombre_cat[20];
} categoriaPostre;

typedef struct
{
    categoriaPostre dato;
    nodoPostre *lista;
} CeldaPostre;


////////////////////////////////////////////////////////////////////////////////////////////////
stDatosPostres cargarStructPostre();
void cargarArchivoPostres(stDatosPostres auxiliar);
nodoPostre *inicListaPostre();
nodoPostre *crearNodoPostre(postre dato);
nodoPostre *agregarAlPrincipioPostre(nodoPostre *lista, nodoPostre *nvoNodo);
nodoPostre *agregarOrdenadoPostre(nodoPostre *lista, nodoPostre *nvoNodo);
int leerArvchivoPostres(CeldaPostre arreglo[], int dimension);
int buscarPosCatPostre(CeldaPostre arreglo[], int id, int validos);
int agregarCatPostre(CeldaPostre arreglo[], categoriaPostre nvaCat, int validos);
postre agregarPostre(stDatosPostres dtosPostre);
categoriaPostre crearCatPostre(stDatosPostres dtosPostres);
int altaPostres(CeldaPostre arreglo[], stDatosPostres dtosPostres, int validos);
int ingresarNvoPostre(CeldaPostre arreglo[], int validos);
int ingresarNvaCategriaPostre(CeldaPostre arreglo[], int validos, int dimension);
int seleccionarCategoriaPostre(CeldaPostre arreglo[], int validos);
int validarCatPostre(CeldaPostre arreglo[], int validos, int dato);
int validarNombreCatPostre(CeldaPostre arreglo[], int validos, char nombre[]);
int validarNombrePostre(nodoPostre *lista, char nombre[]);
int seleccionarPostre(nodoPostre *lista);
stDatosPostres CargarUnPostre(CeldaPostre arreglo[], int posCategoria);
nodoPostre *borrarNodoPostre(nodoPostre *lista, int id);
nodoPostre *encontrarPostre(nodoPostre *lista, int id);
nodoPostre *ModificarPrecioListaPostre(nodoPostre *lista, float valor);
int retornarIDpostre(nodoPostre *lista, int id);
nodoPostre *modificarNodoPostre(nodoPostre *nodoAux);
void cambiarPrecioPostre(CeldaPostre arreglo[], int validos);
int menuPostre(CeldaPostre arreglo[], int validos);
stDatosPostres cargarStrucPostres();
void persistirArchivoPostres(CeldaPostre arreglo[], int validos);
stDatosPostres cargarPostre(categoriaPostre dato, nodoPostre *lista);



#endif // POSTRES_H_INCLUDED
