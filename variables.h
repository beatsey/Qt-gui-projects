#ifndef VARIABLES_H
#define VARIABLES_H

#include "vec.h"
#include <vector>
#include "delaunay.h"

// Global variables

enum { NoCurve,
       BezierCurve, // Кривая Безье
       LagrangeCurve, // Сплайн Лагранжа
       CubicCurve, // Кубический сплайн (с непрерывной второй производной)
       WavySpline, // Кубический волнистый сплайн
       HermitCurve, // Сплайн Эрмита
       HermitEnergy, // Псевдоупругий сплайн Эрмита
       Rotation, // Предикат поворота
       insideTriangle, // Точка внутри треугольника
       insidePolygon, // Точка внутри многоугольника
       RationalBezierCurve, // Рациональная кривая Безье
       DelaunayTriangulation // Триангуляция Делоне
       };
extern int curve_type; // Тип кривой
extern int vertices; // Количество вершин многоугольника

enum { SetupNewControlLine, Edit, Still, EditDerrivative};
extern int editMode; // Режим работы
extern bool editDerivatives; // Редактируем производные в сплайне Эрмита

extern bool showBrokenLine; // Показывать ломаную?
extern int * classification; // Массив классификации точек для Rotation

// Максимальный и минимальный радиусы в рациональной кривой Безье
extern const int radiusBezierMAX;
extern const int radiusBezierMIN;

extern const double bezierMINweight; // минимальное значение веса
extern const double bezierMAXweight; // максимальный вес

extern Delaunay triangulation;

extern std :: vector<Vector2> control_points; // Опорные точки
extern std :: vector<Vector2> tangent_vectors; // Касательные
extern std :: vector<Vector2> tangent_ends; // Концы касательных для редактирования
extern std :: vector<Vector2> curve_points; // Точки кривой
extern std :: vector<double> bezierWeights; // Веса для рациональной кривой Безье

extern std :: vector<Vector2> evolventCurve; // Сама кривая
extern std :: vector<Vector2> evoluteCurve; // Её эволюта

#endif // VARIABLES_H
