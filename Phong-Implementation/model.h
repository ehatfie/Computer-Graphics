#include <vector>

struct Point {
    float x;
    float y;
    float z;

    Point() {}
    Point(float x, float y, float z): 
        x(x), y(y), z(z) {}
};

struct Color {
    float r;
    float g;
    float b;

    Color() {}
    Color(float r, float g, float b):
        r(r), g(g), b(b) {}
};

struct Material {
    float a;
    float d; 
    float s;
    float alpha;

    Material() {}
    Material(float a, float d, float s, float alpha):
        a(a), d(d), s(s), alpha(alpha) {}
};

struct Light { 
    Color color; 
    Point direction;

    Light() {}
    Light(Color c, Point p):
        color(c), direction(p) {}
};

struct Object {
    Material material;
    Color color;

    Object() {}
    Object(Material m, Color c):
        material(m), color(c) {}
};

class Model {
    public: 
        Model(Point camera, Light light, Object object);
        Model();
        ~Model();
        
        void SetCamera(Point camera);
        void SetLight(Light light);
        void SetObject(Object object);

        Color getShade(Point point, Point normal);

    private: 
       
        float getVectorLength(Point P);
        float dot(Point A, Point B);

        Point normalize(Point P);
        Point calculateVector(Point A, Point B);

        Color scaleToRGB(Color C);
        Color calculateLightIntensity();
        Color calculateLightAspect(Color lightIntensity, float multiplier);

        Point camera;
        Light light;
        Object object;
};