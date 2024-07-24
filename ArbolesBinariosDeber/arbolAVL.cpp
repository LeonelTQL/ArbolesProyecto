#include "arbolAVL.h"
#include <graphics.h>
#include <cstdlib>
#include <cctype>
#include <cstring>

using namespace std;

const int x = 900;
const int y = 100;

int ArbolAVL::altura(nodo_avl* temp){
    int h = 0;
    if(temp != NULL){
        int altura_izquierda = altura(temp->izquierdo);
        int altura_derecha = altura(temp->derecho);
        int altura_maxima = (altura_izquierda > altura_derecha) ? altura_izquierda : altura_derecha;
        h = altura_maxima + 1;
    }
    return h;
}

int ArbolAVL::diferencia(nodo_avl* temp){
    int altura_izquierda = altura(temp->izquierdo);
    int altura_derecha = altura(temp->derecho);
    int factor_equilibrio = altura_izquierda - altura_derecha;
    return factor_equilibrio;
}

nodo_avl* ArbolAVL::rotacion_derecha(nodo_avl* padre){
    nodo_avl* temp;
    temp = padre->derecho;
    padre->derecho = temp->izquierdo;
    temp->izquierdo = padre;
    return temp;
}

nodo_avl* ArbolAVL::rotacion_izquierda(nodo_avl* padre){
    nodo_avl* temp;
    temp = padre->izquierdo;
    padre->izquierdo = temp->derecho;
    temp->derecho = padre;
    return temp;
}

nodo_avl* ArbolAVL::rotacion_izquierda_derecha(nodo_avl* padre){
    nodo_avl* temp;
    temp = padre->izquierdo;
    padre->izquierdo = rotacion_derecha(temp);
    return rotacion_izquierda(padre);
}

nodo_avl* ArbolAVL::rotacion_derecha_izquierda(nodo_avl* padre){
    nodo_avl* temp;
    temp = padre->derecho;
    padre->derecho = rotacion_izquierda(temp);
    return rotacion_derecha(padre);
}

nodo_avl* ArbolAVL::equilibrar(nodo_avl* temp){
    int factor_equilibrio = diferencia(temp);
    if (factor_equilibrio > 1){
        if (diferencia(temp->izquierdo) > 0)
            temp = rotacion_izquierda(temp);
        else
            temp = rotacion_izquierda_derecha(temp);
    } else if(factor_equilibrio < -1){
        if (diferencia(temp->derecho) > 0)
            temp = rotacion_derecha_izquierda(temp);
        else
            temp = rotacion_derecha(temp);
    }
    return temp;
}

nodo_avl* ArbolAVL::balancearArbol(nodo_avl* raiz){
    if (raiz == NULL)
        return raiz;
    raiz->izquierdo = balancearArbol(raiz->izquierdo);
    raiz->derecho = balancearArbol(raiz->derecho);
    return equilibrar(raiz);
}

nodo_avl* ArbolAVL::insertar(nodo_avl* raiz, int valor){
    if (raiz == NULL) {
        raiz = new nodo_avl;
        raiz->dato = valor;
        raiz->izquierdo = NULL;
        raiz->derecho = NULL;
        return raiz;
    }

    if(valor == raiz->dato){
        cout << "El valor ya ha sido ingresado." << endl;
        return raiz;
    }
    if (valor < raiz->dato){
        raiz->izquierdo = insertar(raiz->izquierdo, valor);
    } else if (valor >= raiz->dato){
        raiz->derecho = insertar(raiz->derecho, valor);
    }
    return raiz;
}

nodo_avl* ArbolAVL::eliminarNodo(nodo_avl* raiz, int valor){
    if(raiz == NULL){
        return raiz;
    }
    if (valor < raiz->dato){
        raiz->izquierdo = eliminarNodo(raiz->izquierdo, valor);
    } else if(valor > raiz->dato){
        raiz->derecho = eliminarNodo(raiz->derecho, valor);
    } else{
        if (raiz->izquierdo == NULL || raiz->derecho == NULL){
            nodo_avl* temp = raiz->izquierdo ? raiz->izquierdo : raiz->derecho;
            if (temp == NULL){
                temp = raiz;
                raiz = NULL;
            }else{
                *raiz = *temp;
            }
            delete temp;
        }else{
            nodo_avl* temp = encontrarMin(raiz->derecho);
            raiz->dato = temp->dato;
            raiz->derecho = eliminarNodo(raiz->derecho, temp->dato);
        }
    }
    if(raiz == NULL){
        return raiz;
    }
    return equilibrar(raiz);
}

nodo_avl* ArbolAVL::encontrarMax(nodo_avl* raiz){
    while (raiz->derecho != NULL){
        raiz = raiz->derecho;
    }
    return raiz;
}

nodo_avl* ArbolAVL::encontrarMin(nodo_avl* raiz){
    while (raiz->izquierdo != NULL){
        raiz = raiz->izquierdo;
    }
    return raiz;
}

void ArbolAVL::mostrar(nodo_avl* ptr, int nivel){
    int i;
    if (ptr != NULL){
        mostrar(ptr->derecho, nivel + 1);
        cout << endl;
        if (ptr == raiz)
            cout << "Raiz -> ";
        for (i = 0; i < nivel && ptr != raiz; i++)
            cout << "        ";
        cout << ptr->dato;
        mostrar(ptr->izquierdo, nivel + 1);
    }
}

void ArbolAVL::dibujarNodo(nodo_avl* nodo, int x, int y, int nivel){
    int radio_nodo = 20;
    if (nodo == NULL){
        return;
    }
    setcolor(WHITE);
    circle(x, y, radio_nodo);
    string dato_nodo = to_string(nodo->dato);
    outtextxy(x - 5, y - 10, const_cast<char*>(dato_nodo.c_str()));

    int desplazamiento_x_hijo = pow2(3 - nivel) * 20;
    int desplazamiento_y_hijo = 50;

    if(nodo->izquierdo){
        line(x - radio_nodo, y + radio_nodo, x - desplazamiento_x_hijo + radio_nodo, y + desplazamiento_y_hijo - radio_nodo);
        dibujarNodo(nodo->izquierdo, x - desplazamiento_x_hijo, y + desplazamiento_y_hijo, nivel + 1);
    }

    if(nodo->derecho){
        line(x + radio_nodo, y + radio_nodo, x + desplazamiento_x_hijo - radio_nodo, y + desplazamiento_y_hijo - radio_nodo);
        dibujarNodo(nodo->derecho, x + desplazamiento_x_hijo, y + desplazamiento_y_hijo, nivel + 1);
    }
}

void ArbolAVL::dibujarArbol(nodo_avl* raiz, int x, int y){
    if (raiz == NULL){
        return;
    }
    dibujarNodo(raiz, x, y, 0);
}



void ArbolAVL::imprimirTexto(int x, int y, const char* texto){
    outtextxy(x, y, const_cast<char*>(texto));
}

void ArbolAVL::preOrden(nodo_avl* arbol, int& x, int y){
    if (arbol == NULL)
        return;
    cout << arbol->dato << "  ";
    char dato_str[10];
    sprintf(dato_str, "%d", arbol->dato);
    imprimirTexto(x, y, dato_str);
    x += 40;
    preOrden(arbol->izquierdo, x, y);
    preOrden(arbol->derecho, x, y);
}

void ArbolAVL::enOrden(nodo_avl* arbol, int& x, int y){
    if (arbol == NULL)
        return;

    enOrden(arbol->izquierdo, x, y);
    cout << arbol->dato << "  ";
    char dato_str[10];
    sprintf(dato_str, "%d", arbol->dato);
    imprimirTexto(x, y, dato_str);
    x += 40;
    enOrden(arbol->derecho, x, y);
}

void ArbolAVL::postOrden(nodo_avl* arbol, int& x, int y){
    if (arbol == NULL)
        return;

    postOrden(arbol->izquierdo, x, y);
    postOrden(arbol->derecho, x, y);
    cout << arbol->dato << "  ";
    char dato_str[10];
    sprintf(dato_str, "%d", arbol->dato);
    imprimirTexto(x, y, dato_str);
    x += 40;
}


void ArbolAVL::bfs(nodo_avl* arbol){
    int h = altura(arbol);
    int x = 50;
    int y = 300;
    for (int i = 1; i <= h; i++) {
        imprimirNivelDado(arbol, i, x, y);
    }
    cout << endl;
}

void ArbolAVL::dfs(nodo_avl* arbol, int& x, int y){

    if (arbol == NULL) return;
    cout << arbol->dato << " ";
    char dato_str[10];
    sprintf(dato_str, "%d", arbol->dato);
    imprimirTexto(x, y, dato_str);
    x += 40;
    dfs(arbol->izquierdo, x, y);
    dfs(arbol->derecho, x, y);
}

void ArbolAVL::imprimirNivelDado(nodo_avl* arbol, int nivel, int& x, int y){
    if (arbol == NULL)
        return;
    if (nivel == 1) {
        cout << arbol->dato << "  ";
        char dato_str[10];
        sprintf(dato_str, "%d", arbol->dato);
        imprimirTexto(x, y, dato_str);
        x += 40;
    } else if (nivel > 1) {
        imprimirNivelDado(arbol->izquierdo, nivel - 1, x, y);
        imprimirNivelDado(arbol->derecho, nivel - 1, x, y);
    }
}


int ArbolAVL::validar(string s) {
    if (verificarEntrada(s)) {
        return 100;
    }
    return 400;
}

bool ArbolAVL::verificarEntrada(string s){
    int longitud = s.length();
    for (int i = 0; i < longitud; i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

void ArbolAVL::dibujarBoton(int izquierda, int arriba, int derecha, int abajo, const char* etiqueta){
    setcolor(WHITE);
    rectangle(izquierda, arriba, derecha+15, abajo);
    setcolor(GREEN);
    outtextxy(izquierda+15, arriba + 15, const_cast<char*>(etiqueta));
}

bool ArbolAVL::esBotonClicado(int izquierda, int arriba, int derecha, int abajo, int mx, int my){
    return (mx > izquierda && mx < derecha && my > arriba && my < abajo);
}

string ArbolAVL::ingresarTexto(int izquierda, int arriba, int derecha, int abajo){
    char str[20] = "";
    setcolor(WHITE);
    rectangle(izquierda, arriba, derecha+120, abajo);
    setcolor(GREEN);
    outtextxy(izquierda + 10, arriba + 5, const_cast<char*>("Ingresa un numero:"));
    while (1) {
        if (kbhit()) {
            char c = getch();
            if (c == 13) {
                break;
            } else if (c == 8) {
                if (strlen(str) > 0) {
                    str[strlen(str) - 1] = '\0';
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(izquierda + 10, arriba + 25, derecha, abajo);
                    setcolor(GREEN);
                    outtextxy(izquierda + 10, arriba + 25, str);
                }
            } else {
                if (strlen(str) < sizeof(str) - 1) {
                    strncat(str, &c, 1);
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(izquierda + 10, arriba + 25, derecha, abajo);
                    setcolor(GREEN);
                    outtextxy(izquierda + 10, arriba + 25, str);
                }
            }
        }
    }
    return string(str);
}
