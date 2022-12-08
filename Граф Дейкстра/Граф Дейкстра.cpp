/*
 * Составить программу создания графа и реализовать процедуру для работы с
 * графом, определенную индивидуальным вариантом задания.
 *
 * Самостоятельно выбрать и реализовать способ представления графа в памяти.
 * В программе предусмотреть ввод с клавиатуры произвольного графа. В
 * вариантах построения остовного дерева также разработать доступный способ
 * (форму) вывода результирующего дерева на экран монитора.
 *
 *
 * Нахождение кратчайшего пути методом Дейкстра
 *
 * https://blog.skillfactory.ru/glossary/algoritm-dejkstry/
 */


#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    string Name;

    Node(string name) {
        Name = name;
    }
};

class Graph {
public:
    vector<Node> nodes;
    vector<vector<int>> matrix;

    //Добавление узла в граф
    void addNode(string name) {
        Node* node = new Node(name);

        nodes.push_back(*node);
        matrix.resize(nodes.size());
        for (int i = 0; i < nodes.size(); i++) {
            matrix[i].resize(nodes.size());
        }
    }

    //Получение индекса узла по его имени
    int getNodeIndex(string name) {
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i].Name == name) {
                return i;
            }
        }
        return -1;
    }

    //Добавление ребра в граф
    void addEdge(string from, string to, int weight) {
        int fromIndex = getNodeIndex(from);
        int toIndex = getNodeIndex(to);

        if (fromIndex == -1 || toIndex == -1) {
            cout << "Node not found" << endl;
            return;
        }

        matrix[fromIndex][toIndex] = weight;
        matrix[toIndex][fromIndex] = weight; 
    }

    //Вывод матрицы смежности
    void printMatrix() {
        cout << "  ";
        for (int i = 0; i < nodes.size(); i++) {
            cout << nodes[i].Name << " "; //Имена узлов
        }

        cout << endl;
        for (int i = 0; i < nodes.size(); i++) {
            cout << nodes[i].Name << " ";  //Имя узла

            for (int j = 0; j < nodes.size(); j++) {
                cout << matrix[i][j] << " ";  //Дистанция от узла к 
            }
            cout << endl;
        }
    }

    //Поиск кратчайшего пути
    void find(string from, string to) {
        int fromIndex = getNodeIndex(from);
        int toIndex = getNodeIndex(to);

        if (fromIndex == -1 || toIndex == -1) {
            cout << "Node not found" << endl;
            return;
        }

        // Массив для хранения кратчайших расстояний от начальной вершины до всех остальных
        vector<int> distance(nodes.size(), INT32_MAX);

        // Массив для хранения предыдущих вершин
        vector<int> visited(nodes.size(), 0);

        vector<int> prev(nodes.size(), -1);

        // Начальная вершина
        distance[fromIndex] = 0;

        // Ищем вершину с минимальным расстоянием, пока не пройдем все вершины
        for (int i = 0; i < nodes.size(); i++) {
            int minIndex = -1;
            int minDistance = INT32_MAX;

            for (int j = 0; j < nodes.size(); j++) {
                // Если вершина еще не пройдена и расстояние до нее меньше минимального
                if (!visited[j] && distance[j] < minDistance) {
                    minIndex = j;
                    minDistance = distance[j];
                }
            }

            // Если вершину не нашли
            if (minIndex == -1) {
                break;
            }

            // Помечаем вершину как пройденную
            visited[minIndex] = 1;

            // Обновляем расстояния до соседей
            for (int j = 0; j < nodes.size(); j++) {
                if (matrix[minIndex][j] != 0) {
                    if (distance[j] > distance[minIndex] + matrix[minIndex][j]) {
                        distance[j] = distance[minIndex] + matrix[minIndex][j];
                        prev[j] = minIndex;
                    }
                }
            }
        }

        // Выводим кратчайшие расстояния
        if (distance[toIndex] == INT32_MAX) {
            cout << "Path not found" << endl;
            return;
        }

        // Восстанавливаем путь
        vector<int> path;
        int index = toIndex;

        while (index != -1) {
            path.push_back(index);
            index = prev[index];
        }

        // Выводим путь
        cout << "Path: ";
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << nodes[path[i]].Name << " ";
        }
        cout << endl;
        cout << "Distance: " << distance[toIndex] << endl;
    }

};


int main() {
    Graph graph;
    graph.addNode("L");
    graph.addNode("B");
    graph.addNode("A");
    graph.addNode("N");
    graph.addNode("G");
    graph.addNode("S");
    graph.addNode("R");
    graph.addNode("D");
    graph.addNode("M");

    graph.addEdge("L", "B", 7);
    graph.addEdge("B", "A", 27);
    graph.addEdge("L", "N", 10);
    graph.addEdge("B", "G", 9);
    graph.addEdge("G", "S", 11);
    graph.addEdge("A", "M", 15);
    graph.addEdge("N", "G", 8);
    graph.addEdge("N", "R", 31);
    graph.addEdge("R", "D", 32);
    graph.addEdge("S", "D", 17);
    graph.addEdge("S", "M", 15);
    graph.addEdge("D", "M", 21);

    // Текстовое меню со всеми командами
    string menu = "1. Add node\n"
        "2. Add edge\n"
        "3. Print matrix\n"
        "4. Find path\n"
        "5. Exit\n";


    while (true) {
        cout << menu;
        int command;
        cin >> command;

        switch (command) {
        case 1: {
            string name;
            cout << "Enter node name: ";
            cin >> name;
            graph.addNode(name);
            break;
        }

        case 2: {
            string from, to;
            int weight;
            cout << "Enter from: ";
            cin >> from;
            cout << "Enter to: ";
            cin >> to;
            cout << "Enter weight: ";
            cin >> weight;
            graph.addEdge(from, to, weight);
            break;
        }

        case 3: {
            graph.printMatrix();
            break;
        }

        case 4: {
            string from, to;
            cout << "Enter from: ";
            cin >> from;
            cout << "Enter to: ";
            cin >> to;
            graph.find(from, to);
            break;
        }

        case 5: {
            return 0;
        }

        default: {
            cout << "Unknown command" << endl;
        }
        }
    }
}
