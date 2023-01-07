// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include "queue.h"
// TODO: include any other headers you need; remove this comment
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

    Queue<Vertex*> vertexQ;

    start->visited = true;
    path.push_back(start);
    vertexQ.enqueue(start);

    cout << "Start: " << start->name << endl;

    while (path.back() != end)
    {
        Vertex* curr = vertexQ.dequeue();
        curr->setColor(GREEN);
        path.push_back(curr);

        cout << "Current: " << curr->name << endl;

        for (Vertex* near : graph.getNeighbors(curr))
        {
            if (!near->visited)
            {   // Add all the neighbors not visited to the queue
                cout << "Neighbors: " << near->name << endl;
                near->visited = true;
                near->setColor(YELLOW); // Node is in queue
                vertexQ.enqueue(near);
            }

        }




    }

    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
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
