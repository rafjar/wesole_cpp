#include "moc.hpp"
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QWidget>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_point_data.h>
#include <iostream>


int main(int argc, char **argv) {
    // Inicjalizacja
    if(argc != 2) {
        std::cout << "Blad, zla liczba parametrow!" << std::endl;
        return 1;
    }

    // Wczytanie danych
    auto vec = load_data(argv[1]);
    auto [w_min, w_max, h_min, h_max] = plot_size(vec, 0.1);
    std::vector<double> x(vec->size()), y(vec->size());
    for(const auto &i : *vec) {
        x.push_back(i.first);
        y.push_back(i.second);
    }

    // Regresja
    auto [a, b] = linear_regression(vec);
    std::vector<double> reg_x(2), reg_y(2);
    reg_x[0] = *std::min_element(x.begin(), x.end());
    reg_x[1] = *std::max_element(x.begin(), x.end());
    reg_y[0] = a*reg_x[0] + b;
    reg_y[1] = a*reg_x[1] + b;

    // Główna częśść programu
    QApplication app(argc, argv);

    // Przygotowanie okienka
    QWidget window;
    window.setWindowTitle("Zadanie na ocenkę");
    window.setFixedSize(800, 800);

    // Przygotowanie wykresu
    QwtPlot plot(&window);
    plot.setTitle("Linear regression");
    plot.setAxisTitle(QwtPlot::xBottom, "Channel number");
    plot.setAxisTitle(QwtPlot::yLeft, "Voltage");
    plot.setFixedSize(775, 775);
    plot.setCanvasBackground(QBrush(Qt::white));
    plot.setAxisScale(QwtPlot::xBottom, w_min, w_max);
    plot.setAxisScale(QwtPlot::yLeft, h_min, h_max);

    // Przygotowanie serii danych
    QwtPlotCurve exp_data;
    exp_data.setRawSamples(x.data(), y.data(), x.size());
    exp_data.setStyle(QwtPlotCurve::Dots);
    exp_data.setPen(QPen(Qt::blue, 5));
    exp_data.attach(&plot);

    QwtPlotCurve reg_data;
    reg_data.setRawSamples(reg_x.data(), reg_y.data(), reg_x.size());
    reg_data.setStyle(QwtPlotCurve::Lines);
    reg_data.setPen(QPen(Qt::red, 2));
    reg_data.attach(&plot);
    
    // QComboBox
    MojBox mojBox(&window, &plot, &exp_data, &reg_data);
    QObject::connect(&mojBox, QOverload<int>::of(&MojBox::activated), &mojBox, &MojBox::changeColor);

    window.show();

    return app.exec();
}