#include <stdio.h>
#include <stdbool.h>

#define MAX 100   // Maximum vertices supported

/*
===========================================================
                 GRAPH STRUCTURE (Adjacency Matrix)
===========================================================

We represent graph as:

    - vertex: number of vertices
    - adjMatrix[][]: stores edges
        adjMatrix[i][j] = 1  → there is an edge between i and j
        adjMatrix[i][j] = 0  → no edge

We use 1-based indexing (vertices start from 1)
===========================================================
*/
typedef struct {
    int vertex;
    int adjMatrix[MAX][MAX];
} GRAPH;


/*
===========================================================
               CREATE + INITIALIZE ADJACENCY MATRIX
===========================================================

1. User enters number of vertices (n)
2. We initialize an n×n matrix with all 0s
3. User enters how many edges exist
4. For each edge u v:
        adjMatrix[u][v] = 1
        adjMatrix[v][u] = 1   (undirected graph) remove this line for directed graph

===========================================================
*/
void create_adjMatrix(GRAPH *g) {
    int edges, v1, v2;

    printf("Enter number of vertices: ");
    scanf("%d", &g->vertex);

    // Initialize all matrix values to 0
    for (int i = 0; i <= g->vertex; i++) {
        for (int j = 0; j <= g->vertex; j++) {
            g->adjMatrix[i][j] = 0;
        }
    }

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (vertex1 vertex2):\n");

    /*
    Example input:
        1 2
        2 3
        3 4
    Meaning: edges (1-2), (2-3), (3-4)
    */
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &v1, &v2);

        // Insert edge in adjacency matrix (undirected)
        g->adjMatrix[v1][v2] = 1;
        g->adjMatrix[v2][v1] = 1;
    }

    printf("\nGraph created successfully!\n");
}


/*
===========================================================
                  DISPLAY ADJACENCY MATRIX
===========================================================

Shows matrix like:

      1  2  3  4
  1   0  1  1  0
  2   1  0  1  1
  3   1  1  0  1
  4   0  1  1  0

Rows and columns show which vertices are connected.

===========================================================
*/
void display_adjMatrix(GRAPH *g) {

    printf("\nAdjacency Matrix Representation:\n\n  ");

    // Print column numbers
    for (int i = 1; i <= g->vertex; i++)
        printf("%3d", i);
    printf("\n");

    // Print each row
    for (int i = 1; i <= g->vertex; i++) {
        printf("%3d", i);  // Row label

        for (int j = 1; j <= g->vertex; j++) {
            printf("%3d", g->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

/*
===========================================================
                  BFS CONNECTIVITY CHECK
===========================================================

Goal:
    To check whether ALL vertices can be reached from ANY ONE vertex.

Steps:
1. Start BFS at vertex 1
2. Use queue to visit all reachable nodes
3. Count how many nodes were visited
4. If visited count == total vertices → graph is connected

===========================================================
*/

bool bfs_is_connected(GRAPH *g) {

    int queue[MAX];
    int front = 0, rear = 0;

    int visited[MAX] = {0};  // All initially unvisited
    int count = 1;           // Count how many nodes we reach

    // Start BFS from vertex 1
    queue[rear++] = 1;
    visited[1] = 1;

    while (front < rear) {
        int current = queue[front++];

        // Visit all neighbors of current
        for (int i = 1; i <= g->vertex; i++) {
            if (g->adjMatrix[current][i] == 1 && !visited[i]) {

                queue[rear++] = i;  // Add neighbor to queue
                visited[i] = 1;     // Mark visited
                count++;            // Increase count
            }
        }
    }

    // If BFS visited all vertices → graph is connected
    return (count == g->vertex);
}


/*
===========================================================
                  BFS CYCLE DETECTION
===========================================================

In BFS, a cycle exists if:

    We visit a previously visited vertex
    AND it is NOT the parent of the current vertex

Parent array helps:

Example:
    If BFS comes from 1 → 2 → 3
    but finds an edge 3 → 1
    and 1 != parent[3]
    → Cycle!

===========================================================
*/
bool bfs_contains_cycle(GRAPH *g) {

    int queue[MAX], visited[MAX], parent[MAX];
    int front, rear;

    // Initialize visited & parent arrays
    for (int i = 1; i <= g->vertex; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

    // Graph may be disconnected ⇒ BFS from each component
    for (int start = 1; start <= g->vertex; start++) {

        if (!visited[start]) {

            front = rear = 0;

            queue[rear++] = start;
            visited[start] = 1;

            while (front < rear) {

                int current = queue[front++];

                // Explore all neighbors
                for (int i = 1; i <= g->vertex; i++) {

                    if (g->adjMatrix[current][i] && !visited[i]) {

                            queue[rear++] = i;
                            visited[i] = 1;
                            parent[i] = current;
                    }
                        else if (i != parent[current]) {
                            // If visited & NOT parent → cycle detected
                            return true;
                        }
                    }
                }
            }
        }
    return false;   // No cycle detected
}


/*
===========================================================
                 BFS SHORTEST PATH BETWEEN TWO VERTICES
===========================================================

Because BFS explores level-by-level, the first time we reach
the destination, we have the SHORTEST unweighted path.

Algorithm:
-----------
1. Start BFS from 'start'
2. Maintain parent[i] = the node that led to i
3. When destination is reached, backtrack using parent[]
4. Print the path in reverse

Example:
    parent[4] = 2
    parent[2] = 1
    parent[1] = -1

Path: 1 → 2 → 4

===========================================================
*/
void bfs_find_path(int start, int destination, GRAPH *g) {

    int queue[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};
    int parent[MAX];
    bool found = false;

    // Initialize BFS
    queue[rear++] = start;
    visited[start] = 1;
    parent[start] = -1;

    /*
    BFS search until queue empties OR destination found
    */
    while (front < rear) {
        int current = queue[front++];

        if (current == destination) {
            found = true;
            break;
        }

        for (int i = 1; i <= g->vertex; i++) {
            if (g->adjMatrix[current][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
                parent[i] = current;
            }
        }
    }

    // If destination found → reconstruct and print path
    if (found) {

        printf("Shortest Path: ");

        int path[MAX], index = 0;
        int crawl = destination;

        // Backtrack using parent array
        while (crawl != -1) {
            path[index++] = crawl;
            crawl = parent[crawl];
        }

        // Print reverse (start → destination)
        for (int i = index - 1; i >= 0; i--) {
            printf("%d ", path[i]);
        }
        printf("\n");
    }
    else {
        printf("No path exists between %d and %d\n", start, destination);
    }
}


/*
===========================================================
                      MAIN MENU PROGRAM
===========================================================
Provides user options:

1. Check Connectivity
2. Detect Cycle
3. Find Shortest Path
4. Display Adjacency Matrix
5. Exit

===========================================================
*/
int main() {
    GRAPH g;
    int choice, start, destination;

    create_adjMatrix(&g);  // Initial graph setup

    while (1) {
        printf("\n===========================================\n");
        printf("      ADJACENCY MATRIX - BFS OPERATIONS\n");
        printf("===========================================\n");
        printf("1. Check Connectivity (BFS)\n");
        printf("2. Detect Cycle (BFS)\n");
        printf("3. Find Shortest Path (BFS)\n");
        printf("4. Display Adjacency Matrix\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                if (bfs_is_connected(&g))
                    printf("The graph is CONNECTED.\n");
                else
                    printf("The graph is NOT connected.\n");
                break;

            case 2:
                if (bfs_contains_cycle(&g))
                    printf("The graph contains at least ONE cycle.\n");
                else
                    printf("The graph does NOT contain any cycles.\n");
                break;

            case 3:
                printf("Enter start and destination vertices: ");
                scanf("%d %d", &start, &destination);
                bfs_find_path(start, destination, &g);
                break;

            case 4:
                display_adjMatrix(&g);
                break;

            case 5:
                printf("\nExiting program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
