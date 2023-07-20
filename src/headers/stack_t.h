/**
 * @file calc.h
 * @author mavissig
 * @brief В этом файле содержится структура лексем
 */
#ifndef SRC_HEADERS_STACK_T_H_
#define SRC_HEADERS_STACK_T_H_

#include "lexem_t.h"

struct stack_s {
  struct stack_s *next;
  lexem_t *data;
};

#endif  // SRC_HEADERS_STACK_T_H_
