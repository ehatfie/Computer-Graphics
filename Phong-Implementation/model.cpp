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
    this->object.color = Color();
    this->object.material = Material();
}

void Model::SetCamera(Point camera) {
    this->camera = camera;
}

void Model::SetLight(Light light) {
    this->light.color = light.color;
    this->light.direction = normalize(light.direction);
}

void Model::SetObject(Object object) {
    this->object = object;
}

Color Model::getShade(Point point, Point normal) {
    Color lightIntensity = calculateLightIntensity();
    
    Point V = normalize(calculateVector(camera, point));
    Point R = normalize(calculateVector(normalize(normal), light.direction));

    float VdotR = dot(V, R);
    float LdotN = dot(light.direction, normalize(normal));

    float multiplier_d = LdotN < 0 ? 0 : object.material.d * LdotN;
    float multiplier_s = VdotR < 0 ? 0 : object.material.s * pow(dot(V, R), object.material.alpha);
    
    Color ambient = calculateLightAspect(lightIntensity, object.material.a);
    Color diffuse = calculateLightAspect(lightIntensity, multiplier_d);
    Color specular = calculateLightAspect(light.color, multiplier_s);
    
    return Color(ambient.r + diffuse.r + specular.r, 
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