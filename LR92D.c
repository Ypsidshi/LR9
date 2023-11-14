#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <clocale>

#define MAX_VERTICES 100

int graph[MAX_VERTICES][MAX_VERTICES];

void addEdge(int from, int to) {
	graph[from][to] = 1;
	graph[to][from] = 1; // Учтем симметрию для неориентированного графа
}

void initializeGraph(int vertices) {
	for (int i = 0; i < vertices; ++i) {
		for (int j = 0; j < vertices; ++j) {
			graph[i][j] = 0;
		}
	}
}

void printAdjacencyList(int vertices) {
	printf("Список смежности:\n");
	for (int i = 0; i < vertices; ++i) {
		printf("%d: ", i);
		for (int j = 0; j < vertices; ++j) {
			if (graph[i][j] == 1) {
				printf("%d ", j);
			}
		}
		printf("\n");
	}
}

void dfs(int currentVertex, int vertices, bool visited[], int distances[]) {
	visited[currentVertex] = true;

	for (int i = 0; i < vertices; ++i) {
		if (graph[currentVertex][i] == 1 && !visited[i]) {
			distances[i] = distances[currentVertex] + 1;
			dfs(i, vertices, visited, distances);
		}
	}
}

void findDistancesDFS(int startVertex, int vertices, int distances[]) {
	bool visited[MAX_VERTICES] = { false };
	distances[startVertex] = 0;

	dfs(startVertex, vertices, visited, distances);
}

int main() {
	int vertices, edges;
	setlocale(LC_ALL, "Russian");


	// Введите количество вершин и рёбер
	printf("Введите количество вершин и рёбер графа: ");
	scanf("%d %d", &vertices, &edges);

	initializeGraph(vertices);

	// Заполнение списка рёбрами автоматически
	for (int i = 0; i < edges; ++i) {
		int from = rand() % vertices;
		int to;
		do {
			to = rand() % vertices;
		} while (from == to);

		addEdge(from, to);
	}

	printAdjacencyList(vertices);

	int startVertex;
	// Введите начальную вершину
	printf("Введите начальную вершину: ");
	scanf("%d", &startVertex);

	int distances[MAX_VERTICES];
	for (int i = 0; i < vertices; ++i) {
		distances[i] = INT_MAX;
	}

	findDistancesDFS(startVertex, vertices, distances);

	// Выведите расстояния от начальной вершины до всех остальных
	printf("Расстояния от вершины %d до всех остальных (по обходу в глубину):\n", startVertex);
	for (int i = 0; i < vertices; ++i) {
		if (distances[i] == INT_MAX) {
			printf("До вершины %d: Недостижима\n", i);
		}
		else {
			printf("До вершины %d: %d\n", i, distances[i]);
		}
	}

	return 0;
}