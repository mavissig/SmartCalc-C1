/**
 * @file lexem_t.h
 * @author mavissig
 *
 * @brief В этом файле объявлены структуры лексем
 */
#ifndef SRC_HEADERS_LEXEM_T_H_
#define SRC_HEADERS_LEXEM_T_H_

#include "lexem_e.h"

/**
 * @brief структура лексем
 * @param value (double) значение лексемы
 * @param type (enum) тип лексемы
 *
 */
typedef struct {
  double value;
  Type type;
} lexem_t;

#endif  // SRC_HEADERS_LEXEM_T_H_
