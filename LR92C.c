#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <clocale> 
#include <time.h>

#define MAX_VERTICES 400
#define INFINITY 99999

void generateRandomAdjacencyMatrix(int matrix[MAX_VERTICES][MAX_VERTICES], int numVertices, int numEdges) {
    int i, j;
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            matrix[i][j] = 0;
        }
    }

    int edgeCount = 0;
    while (edgeCount < numEdges) {
        int vertex1 = rand() % numVertices;
        int vertex2 = rand() % numVertices;

        if (vertex1 != vertex2 && matrix[vertex1][vertex2] == 0) {
            matrix[vertex1][vertex2] = 1;
            matrix[vertex2][vertex1] = 1;
            edgeCount++;
        }
    }
}

void depthFirstSearch(int matrix[MAX_VERTICES][MAX_VERTICES], bool visited[MAX_VERTICES], int distance[MAX_VERTICES], int currentVertex, int numVertices) {
    visited[currentVertex] = true;

    for (int i = 0; i < numVertices; i++) {
        if (matrix[currentVertex][i] == 1 && !visited[i]) {
            distance[i] = distance[currentVertex] + 1; // Увеличиваем расстояние на 1
            depthFirstSearch(matrix, visited, distance, i, numVertices);
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int numVertices;
    printf("Введите количество вершин в графе: ");
    scanf("%d", &numVertices);

    int numEdges;
    printf("Введите количество ребер в графе: ");
    scanf("%d", &numEdges);


    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    generateRandomAdjacencyMatrix(adjacencyMatrix, numVertices, numEdges);

    printf("Матрица смежности:\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            printf("%d ", adjacencyMatrix[i][j]);
        }
        printf("\n");
    }

    bool visited[MAX_VERTICES];
    int distance[MAX_VERTICES];
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
        distance[i] = INFINITY; // Исходно все расстояния равны бесконечности
    }

    int startVertex;
    printf("Введите стартовую вершину (от 0 до %d): ", numVertices - 1);
    scanf("%d", &startVertex);

    clock_t start = clock();
    if (startVertex >= 0 && startVertex < numVertices) {
        distance[startVertex] = 0; // Расстояние от начальной вершины до самой себя равно 0
        depthFirstSearch(adjacencyMatrix, visited, distance, startVertex, numVertices);

        printf("Результат обхода в глубину, начиная с вершины %d:\n", startVertex);
        for (int i = 0; i < numVertices; i++) {
            printf("Расстояние от вершины %d до вершины %d: %d\n", startVertex, i, distance[i]);
        }
    }
    else {
        printf("Некорректный ввод стартовой вершины.\n");
    }
    clock_t end = clock();
    double time_spent5 = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time adjmatrix for search in depth: %f s.\n", time_spent5);

    return 0;
}
