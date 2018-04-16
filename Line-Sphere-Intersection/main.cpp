
//----------------------------------------------
// Purpose: Definition and implementation of the
//    Point3D, Vector3D, Ray3D and Sphere3D classes.
//
//    These classes have no private variables and
//    they have "inline" method implementations
//    so they should be used with care (since there
//    is no data hiding provided).
//    
// Author:  John Gauch and Nadine Devich
//----------------------------------------------
#include <iostream>
#include <cmath>
using namespace std;

//----------------------------------------------
class Point3D
{
public:
    float px, py, pz;

    Point3D() {}
    Point3D(float px, float py, float pz): px(px), py(py), pz(pz) {}
    Point3D(Point3D* copy): px(copy->px), py(copy->py), pz(copy->pz) {}

    void set(float x, float y, float z) {
        px = x; py = y; pz = z;
    }

    void print() {
        cout << "(" << px << "," << py << "," << pz << ")";
    }

    float distance(Point3D p) {
        return sqrt(pow(px - p.px, 2) + pow(py - p.py, 2) + pow(pz - p.pz, 2));
    }
};

//----------------------------------------------
class Vector3D
{
public:
    float vx, vy, vz;

    void set(float x, float y, float z) {
        vx = x; vy = y; vz = z;
    }

    void print() {
        cout << "(" << vx << "," << vy << "," << vz << ")";
    }

    float length() {
        return sqrt(vx * vx + vy * vy + vz * vz);
    }

    void normalize() {
        float length = this->length();

        if (length != 0) {
            vx = vx / length;
            vy = vy / length;
            vz = vz / length;
        }
    }


    float dot(Vector3D v) {
        return (vx * v.vx) + (vy * v.vy) + (v.vz * v.vz);
    }
};

//----------------------------------------------
class Ray3D
{
public:
    Point3D point;
    Vector3D dir;

    void set(Point3D p, Vector3D d) {
        point = p; dir = d;
        dir.normalize();
    }

    void set(Point3D p1, Point3D p2) {
        point = p1; dir.set(p2.px - p1.px, p2.py - p1.py, p2.pz - p1.pz);
        dir.normalize();
    }

    void print() {
        point.print(); cout << " "; dir.print();
    }

    Point3D get_sample(float t) {
        Point3D coordinate;
        coordinate.set(point.px + t * dir.vx, point.py + t*dir.vy, point.pz + t*dir.vz);
        return coordinate;
    }
};

//----------------------------------------------
class Sphere3D {
public:
    Point3D center;
    float radius;

    void set(Point3D p, float r) {
        center = p; radius = r;
    }

    void print() {
        center.print(); cout << " " << radius;
    }

    bool get_intersection(Ray3D ray, Point3D &point, Vector3D &normal) {
        Vector3D pointToCenter;
        pointToCenter.set(center.px - ray.point.px, 
                          center.py - ray.point.py, 
                          center.pz - ray.point.pz);
        cout << "ray = "; ray.print(); cout << endl;

        float b = (ray.dir.dot(pointToCenter));
        float c = pointToCenter.dot(pointToCenter) - (b * b);
        float d = sqrt((radius * radius) - c);

        float dP = b + d;
        float dM = b - d;

        if (dP < 0 && dM < 0) {
            cout << "no intersection" << endl;
            return false;
        }

        if (dP > 0 && dM > 0) {
            Point3D tempPoint1;
            Point3D tempPoint2;

            tempPoint1 = ray.get_sample(dP);
            tempPoint2 = ray.get_sample(dM);

            float dis1 = tempPoint1.distance(ray.point);
            float dis2 = tempPoint2.distance(ray.point);

            point = (dis1 < dis2) ? tempPoint1 : tempPoint2;
        } else if (dP < 0) {
            point = ray.get_sample(dM);
        } else if (dM < 0) {
            point = ray.get_sample(dP);
        } 

        normal.set((point.px - center.px), (point.py - center.py), (point.pz - center.pz));
        normal.normalize();

        cout << "normal = "; normal.print(); cout << endl;
        cout << "point = "; point.print(); cout << endl;
        return true;
    }
};


//----------------------------------------------
int main()
{
    cout << "\nTest point class\n";
    Point3D p1;
    p1.set(1, 2, 3);
    cout << "p1 = ";
    p1.print();
    cout << endl;
    Point3D p2;
    p2.set(3, 4, 5);
    cout << "p2 = ";
    p2.print();
    cout << endl;

    cout << "dist12 = " << p1.distance(p2) << endl;
    cout << "dist21 = " << p2.distance(p1) << endl;


    cout << "\nTest vector class\n";
    Vector3D v1;
    v1.set(2, 1, 0);
    cout << "v1 = ";
    v1.print();
    cout << endl;
    Vector3D v2;
    v2.set(-1, 1, 0);
    cout << "v2 = ";
    v2.print();
    cout << endl; 
    Vector3D v3;
    v3.set(-0.707107, 0.707107, 0);
    cout << "v3 = ";
    v3.print();
    cout << endl;

    cout << "v1dotv1 = " << v1.dot(v1) << endl;
    cout << "v1dotv3 = " << v1.dot(v3) << endl;
    cout << "v3dotv3 = " << v3.dot(v3) << endl;


    cout << "\nTest ray class\n";
    Ray3D r1;
    r1.set(p1, v1);
    cout << "r1 = ";
    r1.print();
    cout << endl;
    Ray3D r2;
    r2.set(p2, p1);
    cout << "r2 = ";
    r2.print();
    cout << endl;

    Point3D samp1 = r1.get_sample(0);
    Point3D samp2 = r1.get_sample(0.1);
    Point3D samp3 = r1.get_sample(0.2);
    Point3D samp4 = r1.get_sample(0.3);
    Point3D samp5 = r1.get_sample(0.4);
    Point3D samp6 = r1.get_sample(0.5);

    cout << "r1(0) = "; samp1.print(); cout << endl;
    cout << "r1(0.1) = "; samp2.print(); cout << endl;
    cout << "r1(0.2) = "; samp3.print(); cout << endl;
    cout << "r1(0.3) = "; samp4.print(); cout << endl;
    cout << "r1(0.4) = "; samp5.print(); cout << endl;
    cout << "r1(0.5) = "; samp6.print(); cout << endl;


    cout << "\nTest sphere class\n";
    Sphere3D s;
    s.set(Point3D(0, 0, 0), 2);
    cout << "s = ";
    s.print();
    cout << endl;

    Point3D p3; p3.set(-3, 0, 0);
    Point3D p4; p4.set(-2, 0, 0);
    Point3D p5; p5.set(-1, 0, 0);
    Point3D p6; p6.set(0, 0, 0);
    Point3D p7; p7.set(1, 0, 0);
    Point3D p8; p8.set(2, 0, 0);
    Point3D p9; p9.set(3, 0, 0);


    Vector3D v4; v4.set(1, 0, 0);

    Ray3D r3; 
   
    Point3D intersection;
    Vector3D normal;

    r3.set(p3, v4);
    s.get_intersection(r3, intersection, normal);

    r3.set(p4, v4);
    s.get_intersection(r3, intersection, normal);

    r3.set(p5, v4);
    s.get_intersection(r3, intersection, normal);

    r3.set(p6, v4);
    s.get_intersection(r3, intersection, normal);

    r3.set(p7, v4);
    s.get_intersection(r3, intersection, normal);

    r3.set(p8, v4);
    s.get_intersection(r3, intersection, normal);

    r3.set(p9, v4);
    s.get_intersection(r3, intersection, normal);

    return 0;
}