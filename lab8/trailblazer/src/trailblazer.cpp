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

vector<Vertex*> createPath(Vertex* &start, Vertex* &end)
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
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end)
{
    //vector<Vertex*> path;

    //Map<Vertex*, double> costMap;

    //costMap.put(start, 0);*/

    PriorityQueue<Vertex*> costPrio;
    //costPrio.enqueue(start, 0);

    for (Vertex* v : graph.getNodeSet())
    {
        v->cost = POSITIVE_INFINITY;
        costPrio.enqueue(v, v->cost);
    }
    start->cost = 0;
    costPrio.changePriority(start, start->cost);

    Vertex* curr = start;

    while (costPrio.size() > 0)
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
                {
                    near->cost = costToNear;
                    costPrio.changePriority(near, (costToNear));
                    near->setColor(YELLOW);
                    near->previous = curr;
                }
                /*if (costMap.get(near) != POSITIVE_INFINITY)
                {
                    costPrio.changePriority(near, (near->cost + curr->cost));
                }*/
                //else {
                    //costPrio.enqueue(near, (near->cost + curr->cost));
                  //  costPrio.enqueue(near, costToNear);
                    //near->setColor(YELLOW);
                //}
                //costMap.put(near, (near->cost + curr->cost));
                //near->previous = curr;
            }
        }
    }

    return createPath(start, end);
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}
