#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H

#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class Nodo{
public:
    T dato;
    int hI, hD, level, height;
    Nodo<T> * izq;
    Nodo<T> * der;
    Nodo(T d){
        dato = d;
        izq = NULL;
        der = NULL;
        hI = 0;
        hD = 0;
        height = 0;
    }
};

template <class T>
class AVL{
public:
    Nodo<T> * raiz = NULL;
/*
    void crearArbol(Nodo<T> ** nodo){ //Crea un arbol no balanceado dependiendo de lo que ingresa el usuario.
        int d;
        bool answer;
        cout << "Que dato hay en este nodo?\n";
        cin >> d;
        *(nodo) = new Nodo<T>(d);
        cout << "Tiene " << (*nodo)->dato << " hijo izquierdo?\n";
        cin >> answer;
        if(answer)
            crearArbol(&(*nodo)->izq); //Si tiene un hijo, vuelve a entrar a la funcion ahora en la posicion del hijo.
        cout << "Tiene " << (*nodo)->dato << " hijo derecho?\n";
        cin >> answer;
        if(answer)
            crearArbol(&(*nodo)->der);

    }*/
    void insertar(T dato){
        insertarBalanceado(&raiz,dato); //entra a la función insertar balanceado llamando a la posición de la raíz.
    }
    void ascendentemente(){
        inOrden(raiz);
    }
    void descendentemente(){
        desRecursivo(raiz);
    }
    int profundidad(T d){
        return profundidadRecursiva(raiz, d, 0);
    }
    int nivel(T d){
        return profundidadRecursiva(raiz,d,1);
    }
    bool buscar(T dato, Nodo<T> ** lugar){
        return busqueda(raiz,dato,lugar); //Accede a la función recursiva búsqueda mandando inicialmente la raiz.
    }
    bool elimina(T dato){
        return eliminacionBusqueda(&raiz,dato) != -1; //Entra a la función de eliminación balanceada pansando como parámetro la dirección de la raíz (Si regresa menos uno, es el indicador que no se encontró el elemento).
    }
    int altura(T d){
        alturaRecursiva(raiz, d);
    }

private:
    void updateH(Nodo<T>** temp){
        if((*temp)->hI> (*temp)->hD)
            (*temp)->height = (*temp)->hI;
        else (*temp)->height = (*temp)->hD;
    }

    void desRecursivo(Nodo<T> *a){
        if(a == NULL) return;
        desRecursivo(a->der);
        cout << a->dato << " ";
        desRecursivo(a->izq);
    }
    /*
    void crear(string archivo){ //Crea un arbol con los datos recibidos del nombre del archivo pasado como parámetro
        int num; //variable donde se guardará la cantidad de elementos.
        T c; //Variable donde se guardará cada elemento
        ifstream file(archivo, ios::in);
        if(file.is_open()){ //Si pudo abrir el archivo:
            file >> num; //Lee el primer dato en el archivo: la cantidad de enteros
            for(int i = 0; i < num; i++){ //Recorre con un for la cantidad de lecturas que tiene que hacer
                file >> c;
                insertar(c); //Agrega el siguiente número en el archivo al arbol.
            }
            file.close();
        }
        else cout << "File not found\n"; //Lo imprime si no se pudo abrir el archivo
    }*/
    int profundidadRecursiva(Nodo<T>* n, T d, int p){
        if(n == NULL) return -1;
        if(n->dato > d) return profundidadRecursiva(n->izq, d, p+1);
        if(n->dato < d) return profundidadRecursiva(n->der, d, p+1);
        return p;
    }

    int alturaRecursiva(Nodo<T>* n, T d) {
        if (n == NULL) return -1;
        if (n->dato > d) return alturaRecursiva(n->izq, d);
        if (n->dato < d) return alturaRecursiva(n->der, d);
        return n->height;
    }

    int insertarBalanceado(Nodo<T> ** nodo, T d){ //Inserta un elemento y balancea el árbol (si es necesario)
        if(*(nodo)==NULL){ // Si llega a un nodo vacío inserta el nuevo nodo.
            *(nodo) = new Nodo<T>(d);
            return 0; //Regresa 0 ya que no tiene hijos.
        }
        else{
            if((*nodo)->dato >= d){ //Si el dato a insertar es más chico o igual que el dato en el nodo
                (*nodo)->hI = insertarBalanceado(&((*nodo)->izq), d) + 1; //Vuelve iguala la altura de su hijo izquierdo a esta función más uno(ya que tiene un nivel más alto
                if((*nodo)->hD - (*nodo)->hI == -2){  //Evalúa si se requiere hacer algun tipo de rotación (Solo se considera ser posible el lado izquierdo ya que como el elemento se agregará de ese lado es imposible que quede desbalanceado del otro lado.
                    if((*nodo)->izq->hD - (*nodo)->izq->hI == -1){
                        (*nodo) = rotacionDerecha(*nodo); //hace r
                    }
                    else {
                        (*nodo)->izq = rotacionIzquierda((*nodo)->izq);
                        (*nodo) =  rotacionDerecha(*nodo);
                    }

                }
                if(*nodo)
                    return (*nodo)->hI; //Regresa la altura de su hijo izquierdo (ya que el derecho no puede ser más alto debido a que se acaba de agregar un elemento de ese lado).
                else return 0;
            }
            else{
                (*nodo)->hD = insertarBalanceado(&((*nodo)->der), d) + 1; //Si el dato es más grande, se iguala la altura del hijo derecho a lo que regrese la función + 1
                if((*nodo)->hD - (*nodo)->hI == 2){ //Evalúa si se requiere algún tipo de rotación
                    if((*nodo)->der->hD - (*nodo)->der->hI == 1){
                        (*nodo) = rotacionIzquierda(*nodo);

                    }
                    else{
                        (*nodo)->der = rotacionDerecha((*nodo)->der);
                        (*nodo) = rotacionIzquierda(*nodo);
                    }
                }
                if(*nodo)
                return (*nodo)->hD;
                else return 0;
            }

        }
    }

    void preOrden(Nodo<T> * p){
        if(p == NULL)
            return;
        cout << p->dato << " ";
        preOrden(p->izq);
        preOrden(p->der);
    }

    void inOrden(Nodo<T> * p){ //Imprime los elementos en inOrden
        if(p==NULL) //Si el apuntador es nulo, regresa.
            return;
        inOrden(p->izq); //primero entra a la función del lado izquierdo
        cout << p->dato << " "; //Imprime el elemento
        inOrden(p->der); //Entra a la función del lado derecho
    }
    void postOrden(Nodo<T> * p){
        if(p==NULL)
            return;
        postOrden(p->izq);
        postOrden(p->der);
        cout << p->dato << " ";
    }
    void imprime(){ //Llama a la función de inorden enviando la raíz como parametro
        inOrden(raiz);
    }

    bool busqueda(Nodo<T> * p, T bus, Nodo<T> ** lugar){ //Busca el elemento pasado como parámetro en el árbol
        if(p == NULL) //Si el apuntador es nulo, significa que no lo pudo encontrar y regresa falso.
            return false;
        if(p->dato > bus) //Si el dato en el apuntador es más grande que la busqueda entra al lado izquierdo
            return busqueda(p->izq, bus, lugar);
        if(p->dato < bus) //Si es más chico entra al lado derecho
            return busqueda(p->der, bus, lugar);
        *lugar = p;
        return true;//Si no entro a las otras dos condiciones, signfica que encontró el dato, iguala la dirección a la dirección del nodo donde está y regresa true
    }
    /*
    void insercion(Nodo<T> ** p, T d){ //Metodo insertar no balanceado
        if(*p == NULL){
            Nodo<T> * n = new Nodo<T>(d);
            *p = n;
            return;
        }
        if((*p)->dato >= d)
            insercion(&((*p)->izq),d);
        insercion(&((*p)->der),d);
    }*/
    Nodo<T>* rotacionDerecha(Nodo<T> * p){ //Metodo que realiza una rotación derecha desde el punto que se pasó como referencia
        Nodo<T> * temp = p->izq;
        if(!temp) return NULL;
        p->hI = temp->hD;
        p->izq = temp->der;
        temp->der = p;
        if(p->hI > p->hD){
            temp->hD = p->hI + 1; //La nueva altura del hijo derecho de la nueva raíz es la altura del hijo izquierdo de la raíz original más uno
        } //Si la altura izquierda de la raíz original es más alta que la derecha.

        else {
            temp->hD = p->hD + 1;
        }
        updateH(&temp);
        updateH(&p);
        return temp; //Regresa el apuntador a la nueva raíz
    }
    Nodo<T>* rotacionIzquierda(Nodo<T> * p){ //Metodo que realiza una rotación izquierda desde el punto que se pasó como referencia.

        Nodo<T> * temp = p->der;
        if(!temp) return NULL;
        p->hD = temp->hI;
        p->der = temp->izq;
        temp->izq = p;
        if(p->hI > p->hD)
            temp->hI = p->hI + 1;//La nueva altura del hijo izquierdo de la nueva raíz es la altura del hijo izquierdo de la raíz original más uno
            //Si la altura izquierda de la raíz original es más alta que la derecha.
        else temp->hI = p->hD + 1; //O del hijo derecho más uno
        updateH(&temp);
        updateH(&p);
        return temp; //Regresa el apuntador a la nueva raíz
    }

    int eliminacionBusqueda(Nodo<T> ** p, T d){
        Nodo<T> * aux;
        int inter;
        if(*p == NULL) //Si el apuntador es nulo, significa que no se encontró el elemento
            return -1;
        if((*p)->dato == d){ //Si encontró el dato
            if((*p)->izq == NULL){ //Si el nodo no tiene hijo izquierdo
                if(*p == raiz){ //Checa si es la raíz
                    if(raiz->der == NULL){ //Si la raíz no tiene hijo derecho, la elimina
                        delete(raiz);
                        raiz = NULL;
                        return -1;
                    }
                    else{ //Si no, convierte el hijo derecho de la raíz en la nueva raíz
                        aux = raiz->der;
                        delete(raiz);
                        *p = aux;
                        return -1;
                    }
                }
                return -2; //Indicador para la función que dice que no tiene hijos a la izquierda
            }
            inter = intercambio(p,&((*p)->izq)) + 1; //Entra a la función encargada de intercambiar el valor del elminado por el correspondiente; iguala la altura a lo que regresa la función (que es la altura del hijo) + 1;
            if(inter == 0){ //Si la altura es 0 singifica que igualó una hoja directamente, pero aún no ha eliminado el nodo
                aux = (*p)->izq->izq; //Se elimina el hijo de la izuqierda pero se mantiene el propio hijo izquierdo si es que tiene
                delete((*p)->izq);
                (*p)->izq = aux;
            }
            if(aux == NULL) //Si aux es nulo significa que no tuvo otro hijo a la izquierda, por lo que la altura es 0
                (*p)->hI = inter;
            else (*p)->hI = inter+1; //Si no lo es, significa que la altura es 1
        }
        else if((*p)->dato > d){ //Si el dato es menor al del nodo.
            inter = eliminacionBusqueda(&((*p)->izq), d); //Vuelve a entrar a la misma función, pero delhijo izuiqerdo del árbol
            if(inter == -2){ //Si no tiene hijos en la izquierda
                if((*p)->izq->der == NULL){ //Si tampoco tiene en la derecha
                    delete((*p)->izq); //Se elimina la hoja
                    (*p)->izq = NULL;
                    (*p)->hI = 0;
                }
                else{ //Si sí tiene, sólo puede tener un hijo en la derecha, sino asumiríamos que el árbol no está balanceado
                    aux = (*p)->izq->der; //Se pone al hijo de la derecha en el lugar del nodo que se va a eliminar.
                    delete((*p)->izq);
                    (*p)->izq = aux;
                    (*p)->hI = 1;
                }
            }
            else if(inter == -1){ //Si no lo encontró, vuelve a indicarlo
                return -1;
            }
            else (*p)->hI = inter + 1; //Se ajusta la altura
        }
        else {
            inter = eliminacionBusqueda(&((*p)->der), d);//Si entra al hijo de la derecha
            if(inter == -2){ //Se hace lo mismo que con el dato izquierdo
                if((*p)->der->der == NULL){
                    delete((*p)->der);
                    (*p)->der = NULL;
                    (*p)->hD = 0;
                }
                else{
                    aux = (*p)->der->der;
                    delete((*p)->der);
                    (*p)->der = aux;
                    (*p)->hD = 1;
                }
            }
            else if(inter == -1)
                return -1;
            else (*p)->hD = inter+1;
        }
        if(abs((*p)->hI - (*p)->hD) > 1){ //Se checa si se debe hacer alguna rotación
            rotacionesEliminacion(p);//Entra a la función de rotación
        }

        if((*p)->hI >= (*p)->hD) return (*p)->hI; //Regresa la altura más alta para el cálculo del resto de las alturas
        else return (*p)->hD;
    }
    int intercambio(Nodo<T> ** change, Nodo<T> ** p){ //Función encargada de cambiar el dato a eliminar con la hoja correspondiente
        Nodo<T> * aux;
        if((*p)->der == NULL) { //Si ya no tiene hijos en la derecha se cambia el dato
            (*change)->dato = (*p)->dato;
            return -1;
        }
        (*p)->hD = intercambio(change, &((*p)->der)) + 1; //La altura de  la derecha es igual a lo que regrese la función más uno
        if((*p)->hD == 0){ //Si es 0 significa que encontró la hoja a mover
            aux = (*p)->der->izq; //Modifica lo necesario para eliminar la hoja.
            delete((*p)->der);
            (*p)->der = aux;
            if(aux != NULL)
                (*p)->hD= 1;
        }

        if(abs((*p)->hI - (*p)->hD) > 1){ //Verifica si se debe hacer algún tipo de rotación
            rotacionesEliminacion(p);
        }

        if((*p)->hI >= (*p)->hD) return (*p)->hI; else return (*p)->hD; //Regresa la altura más alta
    }
    void rotacionesEliminacion(Nodo<T> ** p){ //Función encargada de evaluar qué tipo de rotación se debe realizar
        if((*p)->hD - (*p)->hI == 2){
            if((*p)->der->hD - (*p)->der->hI == 0 || (*p)->der->hD - (*p)->der->hI == 1){ //Las condiciones que se resuelven con una rotación izquierda
                *p = rotacionIzquierda(*p);
                return;
            }
            else {
                (*p)->der = rotacionDerecha((*p)->der); //Las condiciones que se resuelven con una rotación derecha sobre el hijo derecho y una rotación izquierda sobre la raíz relativa.
                *p = rotacionIzquierda(*p);
                return;
            }
        }
        else{
            if((*p)->izq->hD - (*p)->izq->hI == 0 || (*p)->izq->hD - (*p)->izq->hI == -1){ //Las condiciones que se resuelven con una rotación derecha
                *p = rotacionDerecha(*p);
                return;
            }
            else {
                (*p)->izq = rotacionIzquierda((*p)->izq); //Las condiciones que se resuelven con una rotación izquierda sobre el hijo izquierdo y una rotación derecha sobre la raíz relativa.
                *p = rotacionDerecha(*p);
                return;
            }
        }
    }



};

#endif