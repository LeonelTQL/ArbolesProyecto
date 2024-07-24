#ifndef ARBOL_AVL_H
#define ARBOL_AVL_H

#include <iostream>
#include <cstring>

using namespace std;
#define pow2(n) (1 << (n))

struct nodo_avl{
    int dato;
    nodo_avl* izquierdo;
    nodo_avl* derecho;
};

class ArbolAVL{
public:
    nodo_avl* raiz;
    ArbolAVL(){
        raiz = NULL;
    }

    int altura(nodo_avl*);
    int diferencia(nodo_avl*);
    nodo_avl* rotacion_derecha(nodo_avl*);
    nodo_avl* rotacion_izquierda(nodo_avl*);
    nodo_avl* rotacion_izquierda_derecha(nodo_avl*);
    nodo_avl* rotacion_derecha_izquierda(nodo_avl*);
    nodo_avl* equilibrar(nodo_avl*);
    nodo_avl* balancearArbol(nodo_avl*);
    nodo_avl* insertar(nodo_avl*, int);
    nodo_avl* eliminarNodo(nodo_avl*, int);
    nodo_avl* encontrarMax(nodo_avl*);
    nodo_avl* encontrarMin(nodo_avl*);
    void mostrar(nodo_avl*, int);
    void dibujarNodo(nodo_avl*, int, int, int);
    void dibujarArbol(nodo_avl*, int, int);
    void enOrden(nodo_avl* arbol, int& x, int y);
    void preOrden(nodo_avl* arbol, int& x, int y);
    void imprimirTexto(int x, int y, const char* texto);
    void postOrden(nodo_avl* arbol, int& x, int y);
    void bfs(nodo_avl*);
    void dfs(nodo_avl* arbol, int& x, int y);
    void imprimirNivelDado(nodo_avl* arbol, int nivel, int& x, int y);
    int validar(string s);
    bool verificarEntrada(string s);
    void dibujarBoton(int, int, int, int, const char*);
    bool esBotonClicado(int, int, int, int, int, int);
    string ingresarTexto(int, int, int, int);
};
#endif // ARBOL_AVL_H
