#include <iostream>
#include <stdlib.h>     /* malloc, free, rand */

using namespace std;


struct nodo{
    int id;
    int fobia;
    int color;
    struct nodo *sgte;
    struct arista *ady;//puntero hacia la primera arista del nodo
};
struct arista{
    struct nodo *destino;//puntero al nodo de llegada
    struct arista *sgte;
};
typedef struct nodo *Tnodo;//  Tipo Nodo
typedef struct arista *Tarista; //Tipo Arista

class Grafo
{
private:
    Tnodo p;//puntero cabeza
    int nArcos, nVertices;
public:
    Grafo();
    ~Grafo();
    void insertar_nodo(int id, int fobia);
    void agrega_arista(Tnodo &, Tnodo &, Tarista &);
    void setEdge(int ini, int fin);
    void vaciar_aristas(Tnodo &);
    void eliminar_nodo(int id);
    void deleteEdge(int inicio, int fin);
    void mostrar_grafo();
    void mostrar_aristas(int var);
    void setMark(int id, int color);
    void setFobia(int id, int color);
    int getMark(int id);
    int getFobia(int id);
    int nVertex();
    int nEdges();
    int getElement(int posicion);
    int first(int nodo);
    int next(int nodo, int posicion);
};
Grafo::Grafo(){
    p = NULL;
    nArcos = 0;
    nVertices = 0;
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
        eliminar_nodo(aux->fobia);
        aux=next;
    }
}
void Grafo::insertar_nodo(int id,int fobia){
    Tnodo t,nuevo=new struct nodo;
    nuevo->fobia = fobia;
    nuevo->id = id;
    nuevo->sgte = NULL;
    nuevo->ady=NULL;
    nuevo->color=-1;
// Verificar si hay nodos
    if(p==NULL){
        p = nuevo;
    }
// Buscar donde lo podemos insertar
    else{
        int flag = false;
        t = p;
        while(t->sgte!=NULL){
            if(t->sgte->id == id){
                flag = true;
            }
            t = t->sgte;
        }
        if(flag == false && id != 0){
            nVertices+=1;
            t->sgte = nuevo;
        }
        else{
            // delete(t);
            delete(nuevo);
        }
    }
}
void Grafo::agrega_arista(Tnodo &aux, Tnodo &aux2, Tarista &nuevo){
    Tarista q;
    if(aux->ady==NULL){
        aux->ady=nuevo;
        nuevo->destino=aux2;
    }
    else{
        q=aux->ady;
        while(q->sgte!=NULL)
            q=q->sgte;
        nuevo->destino=aux2;
        q->sgte=nuevo;
    }
    nArcos+=1;
}
void Grafo::setEdge(int ini,int fin){
    Tarista nuevo=new struct arista;
    Tnodo aux, aux2;

    // Grafo vacio
    if(p==NULL){
        return;
    }
    nuevo->sgte=NULL;
    aux=p;
    aux2=p;
    while(aux2!=NULL){
        if(aux2->id==fin){
            break;
        }
        aux2=aux2->sgte;
    }
    while(aux!=NULL){
        if(aux->id==ini){
            agrega_arista(aux,aux2, nuevo);
            return;
        }
        aux = aux->sgte;
    }
}
void Grafo::vaciar_aristas(Tnodo &aux)
{
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
void Grafo::mostrar_aristas(int var)
{
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
void Grafo::setMark(int id, int color){
    Tnodo aux;
    aux=p;
    // Grafo Vacio
    if(p==NULL){
        return;
    }
    while(aux!=NULL){
        if(aux->id==id){
            aux->color = color;
            return;
        }
        else{
            aux=aux->sgte;
        }
    }
}
int Grafo::getMark(int id){
    Tnodo aux;
    aux=p;
    // Grafo Vacio
    if(p==NULL){
        return -1;
    }
    while(aux!=NULL){
        if(aux->id==id){
            return aux->color;
        }
        else{
            aux=aux->sgte;
        }
    }
    return -1;
}
void Grafo::setFobia(int id, int fobia){
    Tnodo aux;
    aux=p;
    // Grafo Vacio
    if(p==NULL){
        return;
    }
    while(aux!=NULL){
        if(aux->id==id){
            aux->fobia = fobia;
            return;
        }
        else{
            aux=aux->sgte;
        }
    }
}
int Grafo::getFobia(int id){
    Tnodo aux;
    aux=p;
    // Grafo Vacio
    if(p==NULL){
        return -1;
    }
    while(aux!=NULL){
        if(aux->id==id){
            return aux->fobia;
        }
        else{
            aux=aux->sgte;
        }
    }
    return -1;
}
int Grafo::getElement(int posicion){
    Tnodo aux;
    aux=p;
    // Grafo Vacio
    if(p==NULL){
        return -1;
    }
    int i = 0;
    while(aux!=NULL){
        if(i == posicion){
            return aux->fobia;
        }
        else{
            aux=aux->sgte;
        }
        i++;
    }
    return -1;
}
int Grafo::nVertex(){
    return nVertices+1;
}
int Grafo::nEdges(){
    return nArcos;
}
int Grafo::first(int id){
    Tnodo aux;
    aux=p;
    // Grafo Vacio
    if(p==NULL){
        return -1;
    }
    while(aux!=NULL){
        if(aux->id==id){
            if(aux->ady == NULL){
                return nVertex()+1;
            }
            return aux->ady->destino->id;
        }
        else{
            aux=aux->sgte;
        }
    }
    return nVertex()+1;
}
int Grafo::next(int id, int posicion){
    Tnodo aux;
    Tarista ar;
    aux=p;
    // cout << "Solicitada posición "<< posicion << endl;
    // Grafo Vacio
    if(p==NULL){
        return -1;
    }
    while(aux!=NULL){
        if(aux->id==id){
            ar=aux->ady;
            int i = 1;
            //cout << "Interacion"<<endl;
            while(ar!=NULL){
                //	cout << i << posicion << endl;
                if(i == posicion){
                    return ar->destino->id;
                }
                ar=ar->sgte;
                i++;
            }
            return nVertex()+1;
        }
        else{
            aux=aux->sgte;
        }
    }
    return nVertex()+1;
}

void DFS(Grafo *G,int aux1,int *w,int *cvert, int pintura, int* fobias_comunidad){
    //cout << "Recibido el elemento "<< aux1 << endl;
    *cvert = 0;
    int cvert2 = 0;
    if(G->getMark(aux1) == -1){
       // cout << aux1 << "?" << G->getFobia(aux1)<<"\n";
        fobias_comunidad[G->getFobia(aux1)]+=1; // Aumentar al contador de fobias
        G->setMark(aux1, pintura);
    }
        
    
    for(*w= G->first(aux1); *w< G->nVertex()+1; *w = G->next(aux1,*cvert)){
       // cout << "Iterando sobre "<< *w <<endl;
        (*cvert)++; // Aumentamos los elementos recorridos
        if(G->getMark(*w) == -1){
             DFS(G,*w, w, &cvert2, pintura, fobias_comunidad);
        }

    }
}
int main(){
    Grafo G;
    int cantidad_datos, aux1,aux2, i, cantidad_vertices;
    cin >> cantidad_datos;

    // Agregar Nodos
    i = 1;
    while(i <= cantidad_datos){
        cin >> aux1;
        G.insertar_nodo(i,aux1);
        i++;
    }


    // Agregar Vertices
    cin >> cantidad_vertices;
    i = 0;
    while(i < cantidad_vertices){
        cin >> aux1;
        cin >> aux2;
        G.setEdge(aux1,aux2);
        G.setEdge(aux2,aux1);
        i++;
    }
   // G.mostrar_grafo();

    int nodos_visitados = 0;
    int cantidad_comunidades = 0;
    int* comunidades = (int*) calloc(cantidad_datos, sizeof(int)); // Suficiente espacio para todas las comunidades, el peor caso seria que nadie tenga amigos

    int w = 0; // Auxiliar para DFS
    int i2 = 1;
    while(nodos_visitados <=cantidad_datos){
        
        // Buscar Nodo no visitado
        while(G.getMark(i2) != -1){
            i2++;
        }


        int* fobias_comunidad = (int*) calloc(10000, sizeof(int)); // Vamos guardando las veces que se ve una fobia


       
        int dfs_visits = 0; 
        DFS(&G,i2,&w,&dfs_visits,cantidad_comunidades,fobias_comunidad); 

        

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
        nodos_visitados+=dfs_visits+1; // El 1 de la visita del nodo padre

    }

    
    cout << cantidad_comunidades << '\n';
    // Liberamos el espacio que quedo en 0 antes de 
    comunidades = (int*) realloc(comunidades, cantidad_comunidades*sizeof(int));
    for(i=0; i<cantidad_comunidades;i++){
        cout << comunidades[i] << '\n';
    }


    free(comunidades);


    //G.mostrar_grafo();




   
    // int N,
    //         M,     // Cantidad de vuelos entre pares de fobiaes que tiene la compañía
    //         Q,     // El número de consultas que se harán sobre el grafo
    //         i,
    //         aux1,
    //         aux2;
    // cin >> N;
    // cin >> M;

    // // Procesar
    // // Agregar Nodos y Arcos
    // i = 0;
    // while(i < M){
    //     cin >> aux1;
    //     G.insertar_nodo(aux1);
    //     cin >> aux2;
    //     G.insertar_nodo(aux2);
    //     G.setEdge(aux1,aux2);
    //     i++;
    // }
    // cin >> Q;
    // i = 0;
    // int w;
    // int cvert=0;
    // // cout << G.nVertex();
    // cout<<Q<<endl; // Primera Linea salida
    // while(i < Q){
    //     cin >> aux1; // Vertice a trabjar
    //     // cout << "Elemento " << aux1 << endl;
    //     // Buscar vertices no alcanzables desde aux1;
    //     //vertices que llego desde aux1;
    //     DFS(&G,aux1,&w,&cvert,aux1);

    //     // G.mostrar_grafo();
    //     cout << 'hola\n';

    //     //recorrer grafo y ver si esta marcado;
    //     int noalcanzables[G.nVertex()];
    //     cvert = 0;
    //     for (w=0; w<G.nVertex(); w++){
    //         // cout << "Analizando : "<<G.getElement(w) << endl;
    //         if (G.getMark(G.getElement(w))!=aux1 && G.getElement(w) != aux1){
    //             noalcanzables[cvert] = G.getElement(w);
    //             cvert++;
    //         }
    //     }
    //     // G.mostrar_grafo();
    //     cout << cvert<< " ";
    //     qsort(noalcanzables, cvert, sizeof(int), compare);
    //     for (w=0; w<cvert; w++){
    //         if (G.getMark(w)!=Q){
    //             cout<<noalcanzables[w]<<" ";
    //         }
    //     }
    //     cout << endl;

    //     i++;
    // }


    G.~Grafo();

    return 0;
}