#include "calcwindow.h"

#include <QAbstractItemView>
#include <QCompleter>
#include <QDate>
#include <QMessageBox>
#include <cmath>
#include <iostream>

#include "qcustomplot.h"
#include "ui_calcwindow.h"

extern "C" {
#include "../headers/notation.h"
#include "../headers/parser.h"
#include "../headers/validation.h"
}

CalcWindow::CalcWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CalcWindow) {
  ui->setupUi(this);

  QStringList completions = {"cos(",  "sin(", "tan(",  "ln(",   "log(",
                             "sqrt(", "mod",  "asin(", "acos(", "atan("};

  QCompleter *completer = new QCompleter(completions, this);
  completer->popup()->setFont(QFont("Arial", 24));
  completer->popup()->setStyleSheet(
      "QAbstractItemView {"
      "   color: #FF8C00;"
      "   background-color: #f6f5f4;"
      "   border: 2px solid black;"
      "   border-radius: 10px;"
      "}");
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  completer->setCompletionMode(QCompleter::PopupCompletion);
  ui->lineEdit->setCompleter(completer);

  ui->widget->setInteraction(QCP::iRangeDrag);
  ui->widget->setInteraction(QCP::iRangeZoom);
}

CalcWindow::~CalcWindow() { delete ui; }

void CalcWindow::text_color_black() {
  QPalette palette = ui->lineEdit->palette();
  palette.setColor(QPalette::Text, Qt::black);
  ui->lineEdit->setPalette(palette);
}

void CalcWindow::graph(struct list *notation) {
  double min_range = ui->min_range->value();
  double max_range = ui->max_range->value();

  if (min_range == max_range) {
    min_range = -5;
    max_range = 5;
  }

  double delta = fabs(max_range - min_range) / 100000;

  QVector<double> *coordinates_x = new QVector<double>{};
  QVector<double> *coordinates_y = new QVector<double>{};

  ui->widget->clearGraphs();
  for (double x = min_range; x <= max_range; x += delta) {
    const double y = calculation(notation, x);
    coordinates_x->push_back(x);
    coordinates_y->push_back(y);
  }

  ui->widget->addGraph();
  ui->widget->graph(0)->setData(*coordinates_x, *coordinates_y);
  ui->widget->yAxis->setRange(min_range, max_range);
  ui->widget->xAxis->setRange(min_range, max_range);
  ui->widget->replot();

  delete coordinates_x;
  delete coordinates_y;
}

void CalcWindow::on_but_1_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_1->text();
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_2_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_2->text();
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_3_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_3->text();
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_4_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_4->text();
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_5_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_5->text();
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_6_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_6->text();
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_7_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_7->text();
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_8_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_8->text();
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_9_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_9->text();
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_0_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_0->text();
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_sep_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ".";
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_eq_clicked() {
  int status = ERROR;
  QString text = ui->lineEdit->text();
  //    text.erase(std::remove(text.begin(),text.end(),' '),text.end());
  text = text.remove(QRegularExpression("\\s+"));
  struct list *root = nullptr;
  const std::string line = text.toUtf8().toStdString();
  const size_t size = line.size();
  char *data = nullptr;
  if (false ==line.empty())
  {
      status = OK;
      data = static_cast<char*>(calloc(size+1,sizeof(char)));
      for(size_t i =0; i < size;++i) {
          data[i] = line[i];
      }
      status = prevalidation(data);
      if (status == OK) {
        root = parser(data, &status);
        if (status == OK) {
          root = prefix_unary(root);
          status = validation(root);
          if (status == OK) {
            struct list *notation = polish_notation(root);
            double x_value = ui->x_value->value();
            double result = calculation(notation, x_value);

            QPalette palette = ui->lineEdit->palette();
            palette.setColor(QPalette::Text, Qt::red);
            ui->lineEdit->setPalette(palette);

            ui->lineEdit->setText(QString::number(result));
            graph(notation);
            free(data);
            data = nullptr;
          }
        }
      }
  }
  if (status != OK) {
    QMessageBox::information(this, "ERROR", "InputError");
  }
}

void CalcWindow::on_but_sum_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_sum->text();
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_sub_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_sub->text();
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_mul_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_mul->text();
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_div_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += "/";
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_brct_r_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_brct_r->text();
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_brct_l_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_brct_l->text();
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_pow_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += "^";
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_sqrt_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += "sqrt(";
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_mod_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_mod->text();
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_del_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  int cont_del = 0;
  if (text != "") {
    if (text[text.size() - 1].unicode() > 57) {
      for (int i = text.size() - 1; i >= 0 && text[i].unicode() > 57; i--) {
        cont_del++;
      }
    } else {
      cont_del = 1;
    }

    text.chop(cont_del);
    ui->lineEdit->setText(text);
  }
}

void CalcWindow::on_but_cos_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_cos->text() + "(";
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_acos_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_acos->text() + "(";
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_sin_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_sin->text() + "(";
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_asin_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_asin->text() + "(";
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_tan_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_tan->text() + "(";
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_atan_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_atan->text() + "(";
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_ln_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_ln->text() + "(";
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_log_clicked() {
  text_color_black();
  QString text = ui->lineEdit->text();
  text += ui->but_log->text() + "(";
  ui->lineEdit->setText(text);
}

void CalcWindow::on_but_calc_clicked() {
  bool type_anuit = ui->but_type_anuit->isChecked();

  double in_sum_credit = ui->in_sum->value();
  double in_percent_credit = ui->in_percent->value();
  double in_months = ui->in_months->value();

  double out_payments = 0;
  double out_percent = 0;
  double out_sum = 0;

  double percent_payments = 0;

  if (type_anuit == true) {
    double monthly_interest_rate = in_percent_credit / (100 * 12);
    out_payments = in_sum_credit *
                   ((monthly_interest_rate) /
                    (1 - pow(1 + (monthly_interest_rate), -1 * in_months)));
    out_percent = out_payments * in_months - in_sum_credit;
    out_sum = out_percent + in_sum_credit;

    ui->out_payments->setText(QString::number(out_payments, 'f', 2));
  } else {
    double first_payments = 0;
    double main_payments = 0;
    double outstanding_balance = in_sum_credit;
    QDate month = QDate::currentDate();
    main_payments = in_sum_credit / in_months;
    for (int i = 0; i < in_months; i++) {
      percent_payments = (outstanding_balance * (in_percent_credit / 100) *
                          month.daysInMonth()) /
                         month.daysInYear();
      if (i != in_months - 1) {
        out_payments = main_payments + percent_payments;
      }

      outstanding_balance -= out_payments;
      out_sum += out_payments;
      out_percent = out_sum - in_sum_credit;
      month = month.addMonths(1);

      if (i == 0) {
        first_payments = out_payments;
      }
    }
    ui->out_payments->setText(QString::number(first_payments, 'f', 2) + " | " +
                              QString::number(out_payments, 'f', 2));
  }
  ui->out_percent->setText(QString::number(out_percent, 'f', 2));
  ui->out_sum->setText(QString::number(out_sum, 'f', 2));
}
