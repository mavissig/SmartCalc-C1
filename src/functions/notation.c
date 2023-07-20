#include "../headers/notation.h"

static void add_node(struct list *node, const lexem_t data);
static int is_unary(const int type);
static int priority(const int current_type);

static void add_node(struct list *node, const lexem_t data) {
  if (NULL != node) {
    node->data = (lexem_t *)calloc(1, sizeof(lexem_t));
    if (NULL != node->data) {
      node->data->value = data.value;
      node->data->type = data.type;
      node->next = NULL;
    }
  }
}

struct list *insert(struct list *root, const lexem_t data) {
  if (NULL == root) {
    root = (struct list *)calloc(1, sizeof(struct list));
    add_node(root, data);
  } else {
    struct list *temp = root;
    while (NULL != temp->next) {
      temp = temp->next;
    }
    temp->next = (struct list *)calloc(1, sizeof(struct list));
    add_node(temp->next, data);
  }

  return root;
}

void remove_(struct list *list) {
  while (NULL != list) {
    struct list *temp = list;
    list = list->next;
    free(temp->data);
    temp->data = NULL;
    free(temp);
    temp = NULL;
  }
}

struct list *prefix_unary(struct list *root) {
  struct list *temp = root;
  int prev = temp->data->type;
  if (type_sum == prev || type_sub == prev) temp->data->type = is_unary(prev);
  temp = temp->next;
  while (NULL != temp) {
    const int current_type = temp->data->type;
    if (current_type == type_sum || current_type == type_sub) {
      if (type_sum == prev || type_sub == prev || type_div == prev ||
          type_mul == prev || type_pow == prev || type_bracket_l == prev ||
          type_mod == prev)
        temp->data->type = is_unary(current_type);
    }
    prev = current_type;
    temp = temp->next;
  }
  return root;
}

static int is_unary(const int type) {
  int res_type = type_init;
  if (type == type_sum) {
    res_type = type_un_plus;
  } else {
    res_type = type_un_minus;
  }
  return res_type;
}

struct list *polish_notation(struct list *root) {
  struct list *notation = NULL;
  struct stack_s *stack = NULL;
  struct list *temp = root;
  while (NULL != temp) {
    const int current_type = temp->data->type;
    if (current_type == type_value || current_type == type_x) {
      notation = insert(notation, *temp->data);
    }
    if (is_arithmetic(current_type) || is_functions(current_type) ||
        current_type == type_bracket_l) {
      if (is_arithmetic(current_type)) {
        while (NULL != stack &&
               priority(current_type) <= priority(stack->data->type) &&
               is_arithmetic(stack->data->type)) {
          lexem_t data = {.type = type_init, .value = 0.0};
          stack = pop(stack, &data);
          notation = insert(notation, data);
        }
      }
      stack = push(stack, temp->data);
    }
    if (current_type == type_bracket_r) {
      while (NULL != stack && type_bracket_l != stack->data->type) {
        lexem_t data = {.type = type_init, .value = 0.0};
        stack = pop(stack, &data);
        notation = insert(notation, data);
      }
      lexem_t data = {.type = type_init, .value = 0.0};
      stack = pop(stack, &data);
      if (NULL != stack) {
        if (is_functions(stack->data->type) && type_mod != stack->data->type) {
          lexem_t data = {.type = type_init, .value = 0.0};
          stack = pop(stack, &data);
          notation = insert(notation, data);
        }
      }
    }
    temp = temp->next;
  }
  while (NULL != stack) {
    lexem_t data = {.type = type_init, .value = 0.0};
    stack = pop(stack, &data);
    notation = insert(notation, data);
  }
  return notation;
}

int is_functions(const int current_type) {
  int is_func = FALSE;
  if (current_type == type_sqrt || current_type == type_sin ||
      current_type == type_asin || current_type == type_cos ||
      current_type == type_acos || current_type == type_tan ||
      current_type == type_atan || current_type == type_ln ||
      current_type == type_log || current_type == type_mod) {
    is_func = TRUE;
  }
  return is_func;
}

int is_arithmetic(const int current_type) {
  int is_arithm = FALSE;
  if (current_type == type_sum || current_type == type_sub ||
      current_type == type_div || current_type == type_mul ||
      current_type == type_pow || current_type == type_un_minus ||
      current_type == type_un_plus) {
    is_arithm = TRUE;
  }
  return is_arithm;
}

static int priority(const int current_type) {
  int res = 1;
  if (current_type == type_mul || current_type == type_div) {
    res = 2;
  } else if (current_type == type_pow) {
    res = 3;
  } else if (current_type == type_un_minus || current_type == type_un_plus) {
    res = 4;
  }

  return res;
}
