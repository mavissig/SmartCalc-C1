#include "../headers/stack.h"

struct s21_stack_t *push(struct s21_stack_t *stack, const lexem_t *data) {
  struct s21_stack_t *new_node =
      (struct s21_stack_t *)calloc(1, sizeof(struct s21_stack_t));
  if (NULL != new_node) {
    new_node->data = (lexem_t *)calloc(1, sizeof(lexem_t));
    if (NULL != new_node->data) {
      new_node->next = NULL;
      new_node->data->type = data->type;
      new_node->data->value = data->value;
      if (NULL == stack) {
        stack = new_node;
      } else {
        struct s21_stack_t *temp = stack;
        stack = new_node;
        stack->next = temp;
      }
    }
  }

  return stack;
}

struct s21_stack_t *pop(struct s21_stack_t *stack, lexem_t *data) {
  if (NULL != stack) {
    data->type = stack->data->type;
    data->value = stack->data->value;
    struct s21_stack_t *temp = stack;
    stack = stack->next;
    free(temp->data);
    temp->data = NULL;
    free(temp);
    temp = NULL;
  }
  return stack;
}