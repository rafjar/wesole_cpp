#pragma once

#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QWidget>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_point_data.h>

std::unique_ptr<std::vector<std::pair<double, double>>> load_data(std::string filename);

std::pair<double, double> linear_regression(std::unique_ptr<std::vector<std::pair<double, double>>> &pointer);

std::tuple<int, int, int, int> plot_size(std::unique_ptr<std::vector<std::pair<double, double>>> &pointer, float m);

class MojBox : public QComboBox {
    Q_OBJECT

    public:
        MojBox(QWidget* qw, QwtPlot *plot, QwtPlotCurve *exp_data, QwtPlotCurve *reg_data) : QComboBox(qw), kolory_(10), plot_(plot), exp_data_(exp_data), reg_data_(reg_data) {
            this->addItems(QStringList() << "Bialy" << "Czerwony" << "Czarny" << "Niebieski" << "Zielony" << "Zolty" << "Magenta" << "Cyjan" << "Szary" << "Ciemno niebieski");
            
            kolory_[0] = "white";
            kolory_[1] = "red";
            kolory_[2] = "black";
            kolory_[3] = "blue";
            kolory_[4] = "green";
            kolory_[5] = "yellow";
            kolory_[6] = "magenta";
            kolory_[7] = "cyan";
            kolory_[8] = "grey";
            kolory_[9] = "darkBlue";
        }
        virtual ~MojBox() {}

    private:
        std::vector<std::string> kolory_;
        QwtPlot *plot_;
        QwtPlotCurve *exp_data_, *reg_data_;


    public slots:
        void changeColor(int indx) {
            exp_data_->setPen(QPen(QColor(kolory_[indx].c_str()), 5));
            plot_->replot();
        }
    
};