#include "../headers/parser.h"

static int get_type_operations(const char sym, int *index);
static int get_type_functions(const char *src, int *index);
static double str_to_double(const char *str);

struct list *parser(const char *src, int *status) {
  struct list *root = NULL;
  for (int i = 0; '\0' != src[i];) {
    const char current_sym = src[i];
    lexem_t current_node = {.type = type_init, .value = 0.0};
    if (current_sym == '.') {
      *status = ERROR;
      break;
    }
    if (current_sym >= '0' && current_sym <= '9') {
      const double num = parsing_num(src, &i);
      if (0 == i) {
        *status = ERROR;
        break;
      }
      current_node.type = type_value;
      current_node.value = num;
    }
    if (current_sym == '+' || current_sym == '-' || current_sym == '*' ||
        current_sym == '/' || current_sym == '^' || current_sym == '(' ||
        current_sym == ')' || current_sym == 'x') {
      const int type = get_type_operations(current_sym, &i);
      current_node.type = type;
    } else if (current_node.type == type_init) {
      const int type = get_type_functions(src, &i);
      current_node.type = type;
    }
    root = insert(root, current_node);
  }
  return root;
}

double parsing_num(const char *src, int *index) {
  double result = 0.0;
  int iter = TRUE;
  int count_dot = 0;
  size_t size = 0;
  char *num = NULL;
  num = (char *)calloc(1, sizeof(char));
  while (FALSE != iter) {
    if ((src[*index] >= '0' && src[*index] <= '9') || src[*index] == '.') {
      num[size] = src[*index];
      if (src[*index] == '.') count_dot++;
      size++;
      num = (char *)realloc((void *)num, size + 1);
      num[size] = '\0';
      (*index)++;

    } else {
      iter = FALSE;
    }
  }

  if (1 >= count_dot) {
    result = str_to_double(num);
  } else {
    *index = 0;
  }

  free(num);
  num = NULL;
  return result;
}

static double str_to_double(const char *str) {
  double result = 0.0;
  double var = 10.0;
  int status_dot = FALSE;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == '.') {
      status_dot = TRUE;
    } else if (FALSE == status_dot) {
      result = result * 10 + (str[i] - 48);
    } else {
      result += (str[i] - 48) / var;
      var *= 10;
    }
  }
  return result;
}

static int get_type_operations(const char sym, int *index) {
  int type = type_init;
  switch (sym) {
    case 'x':
      type = type_x;
      break;
    case '+':
      type = type_sum;
      break;
    case '-':
      type = type_sub;
      break;
    case '*':
      type = type_mul;
      break;
    case '/':
      type = type_div;
      break;
    case '^':
      type = type_pow;
      break;
    case '(':
      type = type_bracket_l;
      break;
    case ')':
      type = type_bracket_r;
      break;
  }
  (*index)++;
  return type;
}

static int get_type_functions(const char *src, int *index) {
  int type = type_init;
  switch (src[*index]) {
    case 'm': {
      type = type_mod;
      *index += 3;
      break;
    }
    case 'c': {
      type = type_cos;
      *index += 3;
      break;
    }
    case 't': {
      type = type_tan;
      *index += 3;
      break;
    }
    case 's':
      if (src[*index + 1] == 'q') {
        type = type_sqrt;
        *index += 4;
      } else {
        type = type_sin;
        *index += 3;
      }
      break;
    case 'l':
      if (src[*index + 1] == 'n') {
        type = type_ln;
        *index += 2;
      } else {
        type = type_log;
        *index += 3;
      }
      break;
    case 'a':
      if (src[*index + 1] == 'c') {
        type = type_acos;
      } else if (src[*index + 1] == 's') {
        type = type_asin;
      } else {
        type = type_atan;
      }
      *index += 4;
      break;
  }
  return type;
}