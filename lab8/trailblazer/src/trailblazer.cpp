// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include "queue.h"
#include "map.h"
#include "pqueue.h"

using namespace std;

/*
* Help function
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
            path.push_back(near);           // Add node to the recursion stack
            dFSRecursive(graph, near, end, path);
        }
        if (path.back() == end) return;
    }
    path.pop_back();
    curr->setColor(GRAY);
}

/*
*
* https://www.ida.liu.se/opendsa/Books/TDDD86F22/html/GraphTraversal.html
*/
vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end)
{
    graph.resetData();
    vector<Vertex*> path;

    if (start == nullptr) return path;

    path.push_back(start);
    dFSRecursive(graph, start, end, path);

    return path;
}

/*
*
* https://www.ida.liu.se/opendsa/Books/TDDD86F22/html/GraphTraversal.html
*/
vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end)
{
    graph.resetData();
    vector<Vertex*> path;

    if (start == nullptr) return path;

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
* Help function
*/
PriorityQueue<Vertex*> setup(BasicGraph& graph, Vertex* &start)
{
    PriorityQueue<Vertex*> costPrio;

    for (Vertex* v : graph.getNodeSet())
    {
        v->cost = POSITIVE_INFINITY;
        //costPrio.enqueue(v, v->cost);
    }
    start->cost = 0;
    costPrio.enqueue(start, start->cost);
    //costPrio.changePriority(start, start->cost);

    return costPrio;
}

/*
* Help function
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
 *
 * https://www.ida.liu.se/opendsa/Books/TDDD86F22/html/GraphShortest.html
 * https://www.ida.liu.se/~TDDD86/info/misc/fo21.pdf
 */
vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end)
{
    graph.resetData();

    PriorityQueue<Vertex*> costPrio = setup(graph, start);


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
                if (near->cost > costToNear)
                {   // Check if cost to 'near' needs to be updated
                    near->cost = costToNear;

                    if (near->previous == nullptr) costPrio.enqueue(near, costToNear);
                    else costPrio.changePriority(near, costToNear);

                    near->setColor(YELLOW);
                    near->previous = curr;
                }
            }
        }
    }
    return createPath(start, end);
}

/*
* Help function
*/
double getHeuristic(Vertex* const &curr, Vertex* const &other)
{
    return  curr->heuristic(other) + curr->cost;
}

/*
 *
 * https://www.ida.liu.se/~TDDD86/info/misc/fo21.pdf
 */
vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end)
{
    graph.resetData();

    PriorityQueue<Vertex*> costPrio = setup(graph, start);

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
                if (near->cost > costToNear)
                {   // Check if cost to 'near' needs to be updated
                    near->cost = costToNear;
                    if (near->previous == nullptr) costPrio.enqueue(near, getHeuristic(near, end));
                    else costPrio.changePriority(near, getHeuristic(near, end));

                    near->setColor(YELLOW);
                    near->previous = curr;
                }
            }
        }
    }
    return createPath(start, end);
}
