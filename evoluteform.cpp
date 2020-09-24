#include "evoluteform.h"
#include "ui_evoluteform.h"
#include <QDebug>
#include "variables.h"
#include "math_func_util.h"

EvoluteForm::EvoluteForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::evoluteform),
  initialized(false)
{
  ui->setupUi(this);

  ui->evolutetable->verticalHeader()->show();
  ui->evolutetable->horizontalHeader()->stretchLastSection();

  ui->evolutetable->setRowCount(5);

  // Начальные значения
  ui->evolutetable->setItem(0, 0, new QTableWidgetItem("cos(t)^9"));
  ui->evolutetable->setItem(1, 0, new QTableWidgetItem("sin(t)^3"));
  ui->evolutetable->setItem(2, 0, new QTableWidgetItem("0.01"));
  ui->evolutetable->setItem(3, 0, new QTableWidgetItem("-3.14"));
  ui->evolutetable->setItem(4, 0, new QTableWidgetItem("3.14"));

  ui->graphic_widget->showCircle  = ui->cBshowCircle->isChecked();
  ui->graphic_widget->showEvolute = ui->cBshowEvolute->isChecked();
  ui->graphic_widget->circlePos   = ui->sliderCircle->value();

  ready();
}

void EvoluteForm::ready() {
  initialized = true;
  parse(ui->graphic_widget->statusX, ui->graphic_widget->statusY);
  repaint();
}

EvoluteForm::~EvoluteForm() {
  delete ui;
}

#include <chrono>
class Timer {
public:

  Timer()
  {
    startTimepoint = std::chrono::high_resolution_clock::now();
  }

  ~Timer()
  {
    std::chrono::time_point<std::chrono::high_resolution_clock> endTimepoint =
      std::chrono::high_resolution_clock::now();

    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(
      startTimepoint).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(
      endTimepoint).time_since_epoch().count();

    auto   duration = end - start;
    double ms       = duration * .001;

    std::cout << ms << "ms" << std::endl;
  }

private:

  std::chrono::time_point<std::chrono::high_resolution_clock>startTimepoint;
};

void EvoluteForm::parse(bool& statusX, bool& statusY) {
  // Map with constants
  math_func::func_constants values;
  math_func::func_functions functions;

  functions["sin"] = [](const std::vector<double>& args) -> double {
                       return std::sin(args[0]);
                     };
  functions["cos"] = [](const std::vector<double>& args) -> double {
                       return std::cos(args[0]);
                     };
  functions["ln"] = [](const std::vector<double>& args) -> double {
                      return std::log(args[0]);
                    };


  // Функция
  math_func::func *fx;
  math_func::func *fy;

  // Эволюта
  math_func::func *cx;
  math_func::func *cy;

  std::string strfx =
    ui->evolutetable->model()->index(0, 0).data().toString().toUtf8().constData();
  std::string strfy =
    ui->evolutetable->model()->index(1, 0).data().toString().toUtf8().constData();

  double step  = ui->evolutetable->model()->index(2, 0).data().toDouble();
  double start = ui->evolutetable->model()->index(3, 0).data().toDouble();
  double end   = ui->evolutetable->model()->index(4, 0).data().toDouble();

  {
    Timer hey; // 3.99 ms

    fx = math_func::parse(strfx);
    fy = math_func::parse(strfy);

    statusX = fx != nullptr;
    statusY = fy != nullptr;

    if (!(statusX && statusY)) // Что-то не спарсилось
      return;

    std::cout << "x(t): " << *fx << std::endl;
    std::cout << "y(t): " << *fy << std::endl;

    // Производные
    math_func::func *dfx = math_func::derivate(fx, "t");
    math_func::func *dfy = math_func::derivate(fy, "t");

    math_func::func *optfx = math_func::optimize(dfx);
    math_func::func *optfy = math_func::optimize(dfy);

    delete dfx;
    delete dfy;

    dfx = optfx;
    dfy = optfy;

    // Вторые производные
    math_func::func *d2fx = math_func::derivate(dfx, "t");
    math_func::func *d2fy = math_func::derivate(dfy, "t");

    optfx = math_func::optimize(d2fx);
    optfy = math_func::optimize(d2fy);

    delete d2fx;
    delete d2fy;

    d2fx = optfx;
    d2fy = optfy;

    math_func::func *mult =
      math_func::div(math_func::sum(math_func::pow(dfx->copy(), 2),
                                    math_func::pow(dfy->copy(),
                                                   2)),
                     math_func::sub(math_func::mul(dfx->copy(),
                                                   d2fy),
                                    math_func::mul(d2fx,
                                                   dfy->copy())));

    math_func::func *f = optimize(mult);
    delete mult;

    cx   = sub(fx->copy(), mul(dfy, f->copy()));
    mult = optimize(cx);
    delete cx;
    cx = mult;

    cy   = sum(fy->copy(), mul(dfx, f->copy()));
    mult = optimize(cy);
    delete cy;
    cy = mult;

    delete f;

    std::cout << "cx(t): " << *cx << std::endl;
    std::cout << "cy(t): " << *cy << std::endl;

    // Подкорректировали размер шага
    int N = (end - start) / step;
    step = (end - start) / N;

    evolventCurve.resize(N);
    evoluteCurve.resize(N);

    double t = start;

    for (int i = 0; i < N; ++i, t += step) {
      values["t"]        = t;
      evolventCurve[i].x = fx->evaluate(values, functions);
      evolventCurve[i].y = fy->evaluate(values, functions);

      evoluteCurve[i].x = cx->evaluate(values, functions);
      evoluteCurve[i].y = cy->evaluate(values, functions);

      if (i == 0) {
        std::cout << "cx(0): " << evoluteCurve[i].x << std::endl;
        std::cout << "cy(0): " << evoluteCurve[i].y << std::endl;
      }
    }

    std::cout << std::endl;

    delete fx;
    delete fy;
    delete cx;
    delete cy;
  }
}

void EvoluteForm::on_evolutetable_cellChanged(int row, int column) {
  if (initialized) parse(ui->graphic_widget->statusX,
                         ui->graphic_widget->statusY);
  repaint();
}

void EvoluteForm::on_cBshowCircle_clicked(bool checked) {
  ui->graphic_widget->showCircle = checked;
  repaint();
}

void EvoluteForm::on_cBshowEvolute_clicked(bool checked) {
  ui->graphic_widget->showEvolute = checked;
  repaint();
}

void EvoluteForm::on_sliderCircle_valueChanged(int value) {
  ui->graphic_widget->circlePos = value;
  repaint();
}
