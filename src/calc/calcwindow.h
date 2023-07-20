#ifndef CALCWINDOW_H
#define CALCWINDOW_H

#include <QMainWindow>

extern "C" {
    #include "../headers/calc.h"
}


QT_BEGIN_NAMESPACE
namespace Ui { class CalcWindow; }
QT_END_NAMESPACE

class CalcWindow : public QMainWindow
{
    Q_OBJECT

public:
    CalcWindow(QWidget *parent = nullptr);
    ~CalcWindow();

private slots:
    void text_color_black();

    void graph(struct list*notation);

    void on_but_1_clicked();

    void on_but_2_clicked();

    void on_but_3_clicked();

    void on_but_4_clicked();

    void on_but_5_clicked();

    void on_but_6_clicked();

    void on_but_7_clicked();

    void on_but_8_clicked();

    void on_but_9_clicked();

    void on_but_0_clicked();

    void on_but_sep_clicked();

    void on_but_eq_clicked();

    void on_but_sum_clicked();

    void on_but_sub_clicked();

    void on_but_mul_clicked();

    void on_but_div_clicked();

    void on_but_brct_r_clicked();

    void on_but_brct_l_clicked();

    void on_but_pow_clicked();

    void on_but_sqrt_clicked();

    void on_but_mod_clicked();

    void on_but_del_clicked();

    void on_but_cos_clicked();

    void on_but_acos_clicked();

    void on_but_sin_clicked();

    void on_but_asin_clicked();

    void on_but_tan_clicked();

    void on_but_atan_clicked();

    void on_but_ln_clicked();

    void on_but_log_clicked();

    void on_but_calc_clicked();

private:
    Ui::CalcWindow *ui;
};
#endif // CALCWINDOW_H
