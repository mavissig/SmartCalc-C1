#include "../headers/stack.h"

struct stack_s *push(struct stack_s *stack, const lexem_t *data) {
  struct stack_s *new_node =
      (struct stack_s *)calloc(1, sizeof(struct stack_s));
  if (NULL != new_node) {
    new_node->data = (lexem_t *)calloc(1, sizeof(lexem_t));
    if (NULL != new_node->data) {
      new_node->next = NULL;
      new_node->data->type = data->type;
      new_node->data->value = data->value;
      if (NULL == stack) {
        stack = new_node;
      } else {
        struct stack_s *temp = stack;
        stack = new_node;
        stack->next = temp;
      }
    }
  }

  return stack;
}

struct stack_s *pop(struct stack_s *stack, lexem_t *data) {
  if (NULL != stack) {
    data->type = stack->data->type;
    data->value = stack->data->value;
    struct stack_s *temp = stack;
    stack = stack->next;
    free(temp->data);
    temp->data = NULL;
    free(temp);
    temp = NULL;
  }
  return stack;
}