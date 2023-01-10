/*
* Last Updated: 2023-01-09
* Gustav Svennas, gussv907
* File: trailblazer.cpp
* ------------
* This file contains all the functions used by the program to traverse
* the graphs and terrains and search for the given 'end' vertex.
* There are 4 'main' functions which each uses a special algorithm:
* - Depth-first search (DFS)
* - Breadth-first search (BFS)
* - Dijkstra’s algorithm
* - The A*-algorithm
* The file also contains help functions for all the 'main' functions.
* ------------
* Sources used for this file:
* https://www.ida.liu.se/opendsa/Books/TDDD86F22/html/GraphTraversal.html
* https://www.ida.liu.se/~TDDD86/info/misc/fo20.pdf
* https://www.ida.liu.se/opendsa/Books/TDDD86F22/html/GraphShortest.html
* https://www.ida.liu.se/~TDDD86/info/misc/fo21.pdf
*/

#include "costs.h"
#include "trailblazer.h"
#include "queue.h"
#include "pqueue.h"

using namespace std;

/*
* Help function to the depthFirstSearch() function.
* This function recursively goes through the given graph until the end Vertex has
* been found.
* The function uses the 'Depth-first search' algorithm, which goes through the graph
* by following one branch at a time down to its conclusion before backtracking
* back to the next branch. The search stops when the 'end' Vertex has been found.
*
* Source used: https://www.ida.liu.se/opendsa/Books/TDDD86F22/html/GraphTraversal.html
*/
void dFSRecursive(BasicGraph& graph, Vertex* curr, Vertex* end, vector<Vertex*>& path)
{
    curr->visited = true;
    curr->setColor(GREEN);
    if (path.back() == end) return;

    for (Vertex* near : graph.getNeighbors(curr))
    {
        if (!near->visited)
        {
            path.push_back(near);           // Add node to the recursion stack (path)
            dFSRecursive(graph, near, end, path);
        }
        if (path.back() == end) return;
    }
    path.pop_back();
    curr->setColor(GRAY);       // This path led nowhere, color the Vertex gray
}

/*
* Main function for 'Depth-first search' which use used to traverse graphs
* and terrains in the program.
* This function calls on the help function dFSRecursive() which uses the
* 'Depth-first search' algorithm to find the 'end' Vertex.
*
* Returns the path from the Vertex 'start' to the Vertex 'end'.
*/
vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end)
{
    graph.resetData();
    vector<Vertex*> path;

    path.push_back(start);
    dFSRecursive(graph, start, end, path);

    return path;
}

/*
* Main function for 'Breadth-first search' which use used to traverse graphs
* and terrains in the program.
* The function uses the 'Breadth-first search' algorithm, which goes through all
* the connecting vertices (all the neighbors) before going to deeper vertices in
* the graph. The search stops when the 'end' Vertex has been found.
*
* Source used: https://www.ida.liu.se/opendsa/Books/TDDD86F22/html/GraphTraversal.html
*/
vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end)
{
    graph.resetData();
    vector<Vertex*> path;

    Queue<vector<Vertex*>> pathQueue;

    start->visited = true;
    path.push_back(start);
    pathQueue.enqueue(path);

    while (pathQueue.size() > 0)
    {
        path  = pathQueue.dequeue();
        Vertex* curr = path.back();
        curr->setColor(GREEN);

        if (path.back() == end) break;

        for (Vertex* near : graph.getNeighbors(curr))
        {
            if (!near->visited)
            {   // Add all the neighbors not visited with a new path to the queue
                near->visited = true;          // Mark Vertex 'near'
                near->setColor(YELLOW);
                vector<Vertex*> newPath = path;
                newPath.push_back(near);       // Add the edge to path
                pathQueue.enqueue(newPath);    // Enqueue the new path
            }
        }
    }
    return path;
}

/*
* Help function (used by dijkstrasAlgorithm() and aStar()).
*
* This function sets up an priority queue and adds the starting vertex to it.
* Also gives all the vertices in the graph the cost POSITIVE_INFINITY,
* which is used in both Dijkstra and A*.
* Returns the priority queue costPrio, to be containing vertices.
*/
PriorityQueue<Vertex*> setup(BasicGraph& graph, Vertex* start)
{
    PriorityQueue<Vertex*> costPrio;

    for (Vertex* v : graph.getNodeSet())
    {
        v->cost = POSITIVE_INFINITY;
    }
    start->cost = 0;
    costPrio.enqueue(start, start->cost);

    return costPrio;
}

/*
* Help function.
*
* This function returns a heuristic value for the cost between
* the two given vertices.
*/
double getHeuristic(Vertex* const curr, Vertex* const other)
{
    return  curr->heuristic(other) + curr->cost;
}

/*
* Help function (used by dijkstrasAlgorithm() and aStar()).
*
* This function uses Dijkstra’s algorithm to search through the given graph or terrain
* to find the end vertex.
* Dijkstra’s algorithm is similar to BFS in that it goes through all the connecting vertices
* (all the neighbors) before going to deeper. Difference is that Dijkstra uses a priority
* queue and constantly updates the cost to reach each vertex from the starting vertex.
* With this the algorithm can always search from the most promising vertex.
*
* This algorithm can also choose to use heuristic values for all the vertices in the
* priority queue (used by A*).
*
* Sources used:
* https://www.ida.liu.se/opendsa/Books/TDDD86F22/html/GraphShortest.html
* https://www.ida.liu.se/~TDDD86/info/misc/fo21.pdf
*/
void dijkstraSearch(BasicGraph& graph, Vertex* start, Vertex* end, PriorityQueue<Vertex*>& costPrio, bool const useHeur)
{
    Vertex* curr = start;

    while (!costPrio.isEmpty())
    {
        curr = costPrio.dequeue();
        curr->setColor(GREEN);
        curr->visited = true;

        if (curr == end) break;

        for (Vertex* near : graph.getNeighbors(curr))
        {
            if (!near->visited)
            {
                double costToNear = curr->cost + graph.getEdge(curr, near)->cost;

                if (near->cost > costToNear)    // Check if cost to 'near' needs to be updated
                {
                    near->cost = costToNear;

                    if (useHeur) costToNear = getHeuristic(near, end);  // Check if a heuristic value should be used (A*)

                    if (near->previous == nullptr) costPrio.enqueue(near, costToNear);  // Not in prio queue

                    else costPrio.changePriority(near, costToNear);     // Already in prio queue, update prio value

                    near->setColor(YELLOW);
                    near->previous = curr;
                }
            }
        }
    }
}

/*
* Help function (used by dijkstrasAlgorithm() and aStar()).
*
* This function creates a path from the start vertex to the end vertex.
* Adds all the vertices between the given vertices to path using previous.
* The order of all the vertices in the path is then flipped so that 'start'
* is first.
* Returns the vector path.
*/
vector<Vertex*> createPath(Vertex* const start, Vertex* const end)
{
    vector<Vertex*> path;
    Vertex* temp = end;
    Vertex* prev = end->previous;
    path.push_back(end);

    while (temp != start)
    {
        path.push_back(prev);
        temp = prev;
        prev = temp->previous;
    }
    vector<Vertex*> tempPath = path;
    path.clear();
    for (unsigned i = tempPath.size(); i > 0; --i)
    {
        path.push_back(tempPath[i-1]);
    }
    return path;
}

/*
* Main function for 'Dijkstra’s algorithm' which use used to traverse graphs
* and terrains in the program.
* This function calls on the help function dijkstraSearch() which uses the
* Dijkstra’s algorithm to find the 'end' Vertex.
*
* Also uses the help functions setup() and createPath().
*
* Returns the path from the Vertex 'start' to the Vertex 'end'.
*/
vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end)
{
    graph.resetData();

    PriorityQueue<Vertex*> costPrio = setup(graph, start);

    dijkstraSearch(graph, start, end, costPrio, false);

    return createPath(start, end);
}



/*
* Main function for 'A* Search' which use used to traverse graphs
* and terrains in the program.
* This function calls on the help function dijkstraSearch() which uses the
* Dijkstra’s algorithm to find the 'end' Vertex. Furthermore, this functions makes
* sure that the help function dijkstraSearch() uses heuristic values for the prio queue.
*
* Also uses the help functions setup() and createPath().
*
* Returns the path from the Vertex 'start' to the Vertex 'end'.
*/
vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end)
{
    graph.resetData();

    PriorityQueue<Vertex*> costPrio = setup(graph, start);

    dijkstraSearch(graph, start, end, costPrio, true);

    return createPath(start, end);
}
