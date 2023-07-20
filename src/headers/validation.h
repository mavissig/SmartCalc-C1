/**
 * @file calc.h
 * @author mavissig
 * @brief В этом файле содержатся объявления функций валидации
 */
#ifndef SRC_HEADERS_VALIDATION_H_
#define SRC_HEADERS_VALIDATION_H_

#include "notation.h"
#include "utils.h"

/**
 * @brief предварительная валидация
 *
 * @param src
 * @return int
 */
int prevalidation(const char *src);

/**
 * @brief основная валидация
 *
 * @param root
 * @return int
 */
int validation(const struct list *root);

/**
 * @brief проверка числа на валидность
 *
 * @param src
 * @param index
 * @return int
 */
int valid_num(const char *src, const int index);

/**
 * @brief проверка операций на валидность
 *
 * @param src
 * @param index
 * @return int
 */
int valid_operations(const char *src, const int index);

#endif  // SRC_HEADERS_VALIDATION_H_