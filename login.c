//typedef struct
//{
//    char nombreYApellido[30];
//    char dni[8];
//    char calleYAltura[30];
//    char telefono[15];
//    char pass[20];
//    bool admin;
//    bool baja;
//} cliente;
//
//
//void cargarArchivoUsuario()
//{
//    cliente a;
//    int flagValidacion = -1;
//
//    printf("\n\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,187);
//    printf("\n\t\t\t\t%cREGISTRARSE%c",186,186);
//    printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,188);
//    printf("\n\n\t DNI : ");
//    fflush(stdin);
//    gets(a.dni);
//
//    flagValidacion = verificarDni(a.dni);
//    if(flagValidacion == 0)
//    {
//        printf("\n\t Nombre y apellido : ");
//        fflush(stdin);
//        gets(a.nombreYApellido);
//        printf("\n\t Calle y altura : ");
//        fflush(stdin);
//        gets(a.nombreYApellido);
//        printf("\n\t Contrasenia : ");
//        fflush(stdin);
//        ocultarPass(a.pass);
//        a.admin=false;
//        a.baja=false;
//        printf("\n\t Telefono : ");
//        fflush(stdin);
//        gets(a.telefono);
//
//
//        guardarUsuario(a);
//
//    }
//    else
//    {
//        printf("\n\n\t DNI YA EXISTENTE. ");
//    }
//}
//
//void guardarUsuario(cliente a)
//{
//    FILE * pArchUsuarios = fopen("usuarios.bin","ab");
//    if(pArchUsuarios!=NULL)
//    {
//        fwrite(&a,sizeof(cliente),1,pArchUsuarios);
//        fclose(pArchUsuarios);
//    }
//}
//
//int verificarDni(char dni[])
//{
//    cliente a;
//    int flag = 0;
//
//    FILE * pArchUsuario = fopen("usuarios.bin","rb");
//    if(pArchUsuario!=NULL)
//    {
//        while(fread(&a,sizeof(cliente),1,pArchUsuario)>0)
//        {
//            if(strcmp(dni,a.dni)==0)
//            {
//                flag=1;
//            }
//        }
//        fclose(pArchUsuario);
//    }
//    return flag;
//}
//
//void muestraUnUsuario(stUsuario a)
//{
//    printf("\n\t Nombre y apellido................: %s",a.nombreYApellido);
//    printf("\n\t Dni................: %s",a.dni);
//    printf("\n\t Telefono................: %s",a.telefono);
//    printf("\n\t Direccion................: %s",a.calleYAltura);
//    if(a.admin == true)
//    {
//        printf("\n\tAdministrador................ Si");
//    }
//    else
//        printf("\n\tAdministrador................ No");
//    printf("\n\t____________________________________");
//}
//
//void muestraUsuarios()
//{
//    cliente a;
//    FILE * pArchUsuarios = fopen("usuarios.bin","rb");
//    if(pArchUsuarios!=NULL)
//    {
//        while(fread(&a,sizeof(cliente),1,pArchUsuarios)>0)
//        {
//            if(a.baja==false)
//            {
//                muestraUnUsuario(a);
//            }
//        }
//        fclose(pArchUsuarios);
//    }
//}
//
//void ocultarPass(char pass[20])
//{
//
//
//    int i=0;
//    char aux;
//    while(aux=getch())
//    {
//        if (aux == TECLA_ENTER)
//        {
//            pass[i] = '\0';
//            break;
//        }
//
//        if(aux!=TECLA_ENTER)
//        {
//            if(aux==TECLA_BACKSPACE)
//            {
//                if(i>0)
//                {
//                    pass[i]--;
//                    i--;
//                    printf("\b \b");
//                }
//            }
//            else
//            {
//                printf("*", aux);
//                pass[i]=aux;
//                i++;
//            }
//        }
//    }
//
//}
//
//int verificarUsuario(char dni[],char pass[])
//{
//    cliente a;
//    int flag = -1;
//    FILE *pArchUsuarios = fopen("usuarios.bin","rb");
//    if(pArchUsuarios != NULL)
//    {
//        while(fread(&a,sizeof(cliente),1,pArchUsuarios)>0)
//        {
//            if(strcmp(a.dni,dni) == 0)
//            {
//                if(strcmp(a.pass,pass)==0)
//                {
//                    if(a.baja == false)
//                    {
//                        flag = 1;
//                    }
//                }
//                if(flag==1)
//                {
//                    return 1;
//                }
//                else
//                    return -1;
//            }
//        }
//    }
//}
