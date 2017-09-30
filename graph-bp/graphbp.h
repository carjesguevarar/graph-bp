/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   graphbp.h
 * Author: Carlos
 * GitHub repository: https://github.com/carjesguevarar/graph-bp
 *
 * Created on September 30, 2017, 9:48 AM
 */

#ifndef GRAPHBP_H
#define GRAPHBP_H
#include <fstream>
#include <list>
#include <vector>
#include <string>

class graphbp {
public:
    graphbp();
    graphbp(const graphbp& orig);
    virtual ~graphbp();
    void breakingPoint();
    void writeBP();
private:
    bool isBPoint(bool* visited);
    void BFS(int s, bool* visited);
    std::list<int>* adj; // Lista de adyacencia.
    std::vector<std::string> BP; // Contenedor de nodos determinados como nodo de ruptura.
    std::vector<std::string> split(std::string str, char pattern);
    std::vector<std::string> nomPla; // Contenedor de los nombres de los nodos (planetas).
    void addEdge(int v, int w);
    void readNames();
    void readConnections();
};

#endif /* GRAPHBP_H */

