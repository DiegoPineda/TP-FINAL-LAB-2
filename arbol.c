#include "loginYMenu.h"
#include "arbol.h"
#include "string.h"


nodoArbol *inicArbol()
{
    return NULL;
}

nodoArbol *crearNodoArbol(cliente nvoCliente)
{
    nodoArbol *nvoArbol= (nodoArbol*) malloc(sizeof(nodoArbol));
    nvoArbol->dato = nvoCliente;
    nvoArbol->der= NULL;
    nvoArbol->izq= NULL;
    return nvoArbol;
}

nodoArbol *insertar(nodoArbol *arbol, nodoArbol *nvoNodo)
{
    if(arbol == NULL)
    {
        arbol = nvoNodo;
    }
    else
    {
        if(strcmpi(nvoNodo->dato.dni, arbol->dato.dni) < 0)
        {
            arbol->der= insertar(arbol->der, nvoNodo);
        }
        else
        {
            arbol->izq= insertar(arbol->izq, nvoNodo);
        }
    }
    return arbol;
}

nodoArbol *leerArvchivoClientes(nodoArbol *arbol)
{
    cliente nvoCliente;
    nodoArbol *nvoNodo;
    FILE *buffer = fopen("usuarios.dat","rb");
    if(buffer != NULL)
    {
        while(fread(&nvoCliente, sizeof(cliente), 1, buffer)> 0)
        {
            nvoNodo = crearNodoArbol(nvoCliente);
            arbol = insertar (arbol, nvoNodo);
        }
        fclose(buffer);
    }
    return arbol;
}

void inorder(nodoArbol *arbol)
{
    if(arbol != NULL)
    {
        inorder(arbol->der);
        if(arbol->dato.baja == 0)
        {
            muestraUnUsuario(arbol->dato);
        }
        inorder(arbol->izq);
    }
}

nodoArbol *busqueda(nodoArbol *arbol, char dni[])
{
    nodoArbol *auxiliar =NULL;
    if(arbol != NULL)
    {
        if(strcmpi(arbol->dato.dni, dni) == 0)
        {
            auxiliar=arbol;
        }
        else
        {
            if(strcmpi(dni, arbol->dato.dni) >0)
            {
                auxiliar=busqueda(arbol->der, dni);
            }
            else
            {
                auxiliar=busqueda(arbol->izq, dni);
            }
        }
    }
    return auxiliar;
}

nodoArbol *bajaLogicaCliente(nodoArbol *arbol)
{
    printf("\n\tDAR DE BAJA UN CLIENTE\n");
    printf("Ingrese el DNI del cliente: ");
    fflush(stdin);
    char dni[10];
    gets(dni);
    nodoArbol *nodoBuscado = busqueda(arbol, dni);
    if(nodoBuscado != NULL)
    {
        nodoBuscado->dato.baja=1;
    }
    return arbol;
}

nodoArbol *modificarCliente(nodoArbol *arbol)
{
    char dni[10];
    int modificacion;
   // system("cls");
    printf("\n\tMODIFICAR UN CLIENTE\n");
    if(usuarioLogeado.admin == 1)
    {
        printf("Ingrese el DNI del cliente: ");
        fflush(stdin);
        gets(dni);
    }
    else
    {
        strcpy(dni, usuarioLogeado.dni);
    }

    nodoArbol *nodoBuscado = busqueda(arbol, dni);
    if(nodoBuscado != NULL)
    {
        printf("\nEste es el cliente: ");
        printf("\n---------------------------------");
        mostrarUnCliente(nodoBuscado);
        printf("\n---------------------------------\n");
        printf("\nQue desea modificar?\n1.Nombre y apellido\n2.Calle y altura\n3.Contrasenia\n4.Telefono\nIngrese una opcion: ");
        fflush(stdin);
        scanf("%d", &modificacion);
        if(modificacion == 1)
        {
            printf("\nIngrese nuevo nombre y apellido: ");
            fflush(stdin);
            scanf("%s", &arbol->dato.nombreYApellido);
        }
        if(modificacion == 2)
        {
            printf("\nIngrese nuevo domicilio: ");
            fflush(stdin);
            scanf("%s", &arbol->dato.calleYAltura);
        }
        if(modificacion == 3)
        {
            printf("\nIngrese nueva contrasenia: ");
            fflush(stdin);
            scanf("%s", &arbol->dato.pass);
        }
        if(modificacion == 4)
        {
            printf("\nIngrese nuevo telefono: ");
            fflush(stdin);
            scanf("%s", &arbol->dato.telefono);
        }
        sobreEscribirArchivo(arbol);

    }
    return arbol;
}

void sobreEscribirArchivo(nodoArbol *arbol)
{
    cliente a;
    FILE * archi = fopen("usuarios.dat", "wb");
    cargarClienteRec(arbol, archi);
    fclose(archi);
}
void mostrarUnCliente(nodoArbol * arbol)
{
    printf("\nNombre y apellido: %s", arbol->dato.nombreYApellido);
    printf("\nDNI: %s", arbol->dato.dni);
    printf("\nTelefono: %s", arbol->dato.telefono);
    printf("\nDireccion: %s", arbol->dato.calleYAltura);
    printf("\nContrasenia: %s", arbol->dato.pass);
}

void cargarClienteRec(nodoArbol* arbol, FILE* archi)
{
    if(arbol!=NULL)
    {
        fwrite(&arbol->dato, sizeof(cliente), 1, archi);
        cargarClienteRec(arbol->der, archi);
        cargarClienteRec(arbol->izq, archi);
    }
}
