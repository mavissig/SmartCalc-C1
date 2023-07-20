/**
 * @file calc.h
 * @author mavissig
 * @brief В этом файле содержатся объявления функций для работы со стеком
 */
#ifndef SRC_HEADERS_STACK_H_
#define SRC_HEADERS_STACK_H_

#include "stack_t.h"
#include "utils.h"

/**
 * @brief функция добавления в стек
 *
 * @param stack
 * @param data
 * @return struct s21_stack_t*
 */
struct s21_stack_t *push(struct s21_stack_t *stack, const lexem_t *data);

/**
 * @brief функция снятия со стека
 *
 * @param stack
 * @param data
 * @return struct s21_stack_t*
 */
struct s21_stack_t *pop(struct s21_stack_t *stack, lexem_t *data);

#endif  // SRC_HEADERS_STACK_H_
