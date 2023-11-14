#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <queue>
#include <clocale>

#define MAX_NODES 400

// Функция для генерации случайной матрицы смежности
void generateRandomGraph(int graph[MAX_NODES][MAX_NODES], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                graph[i][j] = 0; // Нет петель
            }
            else {
                int random_value = rand() % 2; // Генерируем 0 или 1
                graph[i][j] = random_value;
                graph[j][i] = random_value; // Граф неориентированный
            }
        }
    }
}

// Функция для поиска расстояний в графе с использованием BFS
void bfs(int graph[MAX_NODES][MAX_NODES], int n, int startNode) {
    bool visited[MAX_NODES] = { false };
    int distances[MAX_NODES] = { 0 };
    std::queue<int> q;

    q.push(startNode);
    visited[startNode] = true;

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();

        for (int i = 0; i < n; i++) {
            if (graph[currentNode][i] && !visited[i]) {
                q.push(i);
                visited[i] = true;
                distances[i] = distances[currentNode] + 1;
            }
        }
    }

    // Выводим расстояния от startNode до всех остальных узлов
    for (int i = 0; i < n; i++) {
        printf("Расстояние от ребра %d до ребра %d: %d\n", startNode, i, distances[i]);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL)); // Инициализируем генератор случайных чисел

    int n; // Количество узлов в графе
    printf("Введите количество ребер в графе: ");
    scanf("%d", &n);

    int graph[MAX_NODES][MAX_NODES] = { 0 };

    generateRandomGraph(graph, n);

    // Выводим матрицу смежности
    printf("Матрица смежности графа:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    int startNode;
    printf("Введите начальный узел для поиска расстояний: ");
    scanf("%d", &startNode);

    clock_t start = clock();
    bfs(graph, n, startNode);
    clock_t end = clock();
    double time_spent5 = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time adjmatrix for search in width: %f s.\n", time_spent5);

    return 0;
}