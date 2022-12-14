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
        if(strcmp(arbol->dato.dni, dni) == 0)
        {
            auxiliar=arbol;
        }
        else
        {
            if(strcmp(arbol->dato.dni, dni) >0)
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
    char control = 's';
    int modificacion = 0;
    int flag = 0;
    system("cls");
    printf("\n\tMODIFICAR UN CLIENTE\n");
    flag = verificarDni(usuarioLogeado.dni);
    if(flag == 1)
    {

        nodoArbol *nodoBuscado = busqueda(arbol, usuarioLogeado.dni);
        if(nodoBuscado == NULL)
        {
            printf("hola");
        }
        if(nodoBuscado != NULL)
        {
            printf("\nEste es el cliente: ");
            printf("\n---------------------------------");
            mostrarUnCliente(nodoBuscado->dato);
            printf("\n---------------------------------\n");
            do
            {
                do
                {
                    printf("\nQue desea modificar?\n1.Nombre y apellido\n2.Calle y altura\n3.Contrasenia\n4.Telefono\nIngrese una opcion: ");
                    fflush(stdin);
                    scanf("%d", &modificacion);
                    system("cls");
                }
                while(modificacion !=1 && modificacion!=2 && modificacion!=3 &&modificacion!= 4);

                if(modificacion == 1)
                {
                    printf("\nIngrese nuevo nombre y apellido: ");
                    fflush(stdin);
                    scanf("%s", &nodoBuscado->dato.nombreYApellido);
                }
                if(modificacion == 2)
                {
                    printf("\nIngrese nuevo domicilio: ");
                    fflush(stdin);
                    scanf("%s", &nodoBuscado->dato.calleYAltura);
                }
                if(modificacion == 3)
                {
                    printf("\nIngrese nueva contrasenia: ");
                    fflush(stdin);
                    scanf("%s", &nodoBuscado->dato.pass);
                }
                if(modificacion == 4)
                {
                    printf("\nIngrese nuevo telefono: ");
                    fflush(stdin);
                    scanf("%s", &nodoBuscado->dato.telefono);
                }
                do
                {
                    printf("Desea cambiar algo mas? s/n: ");
                    fflush(stdin);
                    scanf("%c", &control);
                }while(control!='s' && control!='n');

                system("cls");
            }
            while(control == 's');
            sobreEscribirArchivo(arbol);

        }
    }
    else
    {
        printf("\nUsuario no encontrado...");
        system("pause");
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
void mostrarUnCliente(cliente a)
{
    printf("\nNombre y apellido: %s", a.nombreYApellido);
    printf("\nDNI: %s", a.dni);
    printf("\nTelefono: %s", a.telefono);
    printf("\nDireccion: %s", a.calleYAltura);
    printf("\nContrasenia: %s", a.pass);
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
