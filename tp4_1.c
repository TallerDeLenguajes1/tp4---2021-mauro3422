#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Starea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion;//10-100
}tarea;

typedef struct SToDo ToDo;
struct SToDo{
    tarea tareas;
    ToDo *next;
};


//Funcion para crear listas del tipo ToDo vacias
ToDo * CrearListaVacia();

//Espero una variable/reserva de memoria para cargarla con los datos y devolver su direccion de memoria para que sea agregada al nodo.
void cargarTareas(tarea *item,int id);
//Mando el item de tarea, obtengo una tarea y lo inserto en un nodo para devolverlo.
ToDo * CrearNodo(tarea *item);
//Mando la lista de tarea para insertar el nodo en ella y empezar a enlazar.
void insertarNodo(ToDo **Lista, ToDo *Nodo);
//Quito un nodo.
ToDo * QuitarNodo(ToDo **Lista);
//Muestro una lista completa
void mostrarLista(ToDo *Lista);
//Muestro una tarea.
void mostrarTarea(tarea item);
//Control de realizacion
void ControlRealizacion(ToDo **ListaPen,ToDo **ListaReal);
//Devuelvo un Nodo, depediendo de una palabra clave.
ToDo * BusquedaPorPalabra(ToDo *Lista);
ToDo * BusquedaPorId(ToDo *Lista);
void freeLista(ToDo **Lista);

int main(){
    srand(time(NULL));
    int cantTar;

   
    //Inicializo start en NULL
    ToDo *ListaPendientes=CrearListaVacia();
    ToDo *ListaRealizadas=CrearListaVacia();

    //Pido la cantidad de tareas. P1
    printf("Ingrese la cantidad de tareas:");
    scanf("%d",&cantTar);
    fflush(stdin);

    tarea *Tareas;
    
    for (int i = 0; i < cantTar; i++)
    {   
        tarea *TareaItem=(tarea *)malloc(sizeof(tarea));
        //Cargo las Tareas en un arreglo.
        cargarTareas(TareaItem,i);
        //Mando la tarea ya cargada y la guardo en un nodo
        ToDo *Nnodo=CrearNodo(TareaItem);
        //La inserto en la lista de tareas Pendientes.
        insertarNodo(&ListaPendientes,Nnodo);
    }
    ControlRealizacion(&ListaPendientes,&ListaRealizadas);

    printf("-----------Tareas realizadas---------\n");
    mostrarLista(ListaRealizadas);
    printf("-----------Tareas pendientes---------\n");
    mostrarLista(ListaPendientes);

    printf("--------Busqueda por palabra clave------\n");
    ToDo *nodoExt=BusquedaPorPalabra(ListaRealizadas);
    tarea item=nodoExt->tareas;
    mostrarTarea(item);
    printf("-------Busqueda por ID--------\n");
    nodoExt=BusquedaPorId(ListaRealizadas);
    item=nodoExt->tareas;
    mostrarTarea(item);
    
    if(ListaRealizadas!=NULL){
        freeLista(&ListaRealizadas);
    }
    if (ListaPendientes!=NULL)
    {
        freeLista(&ListaPendientes);
    }
    
   

    getchar();
    return 0;
}


ToDo * CrearListaVacia(){
    return NULL;
}


void cargarTareas(tarea *item,int id){

    item->TareaID=id+1;
    printf("--------Cargando Tarea ID[%d]---------\n",item->TareaID);
    item->Descripcion=(char *)malloc(sizeof(char)*180);
    fflush(stdin);
    printf("Ingrese Descripcion de la tarea:");
    gets(item->Descripcion);
    item->Duracion=rand()%(100-10+1)+10;
}


ToDo * CrearNodo(tarea *item){
    //Reservo un espacio de memoria.
    ToDo *NuevoNodo=(ToDo*)malloc(sizeof(ToDo));
    //Hago que el nuevo Nodo guarde lo que contiene la Lista de tareas(Arreglo). 
    NuevoNodo->tareas=*item;
    //Hago que el siguiente que nodo sea null
    NuevoNodo->next=CrearListaVacia();
    //Devuelvo el Nodo con la Tarea adentro.
    return NuevoNodo;
}

void insertarNodo(ToDo **Lista, ToDo *Nodo){
    if(Lista){
    //Inserto en el Nodo->Siguiente la direccion de memoria de la Lista  para enlazarla.
    Nodo->next=*Lista;
    //Y aqui lista obtiene la direccion Actual del Nodo, al hacer esto repetidamente, se va desplazando y se hace una Lista de nodos.
    *Lista=Nodo;
    }else{
        *Lista=Nodo;
    }
}
ToDo * QuitarNodo(ToDo **Lista){
    ToDo *NodoExtr=(ToDo *)malloc(sizeof(ToDo));
    //Guardo la direccion de memoria del Nodo en el que estoy(Lista contiene un nodo).
    NodoExtr=*Lista;
    //Hago que Lista Apunte al otro Nodo, rompiendo el enlace que habia antes.
    *Lista=(*Lista)->next;
    //Este Nodo puede tener basura en su Siguiente, asi que lo igualo a NULL.
    NodoExtr->next=NULL;
    //Devuelvo el Nodo extraido.
    return NodoExtr;
}
void mostrarLista(ToDo *Lista){
    //Hago un auxiliar para no perder la direccion de lista.
    ToDo *aux=Lista;
    //Mientras aux sea diferente de null se ira mostrando la lista.
    while (aux)
    {
        printf("Tarea ID:[%d]\n",aux->tareas.TareaID);
        printf("Descripcion:%s\n",aux->tareas.Descripcion);
        printf("Duracion:%d\n",aux->tareas.Duracion);
        //Entro a la tarea siguiente de la lista.
        aux=aux->next;
    }
    
}
void mostrarTarea(tarea item){
    printf("Tarea ID:[%d]\n",item.TareaID);
    printf("Descripcion:%s\n",item.Descripcion);
    printf("Duracion:%d\n",item.Duracion);
}
void ControlRealizacion(ToDo **ListaPen, ToDo **ListaReal){
    tarea temp;
    ToDo *aux,*Nnodo;
    ToDo *ListaTemp=CrearListaVacia();
    char ask;
    while ((*ListaPen))
    {
        Nnodo=QuitarNodo(ListaPen);
        insertarNodo(&ListaTemp,Nnodo);
    }
    aux=ListaTemp;
    while (aux)
    {
        temp=aux->tareas;
        //Reseteo
        ask='c';
        do
        {
            printf("La tarea----\n ");
            mostrarTarea(temp);
            printf("¿Fue realizada? Ingrese caracter[s/n]");
            scanf("%c",&ask);
            fflush(stdin);
        } while (ask !='s'&& ask!='S' && ask !='n'&& ask!='N');
        
        Nnodo=QuitarNodo(&ListaTemp);
        aux=ListaTemp;
        if (ask=='S' || ask == 's'){
            insertarNodo(ListaReal,Nnodo);
        }else{
            insertarNodo(ListaPen,Nnodo);
        }
    }
}
ToDo * BusquedaPorPalabra(ToDo *Lista){
    char arrCad[20];
    ToDo *aux=Lista;
    printf("Ingresa la palabra a buscar:");
    gets(arrCad);
    fflush(stdin);
    while (aux)
    {
        if (strstr((aux->tareas.Descripcion),arrCad)!=NULL)
        {
            return aux;
        }
        aux=aux->next;
    }
    
    printf("No se encontro la palabra en ninguna de las tareas.\n");
}
ToDo * BusquedaPorId(ToDo *Lista){
    int id;
    ToDo *aux=Lista;
    printf("Ingrese el ID de la tarea a buscar:");
    scanf("%d",&id);
    fflush(stdin);
    while (aux)
    {
        if (aux->tareas.TareaID==id)
        {
            return aux;
        }
        aux=aux->next;
    }
    
}
void freeLista(ToDo **Lista){
    ToDo *aux=*Lista, *nodoExtr;
    while (aux)
    {
        
        nodoExtr=QuitarNodo(Lista);
        free(nodoExtr->tareas.Descripcion);
        free(nodoExtr);
        aux=*Lista;
    }
    
}