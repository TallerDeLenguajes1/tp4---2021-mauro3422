#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Starea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion;//10-100
}tarea;

//Cargo todas las tareas.
void cargarTarea(tarea **arreglo,int cant);
//Muestro una tarea a la vez.
void mostrarTarea(tarea **arreglo);
//Control de tareas realizadas
void controlTarea(tarea **tareasPen,tarea **tareaReal,int cant);
//Busqueda por palabra clave
tarea * BusquedaPorPalabra(tarea **tarea,int cant);
//Busca tarea por id ingresado.
tarea *BusquedaPorId(tarea **tarea,int cant);
//Libero memoria.
void freeMem(tarea **tarea,int cant);


int main(){

    int cantTareas,id;
    printf("Cantidad de tareas:");
    scanf("%d",&cantTareas);
    fflush(stdin);
    printf("\n");
    tarea **tareasPendientes=(tarea **)malloc(sizeof(tarea)*cantTareas);
    tarea **tareasRealizadas=(tarea **)malloc(sizeof(tarea)*cantTareas);

        cargarTarea(tareasPendientes,cantTareas);
        controlTarea(tareasPendientes,tareasRealizadas,cantTareas);
        
        printf("--------------Tareas Realizada-------------\n");
        for (int i = 0; i < cantTareas; i++)
        {   

            if ((*(tareasRealizadas+i))!=NULL)
            {
                
                mostrarTarea((tareasRealizadas+i));

            }
            
        }
        printf("--------------Tareas Pendientes-------------\n");
        for (int i = 0; i < cantTareas; i++)
        {   
            if ((*(tareasPendientes+i))!=NULL)
            {
                mostrarTarea((tareasPendientes+i));
            }
        }
        
        printf("------------Busqueda de tarea por palabra clave----------\n");
        tarea *tareaEncPal=BusquedaPorPalabra(tareasRealizadas,cantTareas);
        mostrarTarea(&tareaEncPal);

        printf("---------Busqueda de tarea por ID----------\n");
        tarea *tareaEncID=BusquedaPorId(tareasRealizadas,cantTareas);
        mostrarTarea(&tareaEncID);

        freeMem(tareasPendientes,cantTareas);
        freeMem(tareasRealizadas,cantTareas);
        free(tareasPendientes);
        free(tareasRealizadas);
        
    getchar();
    return 0;
}
void cargarTarea(tarea **arreglo,int cant){
    for (int i = 0; i < cant; i++)
    {
        printf("------Cargando tarea [%d]-----\n",i+1);
        tarea *item=(tarea *)malloc(sizeof(tarea));
        (item)->TareaID=i;
        (item)->Descripcion=(char *)malloc(sizeof(char)*180);
        printf("Ingresar Descripcion:");
        gets((item)->Descripcion);
        fflush(stdin);
        (item)->Duracion=rand()%(100-10+1)+10;
        *(arreglo+i)=item;
    }
    
}
void mostrarTarea(tarea **arreglo){

        printf("----Tarea ID [%d]----\n",(*arreglo)->TareaID);
        printf("Descripcion de la tarea:%s\n",(*arreglo)->Descripcion);
        printf("Duracion de la tarea:[%d]\n",(*arreglo)->Duracion);
        
    
}
void controlTarea(tarea **tareasPen,tarea **tareaReal,int cant){
    char ask='c';
    for (int i = 0; i < cant; i++)
    {   
        
       do
       {
        ask='c';
        printf("La siguiente tarea:\n");
        mostrarTarea((tareasPen+i));
        printf("Se realizo? Ingrese caracter S/N:");
        scanf("%c",&ask);
        fflush(stdin);
       } while (ask !='s'&& ask!='S' && ask !='n'&& ask!='N');
       
        if (ask=='s' || ask=='S')
        {
            
            (*(tareaReal+i))=*(tareasPen+i);
            (*(tareasPen+i))=NULL;
        }else{
            (*(tareaReal+i))=NULL;
        }
    }
    
}
tarea * BusquedaPorPalabra(tarea **tarea,int cant){
    char arrCad[20];
    printf("Ingresa la palabra a buscar:");
    gets(arrCad);
    fflush(stdin);
    for (int i = 0; i < cant; i++)
    {
        if (strstr(((*(tarea+i))->Descripcion),arrCad)!=NULL)
        {
            return (*(tarea+i));
        }   
    }
    printf("No se encontro la palabra en ninguna de las tareas.\n");
}

tarea *BusquedaPorId(tarea **tarea,int cant){
    int id;
    printf("Ingrese el ID de la tarea a buscar:");
    scanf("%d",&id);
    fflush(stdin);
    for(int i=0;i <cant; i++){
        if ((*(tarea+i))->TareaID=id && (*(tarea+i))!=NULL)
        {
            return (*(tarea+i));
        }
        
    }
}

void freeMem(tarea **tarea,int cant){
    for (int i = 0; i < cant; i++)
    {
        if ((*(tarea+i))!=NULL)
        {
        free((*(tarea+i))->Descripcion);
        free((*(tarea+i)));
        }   
    }
}