// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
// TODO: include any other headers you need; remove this comment
using namespace std;

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end)
{
    vector<Vertex*> path;

    if (start == nullptr) return path;

    start->visited = true;
    vector<Vertex*> neighbours;

    //for (int i = 0; i < 5; ++i)
    //{
    cout << "---> " << start->toString()<< endl;
    cout << "Arcs" << start->arcs.toString() << endl;
    cout << "---> " << end->toString()<< endl;
    cout << "Arcs" << end->arcs.toString() << endl;
    //}

    Node* next = start->arcs.first()->start;



    return path;
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
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
