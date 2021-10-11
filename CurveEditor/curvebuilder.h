#ifndef CURVEBUILDER_H
#define CURVEBUILDER_H
#include "vec.h"
#include "variables.h"
#include <QDebug>
#include "cppmath.h"

//#include <iostream>
//#include <vector>
//#include <iterator>
//#include <algorithm>
//#include <array>

//#include "vec.h"
//#include "triangle.h"
#include "delaunay.h"

class MainWindow;

class CurveBuilder
{
    double t; // Параметр кривой
    double step; // Шаг параметра
    size_t number_curve_points; // Кол-во опорных точек
    int coordinate; // Вспомогательная для Безье

    // Алгоритм де Кастельжо
    double DeCasteljo(size_t i, size_t num){
      if(!num) return 1;
      /*Vector2 a(DeCasteljoVec(i, num-1));
      Vector2 b(DeCasteljoVec(i+1, num-1));
      a*=1-t;
      b*=t;
      a+=b;*/
      return DeCasteljo(i, num-1)*(1-t)+DeCasteljo(i+1, num-1)*t;
    }

    // Алгоритм де Кастельжо
    Vector2 DeCasteljoVec(size_t i, size_t num){
      if(!num) return control_points[i];
      Vector2 a(DeCasteljoVec(i, num-1));
      Vector2 b(DeCasteljoVec(i+1, num-1));
      a*=1-t;
      b*=t;

      a+=b;
      return a;
    }

    // Вспомогательный многочлен для полинома Лагранжа
    double lagrange_mult(size_t i){
      double ret = 1.0;
      for(size_t q=i; q; --q)
          ret *= static_cast<double>(t-(q-1))/q;

      for(size_t q=control_points.size()-i-1; q; --q)
        ret *= -static_cast<double>(t-(q+i))/q;

      return ret;
    }

    CurveBuilder(size_t ptsAmount):number_curve_points(ptsAmount){
        curve_type = NoCurve;
        classification = nullptr;
    }

    ~CurveBuilder(){
        if(classification)
        delete[] classification;
    }

    // Расчёт точек предикат поворота
    void classifyRotation(){
        if(classification) delete[] classification;

        // Классификация точки относительно прямой [a,b]
        Vector2 a = control_points[0];
        Vector2 b = control_points[1];

        // Единичный направляющий вектор
        Vector2 vec(b - a);
        vec.normalize();

        // В массиве classification результат для каждой точки
        // На местах первых двух стоят два флага
        int n=static_cast<int>(control_points.size());
        classification = new int[n];

        classification[0] = abs(vec.y)<0.4; // Тип классификации в зависимости от синуса угла
        classification[1] = classification[0]?vec.x>0:vec.y<0; // Инвертируем ответ при необходимости

        for(int q=2; q < n; ++q){
            Vector2 delta = control_points[static_cast<size_t>(q)] - a;

            double det = vec.cross(delta);
            double e = (1 + delta.len()) * std::numeric_limits<double>::epsilon() * 4;
            if(abs(det)<e) classification[q] = 2; // Коллинеарны
            else classification[q] = det > 0; // Неколлинеарны
        }
    }

    // Расчёт. Точка внутри треугольника. Без граничных
    void classifyTriangle(){
        if(classification) delete[] classification;

        // Классификация точки относительно треугольника ABC
        Vector2 A = control_points[0];
        Vector2 B = control_points[1];
        Vector2 C = control_points[2];

        // Единичный направляющий вектор
        Vector2 BA(B - A);
        Vector2 CB(C - B);
        Vector2 AC(A - C);

        int n=static_cast<int>(control_points.size());
        classification = new int[n];

        for(int q=3; q < n; ++q){
            Vector2 &vec = control_points[static_cast<size_t>(q)];
            double det = BA.cross(vec - A);
            double det1 = CB.cross(vec - B);

            bool flag = det*det1>0;
            if(flag){
                double det2 = AC.cross(vec - C);
                classification[q] = flag && det2*det>0;
            }else
                classification[q]=0;
        }
    }

    bool isPointInside(const Vector2& pt){
        // Non zero winding rule
        int windingNumber = 0;    // Счётчик числа оборотов

        for (int q = 1; q <= vertices; q++) {
            Vector2 &start = control_points[static_cast<size_t>(q)-1];
            Vector2 &end = (q == vertices)?control_points[0]:control_points[static_cast<size_t>(q)];

            if (start.y <= pt.y) {
                if (end.y > pt.y) // Восходящая грань
                    if ((end-start).cross(pt-start)>0)
                        // Точка P слева от грани многоугольника
                        ++windingNumber;

            } else {
                if (end.y <= pt.y) // Нисходящая грань
                    if ((end-start).cross(pt-start)<0)
                        // Точка P справа от грани
                        --windingNumber;

            }
        }

        return windingNumber != 0;
    }

    // Расчёт. Точка внутри многоугольника
    void classifyPolygon(){
        if(classification) delete[] classification;

        // Границы многоугольника
        double maxX = control_points[0].x;
        double minX = control_points[0].x;

        double maxY = control_points[0].y;
        double minY = control_points[0].y;

        for(size_t q=1,n=static_cast<size_t>(vertices);q<n;++q){
            Vector2& vec = control_points[q];
            if(vec.x>maxX)      maxX=vec.x;
            else if(vec.x<minX) minX=vec.x;

            if(vec.y>maxY)      maxY=vec.y;
            else if(vec.y<minY) minY=vec.y;
        }

        size_t n=control_points.size();
        classification = new int[n];

        for(size_t q=static_cast<size_t>(vertices); q < n; ++q){
            Vector2 &vec = control_points[q];
            if(vec.x>maxX||vec.x<minX||vec.y>maxY||vec.y<minY)
                classification[q] = 0;
            else
                classification[q] = isPointInside(vec);
                //classification[q] = 1;
        }
    }

    void cubicSpline(){
        // Построение кубического сплайна по имеющимся узлам и производным
        const int ptsNum=70; // Кол-во опорных точек на каждой дуге
        size_t n =control_points.size();
        curve_points.resize((n-1)*ptsNum+1);
        const double step = 1.0/ptsNum;
/*
        if(0 && curve_type==CubicCurve){
            for(size_t q=0; q<n-1; ++q){
                t=0;
                for(int i=0; i<ptsNum; ++i, t += step)
                    curve_points[q*ptsNum+static_cast<size_t>(i)] =
                            (1-t)*control_points[q]+t*control_points[q+1]
                            +((-2*t+3*t*t-t*t*t)*tangent_vectors[q]+(-t+t*t*t)*tangent_vectors[q+1])*1/6.0;
            }

        }else
        */
        for(size_t q=0; q<n-1; ++q){
            t=0;

            // Вспомонательные векторы
            Vector2 delta(control_points[q+1]-control_points[q]);
            Vector2 A(tangent_vectors[q]+tangent_vectors[q+1]-2.0*delta);
            Vector2 B(-A+delta-tangent_vectors[q]);

            for(int i=0; i<ptsNum; ++i, t += step)
                curve_points[q*ptsNum+static_cast<size_t>(i)] =
                        control_points[q]+t*(tangent_vectors[q]+t*(B+t*A));

        }
        curve_points[(n-1)*ptsNum]=control_points[n-1];
    }

    void hermit(){
        // Функция присваивает значения производной в узлах

        size_t n =control_points.size();
        // Строим касательные по умолчанию
        if(tangent_vectors.size()==0){
            // Расчёт производных по соседям
            tangent_vectors.resize(n);
            for(size_t q=1; q<n-1; ++q){
              tangent_vectors[q]=(control_points[q+1]-control_points[q-1]);
              tangent_vectors[q]*=0.5;
            }

            // Производные в первой и последней точках
            tangent_vectors[0]=2*(control_points[1]-control_points[0])-tangent_vectors[1];
            tangent_vectors[n-1]=2*(control_points[n-1]-control_points[n-2])-tangent_vectors[n-2];

            tangent_ends.resize(n);
            for(size_t q=0; q<n; ++q){
              // Укорачиваем реальную длину для удобного управления
              tangent_ends[q]=control_points[q]+tangent_vectors[q]*0.4;
            }
        }else{
            // Восстанавливаем касательные из их концов
            for(size_t q=0; q<n; ++q)
              tangent_vectors[q]=(tangent_ends[q]-control_points[q])*(1.0/0.4);
        }
    }

    void cubicCurve(){ // Непрерывная вторая производная с краевыми условиями
        size_t n =control_points.size();

        double *a = new double[n-1];
        double *b = new double[n];
        double *c = new double[n-1];

        std :: vector<Vector2>f;
        f.resize(n);

        // a - диагональ под главной
        a[n-2]=0;
        for(size_t i=0;i<n-2;++i)a[i]=1;

        // c - диагональ над главной
        c[0]=0;
        for(size_t i=1;i<n-1;++i)c[i]=1;

        // b - главная диагональ
        for(size_t i=1;i<n-1;++i){
            b[i]=4;
            f[i]=(control_points[i+1]-control_points[i-1])*3.0;
        }
        b[0]=b[n-1]=1;


        // Краевые условия
        if(tangent_vectors.size()==0){
            // Стандартные краевые, если строим с нуля
            tangent_vectors.resize(n);

            //f[0]=-11.0/6*control_points[0]+3.0*control_points[1]-9.0/6*control_points[2];
            //f[n-1]=11.0/6*control_points[n-1]-3.0*control_points[n-2]+9.0/6*control_points[n-3];

            //f[0]=(control_points[1]-control_points[0])*0.5;
            //f[n-1]=(control_points[n-1]-control_points[n-2])*0.5;

            f[0]=f[n-1]=0;

        }else{
            // Восстанавливаем касательные из их концов
              tangent_vectors[0]=(tangent_ends[0]-control_points[0])*(1.0/0.4);
              tangent_vectors[n-1]=(tangent_ends[1]-control_points[n-1])*(1.0/0.4);

            // Предыдущие условия, если редактируем
            f[0]=tangent_vectors[0];
            f[n-1]=tangent_vectors[n-1];
        }

        solveMatrix (n,a,b,c,f,tangent_vectors);

        delete[] a;
        delete[] b;
        delete[] c;

        f.clear();

        tangent_ends.resize(2);
        tangent_ends[0]=control_points[0]+tangent_vectors[0]*0.4;
        tangent_ends[1]=control_points[n-1]+tangent_vectors[n-1]*0.4;

    }

/*
    void cubicCurve(){ // Непрерывная вторая производная с краевыми условиями
        size_t n =control_points.size();

        double *a = new double[n-1];
        double *b = new double[n];
        double *c = new double[n-1];

        std :: vector<Vector2>f;
        f.resize(n);

        // a - диагональ под главной
        a[n-2]=0;
        for(size_t i=0;i<n-2;++i)a[i]=1;

        // c - диагональ над главной
        c[0]=0;
        for(size_t i=1;i<n-1;++i)c[i]=1;

        // b - главная диагональ
        for(size_t i=1;i<n-1;++i){
            b[i]=4;
            f[i]=(control_points[i+1]+control_points[i-1]-2.0*control_points[i])*6.0;
        }
        b[0]=b[n-1]=1;

        tangent_vectors.resize(n);
        f[0]=f[n-1]=0;


        // Краевые условия
        if(tangent_vectors.size()==0){
            // Стандартные краевые, если строим с нуля
            tangent_vectors.resize(n);

            //f[0]=-11.0/6*control_points[0]+3.0*control_points[1]-9.0/6*control_points[2];
            //f[n-1]=11.0/6*control_points[n-1]-3.0*control_points[n-2]+9.0/6*control_points[n-3];

            //f[0]=(control_points[1]-control_points[0])*0.5;
            //f[n-1]=(control_points[n-1]-control_points[n-2])*0.5;

            f[0]=f[n-1]=0;

        }else{
            // Восстанавливаем касательные из их концов
              tangent_vectors[0]=(tangent_ends[0]-control_points[0])*(1.0/0.4);
              tangent_vectors[n-1]=(tangent_ends[1]-control_points[n-1])*(1.0/0.4);

            // Предыдущие условия, если редактируем
            f[0]=tangent_vectors[0];
            f[n-1]=tangent_vectors[n-1];
        }


        solveMatrix (n,a,b,c,f,tangent_vectors);

        delete[] a;
        delete[] b;
        delete[] c;

        f.clear();

        tangent_ends.resize(2);
        tangent_ends[0]=control_points[0]+tangent_vectors[0]*0.4;
        tangent_ends[1]=control_points[n-1]+tangent_vectors[n-1]*0.4;

    }
*/
    inline double K(size_t i){
        return (control_points[i]-control_points[i-1]).len()/
               (control_points[i+1]-control_points[i]).len();

    }

    void hermitEnergy(){ // Псевдоупругий сплайн Эрмита
        size_t n =control_points.size();

        double *a = new double[n-1];
        double *b = new double[n];
        double *c = new double[n-1];

        std :: vector<Vector2>f;
        f.resize(n);

        // a - диагональ под главной
        for(size_t i=0;i<n-1;++i)a[i]=1;

        // Вспомогательный массив
        double *k = new double[n];

        k[0]=1;
        for(size_t i=1;i<n;++i){
            k[i]=K(i);
        }

        // c - диагональ над главной
        for(size_t i=0;i<n-1;++i){
            c[i]=k[i+1]*k[i]*k[i];
        }

        // b - главная диагональ
        // f - правая часть
        for(size_t i=1;i<n-1;++i){
            b[i]=2*k[i]*(1+k[i]);
            f[i]=3.0*(control_points[i]-control_points[i-1]+(control_points[i+1]-control_points[i])*k[i]*k[i]);
        }

        delete[] k;

        b[0]=b[n-1]=2;

        f[0]=3*0*(control_points[1]-control_points[0]);
        f[n-1]=3*0*(control_points[n-1]-control_points[n-2]);

        tangent_ends.clear();
        tangent_vectors.resize(n);
        solveMatrix (n,a,b,c,f,tangent_vectors);

        delete[] a;
        delete[] b;
        delete[] c;

        f.clear();
    }

    void bldBezierCurve(){
        /*
            Метод можно ускорить вычисляя сочетания только при изменении количества точек в mainwindow.
            А также массив arrayT можно просчитывать в 2 раза реже, т.к. для любой точки из i curve_points
            есть симметричная точка number_curve_points-1-i , i от 0 до number_curve_points-1
            такая, что массив для неё зеркальный, т.е. первый эл-т меняется с последним, а в середине на месте.

            Также восстанавливать касательные надо только при их изменении.
            Тут они перерасчитываются при каждом вызове функции
        */

        size_t n = control_points.size();
        if(tangent_vectors.size()==0){
            tangent_vectors.resize(n);
            bezierWeights.resize(n);

            for(size_t q=0; q<n; ++q){
                bezierWeights[q]=bezierMAXweight; // Начальный вес максимальный
                tangent_vectors[q]=Vector2(radiusBezierMAX,0);
            }

            tangent_ends.resize(n);
            for(size_t q=0; q<n; ++q){
              // Укорачиваем реальную длину для удобного управления
              tangent_ends[q]=control_points[q]+tangent_vectors[q];
            }

        }else{
            // Восстанавливаем касательные из их концов
            for(size_t q=0; q<n; ++q){
                tangent_vectors[q]=tangent_ends[q]-control_points[q];

                double alpha = (tangent_vectors[q].len()-radiusBezierMIN)/(radiusBezierMAX-radiusBezierMIN); // от 0 до 1

                if(alpha<0)alpha=0;
                else if(alpha>1)alpha=1;

                bezierWeights[q] = bezierMAXweight*alpha + bezierMINweight*(1-alpha);
            }
        }

        // Вычисление числа сочетаний
        // Массив с сочетаниями
        size_t * array = new size_t[n];

        array[0]=1;
        for(size_t q=1;q<n;++q)
            array[q]=array[q-1]*(n-q)/q;

        // Массив с параметрами t
        double * arrayT = new double[n]; // t^i*(1-t)^n-i

        curve_points.resize(number_curve_points);
        step = 1.0 / (number_curve_points - 1);

        t=step;

        curve_points[0]=control_points[0];

        for(size_t q=1; q<number_curve_points-1; ++q, t += step){

            // Строим массив T
            arrayT[0] = pow(1-t,n-1);
            const double stp=t/(1-t);
            for(size_t i=1;i<n;++i)
                arrayT[i]=arrayT[i-1]*stp;

            // Полином бернштейна * на веса в arrayT.
            double sum = 0; // Считаем сумма для знаменателя
            for(size_t i=0;i<n;++i){
                arrayT[i]=bezierWeights[i]*array[i]*arrayT[i];
                sum+=arrayT[i];
            }


            // Кривая Безье по определению
            Vector2 point(0,0);
            for(size_t i=0;i<n;++i)
                point+=control_points[i]*arrayT[i]; // Полином Бернштейна

            curve_points[q] = point/sum;
        }
        curve_points[number_curve_points-1]=control_points[n-1];

        delete[] array;
        delete[] arrayT;
    }

    bool build(){
        switch(curve_type){
          case LagrangeCurve: // Кривая лагранжа. t[0,n-1]

            t=0;
            curve_points.resize(number_curve_points);

            step = static_cast<double>(control_points.size() - 1) / (number_curve_points - 1);

            for(size_t q=0; q < number_curve_points; ++q, t += step){
               curve_points[q].x=0;
               curve_points[q].y=0;
               for(size_t i=0,n=control_points.size(); i < n; ++i)
                 curve_points[q]+=lagrange_mult(i)*control_points[i]; // Сплайн Лагранжа
            }
            return true;

          case RationalBezierCurve: // Рациональная кривая Безье. t[0,1]
            // Массив tangent_vectors используется как веса
            bldBezierCurve();
            return true;

          case BezierCurve: // Кривая Безье. t[0,1]
            t=0;
            curve_points.resize(number_curve_points);

            step = 1.0 / (number_curve_points - 1);
            for(size_t q=0; q<number_curve_points; ++q, t += step)
                curve_points[q] = DeCasteljoVec(0, control_points.size() - 1);
            return true;

        case HermitEnergy: // Псведоупругий сплайн Эрмита.
            hermitEnergy();
            cubicSpline();
            return true;

        case HermitCurve: // Сплайн Эрмита.
            hermit();
            cubicSpline();
            return true;

        case CubicCurve: // Кубический сплайн
            cubicCurve();
            cubicSpline();
            return true;

        case Rotation: // Предикат поворота t=0,1
            curve_points.resize(2);
            curve_points[0]=control_points[0];
            curve_points[1]=control_points[1];
            classifyRotation();
            return true;

        case insideTriangle: // Точка внутри треугольника
            curve_points.resize(4);
            curve_points[3]=curve_points[0]=control_points[0];
            curve_points[1]=control_points[1];
            curve_points[2]=control_points[2];
            classifyTriangle();
            return true;

        case insidePolygon: // Точка внутри многоугольника
            curve_points.resize(static_cast<size_t>(vertices)+1);
            for(size_t q=0,n=static_cast<size_t>(vertices);q<n;++q)
                curve_points[q]=control_points[q];
            curve_points[static_cast<size_t>(vertices)]=curve_points[0];
            classifyPolygon();
            return true;

        case DelaunayTriangulation:
            triangulation.triangulate(control_points);


            return true;

        }
        return false;
    }

    friend MainWindow;
};

#endif // CURVEBUILDER_H
