
#include "avlTree.h"
#include "avlTree.cpp"
#include <graphics.h>
#include <iostream>

using namespace std;



int main() {
    int choice, item, bf;
    int c;
    string str;
    avlTree avl;

    int gd = DETECT;
    int gm;
    initwindow(1920, 1080, "Interfaz Grafica Arbol AVL", 0, 0, false, true);

    cout << "\n---------------------" << endl;
    cout << "Implementacion Arbol AVL" << endl;
    cout << "\n---------------------" << endl;

    while (1) {

        avl.drawButton(50, 600, 150, 650, "Insertar");
        avl.drawButton(200, 600, 300, 650, "Display");
        avl.drawButton(350, 600, 450, 650, "Balancea");
        avl.drawButton(500, 600, 600, 650, "PreOrder");
        avl.drawButton(650, 600, 750, 650, "InOrder");
        avl.drawButton(800, 600, 900, 650, "PostOrder");
        avl.drawButton(950, 600, 1050, 650, "BFS");
        avl.drawButton(1100, 600, 1200, 650, "DFS");
        avl.drawButton(1250, 600, 1350, 650, "Eliminar");
        avl.drawButton(1400, 600, 1500, 650, "Salir");

        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx = mousex();
            int my = mousey();
            clearmouseclick(WM_LBUTTONDOWN);

            if (avl.isButtonClicked(50, 600, 150, 650, mx, my)) {
                cout << "Ingresa un elemento: " << endl;
                str = avl.inputText(50, 500, 150, 550);
                c = avl.validate(str);
                if (c == 100) {
                    item = std::stoi(str);
                    avl.root = avl.insert(avl.root, item);
                    cleardevice();
                    settextstyle(10, HORIZ_DIR, 3);
                    if (avl.root == NULL) {
                        cout << "Arbol vacio" << endl;
                        outtextxy(400, 10, const_cast<char*>("Arbol vacio"));
                    } else {
                        outtextxy(10, 50, const_cast<char*>("Antes de Rotar : "));
                        avl.drawTree(avl.root, x, y);
                    }
                } else {
                    cout << "\nEntrada Invalida!" << endl;
                }
            } else if (avl.isButtonClicked(200, 600, 300, 650, mx, my)) {
                cout << "Display" << endl;
                if (avl.root == NULL) {
                    cout << "Arbol vacio" << endl;
                } else {
                    avl.display(avl.root, 1);
                    cleardevice();
                    avl.drawTree(avl.root, x, y);
                }
            } else if (avl.isButtonClicked(350, 600, 450, 650, mx, my)) {
                cout << "Arbol Balanceado" << endl;
                avl.root = avl.balanceTree(avl.root);
                cleardevice();
                settextstyle(10, HORIZ_DIR, 3);
                outtextxy(10, 50, const_cast<char*>("Despues de Rotar : "));
                avl.drawTree(avl.root, x, y);
            } else if (avl.isButtonClicked(500, 600, 600, 650, mx, my)) {
                cout << "PreOrder" << endl;
                avl.preorder(avl.root);
                cout << endl;
            } else if (avl.isButtonClicked(650, 600, 750, 650, mx, my)) {
                cout << "InOrder" << endl;
                avl.inorder(avl.root);
                cout << endl;
            } else if (avl.isButtonClicked(800, 600, 900, 650, mx, my)) {
                cout << "PostOrder" << endl;
                avl.postorder(avl.root);
                cout << endl;
            } else if (avl.isButtonClicked(950, 600, 1050, 650, mx, my)) {
                cout << "Por Anchura" << endl;
                avl.bfs(avl.root);
                cout << endl;
            } else if (avl.isButtonClicked(1100, 600, 1200, 650, mx, my)) {
                cout << "Por Profundidad" << endl;
                avl.dfs(avl.root);
                cout << endl;
            } else if (avl.isButtonClicked(1250, 600, 1350, 650, mx, my)) {
                cout << "Eliminar elemento del arbol" << endl;
                str = avl.inputText(1250, 500, 1350, 550);
                c = avl.validate(str);
                if (c == 100) {
                    item = std::stoi(str);
                    avl.root = avl.deleteNode(avl.root, item);
                    cleardevice();
                    settextstyle(10, HORIZ_DIR, 3);
                    if (avl.root == NULL) {
                        cout << "Arbol vacio" << endl;
                        outtextxy(400, 10, const_cast<char*>("Arbol vacio"));
                    } else {
                        avl.drawTree(avl.root, x, y);
                    }
                } else {
                    cout << "\nEntrada Invalida!" << endl;
                }
            } else if (avl.isButtonClicked(1400, 600, 1500, 650, mx, my)) {
                exit(1);
            }
        }
    }

    getch();
    closegraph();
    return 0;
}
