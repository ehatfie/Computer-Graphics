#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "model.h"
using namespace std;

Model PhongShader;

ifstream input;
ofstream output;

void printOutput(Point p, Color c) {
    output << p.x << ", " << p.y << ", " << p.z << " -> ";
    output << c.r << ", " << c.g << ", " << c.b << endl;
}

void readInput() {
    Point camera;
    Light light;

    Object object;

    string data;
    if (input.is_open()) {
        while (!input.eof()) {
            getline(input, data);
            stringstream line(data);
            string word;

            line >> word;
            if (word == "Camera") {
                Point p;

                line >> p.x;
                line >> p.y;
                line >> p.z;    

                PhongShader.SetCamera(p);               
            } else if (word == "Light") {   
                Light l;

                line >> l.color.r;
                line >> l.color.g;
                line >> l.color.b;
                line >> l.direction.x;
                line >> l.direction.y;
                line >> l.direction.z;

                PhongShader.SetLight(l);
            } else if (word == "Object") {
                Object o;

                line >> o.color.r;
                line >> o.color.g;
                line >> o.color.b;
                line >> o.material.a;
                line >> o.material.d;
                line >> o.material.s;
                line >> o.material.alpha;


                PhongShader.SetObject(o);
            } else if (word == "Point") {
                Point p, n;

                cout << data;

                line >> p.x;
                line >> p.y;
                line >> p.z;
                line >> n.x;
                line >> n.y;
                line >> n.z;
                
                printOutput(p, PhongShader.getShade(p, n));
            }
        }
    }


   
}

int main()
{
    input.open("input.txt");
    output.open("output.txt");
    
    readInput();

    input.close();
    output.close();
    return 0;
}

