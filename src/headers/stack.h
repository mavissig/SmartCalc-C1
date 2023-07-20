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
 * @return struct stack_s*
 */
struct stack_s *push(struct stack_s *stack, const lexem_t *data);

/**
 * @brief функция снятия со стека
 *
 * @param stack
 * @param data
 * @return struct stack_s*
 */
struct stack_s *pop(struct stack_s *stack, lexem_t *data);

#endif  // SRC_HEADERS_STACK_H_
