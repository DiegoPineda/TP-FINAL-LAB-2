#ifndef COMIDAS_H_INCLUDED
#define COMIDAS_H_INCLUDED
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
} stDatosComida;

typedef struct
{
    int id;
    char nombre[20];
    float precio;
} comida;

typedef struct
{
    comida dato;
    struct nodoComida* anterior;
    struct nodoComida* siguiente;
} nodoComida;

typedef struct
{
    int id_categoria;
    char nombre_cat[20];
} categoria;

typedef struct
{
    categoria dato;
    nodoComida *lista;
} CatComida;

///Cargar arreglo de listas
nodoComida *inicLista();
nodoComida *crearNodo(comida dato);
nodoComida *agregarAlPrincipio(nodoComida *lista, nodoComida *nvoNodo);
nodoComida *agregarOrdenado(nodoComida *lista, nodoComida *nvoNodo);
int leerArvchivoComidas(CatComida arreglo[], int dimension);
int buscarPosCatComida(CatComida arreglo[], int id, int validos);
int agregarCatComida(CatComida arreglo[], categoria nvaCat, int validos);
comida agregarComida(stDatosComida dtosComida);
categoria crearCatComida(stDatosComida dtosComida);
int altaComidas(CatComida arreglo[], stDatosComida dtosComida, int validos);
///cargar nueva comida
int ingresarNvaComida(CatComida arreglo[], int validos, int dimension);
int validarCat(CatComida arreglo[], int validos, stDatosComida auxiliar);
int validarcomida(nodoComida *lista, int id);
int seleccionarCategoria(CatComida arreglo[], int validos);
int seleccionarComida(nodoComida *lista);
///borrar comida
void BorrarUnaComida(CatComida arreglo[], int validos);
nodoComida *borrarNodo(nodoComida *lista, int id);
///modificar precio
void cambiarPrecioComida(CatComida arreglo[], int validos);
nodoComida *modificarNodo(nodoComida *nodoAux);
nodoComida *encontrarComida(nodoComida *lista, int id);
stDatosComida cargarStruct();

#endif // COMIDAS_H_INCLUDED
