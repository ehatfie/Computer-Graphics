#include "model.h"
#include "math.h"
using namespace std;

Model::Model(Point camera, Light light, Object object):
    camera(camera),
    light(light),
    object(object) {}

Model::Model() {
    this->camera = Point();
    this->light = Light();
    this->object = Object();
}

Model::~Model() {
    // clean up dynamic data
}

void Model::SetCamera(Point camera) {
    this->camera = camera;
}

void Model::SetLight(Light light) {
    this->light = light;
}

void Model::SetObject(Object object) {
    this->object = object;
}

Color Model::getShade(Point point, Point normal) {
    Color lightIntensity = calculateLightIntensity();
    
    Color ambient = calculateLightAspect(lightIntensity, object.material.a);

    float multiplier_d = object.material.d * dot(light.direction, normal);
    Color diffuse = multiplier_d < 0 ? Color() : calculateLightAspect(lightIntensity, multiplier_d);
        
    Point V = normalize(calculateVector(camera, point));
    Point R = normalize(calculateVector(normal, light.direction));
    float VdotR = dot(V, R);

    float multiplier_s = VdotR < 0 ? 0 : object.material.s * pow(dot(V, R), object.material.alpha);
    Color specular = calculateLightAspect(light.color, multiplier_s);
    
    return Color(ambient.r + diffuse.r + specular.b, 
                ambient.g + diffuse.g + specular.g, 
                ambient.b + diffuse.b + specular.b);
}

Color Model::calculateLightAspect(Color lightIntensity, float multiplier) {
    return Color(multiplier * lightIntensity.r,
                 multiplier * lightIntensity.g,
                 multiplier * lightIntensity.b);
}

Color Model::calculateLightIntensity() {
    Color C = Color(light.color.r * object.color.r,
                    light.color.g * object.color.g,
                    light.color.b * object.color.b);
    return scaleToRGB(C);
}

Point Model::calculateVector(Point A, Point B) {
    return Point(A.x - B.x, A.y - B.y, A.z - B.z);
}

float Model::dot(Point A, Point B) {
    return (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
}

float Model::getVectorLength(Point P) {
    return sqrt(P.x * P.x + P.y * P.y + P.z * P.z);
}

Point Model::normalize(Point P) {
    float length = getVectorLength(P);

    if (length != 0) {
        P.x = P.x / length;
        P.y = P.y / length;
        P.z = P.z / length;
    }
    return P;
}

Color Model::scaleToRGB(Color C) {
    C.r = C.r / 255;
    C.g = C.g / 255;
    C.b = C.b / 255;
    return C;
}