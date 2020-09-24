#include "variables.h"

int curve_type;
int editMode;
int vertices;

bool showBrokenLine;
bool editDerivatives;

const int radiusBezierMAX=65;
const int radiusBezierMIN=25;

const double bezierMINweight=10;
const double bezierMAXweight=1000;

Delaunay triangulation;

std :: vector<Vector2> control_points;
std :: vector<Vector2> tangent_vectors;
std :: vector<double> bezierWeights;
std :: vector<Vector2> tangent_ends;
std :: vector<Vector2> curve_points;

std :: vector<Vector2> evolventCurve;
std :: vector<Vector2> evoluteCurve;

int * classification = nullptr;
