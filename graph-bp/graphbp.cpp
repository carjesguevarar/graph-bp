/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   graphbp.cpp
 * Author: Carlos
 * GitHub repository: https://github.com/carjesguevarar/graph-bp
 * 
 * Created on September 30, 2017, 9:48 AM
 */

#include "graphbp.h"

/**
 * Contructor de la clase.
 */
graphbp::graphbp() {
    // Se lee la primera línea del archivo "mapa.txt"; se almacenan los nombres
    // en la variable (nomPla).
    readNames();
    // De acuerdo a la cantidad de nombres, es decir la cantidad de planetas, se
    // reserva memoria con la misma cantidad.
    adj = new std::list<int>[nomPla.size()];
    // Se leen las conexiones entre los nodos (planetas), en el archivo
    // "mapa.txt", también se hace un llenado de la lista de adyacencia.
    readConnections();
}

/**
 * Copy constructor.
 * 
 * @param orig
 */
graphbp::graphbp(const graphbp& orig) {
}

/**
 * Free memory
 */
graphbp::~graphbp() {
    delete[] adj;
}

/**
 * Método que agrega una conexión entre nodos.
 * 
 * @param v Nodo al que se le agrega la conexión (w).
 * @param w Conexión que se le agrega al nodo (v).
 */
void graphbp::addEdge(int v, int w) {
    adj[v].push_back(w);
}

/**
 * Método que realiza el recorrido BFS sobre el grafo, a partir de un nodo.
 * 
 * @param s Nodo desde el cual se empieza el recorrido.
 * @param visited Array que indica los nodos visitados. (true recorrido, false 
 * todo lo contrario)
 */
void graphbp::BFS(int s, bool* visited) {
    std::list<int> queue; // Cola para realizar el recorrido.
    visited[s] = true;
    queue.push_back(s); // Se encola el nodo de llegada (s).
    std::list<int>::iterator i;
    // Se realiza el ciclo "while", mientras la cola no este vacía.
    while (!queue.empty()) {
        s = queue.front();
        queue.pop_front();
        // Se realiza un ciclo "for", para todos los arcos del nodo, de dicho nodo
        // en la posición (s) de la lista de adyancencia.
        for (i = adj[s].begin(); i != adj[s].end(); ++i) {
            // Si no ha sido recorrido, se agrega como recorrido, y se encola.
            if (!visited[*i]) {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}

/**
 * Método que determina los puntos de ruptura de un grafo conexo.
 * 
 * @see isB_Point(bool* visited)
 * @see BFS(int s, bool* visited)
 */
void graphbp::breakingPoint() {
    bool* visited = new bool[nomPla.size()];
    for (int i = 0; i < nomPla.size(); i++) {
        // Condicional por el hecho en qué, el recorrido se realiza al nodo
        // siquiente, por tal razón, (i) debe ser menor al número de planetas.
        if ((i + 1) < nomPla.size()) {
            // Se coloca todos los nodos como no visitado (false).
            for (int j = 0; j < nomPla.size(); j++) {
                visited[j] = false;
            }
            // Se coloca el nodo actual como visitado.
            visited[i] = true;
            // Se aplica el recorrido BFS desde el siquiente nodo.
            BFS(i + 1, visited);
            // Se verifca si todo los nodos fueron recorridos.
            if (isBPoint(visited)) {
                // Si el nodo determina un nodo de ruptura, se guarda.
                BP.push_back(nomPla[i]);
            }
        }
    }
    delete[] visited; // Free memory.
}

/**
 * Método que verifica si fueron recorrido todos los nodos.
 * 
 * @param visited Array de nodos visitados.
 * @return True: encontró un nodo no recorrido; False: todos fueron recorridos.
 */
bool graphbp::isBPoint(bool* visited) {
    int j = 0;
    while (j < nomPla.size()) {
        if (!visited[j]) {
            return true;
        }
        j++;
    }
    return false;
}

/**
 * Método de lectura de los nombres de los nodos (planetas).
 * 
 * @see split(string str, char pattern)
 */
void graphbp::readNames() {
    std::ifstream mapNames("mapa.txt");
    std::string c = ",";
    std::string content;
    if (!mapNames.fail()) {
        std::getline(mapNames, content);
        content.erase(content.begin());
        content.erase(content.end() - 1);
        nomPla = split(content, c[0]);
    }
    mapNames.close();
}

/**
 * Método de lectura de las conexiones entre los nodos (planetas).
 * 
 * @see split(string str, char pattern)
 * @see addEdge(int v, int w)
 */
void graphbp::readConnections() {
    std::ifstream connections("mapa.txt");
    std::string c = " ";
    // Variable auxiliar que representa una fila en la matriz.
    std::vector<std::string> fila_matrix;
    // Se crea una matriz con la dimensiones de acuerdo al número planetas.
    int matrix[nomPla.size()][nomPla.size()];
    std::string content;
    if (!connections.fail()) {
        // Variable auxiliar para recorrer las columnas de la matriz.
        int j = 0;
        // Nótese que la variable (sw) sirve para empezar a hacer el proceso de
        // lectura en la segunda línea del archivo "mapa.txt".
        bool sw = false;
        while (std::getline(connections, content)) {
            if (sw == true) {
                fila_matrix = split(content, c[0]);
                for (int i = 0; i < fila_matrix.size(); i++) {
                    matrix[j][i] = std::stoi(fila_matrix[i]); // Se llena la matriz.
                }
                j++;
            } else {
                sw = true;
            }
        }
    }
    connections.close();
    // LLenado de la lista de adyacencia, de acuerdo a la matriz.
    for (int i = 0; i < nomPla.size(); i++) {
        for (int j = 0; j < nomPla.size(); j++) {
            // Se verifica si hay arco.
            if (matrix[i][j] == 1) {
                addEdge(i, j); // Se guarda el arco o conexión.
            }
        }
    }
}

/**
 * Método que divide una cadena de caracteres.
 * 
 * @param str Cadena de caracteres que será dividida.
 * @param pattern Caractér o criterio de partición.
 * @return Vector con las cadenas resultantes.
 */
std::vector<std::string> graphbp::split(std::string str, char pattern) {
    int posInit = 0, posFound = 0;
    std::string splitted;
    std::vector<std::string> result;
    while (posFound >= 0) {
        posFound = str.find(pattern, posInit);
        splitted = str.substr(posInit, posFound - posInit);
        posInit = posFound + 1;
        result.push_back(splitted);
    }
    return result;
}

/**
 * Método de escritura en el archivo de salida.
 */
void graphbp::writeBP() {
    std::ofstream ruptura("ruptura.txt");
    // Verificación si se determinaron nodos de ruptura.
    if (BP.size() != 0 && !ruptura.fail()) {
        // stringCon: Cadena donde se almacenará todos los puntos de ruptura.
        std::string stringCon = "[", diff = " ]";
        // Concatenación de las cadenas en una sola.
        for (int i = 0; i < BP.size(); i++) {
            if ((i + 1) < BP.size()) {
                stringCon = stringCon + BP[i] + ",";
            } else {
                stringCon = stringCon + BP[i] + "]";
            }
        }
        if ((stringCon[stringCon.find(diff[1])] - 1) == diff[0]) {
            stringCon.erase(stringCon.end() - 1);
        }
        if (stringCon[1] == diff[0]) {
            stringCon.erase(stringCon.begin() + 1);
        }
        // Escritura de la cadena concatenada en el archivo "ruptura.txt".
        ruptura << stringCon;
    } else {
        // Si no se econtraron nodos de rupturas.
        ruptura.clear(); // Limpieza del contenido del archivo.
    }
    ruptura.close();
}

