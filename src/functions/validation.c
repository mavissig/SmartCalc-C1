#include "../headers/validation.h"

static int check_bracket(const char* src);
static int check_forbidden_symbol(const char* src);

static int check_sqrt(const char* src, int* index);
static int check_mod(const char* src, int* index);
static int check_cos(const char* src, int* index);
static int check_sin(const char* src, int* index);
static int check_tan(const char* src, int* index);
static int check_log(const char* src, int* index);
static int check_ln(const char* src, int* index);
static int check_functions_name(const char* src);

int prevalidation(const char* src) {
  int status = OK;
  status = check_bracket(src);
  if (OK == status) status = check_forbidden_symbol(src);
  if (OK == status) status = check_functions_name(src);
  return status;
}

int validation(const struct list* root) {
  int status = OK;
  struct list* temp = (struct list*)root;
  int prev = temp->data->type;
  if (type_mul == prev || type_div == prev || type_pow == prev ||
      type_mod == prev)
    status = ERROR;
  temp = temp->next;
  while (NULL != temp) {
    const int current_type = temp->data->type;
    if (current_type == type_sum || current_type == type_sub ||
        current_type == type_div || current_type == type_mul ||
        current_type == type_pow || current_type == type_mod ||
        current_type == type_bracket_r) {
      if (type_value != prev && type_x != prev && type_bracket_r != prev) {
        status = ERROR;
        break;
      }
    }
    if (current_type == type_value || current_type == type_x ||
        current_type == type_sqrt || current_type == type_sin ||
        current_type == type_asin || current_type == type_cos ||
        current_type == type_acos || current_type == type_tan ||
        current_type == type_atan || current_type == type_ln ||
        current_type == type_log || current_type == type_bracket_l) {
      if (type_value == prev || type_x == prev || type_bracket_r == prev) {
        status = ERROR;
        break;
      }
    }
    prev = current_type;
    temp = temp->next;
  }

  return status;
}

static int check_bracket(const char* src) {
  int condition = 0;
  for (int i = 0; src[i] != '\0'; i++) {
    if (src[i] == '(') {
      condition++;
    }
    if (src[i] == ')') {
      condition--;
      if (0 > condition) {
        break;
      }
    }
  }
  return (0 != condition) ? ERROR : OK;
}

int check_forbidden_symbol(const char* src) {
  int status = OK;
  for (int i = 0; src[i] != '\0' && status == OK; i++) {
    status = valid_num(src, i) && valid_operations(src, i);
  }
  return status;
}

int valid_num(const char* src, const int index) {
  int status = OK;
  if ((src[index] < '0' || src[index] > '9') && src[index] != '.')
    status = ERROR;
  return status;
}

int valid_operations(const char* src, const int index) {
  int status = OK;
  if (src[index] != '+' && src[index] != '-' && src[index] != '*' &&
      src[index] != '/' && src[index] != '^' && src[index] != '(' &&
      src[index] != ')' && src[index] != 'c' && src[index] != 'o' &&
      src[index] != 's' && src[index] != 'i' && src[index] != 'n' &&
      src[index] != 't' && src[index] != 'a' && src[index] != 'l' &&
      src[index] != 'g' && src[index] != 'm' && src[index] != 'd' &&
      src[index] != 'q' && src[index] != 'r' && src[index] != 'x')
    status = ERROR;

  return status;
}

static int check_functions_name(const char* src) {
  int status = OK;
  for (int i = 0; status == OK && src[i] != '\0'; i++) {
    const char current_sym = src[i];
    if (current_sym == 'm') {
      status = check_mod(src, &i);
    } else if (current_sym == 'c') {
      status = check_cos(src, &i);
    } else if (current_sym == 't') {
      status = check_tan(src, &i);
    } else if (current_sym == 's') {
      if (src[i + 1] == 'i') {
        status = check_sin(src, &i);
      } else {
        status = check_sqrt(src, &i);
      }
    } else if (current_sym == 'l') {
      if (src[i + 1] == 'o') {
        status = check_log(src, &i);
      } else {
        status = check_ln(src, &i);
      }
    } else if (current_sym == 'a') {
      i++;
      if (src[i] == 's') {
        status = check_sin(src, &i);
      } else if (src[i] == 'c') {
        status = check_cos(src, &i);
      } else if (src[i] == 't') {
        status = check_tan(src, &i);
      } else {
        status = ERROR;
      }
    }
  }
  return status;
}

static int check_mod(const char* src, int* index) {
  int status = ERROR;
  if (src[*index + 1] == 'o' && src[*index + 2] == 'd') {
    status = OK;
    *index += 2;
  }
  return status;
}

static int check_sqrt(const char* src, int* index) {
  int status = ERROR;
  if (src[*index + 1] == 'q' && src[*index + 2] == 'r' &&
      src[*index + 3] == 't' && src[*index + 4] == '(') {
    status = OK;
    *index += 4;
  }
  return status;
}

static int check_cos(const char* src, int* index) {
  int status = ERROR;
  if (src[*index + 1] == 'o' && src[*index + 2] == 's' &&
      src[*index + 3] == '(') {
    status = OK;
    *index += 3;
  }
  return status;
}

static int check_sin(const char* src, int* index) {
  int status = ERROR;
  if (src[*index + 1] == 'i' && src[*index + 2] == 'n' &&
      src[*index + 3] == '(') {
    status = OK;
    *index += 3;
  }
  return status;
}

static int check_tan(const char* src, int* index) {
  int status = ERROR;
  if (src[*index + 1] == 'a' && src[*index + 2] == 'n' &&
      src[*index + 3] == '(') {
    status = OK;
    *index += 3;
  }
  return status;
}

static int check_log(const char* src, int* index) {
  int status = ERROR;
  if (src[*index + 1] == 'o' && src[*index + 2] == 'g' &&
      src[*index + 3] == '(') {
    status = OK;
    *index += 3;
  }
  return status;
}

static int check_ln(const char* src, int* index) {
  int status = ERROR;
  if (src[*index + 1] == 'n' && src[*index + 2] == '(') {
    status = OK;
    *index += 2;
  }
  return status;
}