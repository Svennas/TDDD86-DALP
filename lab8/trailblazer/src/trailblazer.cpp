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

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end)
{
    graph.resetData();
    vector<Vertex*> path;

    if (start == nullptr) return path;

    //cout << "---Current vertex--> " << start->toString()<< endl;

    path.push_back(start);
    dFSRecursive(graph, start, end, path);

    return path;
}

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

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end)
{
    /*
     * Map: put(), get(), remove(), containsKey(), keys(), values()
     *
     */
    vector<Vertex*> path;

    Map<Vertex*, double> costMap;
    for (Vertex* v : graph.getNodeSet())
    {
        costMap.put(v, POSITIVE_INFINITY);
    }
    costMap.put(start, 0);
    // ^
    // |
    // | HEEEEEEEEEEEEEEERE


    PriorityQueue<Vertex*> costPrio;
    costPrio.enqueue(start, 0);

    Vertex* curr = start;

    while (costPrio.size() > 0)
    {
        curr = costPrio.dequeue();
        curr->setColor(GREEN);
        curr->visited = true;
        for (Vertex* near : graph.getNeighbors(curr))
        {
            if (!near->visited)
            {
                near->setColor(YELLOW);
                costMap.put(near, (near->cost + curr->cost));

            }
        }
    }

    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}
