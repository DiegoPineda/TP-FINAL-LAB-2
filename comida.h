#ifndef COMIDA_H_INCLUDED
#define COMIDA_H_INCLUDED
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
int ingresarNvaComida(CatComida arreglo[], int validos);
int ingresarNvaCategria(CatComida arreglo[], int validos, int dimension);
int seleccionarCategoria(CatComida arreglo[], int validos);
int validarCat(CatComida arreglo[], int validos, int dato);
int validarNombreCat(CatComida arreglo[], int validos, char nombre[]);
int validarNombrecomida(nodoComida *lista, char nombre[]);
int seleccionarComida(nodoComida *lista);
stDatosComida CargarUnaComida(CatComida arreglo[], int posCategoria);
nodoComida *borrarNodo(nodoComida *lista, int id);
nodoComida *encontrarComida(nodoComida *lista, int id);
nodoComida *ModificarPrecioLista(nodoComida *lista, float valor);
nodoComida *modificarNodo(nodoComida *nodoAux);
void cambiarPrecioComida(CatComida arreglo[], int validos);
int menuComidas(CatComida arreglo[], int validos);
stDatosComida cargarStruct();

#endif // COMIDAS_H_INCLUDED


