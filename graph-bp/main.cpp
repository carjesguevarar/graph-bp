/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Carlos
 * GitHub repository: https://github.com/carjesguevarar/graph-bp
 *
 * Created on September 30, 2017, 9:37 AM
 */

#include <cstdlib>
#include "graphbp.h"

using namespace std;

/*
 * Main (graph-bp)
 */
int main(int argc, char** argv) {
    graphbp grafo; // Creación del objeto de tipo (graph).
    grafo.breakingPoint(); // Se determinan los nodos de ruptura del grafo.
    grafo.writeBP(); // Se escribe en el archivo de salida "ruptura.txt".
    return 0;
}

