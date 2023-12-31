#include <stdio.h>
#include <stdbool.h>

#define INFINITY 9999
#define MAX_NODES 100

void dijkstra(int graph[MAX_NODES][MAX_NODES], int source, int target, int numNodes) {
    int dist[MAX_NODES];
    bool visited[MAX_NODES];
    int previous[MAX_NODES];

    for (int i = 0; i < numNodes; ++i) {
        dist[i] = INFINITY;
        visited[i] = false;
        previous[i] = -1;
    }

    dist[source] = 0;

    for (int count = 0; count < numNodes - 1; ++count) {
        int minDist = INFINITY;
        int minDistNode = -1;

        for (int v = 0; v < numNodes; ++v) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                minDistNode = v;
            }
        }

        visited[minDistNode] = true;

        for (int v = 0; v < numNodes; ++v) {
            if (!visited[v] && graph[minDistNode][v] && dist[minDistNode] != INFINITY
                && dist[minDistNode] + graph[minDistNode][v] < dist[v]) {
                dist[v] = dist[minDistNode] + graph[minDistNode][v];
                previous[v] = minDistNode;
            }
        }
    }

    // Print the shortest path and its cost
    printf("Shortest path from node %d to node %d:\n", source, target);

    int currentNode = target;
    int path[MAX_NODES];
    int pathLength = 0;

    while (currentNode != -1) {
        path[pathLength++] = currentNode;
        currentNode = previous[currentNode];
    }

    if (dist[target] != INFINITY) {
        for (int i = pathLength - 1; i >= 0; --i) {
            printf("%d ", path[i]);
            if (i != 0) {
                printf("-> ");
            }
        }

        printf("\nCost: %d\n", dist[target]);
    } else {
        printf("No path exists.\n");
    }
}

int main() {
    int numNodes, source, target;
    int graph[MAX_NODES][MAX_NODES];

    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &numNodes);

    printf("Enter the adjacency matrix:\n");

    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the source node: ");
    scanf("%d", &source);

    printf("Enter the target node: ");
    scanf("%d", &target);

    dijkstra(graph, source, target, numNodes);

    return 0;
}
