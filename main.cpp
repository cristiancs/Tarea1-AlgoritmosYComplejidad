#include <iostream>
#include <stdlib.h>     /* malloc, free, rand */
#include <queue>
using namespace std;


struct nodo{
    int id;
    int fobia;
    int color;
    struct nodo *sgte;
    struct arista *ady;//puntero hacia la primera arista del nodo
    int currentArista;
};
struct arista{
    struct nodo *destino;//puntero al nodo de llegada
    struct arista *sgte;
    struct arista *final;
};
typedef struct nodo *Tnodo;//  Tipo Nodo
typedef struct arista *Tarista; //Tipo Arista

class Grafo
{
private:
    Tnodo p,current;//puntero cabeza
    int nArcos, nVertices;
public:
    Grafo();
    ~Grafo();
    void insertar_nodo(int id, int fobia, int *a_guardar[]);
    void agrega_arista(Tnodo &, Tnodo &, Tarista &);
    void setEdge(int ini, int fin, int *ubicaciones[]);
    void vaciar_aristas(Tnodo &);
    void eliminar_nodo(int id);
    void deleteEdge(int inicio, int fin);
    void mostrar_grafo();
    void mostrar_aristas(int var);
    void setMark(int id, int color, int *ubicaciones[]);
    int getMark(int id, int *ubicaciones[]);
    int getFobia(int id, int *ubicaciones[]);
    int nVertex();
    int nEdges();
    int first(int nodo, int *ubicaciones[]);
    int next(int nodo, int *ubicaciones[]);
};
Grafo::Grafo(){
    p = NULL;
    nArcos = 0;
    nVertices = 0;
    current = 0;
}
Grafo::~Grafo(){
    Tnodo aux,next;
    aux=p;
    
    next = NULL;
    // Grafo Vacio
    if(p==NULL){
        return;
    }
    while(aux!=NULL){
        next = aux->sgte;
        eliminar_nodo(aux->id);
        aux=next;
    }
}
void Grafo::insertar_nodo(int id,int fobia, int *a_guardar[]){
    Tnodo t,nuevo=new struct nodo;
    nuevo->fobia = fobia;
    nuevo->id = id;
    nuevo->sgte = NULL;
    nuevo->ady=NULL;
    nuevo->color=-1;
    nuevo->currentArista = 1;
    // Verificar si hay nodos
    if(p==NULL){
        p = nuevo;
        current = p;
    }
    // Lo Insertamos al final
    else{
        t = current;
        nVertices+=1;
        t->sgte = nuevo;
        current = t->sgte;
       
    }
    a_guardar[id] = (int*)current;

    //Tnodo dato = (nodo*)a_guardar[id];
    //cout << a_guardar[id] << "|" << dato->id <<  "\n";
}
void Grafo::agrega_arista(Tnodo &aux, Tnodo &aux2, Tarista &nuevo){
    Tarista q;
    if(aux->ady==NULL){
        aux->ady=nuevo;
        nuevo->destino=aux2;
        aux->ady->final = nuevo;
    }
    else{
        q=aux->ady->final;
        nuevo->destino=aux2;
        q->sgte=nuevo;
    }
    nArcos+=1;
}
void Grafo::setEdge(int ini,int fin, int *ubicaciones[]){
    Tarista nuevo=new struct arista;
    Tarista nuevo2=new struct arista;
    Tnodo aux, aux2;

    // Grafo vacio
    if(p==NULL){
        return;
    }
    nuevo->sgte=NULL;
    nuevo2->sgte=NULL;

    aux = (nodo*)ubicaciones[ini];
    aux2 = (nodo*)ubicaciones[fin];

    agrega_arista(aux,aux2, nuevo);
    agrega_arista(aux2,aux, nuevo2);
    
}
void Grafo::vaciar_aristas(Tnodo &aux){
    Tarista q,r;
    q=aux->ady;
    if(q->sgte == NULL){
        delete(q);
    }
    else{
        while(q->sgte!=NULL){
            r=q;
            q=q->sgte;
            delete(r);
        }
        delete(q);
    }
    aux->ady = NULL;
    //  mostrar_grafo();
}
void Grafo::eliminar_nodo(int id){
    Tnodo aux,ant;
    aux=p;
    // Grafo Vacio
    if(p==NULL){
        return;
    }
    while(aux!=NULL){
        if(aux->id==id){
            if(aux->ady!=NULL){
                vaciar_aristas(aux);
            }
            if(aux==p){
                p=p->sgte;
                delete(aux);
                return;
            }
            else {
                ant->sgte = aux->sgte;
                delete(aux);
                return;
            }
        }
        else
        {
            ant=aux;
            aux=aux->sgte;
        }
    }

    nVertices -=1;
}
void Grafo::deleteEdge(int inicio,int fin){
    Tnodo aux, aux2;
    Tarista q,r;
    aux=p;
    aux2=p;
    while(aux2!=NULL){
        if(aux2->id==fin){
            break;
        }
        else
            aux2=aux2->sgte;
    }
    while(aux!=NULL){
        if(aux->id==inicio){
            q=aux->ady;
            while(q!=NULL){
                if(q->destino==aux2){
                    if(q==aux->ady)
                        aux->ady=aux->ady->sgte;
                    else
                        r->sgte=q->sgte;
                    delete(q);
                    return;
                }
            }
            r=q;
            q=q->sgte;
        }
        aux = aux->sgte;
    }
    nArcos-=1;
}
void Grafo::mostrar_grafo(){
    Tnodo ptr;
    Tarista ar;
    ptr=p;
    cout<<"ID|FOBIA|COLOR|LISTA DE ADYACENCIA|\n";
    while(ptr!=NULL){
        cout<<"   "<<ptr->id<<"|";
        cout<<"   "<<ptr->fobia<<"|";
        cout<<"   "<<ptr->color<<"|";
        if(ptr->ady!=NULL)
        {
            ar=ptr->ady;
            while(ar!=NULL){
                cout<<" "<<ar->destino->id;
                ar=ar->sgte;
            }
        }
        ptr=ptr->sgte;
        cout<<endl;
    }
}
void Grafo::mostrar_aristas(int var){
    Tnodo aux;
    Tarista ar;
    aux=p;
    while(aux!=NULL)
    {
        if(aux->id==var){
            if(aux->ady==NULL){
                cout<<"EL NODO NO TIENE ARISTAS...!!!!";
                return;
            }
            else{
                cout<<"NODO|FOBIA|LISTA DE ADYACENCIA\n";
                cout<<"   "<<aux->id<<"|";
                cout<<"   "<<aux->fobia<<"|";
                ar=aux->ady;

                while(ar!=NULL){
                    cout<<ar->destino->id<<" ";
                    ar=ar->sgte;
                }
                cout<<endl;
                return;
            }
        }
        else
            aux=aux->sgte;
    }
}
void Grafo::setMark(int id, int color, int *ubicaciones[]){
    //Tnodo aux;
    //aux=p;
    // Grafo Vacio
    if(p==NULL){
        return;
    }
    Tnodo addr = (nodo*)ubicaciones[id];
    addr->color = color;
    return;
}
int Grafo::getMark(int id, int *ubicaciones[]){
    // Grafo Vacio
    if(p==NULL){
        return -1;
    }
    Tnodo addr = (nodo*)ubicaciones[id];
    return addr->color;
}
int Grafo::getFobia(int id, int *ubicaciones[]){
   Tnodo addr = (nodo*)ubicaciones[id];
    return addr->fobia;
}

int Grafo::nVertex(){
    return nVertices+1;
}
int Grafo::nEdges(){
    return nArcos;
}
int Grafo::first(int id, int *ubicaciones[]){
    // Grafo Vacio
    if(p==NULL){
        return -1;
    }
    Tnodo addr = (nodo*)ubicaciones[id];
    if(addr->ady == NULL){
         return nVertex()+1;
    }
    return addr->ady->destino->id;

}
int Grafo::next(int id, int *ubicaciones[]){
    Tnodo aux;
    Tarista ar;
    // Grafo Vacio
    if(p==NULL){
        return -1;
    }
    Tnodo addr = (nodo*)ubicaciones[id];
    aux=addr;

    if(aux->ady == NULL){
        return nVertex()+1;
    }

    ar=aux->ady;
    int i = 1;
   
    while(ar!=NULL){
        if(i == aux->currentArista){
            aux->currentArista+=1;
            return ar->destino->id;
        }
        ar=ar->sgte;

        i++;
    }
    return nVertex()+1;
}
void BFS(Grafo *G,int nodo,int *cvert, int pintura, int* fobias_comunidad, int* auxiliar_nodos[]){
    queue<int> q;
    int w,z;
    q.push(nodo);
    
    fobias_comunidad[G->getFobia(nodo,auxiliar_nodos)]+=1; // Aumentar al contador de fobias
    G->setMark(nodo, pintura, auxiliar_nodos);

    while(q.size() != 0){
        z = q.front();
        q.pop();
        fobias_comunidad[G->getFobia(z,auxiliar_nodos)]+=1; // Aumentar al contador de fobias
        G->setMark(z, pintura, auxiliar_nodos);
        for(w= G->first(z,auxiliar_nodos); w< G->nVertex()+1; w = G->next(z,auxiliar_nodos)){
            if(G->getMark(w,auxiliar_nodos) == -1){
                (*cvert)++;
                fobias_comunidad[G->getFobia(w,auxiliar_nodos)]+=1; // Aumentar al contador de fobias
                G->setMark(w, pintura, auxiliar_nodos);
                q.push(w);
            }

        }
    }

    
}
int main(){
    Grafo G;
    int cantidad_datos, aux1,aux2, i, cantidad_vertices;
    cin >> cantidad_datos;

    // Agregar Nodos
    //cout << "Agregando nodos"<<"\n";
    i = 1;
    int **auxiliar_nodos = new int*[cantidad_datos+1]; // Lista auxiliar para agilizar setEdge
    while(i <= cantidad_datos){
        cin >> aux1;
        G.insertar_nodo(i,aux1, auxiliar_nodos);
        i++;
    }

    //cout << "Agregando vertices"<<"\n";
    // Agregar Vertices
    cin >> cantidad_vertices;
    i = 0;
    while(i < cantidad_vertices){
        cin >> aux1;
        cin >> aux2;
        //if(i%1000 == 0){
        //    cout << i << " de " << cantidad_vertices << "\n";
        //}
        G.setEdge(aux1,aux2, auxiliar_nodos);
        i++;
    }
   //G.mostrar_grafo();

    int nodos_visitados = 0;
    int cantidad_comunidades = 0;
    int* comunidades = (int*) calloc(cantidad_datos, sizeof(int)); // Suficiente espacio para todas las comunidades, el peor caso seria que nadie tenga amigos

    //int w = 0; // Auxiliar para DFS
    int i2 = 1;
    //cout << "Contabilizando Fobias"<<"\n";
    while(nodos_visitados <cantidad_datos){
        //cout << "Buscando nodos no visitados"<<"\n";
        //cout << "Visitados: " << nodos_visitados << "de " << cantidad_datos<<endl;
        // Buscar Nodo no visitado
        while(G.getMark(i2,auxiliar_nodos) != -1){
            i2++;
        }
        //cout << "Encontrado nodo no visitado " << i2<<"\n";

        int* fobias_comunidad = (int*) calloc(10000, sizeof(int)); // Vamos guardando las veces que se ve una fobia


       
        int dfs_visits = 1; 
        BFS(&G,i2,&dfs_visits,cantidad_comunidades,fobias_comunidad,auxiliar_nodos); 
        

        // Buscar la fobia que mas esta
        int max = 0;
        int fobia_max = 0;
        for(i=0; i<10000;i++){
            if(fobias_comunidad[i] != 0){
            //    cout << i << '|' << fobias_comunidad[i]<<'\n';
            }

            if(fobias_comunidad[i] > max){
                max = fobias_comunidad[i];
                fobia_max = i;
            }
        }
        free(fobias_comunidad);

        comunidades[cantidad_comunidades] = fobia_max;

       

       // cout <<"FOBIA MAXIMA " << fobia_max<<"\n";

        cantidad_comunidades++;
        nodos_visitados+=dfs_visits; // El 1 de la visita del nodo padre

    }

    //cout << "Mostrando salida"<<"\n";
    cout << cantidad_comunidades << '\n';
    // Liberamos el espacio que quedo en 0 antes de 
    comunidades = (int*) realloc(comunidades, cantidad_comunidades*sizeof(int));
    for(i=0; i<cantidad_comunidades;i++){
        cout << comunidades[i] << '\n';
    }

    delete(auxiliar_nodos);
    free(comunidades);

    //G.mostrar_grafo();

    G.~Grafo();

    return 0;
}