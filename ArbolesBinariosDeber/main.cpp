#include "arbolAVL.h"
#include "arbolAVL.cpp"
#include <graphics.h>
#include <iostream>

using namespace std;
void limpiarTextoArea(int x1, int y1, int x2, int y2){
    setfillstyle(SOLID_FILL, BLACK);
    bar(x1, y1, x2, y2);
}
int main(){
    int opcion, elemento, factorEquilibrio;
    int c;
    string str;
    ArbolAVL arbol;

    int gd = DETECT;
    int gm;
    initwindow(1920, 1080, "Interfaz Grafica Arbol AVL", 0, 0, false, true);

    while (1){
        settextstyle(3, HORIZ_DIR, 1);
        outtextxy(700, 10, const_cast<char*>("Arbol AVL"));
        outtextxy(1300, 10, const_cast<char*>("Leonardo Narvaez "));
        outtextxy(1300, 40, const_cast<char*>("Leonel Tipan "));
        arbol.dibujarBoton(50, 700, 150, 750, "Insertar");
        arbol.dibujarBoton(350, 700, 450, 750, " Balancear");
        arbol.dibujarBoton(550, 700, 650, 750, " PreOrden");
        arbol.dibujarBoton(700, 700, 780, 750, " EnOrden");
        arbol.dibujarBoton(850, 700, 950, 750, " PostOrden");
        arbol.dibujarBoton(990, 700, 1050, 750, " BFS");
        arbol.dibujarBoton(1100, 700, 1150, 750, " DFS");
        arbol.dibujarBoton(1250, 700, 1350, 750, " Eliminar");
        arbol.dibujarBoton(1400, 700, 1500, 750, " Salir");

        if(ismouseclick(WM_LBUTTONDOWN)){
            int mx = mousex();
            int my = mousey();
            clearmouseclick(WM_LBUTTONDOWN);

            if(arbol.esBotonClicado(50, 700, 150, 750, mx, my)){
                cout << "Ingresa un elemento: " << endl;
                str = arbol.ingresarTexto(50, 500, 150, 550);
                c = arbol.validar(str);
                if(c == 100){
                    elemento = std::stoi(str);
                    arbol.raiz = arbol.insertar(arbol.raiz, elemento);
                    cleardevice();
                    settextstyle(8, HORIZ_DIR, 1);
                    if(arbol.raiz == NULL){
                        cout << "Arbol vacio" << endl;
                        outtextxy(400, 10, const_cast<char*>("Arbol vacio"));
                    }else{
                        outtextxy(10, 50, const_cast<char*>("Antes de Rotar : "));
                        arbol.dibujarArbol(arbol.raiz, x, y);
                    }
                }else{
                    cout << "\nEntrada Invalida!" << endl;
                }
            }else if(arbol.esBotonClicado(350, 700, 450, 750, mx, my)){
                cout << "Arbol Balanceado" << endl;
                arbol.raiz = arbol.balancearArbol(arbol.raiz);
                cleardevice();
                settextstyle(8, HORIZ_DIR, 1);
                outtextxy(10, 50, const_cast<char*>("Despues de Rotar : "));
                arbol.dibujarArbol(arbol.raiz, x, y);
            }else if(arbol.esBotonClicado(550, 700, 650, 750, mx, my)){
                outtextxy(10, 270, const_cast<char*>("Pre orden: "));
                int x = 50;
                int y = 300;
                arbol.preOrden(arbol.raiz, x, y);
                cout << endl;
            }else if(arbol.esBotonClicado(700, 700, 780, 750, mx, my)){
                outtextxy(10, 270, const_cast<char*>("En orden: "));
                int x = 50;
                int y = 300;
                arbol.enOrden(arbol.raiz, x, y);
                cout << endl;
            }else if(arbol.esBotonClicado(850, 700, 950, 750, mx, my)){
                outtextxy(10, 270, const_cast<char*>("Post orden: "));
                int x = 50;
                int y = 300;
                arbol.postOrden(arbol.raiz, x, y);
                cout << endl;
            }else if(arbol.esBotonClicado(990, 700, 1050, 750, mx, my)){
                limpiarTextoArea(10, 270, 1920, 300);
                outtextxy(10, 270, const_cast<char*>("Busqueda por anchura: "));
                arbol.bfs(arbol.raiz);
                cout << endl;
            }else if(arbol.esBotonClicado(1100, 700, 1150, 750, mx, my)){
                limpiarTextoArea(10, 270, 1920, 300);
                outtextxy(10, 270, const_cast<char*>("Busqueda por profundidad: "));
                int x = 50;
                int y = 300;
                arbol.dfs(arbol.raiz, x, y);
                cout << endl;
            }else if(arbol.esBotonClicado(1250, 700, 1350, 750, mx, my)){
                cout << "Eliminar elemento del arbol" << endl;
                str = arbol.ingresarTexto(1250, 500, 1350, 550);
                c = arbol.validar(str);
                if(c == 100){
                    elemento = std::stoi(str);
                    arbol.raiz = arbol.eliminarNodo(arbol.raiz, elemento);
                    cleardevice();
                    settextstyle(8, HORIZ_DIR, 1);
                    if(arbol.raiz == NULL){
                        cout << "Arbol vacio" << endl;
                        outtextxy(400, 10, const_cast<char*>("Arbol vacio"));
                    }else{
                        arbol.dibujarArbol(arbol.raiz, x, y);
                    }
                }else{
                    cout << "\nEntrada Invalida!" << endl;
                }
            }else if(arbol.esBotonClicado(1400, 700, 1500, 750, mx, my)){
                exit(1);
            }
        }
    }

    getch();
    closegraph();
    return 0;
}
