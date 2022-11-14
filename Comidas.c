#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "comidas.h"

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
int ingresarNvaComida(CatComida arreglo[], int validos, int dimension);
int validarCat(CatComida arreglo[], int validos, stDatosComida auxiliar);
int validarcomida(nodoComida *lista, int id);
int seleccionarCategoria(CatComida arreglo[], int validos);
int seleccionarComida(nodoComida *lista);
nodoComida *borrarNodo(nodoComida *lista, int id);
nodoComida *encontrarComida(nodoComida *lista, int id);

nodoComida *modificarNodo(nodoComida *nodoAux);

void cambiarPrecioComida(CatComida arreglo[], int validos);
stDatosComida cargarStruct();
int main()
{
    //cargarArchivo1();
    //mostrarArchi();
     CatComida Categorias[10];
    int validos = leerArvchivoComidas(Categorias, 10);
    mostrarArregloComidas(Categorias, validos);
    system("PAUSE");
    system("CLS");
    validos = ingresarNvaComida(Categorias,validos, 10);
    mostrarArregloComidas(Categorias, validos);
    system("PAUSE");
    system("CLS");
    cambiarPrecioComida(Categorias, validos);
    mostrarArregloComidas(Categorias, validos);
    system("PAUSE");
    system("CLS");
    BorrarUnaComida(Categorias, validos);
    mostrarArregloComidas(Categorias, validos);




    return 0;


}

void mostrarArchi()
{
    stDatosComida aux;
    FILE*archi=fopen("ArchivoComidas.bin","rb");
    if(archi!=NULL)
    {

        while(fread(&aux,sizeof(stDatosComida),1,archi)>0)
        {
            mostrarArchivo(aux);

        }
        fclose(archi);
    }
}

void mostrarArchivo(stDatosComida aux)
{
    printf("ID %d\n",aux.id);
    printf("NOMBRE %s\n",aux.nombre);
    printf("PRECIO %.2f\n",aux.precio);
    printf("id categoria %i\n",aux.id_categoria);
    printf("Nombre categoria %s\n",aux.nombre_cat);
    printf("--------------------------------------------------------------------------------------------\n");
    printf("\n");
}

void cargarArchivo1()
{
    stDatosComida auxiliar;
    FILE *buffer = fopen("ArchivoComidas.bin", "ab");
    if(buffer != NULL)
    {
        char continuar = 's';
        while(continuar == 's')
        {
        auxiliar = cargarStruct();
        fwrite(&auxiliar, sizeof(stDatosComida), 1, buffer);
        printf("Desea continuar? presione s\n");
        fflush(stdin);
        scanf("%c", &continuar);
        system("CLS");
        }

        fclose(buffer);
    }
}

void cargarArchivo(stDatosComida auxiliar)
{

    FILE *buffer = fopen("ArchivoComidas.bin", "ab");
    if(buffer != NULL)
    {
        fwrite(&auxiliar, sizeof(stDatosComida), 1, buffer);

        fclose(buffer);
    }
}

stDatosComida cargarStruct()
{
    printf("\t\t CARGA DE NUEVA COMIDA\n");
    stDatosComida auxiliar;
    printf("Ingrese el nombre de la categoria: \n");
    fflush(stdin);
    gets(auxiliar.nombre_cat);
    printf("Ingrese la id de la categoria: \n");
    fflush(stdin);
    scanf("%i", &auxiliar.id_categoria);
    printf("Ingrese el nombre de la comida: \n");
    fflush(stdin);
    gets(auxiliar.nombre);
    printf("Ingrese la id de la comida: \n");
    fflush(stdin);
    scanf("%i", &auxiliar.id);
    printf("Ingrese el precio de la comida: \n");
    fflush(stdin);
    scanf("%f", &auxiliar.precio);

    return auxiliar;

}

nodoComida *inicLista()
{
    return NULL;
}

nodoComida *crearNodo(comida dato)
{
    nodoComida *aux=(nodoComida*) malloc(sizeof(nodoComida));
    aux->dato = dato;
    aux->anterior = NULL;
    aux->siguiente = NULL;
    return aux;
}

nodoComida *agregarAlPrincipio(nodoComida *lista, nodoComida *nvoNodo)
{
    if(lista == NULL)
    {
        lista = nvoNodo;
    }
    else
    {
        lista->anterior = nvoNodo;
        nvoNodo->siguiente = lista;
        lista = nvoNodo;
    }
    return lista;
}

nodoComida *agregarOrdenado(nodoComida *lista, nodoComida *nvoNodo)
{
    if(lista == NULL)
    {
        lista = nvoNodo;
    }
    else
    {
        if(nvoNodo->dato.id < lista->dato.id)
        {
            lista = agregarAlPrincipio(lista, nvoNodo);
        }
        else
        {
            nodoComida *anterior = lista;
            nodoComida *seguidora = lista->siguiente;
            while(seguidora != NULL && nvoNodo->dato.id > seguidora->dato.id)
            {
                anterior = seguidora;
                seguidora = seguidora->siguiente;
            }
            anterior->siguiente = nvoNodo;
            nvoNodo->anterior = anterior;
            nvoNodo->siguiente = seguidora;
            if(seguidora != NULL)
            {
                seguidora->anterior = nvoNodo;
            }
        }
    }
    return lista;
}

int leerArvchivoComidas(CatComida arreglo[], int dimension)
{
    int validos =0;
    FILE *buffer = fopen("ArchivoComidas.bin", "rb");
    stDatosComida datosComida;
    if(buffer != NULL)
    {
        while(fread(&datosComida, sizeof(stDatosComida), 1, buffer) > 0 && validos < dimension)
        {
            validos = altaComidas(arreglo, datosComida, validos);
        }
        fclose(buffer);
    }

    return validos;
}

int buscarPosCatComida(CatComida arreglo[], int id, int validos)
{
    int rta =-1;
    int i=0;
    while(i<validos && rta == -1)
    {
        if(arreglo[i].dato.id_categoria == id)
        {
            rta=i;
        }
        i++;
    }
    return rta;
}

int agregarCatComida(CatComida arreglo[], categoria nvaCat, int validos)
{
    arreglo[validos].dato.id_categoria = nvaCat.id_categoria;
    strcpy(arreglo[validos].dato.nombre_cat, nvaCat.nombre_cat);
    arreglo[validos].lista=inicLista();
    validos++;

    return validos;
}

comida agregarComida(stDatosComida dtosComida)
{
    comida nvaComida;
    nvaComida.id = dtosComida.id;
    strcpy(nvaComida.nombre, dtosComida.nombre);
    nvaComida.precio = dtosComida.precio;

    return nvaComida;
}

categoria crearCatComida(stDatosComida dtosComida)
{

    categoria nvaCategoria;
    nvaCategoria.id_categoria = dtosComida.id_categoria;
    strcpy(nvaCategoria.nombre_cat, dtosComida.nombre_cat);
    return nvaCategoria;
}

int altaComidas(CatComida arreglo[], stDatosComida dtosComida, int validos)
{
    comida nvaComida = agregarComida(dtosComida);
    nodoComida *nvoNodo = crearNodo(nvaComida);
    int pos = buscarPosCatComida(arreglo, dtosComida.id_categoria, validos);
    if(pos == -1)
    {
        categoria nvaCategoria = crearCatComida(dtosComida);
        validos = agregarCatComida(arreglo, nvaCategoria, validos);
        pos = validos-1;
    }
    arreglo[pos].lista = agregarOrdenado(arreglo[pos].lista, nvoNodo);

    return validos;
}

void mostrarCategorias(CatComida arreglo[],  int validos)
{
    printf("\tCATEGORIAS\n");
    for(int i=0; i<validos; i++)
    {
        printf("%i - %s\n", arreglo[i].dato.id_categoria, arreglo[i].dato.nombre_cat);
    }
    printf("\n\n");
}

void mostrarArregloComidas(CatComida arreglo[], int validos)
{
    int i=0;
    while(i < validos)
    {
        printf("\tCATEGORIA: %s           ID:  %i\n\n", arreglo[i].dato.nombre_cat, arreglo[i].dato.id_categoria);
        mostrarListaComida(arreglo[i].lista);
        printf("--------------------------------------------------------------\n");
        printf("--------------------------------------------------------------\n");
        i++;
    }
}

void mostrarListaComida(nodoComida*lista)
{
    while(lista != NULL)
    {
        mostrarComida(lista->dato);
        lista = lista->siguiente;
    }
}

void mostrarComida(comida aux)
{
    printf("NOMBRE: %s\n",aux.nombre);
    printf("ID %d\n",aux.id);
    printf("PRECIO %.2f\n",aux.precio);
    printf("\n");
    printf("\n");
}

int ingresarNvaComida(CatComida arreglo[], int validos, int dimension)
{
    stDatosComida auxiliar;
    char continuar = 's';
    while(continuar == 's')
    {
        if(validos < dimension)
        {
            printf("\t\t CARGA DE NUEVA COMIDA\n\n");
            mostrarCategorias(arreglo, validos);
            printf("Ingrese el nombre de la categoria: \n");
            fflush(stdin);
            gets(auxiliar.nombre_cat);
            printf("Ingrese la id de la categoria: \n");
            fflush(stdin);
            scanf("%i", &auxiliar.id_categoria);
            int pos = validarCat(arreglo, validos, auxiliar);
            while(pos == -1)
            {
                printf("Categoria invalida\n");
                printf("Ingrese la id correspondiente a %s : ", auxiliar.nombre_cat);
                fflush(stdin);
                scanf("%i", &auxiliar.id_categoria);
                pos = validarCat(arreglo, validos, auxiliar);
            }

            printf("Ingrese el nombre de la comida: \n");
            fflush(stdin);
            gets(auxiliar.nombre);
            printf("Ingrese la id de la comida: \n");
            scanf("%i", &auxiliar.id);
            int posCom = validarcomida(arreglo[pos].lista, auxiliar.id);
            while(posCom == 1)
            {
                printf("ID de comida no disponible, intente con un nuevo id: ");
                scanf("%i", &auxiliar.id);
                posCom= validarcomida(arreglo[pos].lista, auxiliar.id);
            }
            printf("Ingrese el precio de la comida: \n");
            fflush(stdin);
            scanf("%f", &auxiliar.precio);
        }

        else
        {
            printf("NO SE PUEDE CREAR OTRA CATEGORIA, SELECCIONE UNA EXISTENTE\n");
            int cat = seleccionarCategoria(arreglo, validos);
            auxiliar.id_categoria = cat;
            printf("Ingrese el nombre de la comida: \n");
            fflush(stdin);
            scanf("%s", &auxiliar.nombre);
            printf("Ingrese la id de la comida: \n");
            scanf("%i", &auxiliar.id);
            int pos = buscarPosCatComida(arreglo, auxiliar.id_categoria, validos);
            int posCom = validarcomida(arreglo[pos].lista, auxiliar.id);
            while(posCom == 1)
            {
                printf("ID de comida no disponible, intente con un nuevo id: ");
                scanf("%i", &auxiliar.id);
                posCom= validarcomida(arreglo[pos].lista, auxiliar.id);
            }
            printf("Ingrese el precio de la comida: \n");
            fflush(stdin);
            scanf("%f", &auxiliar.precio);
        }

        validos = altaComidas (arreglo, auxiliar, validos);
        cargarArchivo(auxiliar);

        printf("Desea continuar? presione s\n");
        fflush(stdin);
        scanf("%c", &continuar);
        system("CLS");
    }

    return validos;
}

int validarCat(CatComida arreglo[], int validos, stDatosComida auxiliar)
{
    int aux = -1;
    int pos = buscarPosCatComida(arreglo, auxiliar.id_categoria, validos);
    if(pos != -1 && strcmpi(arreglo[pos].dato.nombre_cat, auxiliar.nombre_cat) ==0)
    {
        aux = pos;
    }
    return aux;
}

int validarcomida(nodoComida *lista, int id)
{
    int auxiliar = -1;
    while(lista != NULL && auxiliar == -1)
    {
        if(lista->dato.id == id)
        {
            auxiliar= 1;
        }
        lista=lista->siguiente;
    }
    return auxiliar;
}

int seleccionarCategoria(CatComida arreglo[], int validos)
{
    int cat;
    printf("Ingrese id de la categoria: ");
    scanf("%i", &cat);

    return cat;
}

int seleccionarComida(nodoComida *lista)
{
    int auxiliar;
    printf("ID de la comida: ");
    scanf("%i", &auxiliar);

    return auxiliar;
}

void BorrarUnaComida(CatComida arreglo[], int validos)
{
    printf("\tBORRAR COMIDA\n\n");
    mostrarCategorias(arreglo, validos);
    int cat = seleccionarCategoria(arreglo, validos);
    int pos = buscarPosCatComida(arreglo, cat, validos);
    while (pos == -1)
    {
        printf("Categoria incorrecta\n");
        cat = seleccionarCategoria(arreglo, validos);
        pos = buscarPosCatComida(arreglo, cat, validos);
    }
    system("CLS");
    mostrarListaComida(arreglo[pos].lista);
    int auxiliar = seleccionarComida(arreglo[pos].lista);
    nodoComida *comidaBorrar = encontrarComida(arreglo[pos].lista, auxiliar);
    while(comidaBorrar == NULL)
    {
        printf("No hay comidas con esa id\n ");
        auxiliar = seleccionarComida(arreglo[pos].lista);
        comidaBorrar = encontrarComida(arreglo[pos].lista, auxiliar);
    }

    arreglo[pos].lista = borrarNodo(arreglo[pos].lista, auxiliar);

}

nodoComida *borrarNodo(nodoComida *lista, int id)
{
    if (lista != NULL)
    {
        if(lista->dato.id == id)
        {
            nodoComida *aBorrar = lista;
            lista = lista->siguiente;
            if(lista != NULL)
            {
                lista->anterior = NULL;
            }
            free(aBorrar);
        }
        else
        {
            nodoComida *seguidora = lista;
            while(seguidora != NULL && seguidora->dato.id != id)
            {
                seguidora=seguidora->siguiente;
            }
            if(seguidora!= NULL)
            {
                nodoComida *anterior = seguidora->anterior;
                anterior->siguiente = seguidora->siguiente;
                if(seguidora->siguiente != NULL)
                {
                    nodoComida *seg = seguidora->siguiente;
                    seg =  anterior;
                }
                free(seguidora);
            }
        }
    }
    return lista;
}

void cambiarPrecioComida(CatComida arreglo[], int validos)
{
    printf("\tCAMBIOS DE PRECIOS\n");
    mostrarCategorias(arreglo, validos);
    int cat = seleccionarCategoria(arreglo, validos);
    int pos = buscarPosCatComida(arreglo, cat, validos);
    while (pos == -1)
    {
        printf("Categoria incorrecta, Ingrese un id valido\n ");
         cat = seleccionarCategoria(arreglo, validos);
         pos = buscarPosCatComida(arreglo, cat, validos);

    }
    system("CLS");
    mostrarListaComida(arreglo[pos].lista);
    int auxiliar = seleccionarComida(arreglo[pos].lista);
    nodoComida *comidaBuscada = encontrarComida(arreglo[pos].lista, auxiliar);
    while(comidaBuscada == NULL)
    {
        printf("No hay comidas con esa id");
        auxiliar = seleccionarComida(arreglo[pos].lista);
        comidaBuscada = encontrarComida(arreglo[pos].lista, auxiliar);
    }

    comidaBuscada = modificarNodo(comidaBuscada);

}

nodoComida *modificarNodo(nodoComida *nodoAux)
{
    printf("Ingrese el nuevo precio para %s: ", nodoAux->dato.nombre);
    scanf("%f", &nodoAux->dato.precio);

    return nodoAux;
}

nodoComida *encontrarComida(nodoComida *lista, int id)
{
    nodoComida *ComidaBuscada = NULL;
    int flag=0;
    while(lista != NULL && flag == 0)
    {
        if(lista->dato.id == id)
        {
            ComidaBuscada=lista;
            flag=1;
        }
        lista=lista->siguiente;
    }
    return ComidaBuscada;
}


