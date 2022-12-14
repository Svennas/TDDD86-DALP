/*
* Last Updated: 2022-12-13
* Gustav Svennas, gussv907
* File: fast.cpp
* ------------
* This file contains ...
* ------------
* Sources used for this file:
*/

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"

// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;

void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}

void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}

QGraphicsScene* setUpGraphics(vector<Point> points)
{
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Brute Force Pattern Recognition");
    view->show();
    return scene;
}

void sortSlopes(vector<Point>& points, vector<Point>& temp, const int left, const int right,
               const Point& origo)
{


    if (left == right) return;

    int mid = (left + right) / 2;

    // Returns at one element in points, first sort with two elements in points
    sortSlopes(points, temp, left, mid, origo);
    sortSlopes(points, temp, (mid+1), right, origo);

    for (int i = left; i <= right; ++i)
    {
        temp[i] = points[i];
    }
    // Here starts the merge operation back to the original vector.
    int i1 = left;
    int i2 = mid + 1;
    for (int curr = left; curr <= right; ++curr)
    {
        if (i1 == i2)           // If the left sublist is empty
        {
            points[curr] = temp[i2++];
        }
        else if (i2 > right)    // If the right sublist is empty
        {
            points[curr] = temp[i1++];
        }
        else if (!(origo.slopeTo(temp[i1]) > origo.slopeTo(temp[i2])))  // Get the smaller value
        {
            points[curr] = temp[i1++];
        }
        else
        {
            points[curr] = temp[i2++];
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // open file
    string filename = "input10.txt";
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    QGraphicsScene *scene = setUpGraphics(points);  // setup graphical window

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());
    auto begin = chrono::high_resolution_clock::now();

    vector<Point> others;
    vector<Point> temp;
    vector<Point> slopes;

    for (int p = 0; p < N; ++p)
    {
        for (int q = p+1; q < N; ++q)
        {
            others.push_back(points.at(q));
        }
        temp = others;
        temp.clear();
        for (int h = 0; h < others.size(); ++h) {
            cout << others[h] << " ";
        }
        cout << "" << endl;
        sortSlopes(others, temp, 0, others.size()-1, points[p]);
        for (int h = 0; h < others.size(); ++h) {
            cout << others[h] << " ";
        }
        cout << "" << endl;
        for (unsigned i = 0; i < others.size()-1; ++i)
        {
            if (points[p].slopeTo(others[i]) == points[p].slopeTo(others[i+1]))
            {
                cout << "Same slope" << endl;
                slopes.push_back(others[i]);
            }
        }
        if (temp.size() >= 3)
        {
            cout << "panda" << endl;
            for (Point pointer : slopes)
            {
                points[p].lineTo(scene, pointer);
            }

        }
    }


    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    return a.exec(); // start Qt event loop
}