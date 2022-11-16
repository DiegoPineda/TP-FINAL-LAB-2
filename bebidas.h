#ifndef BEBIDAS_H_INCLUDED
#define BEBIDAS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nombre[20];
    float precio;
    char cantidad[7];
    int id_categoria;
    char nombre_cat[20];
} stDatosBebidas;

typedef struct
{
    int id;
    char nombre[20];
    float precio;
    char cantidad[5];
} bebida;

typedef struct
{
    bebida dato;
    struct nodoBebida* anterior;
    struct nodoBebida* siguiente;
} nodoBebida;

typedef struct
{
    int id_categoria;
    char nombre_cat[20];
} categoriaBebida;

typedef struct
{
    categoriaBebida dato;
    nodoBebida *lista;
} CeldaBebida;


////////////////////////////////////////////////////////////////////////////////////////////////
stDatosBebidas cargarStructBebida();
void cargarArchivoBebida(stDatosBebidas auxiliar);
nodoBebida *inicListaBebida();
nodoBebida *crearNodoBebida(bebida dato);
nodoBebida *agregarAlPrincipioBebida(nodoBebida *lista, nodoBebida *nvoNodo);
nodoBebida *agregarOrdenadoBebida(nodoBebida *lista, nodoBebida *nvoNodo);
int leerArvchivoBebida(CeldaBebida arreglo[], int dimension);
int buscarPosCatBebida(CeldaBebida arreglo[], int id, int validos);
int agregarCatBebida(CeldaBebida arreglo[], categoriaBebida nvaCat, int validos);
bebida agregarBebida(stDatosBebidas dtosBebida);
categoriaBebida crearCatBebida(stDatosBebidas dtosBebida);
int altaBebidas(CeldaBebida arreglo[], stDatosBebidas dtosBebida, int validos);
int ingresarNvaBebida(CeldaBebida arreglo[], int validos);
int ingresarNvaCategriaBebida(CeldaBebida arreglo[], int validos, int dimension);
int seleccionarCategoriaBebida(CeldaBebida arreglo[], int validos);
int validarCatBebida(CeldaBebida arreglo[], int validos, int dato);
int validarNombreCatBebida(CeldaBebida arreglo[], int validos, char nombre[]);
int validarNombreBebida(nodoBebida *lista, char nombre[]);
int seleccionarBebida(nodoBebida *lista);
stDatosBebidas CargarUnaBebida(CeldaBebida arreglo[], int posCategoria);
nodoBebida *borrarNodoBebida(nodoBebida *lista, int id);
nodoBebida *encontrarBebida(nodoBebida *lista, int id);
nodoBebida *ModificarPrecioListaBebida(nodoBebida *lista, float valor);
int retornarIDbebida(nodoBebida *lista, int id);
nodoBebida *modificarNodoBebida(nodoBebida *nodoAux);
void cambiarPrecioBebida(CeldaBebida arreglo[], int validos);
int menuBebida(CeldaBebida arreglo[], int validos);
void persistirArchivoBebida(CeldaBebida arreglo[], int validos);
stDatosBebidas cargarBebida(categoriaBebida dato, nodoBebida *lista);



#endif // BEBIDAS_H_INCLUDED
