#include "../headers/calc.h"

double calculation(struct list* notation, const double x_value) {
  double result = 0.0;
  struct list* temp = notation;
  struct stack_s* stack = NULL;
  while (NULL != temp) {
    const int current_type = temp->data->type;
    if (current_type == type_value || current_type == type_x) {
      if (current_type == type_x) {
        temp->data->value = x_value;
      }
      stack = push(stack, temp->data);
    } else {
      if ((is_arithmetic(current_type) || current_type == type_mod) &&
          current_type != type_un_minus && current_type != type_un_plus) {
        lexem_t value1 = {.type = type_init, .value = 0.0};
        lexem_t value2 = {.type = type_init, .value = 0.0};
        stack = pop(stack, &value1);
        stack = pop(stack, &value2);
        switch (current_type) {
          case type_sum:
            result = value1.value + value2.value;
            break;
          case type_sub:
            result = value2.value - value1.value;
            break;
          case type_mul:
            result = value1.value * value2.value;
            break;
          case type_div:
            result = value2.value / value1.value;
            break;
          case type_mod:
            result = fmod(value2.value, value1.value);
            break;
          case type_pow:
            result = pow(value2.value, value1.value);
            break;
        }
      } else {
        lexem_t value = {.type = type_init, .value = 0.0};
        stack = pop(stack, &value);
        switch (current_type) {
          case type_cos:
            result = cos(value.value);
            break;
          case type_acos:
            result = acos(value.value);
            break;
          case type_sin:
            result = sin(value.value);
            break;
          case type_asin:
            result = asin(value.value);
            break;
          case type_tan:
            result = tan(value.value);
            break;
          case type_atan:
            result = atan(value.value);
            break;
          case type_log:
            result = log10(value.value);
            break;
          case type_ln:
            result = log(value.value);
            break;
          case type_sqrt:
            result = sqrt(value.value);
            break;
          case type_un_minus:
            result = -1 * value.value;
            break;
        }
      }
      const lexem_t data = {.type = type_value, .value = result};
      stack = push(stack, &data);
    }

    temp = temp->next;
  }
  if (NULL != stack) {
    lexem_t value = {.type = type_init, .value = 0.0};
    stack = pop(stack, &value);
    result = value.value;
  }

  return result;
}
