/**
 * @file notation.h
 * @author mavissig
 * @brief В этом файле объявлены функции для нотации
 */
#ifndef SRC_HEADERS_NOTATION_H_
#define SRC_HEADERS_NOTATION_H_

#include "lexem_t.h"
#include "stack.h"
#include "utils.h"

/**
 * @brief структура списка
 * @param next указатель на следующий элемент списка
 * @param data данные о лексеме находящейся в элементе списка
 *
 */
struct list {
  struct list *next;
  lexem_t *data;
};

void remove_(struct list *list);
struct list *insert(struct list *list, const lexem_t data);
struct list *prefix_unary(struct list *root);
struct list *polish_notation(struct list *root);
int is_functions(const int current_type);
int is_arithmetic(const int current_type);

#endif  // SRC_HEADERS_NOTATION_H_
