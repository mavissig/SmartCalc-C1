/**
 * @file calc.h
 * @author mavissig
 * @brief В этом файле содержатся объявления функций калькуляции
 */
#ifndef SRC_HEADERS_CALC_H_
#define SRC_HEADERS_CALC_H_

#include <math.h>

#include "notation.h"
#include "stack.h"
#include "utils.h"

/**
 * @brief Функция выполняет арифметические операции
 * @brief Для операций используются переменные типа lexem_t value1 и value2
 *
 * @param notation список лексем в виде польской нотации
 * @param x_value значение Х
 * @return double результат калькуляции
 */
double calculation(struct list* notation, const double x_value);

#endif  // SRC_HEADERS_CALC_H_
