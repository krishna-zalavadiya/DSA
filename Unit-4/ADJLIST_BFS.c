#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// ======================================================================
// NODE STRUCTURE FOR ADJACENCY LIST
// Each vertex in the graph has a linked list of its adjacent neighbors.
// Example: If 1 is connected to 2 and 3 → adjList[1] = 3 → 2 → NULL
// ======================================================================
typedef struct Node {
    int vertex;            // Stores the neighbor vertex number
    struct Node* next;     // Points to next neighbor
} Node;

// ======================================================================
// GRAPH STRUCTURE USING ADJACENCY LIST
// numVertices = number of vertices in graph
// adjList[i] = head of the linked list containing neighbors of vertex i
// ======================================================================
typedef struct {
    int numVertices;
    Node* adjList[MAX];
} GRAPH;

// ======================================================================
// CREATE A NEW NODE FOR THE ADJACENCY LIST
// ======================================================================
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;     // Store adjacent vertex
    newNode->next = NULL;    // Initially no next node
    return newNode;
}

// ======================================================================
// BUILD ADJACENCY LIST FROM USER INPUT
// Graph is UNDIRECTED → add edge v1->v2 and v2->v1
// ======================================================================
void create_adjList(GRAPH* g) {
    int edges, v1, v2;

    printf("Enter number of vertices: ");
    scanf("%d", &g->numVertices);

    // Initialize all adjacency list heads as NULL
    for (int i = 1; i <= g->numVertices; i++)
        g->adjList[i] = NULL;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (vertex1 vertex2):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &v1, &v2);

        // -------- Add v2 to v1's list (front insertion) --------
        Node* newNode = createNode(v2);
        newNode->next = g->adjList[v1];   // Link old list
        g->adjList[v1] = newNode;         // Update head

        // -------- Add v1 to v2's list (undirected graph) --------
        newNode = createNode(v1);
        newNode->next = g->adjList[v2];
        g->adjList[v2] = newNode;
    }

    printf("\nGraph created successfully!\n");
}

// ======================================================================
// DISPLAY ADJACENCY LIST
// Prints each vertex and all its connected neighbors
// ======================================================================
void display_adjList(GRAPH* g) {
    printf("\nAdjacency List Representation:\n");

    for (int i = 1; i <= g->numVertices; i++) {
        printf("Vertex %d -> ", i);
        Node* temp = g->adjList[i];

        while (temp != NULL) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// ======================================================================
// BFS CONNECTIVITY CHECK
// If BFS starting from vertex 1 can visit ALL vertices → graph connected
// queue[] = used to process vertices in BFS order (FIFO)
// visited[] = mark vertices as visited
// ======================================================================
bool bfs_is_connected(GRAPH* g) {
    int queue[MAX], front = 0, rear = 0; // BFS queue
    int visited[MAX] = {0};             // All vertices initially unvisited
    int start = 1;                       // BFS always begins at vertex 1
    int count = 1;                       // Count how many vertices visited

    // Start BFS from vertex 1
    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear) {               // While queue not empty
        int current = queue[front++];    // Dequeue
        Node* temp = g->adjList[current];

        // Traverse neighbors of current vertex
        while (temp != NULL) {
            int adjVertex = temp->vertex;

            // Visit unvisited neighbor
            if (!visited[adjVertex]) {
                queue[rear++] = adjVertex; // Enqueue
                visited[adjVertex] = 1;    // Mark visited
                count++;                   // Increase visited count
            }
            temp = temp->next;
        }
    }

    // If BFS visited ALL vertices → graph is connected
    return count == g->numVertices;
}

// ======================================================================
// BFS CYCLE DETECTION (UNDIRECTED GRAPH)
// A cycle exists if we find a visited vertex that is NOT the parent.
// parent[] keeps track of which vertex discovered which.
// ======================================================================
bool bfs_contains_cycle(GRAPH* g) {
    int queue[MAX], front, rear;
    int visited[MAX] = {0};
    int parent[MAX];

    // Initialize parent of all vertices
    for (int i = 1; i <= g->numVertices; i++) {
        parent[i] = -1;
    }

    // BFS must be applied to EACH COMPONENT (graph may be disconnected)
    for (int start = 1; start <= g->numVertices; start++) {

        if (!visited[start]) {

            front = rear = 0;
            queue[rear++] = start;
            visited[start] = 1;

            while (front < rear) {
                int current = queue[front++];
                Node* temp = g->adjList[current];

                while (temp != NULL) {
                    int adjVertex = temp->vertex;

                    if (!visited[adjVertex]) {
                        queue[rear++] = adjVertex;
                        visited[adjVertex] = 1;
                        parent[adjVertex] = current;
                    }
                    else if (adjVertex != parent[current]) {
                        // Found visited vertex that is NOT parent → cycle detected
                        return true;
                    }

                    temp = temp->next;
                }
            }
        }
    }

    return false; // No cycle found in any BFS tree
}

// ======================================================================
// BFS SHORTEST PATH (UNWEIGHTED GRAPH)
// Uses parent[] array to reconstruct path after BFS completes.
// ======================================================================
void bfs_find_path(int start, int destination, GRAPH* g) {
    int queue[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};
    int parent[MAX];               // Stores parent of each vertex in BFS tree
    bool found = false;

    // Begin BFS from the start vertex
    queue[rear++] = start;
    visited[start] = 1;
    parent[start] = -1;            // Start has no parent

    while (front < rear) {
        int current = queue[front++];

        // If we reached the destination, stop BFS
        if (current == destination) {
            found = true;
            break;
        }

        Node* temp = g->adjList[current];
        while (temp != NULL) {
            int adjVertex = temp->vertex;

            if (!visited[adjVertex]) {
                queue[rear++] = adjVertex;  // Enqueue
                visited[adjVertex] = 1;     // Mark visited
                parent[adjVertex] = current; // Set parent
            }

            temp = temp->next;
        }
    }

    // ===================== PATH RECONSTRUCTION =====================
    if (found) {
        printf("Path found: ");

        int path[MAX], path_index = 0;
        int crawl = destination;

        // Trace back from destination → start using parent[]
        while (crawl != -1) {
            path[path_index++] = crawl;
            crawl = parent[crawl];
        }

        // Print path in correct order (start → destination)
        for (int i = path_index - 1; i >= 0; i--)
            printf("%d ", path[i]);

        printf("\n");
    }
    else {
        printf("No path found from %d to %d\n", start, destination);
    }
}

// ======================================================================
// MAIN MENU DRIVER CODE
// ======================================================================
int main() {
    GRAPH g;
    int choice, start, destination;

    create_adjList(&g); // Build graph first

    while (1) {
        printf("\n============= ADJACENCY LIST - BFS OPERATIONS =============\n");
        printf("1. Check Connectivity (BFS)\n");
        printf("2. Detect Cycle (BFS)\n");
        printf("3. Find Shortest Path (BFS)\n");
        printf("4. Display Adjacency List\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            if (bfs_is_connected(&g))
                printf("The graph is connected.\n");
            else
                printf("The graph is not connected.\n");
            break;

        case 2:
            if (bfs_contains_cycle(&g))
                printf("The graph contains a cycle.\n");
            else
                printf("The graph does not contain any cycles.\n");
            break;

        case 3:
            printf("Enter start and destination vertices: ");
            scanf("%d %d", &start, &destination);
            bfs_find_path(start, destination, &g);
            break;

        case 4:
            display_adjList(&g);
            break;

        case 5:
            printf("Exiting program. Goodbye!\n");
            return 0;

        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}