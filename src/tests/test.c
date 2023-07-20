#include <check.h>
#include <stdio.h>
#include <time.h>

#include "../headers/calc.h"
#include "../headers/notation.h"
#include "../headers/parser.h"
#include "../headers/validation.h"

static lexem_t* allocateLexem()
{
  lexem_t* lexem = (lexem_t*)calloc(1, sizeof(lexem_t));
  return lexem;
}

static Type getType(const struct list *node) { return node->data->type; }

static double getValue(const struct list *node) {
  return node->data->value;
}

static int removeNotation(struct list* root);

static int removeNotation(struct list* root){
  struct list*temp = NULL;
  while (NULL != root){
    temp = root->next;
    root->data->type = 0;
    root->data->value = 0;
    free(root->data);
    root->data = NULL;
    free(root);
    root = NULL;
    root = temp;
  }

  return 0;
}

static void removeLexem(lexem_t*root);

static void removeLexem(lexem_t*root){
    root->type= 0;
    root->value = 0;
    free(root);
    root = NULL;
}

static int removeStack(struct stack_s*root);

static int removeStack(struct stack_s*root) {
  struct stack_s*temp = NULL;
  while (NULL != root){
    temp = root->next;
    root->data->type = 0;
    root->data->value = 0;
    free(root->data);
    root->data = NULL;
    free(root);
    root = NULL;
    root = temp;
  }

  return 0;
}

typedef enum {
  SMALL_N = 10,
  N = 10000,
  BIG_N = 1000000,
} sizes;

static double wtime();
static double getResultTime(const double begin, const double end);

START_TEST(stack_check_1) {
  const double start = wtime();
  struct stack_s *stack = NULL;
  for (int i = 0; i < SMALL_N; ++i) {
    lexem_t *lexem = allocateLexem();
    lexem->value = i;
    lexem->type = type_acos;
    stack = push(stack, lexem);
    removeLexem(lexem);
  }
  for (int i = 0; i < SMALL_N; ++i) {
    lexem_t *value = allocateLexem();
    stack = pop(stack, value);
    ck_assert_double_eq(value->value, SMALL_N - i - 1);
    ck_assert_double_eq(value->type, type_acos);
    removeLexem(value);
  }
  removeStack(stack);
  ck_assert_ptr_null(stack);
  const double end = wtime();
  const double resultTime = getResultTime(start, end);
  printf("Elapsed time test:stack_check_1:%f seconds\n", resultTime);
}
END_TEST

START_TEST(stack_check_2) {
  const double start = wtime();
  struct stack_s *stack = NULL;
  for (int i = 0; i < N; ++i) {
    lexem_t *lexem = allocateLexem();
    lexem->value = i;
    lexem->type = type_acos;
    stack = push(stack, lexem);
    removeLexem(lexem);
  }
  for (int i = 0; i < N; ++i) {
    lexem_t *value = allocateLexem();
    stack = pop(stack, value);
    ck_assert_double_eq(value->value, N - i - 1);
    ck_assert_double_eq(value->type, type_acos);
    removeLexem(value);
  }
  removeStack(stack);
  ck_assert_ptr_null(stack);
  const double end = wtime();
  const double resultTime = getResultTime(start, end);
  printf("Elapsed time test:stack_check_2:%f seconds\n", resultTime);
}
END_TEST

START_TEST(stack_test_1) {
  const double start = wtime();
  struct stack_s *stack = NULL;
  for (int i = 0; i < BIG_N; ++i) {
    lexem_t *lexem = allocateLexem();
    lexem->value = i;
    lexem->type = type_atan;
    stack = push(stack, lexem);
    removeLexem(lexem);
  }
  for (int i = 0; i < BIG_N; ++i) {
    lexem_t *value = allocateLexem();
    stack = pop(stack, value);
    ck_assert_double_eq(value->value, BIG_N - i - 1);
    ck_assert_double_eq(value->type, type_atan);
    removeLexem(value);
  }
  removeStack(stack);
  ck_assert_ptr_null(stack);
  const double end = wtime();
  const double resultTime = getResultTime(start, end);
  printf("Elapsed time test:stack_test_1:%f seconds\n", resultTime);
}
END_TEST

START_TEST(stack_test_2) {
  const double start = wtime();
  struct stack_s *stack = NULL;
  for (int i = 0; i < N; ++i) {
    lexem_t *lexem = allocateLexem();
    lexem->type = type_bracket_l;
    if (0 == i % 2) {
      lexem->value = i;
      stack = push(stack, lexem);
    } else {
      lexem->value = i + 11;
      stack = push(stack, lexem);
    }
    removeLexem(lexem);
  }
  for (int i = 0; i < N; ++i) {
    lexem_t *value = allocateLexem();
    stack = pop(stack, value);
    if (0 == i % 2) {
      ck_assert_double_eq(value->value, N - i - 1 + 11);
    } else {
      ck_assert_double_eq(value->value, N - i - 1);
    }
    ck_assert_double_eq(value->type, type_bracket_l);
    removeLexem(value);
  }
  removeStack(stack);
  ck_assert_ptr_null(stack);
  const double end = wtime();
  const double resultTime = getResultTime(start, end);
  printf("Elapsed time test:stack_test_2:%f seconds\n", resultTime);
}
END_TEST

START_TEST(listest_1) {
  const double start = wtime();
  struct list *root = NULL;
  lexem_t *lexem = allocateLexem();
  lexem->value = 10;
  lexem->type = type_mul;
  root = insert(root, *lexem);
  ck_assert_ptr_nonnull(root);
  ck_assert_double_eq(getValue(root), 10);
  ck_assert_int_eq(getType(root), type_mul);
  lexem_t *lexem_1 = allocateLexem();
  lexem_1->value = 10;
  lexem_1->type = type_mul;
  root = insert(root, *lexem_1);
  ck_assert_ptr_nonnull(root->next);
  ck_assert_double_eq(getValue(root->next), 10);
  ck_assert_int_eq(getType(root->next), type_mul);
  removeNotation(root);
  removeLexem(lexem);
  removeLexem(lexem_1);
  const double end = wtime();
  const double resultTime = getResultTime(start, end);
  printf("Elapsed time test:listest_1:%f seconds\n", resultTime);
}
END_TEST

START_TEST(listest_2) {
  int status = OK;
  const double start = wtime();
  const char *text = "1+1";
  const size_t size = 3;
  struct list *notation = parser(text, &status);
  ck_assert_ptr_nonnull(notation);
  ck_assert_double_eq(getValue(notation), 1);
  ck_assert_int_eq(getType(notation), type_value);
  ck_assert_ptr_nonnull(notation->next);
  ck_assert_int_eq(getValue(notation->next), 0);
  ck_assert_int_eq(getType(notation->next), type_sum);
  ck_assert_ptr_nonnull(notation->next->next);
  ck_assert_int_eq(getValue(notation->next->next), 1);
  ck_assert_int_eq(getType(notation->next->next), type_value);
  ck_assert_ptr_null(notation->next->next->next);
  removeNotation(notation);
  const double end = wtime();
  const double resultTime = getResultTime(start, end);
  printf("Elapsed time test:listest_2:%f seconds\n", resultTime);
}
END_TEST

START_TEST(listest_3) {
  int status = OK;
  const double start = wtime();
  const char *text = "sin(x+15^2*(cos(5)))";
  const size_t size = 20;
  struct list *notation = parser(text, &status);
  ck_assert_ptr_nonnull(notation);
  ck_assert_double_eq(getValue(notation), 0);
  ck_assert_int_eq(getType(notation),type_sin);
  ck_assert_ptr_nonnull(notation->next);
  ck_assert_double_eq(getValue(notation->next), 0);
  ck_assert_int_eq(getType(notation->next), type_bracket_l);
  ck_assert_ptr_nonnull(notation->next->next);
  ck_assert_double_eq(getValue(notation->next->next), 0);
  ck_assert_int_eq(getType(notation->next->next),type_x);
  ck_assert_ptr_nonnull(notation->next->next->next);
  ck_assert_double_eq(getValue(notation->next->next->next), 0);
  ck_assert_int_eq(getType(notation->next->next->next), type_sum);
  ck_assert_ptr_nonnull(notation->next->next->next->next);
  ck_assert_int_eq(getValue(notation->next->next->next->next), 15);
  ck_assert_int_eq(getType(notation->next->next->next->next), type_value);
  ck_assert_ptr_nonnull(notation->next->next->next->next->next);
  ck_assert_double_eq(getValue(notation->next->next->next->next->next), 0);
  ck_assert_int_eq(getType(notation->next->next->next->next->next), type_pow);
  ck_assert_ptr_nonnull(notation->next->next->next->next->next->next);
  ck_assert_double_eq(getValue(notation->next->next->next->next->next->next),
                      2);
  ck_assert_int_eq(getType(notation->next->next->next->next->next->next),
                   type_value);
  ck_assert_ptr_nonnull(notation->next->next->next->next->next->next->next);
  ck_assert_double_eq(
      getValue(notation->next->next->next->next->next->next->next), 0);
  ck_assert_int_eq(getType(notation->next->next->next->next->next->next->next),
                   type_mul);
  ck_assert_ptr_nonnull(
      notation->next->next->next->next->next->next->next->next);
  ck_assert_double_eq(
      getValue(notation->next->next->next->next->next->next->next->next), 0);
  ck_assert_int_eq(
      getType(notation->next->next->next->next->next->next->next->next),
      type_bracket_l);
  ck_assert_ptr_nonnull(
      notation->next->next->next->next->next->next->next->next->next);
  ck_assert_double_eq(
      getValue(notation->next->next->next->next->next->next->next->next->next),
      0);
  ck_assert_int_eq(
      getType(notation->next->next->next->next->next->next->next->next->next),
      type_cos);
  ck_assert_ptr_nonnull(
      notation->next->next->next->next->next->next->next->next->next->next);
  ck_assert_double_eq(
      getValue(
          notation->next->next->next->next->next->next->next->next->next->next),
      0);
  ck_assert_int_eq(
      getType(
          notation->next->next->next->next->next->next->next->next->next->next),
      type_bracket_l);
  ck_assert_ptr_nonnull(notation->next->next->next->next->next->next->next->next
                            ->next->next->next);
  ck_assert_double_eq(getValue(notation->next->next->next->next->next->next
                                   ->next->next->next->next->next),
                      5);
  ck_assert_int_eq(getType(notation->next->next->next->next->next->next->next
                               ->next->next->next->next),
                   type_value);
  ck_assert_ptr_nonnull(notation->next->next->next->next->next->next->next->next
                            ->next->next->next->next);
  ck_assert_double_eq(getValue(notation->next->next->next->next->next->next
                                   ->next->next->next->next->next->next),
                      0);
  ck_assert_int_eq(getType(notation->next->next->next->next->next->next->next
                               ->next->next->next->next->next),
                   type_bracket_r);
  ck_assert_ptr_nonnull(notation->next->next->next->next->next->next->next->next
                            ->next->next->next->next->next);
  ck_assert_double_eq(getValue(notation->next->next->next->next->next->next
                                   ->next->next->next->next->next->next->next),
                      0);
  ck_assert_int_eq(getType(notation->next->next->next->next->next->next->next
                               ->next->next->next->next->next->next),
                   type_bracket_r);
  ck_assert_ptr_nonnull(notation->next->next->next->next->next->next->next->next
                            ->next->next->next->next->next->next);
  ck_assert_double_eq(
      getValue(notation->next->next->next->next->next->next->next->next->next
                   ->next->next->next->next->next),
      0);
  ck_assert_int_eq(getType(notation->next->next->next->next->next->next->next
                               ->next->next->next->next->next->next->next),
                   type_bracket_r);
  removeNotation(notation);
  const double end = wtime();
  const double resultTime = getResultTime(start, end);
  printf("Elapsed time test:listest_3:%f seconds\n", resultTime);
}
END_TEST

START_TEST(listest_4) {
  int status = OK;
  const double start = wtime();
  const char *text =
      "tan(ln(log(asin(acos(atan(sqrt(555.124mod5123.13535)))))))";
  const size_t size = 58;
  struct list *notation = parser(text, &status);
  double type_values[24] = {0};
  type_values[14] = 555.124;
  type_values[16] = 5123.13535;
  int types[24] = {0};
  types[0] = type_tan;
  types[2] =type_ln;
  types[4] = type_log;
  types[6] = type_asin;
  types[8] = type_acos;
  types[10] = type_atan;
  types[12] = type_sqrt;
  types[14] = type_value;
  types[15] = type_mod;
  types[16] = type_value;
  types[1] = types[3] = types[5] = types[7] = types[9] = types[11] = types[13] =
      type_bracket_l;
  types[17] = types[18] = types[19] = types[20] = types[21] = types[22] =
      types[23] = type_bracket_r;
  struct list *temp = notation;
  for (int i = 0; i < 24; ++i) {
    ck_assert_ptr_nonnull(temp);
    ck_assert_double_le(getValue(temp) - type_values[i], 1E-7);
    ck_assert_double_eq(getType(temp), types[i]);
    temp = temp->next;
  }
  removeNotation(notation);
  const double end = wtime();
  const double resultTime = getResultTime(start, end);
  printf("Elapsed time test:listest_4:%f seconds\n", resultTime);
}
END_TEST

START_TEST(validation_test_1) {
  const double start = wtime();
  const char *text = "))))))((((((";
  const char *text_1 = "(((())))))";
  const char *text_2 = "sin(cos(tan(x)))";
  const char *text_7 =
      "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
      "((((((((((((((((((((((((((((((((((123;))))))))))))))))))))))))))))))))))"
      ")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))"
      ")";
  const char *text_8 =
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111111111111}";
  const char *text_9 =
      "{{{{{{{{{{{{{{{{{{{{{{{{{{123}}}}}}}}}}}}}}}}}}}}}}}}}}";
  const size_t size = strlen(text), size_1 = strlen(text_1),
               size_2 = strlen(text_2), size_7 = strlen(text_7),
               size_8 = strlen(text_8), size_9 = strlen(text_9);
  const int result = prevalidation(text);
  ck_assert_int_eq(result, ERROR);
  const int result_1 = prevalidation(text_1);
  ck_assert_int_eq(result_1, ERROR);
  const int result_2 = prevalidation(text_2);
  ck_assert_int_eq(result_2, OK);
  const int result_7 = prevalidation(text_7);
  ck_assert_int_eq(result_7, ERROR);
  const int result_8 = prevalidation(text_8);
  ck_assert_int_eq(result_8, ERROR);
  const int result_9 = prevalidation(text_9);
  ck_assert_int_eq(result_9, ERROR);
  const double end = wtime();
  const double resultTime = getResultTime(start, end);
  printf("Elapsed time test:validation_test_1:%f seconds\n", resultTime);
}
END_TEST

START_TEST(validation_test_4) {
  int status = OK;
  const double start = wtime();
  const char *text = "1.123x1";
  const char *text_1 = "xsin(x)";
  const char *text_2 = "sin(x)mod+ln(x)";
  const char *text_3 = "ln(x)123.123";
  const char *text_4 = "1.1/123//123";
  const char *text_5 = "/213";
  const char *text_6 = "+123";
  const char *text_7 = "123+";
  const char *text_8 = "+sin(x)";
  const char *text_9 = "sin(xx)";
  const char *text_10 = "cos(x-123.1^^x)";
  const size_t size = strlen(text), size_1 = strlen(text_1),
               size_2 = strlen(text_2), size_3 = strlen(text_3),
               size_4 = strlen(text_4), size_5 = strlen(text_5),
               size_6 = strlen(text_6), size_7 = strlen(text_7),
               size_8 = strlen(text_8), size_9 = strlen(text_9),
               size_10 = strlen(text_10);
  struct list *notation = parser(text, &status);
  struct list *notation_1 = parser(text_1, &status);
  struct list *notation_2 = parser(text_2, &status);
  struct list *notation_3 = parser(text_3, &status);
  struct list *notation_4 = parser(text_4, &status);
  struct list *notation_5 = parser(text_5, &status);
  struct list *notation_6 = parser(text_6, &status);
  struct list *notation_7 = parser(text_7, &status);
  struct list *notation_8 = parser(text_8, &status);
  struct list *notation_9 = parser(text_9, &status);
  struct list *notation_10 = parser(text_10, &status);
  int error = 0, error_1 = 0, error_2 = 0, error_3 = 0, error_4 = 0,
      error_5 = 0, error_6 = 0, error_7 = 0, error_8 = 0, error_9 = 0,
      error_10 = 0;
  validation(notation);
  validation(notation_1);
  validation(notation_2);
  validation(notation_3);
  validation(notation_4);
  validation(notation_5);
  validation(notation_6);
  validation(notation_7);
  validation(notation_8);
  validation(notation_9);
  validation(notation_10);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(error_1, 0);
  ck_assert_int_eq(error_2, 0);
  ck_assert_int_eq(error_3, 0);
  ck_assert_int_eq(error_4, 0);
  ck_assert_int_eq(error_5, 0);
  ck_assert_int_eq(error_6, 0);
  ck_assert_int_eq(error_7, 0);
  ck_assert_int_eq(error_8, 0);
  ck_assert_int_eq(error_9, 0);
  ck_assert_int_eq(error_10, 0);
  removeNotation(notation);
  removeNotation(notation_1);
  removeNotation(notation_2);
  removeNotation(notation_3);
  removeNotation(notation_4);
  removeNotation(notation_5);
  removeNotation(notation_6);
  removeNotation(notation_7);
  removeNotation(notation_8);
  removeNotation(notation_9);
  removeNotation(notation_10);
  const double end = wtime();
  const double resultTime = getResultTime(start, end);
  printf("Elapsed time test:validation_test_4:%f seconds\n", resultTime);
}
END_TEST

START_TEST(polishlistest_1) {
  int status = OK;
  const double start = wtime();
  const char *text = "1+1";
  struct list *notation = parser(text,  &status);
  struct list *polishNotation = polish_notation(notation);
  ck_assert_ptr_nonnull(polishNotation);
  ck_assert_int_eq(getValue(polishNotation), 1);
  ck_assert_int_eq(getType(polishNotation), type_value);
  ck_assert_ptr_nonnull(polishNotation->next);
  ck_assert_int_eq(getValue(polishNotation->next), 1);
  ck_assert_int_eq(getType(polishNotation->next), type_value);
  ck_assert_ptr_nonnull(polishNotation->next->next);
  ck_assert_int_eq(getValue(polishNotation->next->next), 0);
  ck_assert_int_eq(getType(polishNotation->next->next), type_sum);
  removeNotation(notation);
  removeNotation(polishNotation);
  const double end = wtime();
  const double resultTime = getResultTime(start, end);
  printf("Elapsed time test:polishlistest_1:%f seconds\n", resultTime);
}
END_TEST

START_TEST(polishlistest_2) {
  int status = OK;
  const double start = wtime();
  const char *text = "1+1-2*2^2/5";
  struct list *notation = parser(text,  &status);
  struct list *polishNotation = polish_notation(notation);
  double values[11] = {1, 1, 0, 2, 2, 2, 0, 0, 5, 0, 0};
  Type types[11] = {type_value, type_value, type_sum,   type_value, type_value, type_value,
                    type_pow,   type_mul,  type_value, type_div,  type_sub};
  Type validTypes[11] = {type_value, type_sum, type_value,type_sub, type_value, type_mul,
                         type_value, type_pow, type_value, type_div, type_value};
  double validValues[11] = {1, 0, 1, 0, 2, 0, 2, 0, 2, 0, 5};
  struct list *valid = notation;
  for (int i = 0; i < 11; ++i) {
    ck_assert_ptr_nonnull(valid);
    ck_assert_double_eq(validValues[i], getValue(valid));
    ck_assert_int_eq(validTypes[i], getType(valid));
    valid = valid->next;
  }
  struct list *temp = polishNotation;
  for (int i = 0; i < 11; ++i) {
    ck_assert_ptr_nonnull(temp);
    ck_assert_double_eq(values[i], getValue(temp));
    ck_assert_int_eq(types[i], getType(temp));
    temp = temp->next;
  }
  removeNotation(notation);
  removeNotation(polishNotation);
  const double end = wtime();
  const double resultTime = getResultTime(start, end);
  printf("Elapsed time test:polishlistest_2:%f seconds\n", resultTime);
}
END_TEST

START_TEST(polishlistest_3) {
  int status = OK;
  const double start = wtime();
  const char *text = "1+123.123^(x-123*123)";
  struct list *notation = parser(text,  &status);
  struct list *polishNotation = polish_notation(notation);
  double values[9] = {1, 123.123, 0, 123, 123, 0, 0, 0, 0};
  Type types[9] = {type_value, type_value,type_x, type_value, type_value, type_mul,type_sub, type_pow, type_sum};
  double validValues[11] = {1, 0, 123.123, 0, 0, 0, 0, 123, 0, 123, 0};
  Type validTypes[11] = {type_value, type_sum,   type_value, type_pow,   type_bracket_l,type_x,
                        type_sub,   type_value, type_mul,  type_value, type_bracket_r};
  struct list *valid = notation;
  for (int i = 0; i < 11; ++i) {
    ck_assert_ptr_nonnull(valid);
    ck_assert_double_le(validValues[i] - getValue(valid), 1E-7);
    ck_assert_int_eq(validTypes[i], getType(valid));
    valid = valid->next;
  }
  struct list *temp = polishNotation;
  for (int i = 0; i < 9; ++i) {
    ck_assert_ptr_nonnull(temp);
    ck_assert_double_le(values[i] - getValue(temp), 1E-7);
    ck_assert_int_eq(types[i], getType(temp));
    temp = temp->next;
  }
  removeNotation(notation);
  removeNotation(polishNotation);
  const double end = wtime();
  const double resultTime = getResultTime(start, end);
  printf("Elapsed time test:polishlistest_3:%f seconds\n", resultTime);
}
END_TEST

START_TEST(polishlistest_4) {
  int status = OK;
  const double start = wtime();
  const char *text = "sin(x/123^(cos(x-ln(123.123))))";
  struct list *notation = parser(text, &status);
  struct list *polishNotation = polish_notation(notation);
  polishNotation = prefix_unary(polishNotation);
  double values[10] = {0, 123, 0, 123.123, 0, 0, 0, 0, 0, 0};
  Type types[10] = {type_x, type_value,type_x, type_value,type_ln,type_sub, type_cos, type_pow, type_div,type_sin};
  double validValues[18] = {0, 0, 0, 0, 123,     0, 0, 0, 0,
                            0, 0, 0, 0, 123.123, 0, 0, 0, 0};
  Type validTypes[18] = {type_sin,
                         type_bracket_l,
                        type_x,
                         type_div,
                         type_value,
                         type_pow,
                         type_bracket_l,
                         type_cos,
                         type_bracket_l,
                        type_x,
                        type_sub,
                        type_ln,
                         type_bracket_l,
                         type_value,
                         type_bracket_r,
                         type_bracket_r,
                         type_bracket_r,
                         type_bracket_r};
  struct list *valid = notation;
  for (int i = 0; i < 18; ++i) {
    ck_assert_ptr_nonnull(valid);
    ck_assert_double_le(validValues[i] - getValue(valid), 1E-7);
    ck_assert_int_eq(validTypes[i], getType(valid));
    valid = valid->next;
  }
  struct list *temp = polishNotation;
  for (int i = 0; i < 10; ++i) {
    ck_assert_ptr_nonnull(temp);
    ck_assert_double_le(values[i] - getValue(temp), 1E-7);
    ck_assert_int_eq(types[i], getType(temp));
    temp = temp->next;
  }
  removeNotation(notation);
  removeNotation(polishNotation);
  const double end = wtime();
  const double resultTime = getResultTime(start, end);
  printf("Elapsed time test:polishlistest_4:%f seconds\n", resultTime);
}
END_TEST

START_TEST(calculate_test_1) {
  int status = OK;
  const double start = wtime();
  const char *text = "sin(x/123^(cos(x-ln(123.123))))";
  struct list *notation = parser(text, &status);
  struct list *polishNotation = polish_notation(notation);
  polishNotation = prefix_unary(polishNotation);
  double values[10] = {0, 123, 0, 123.123, 0, 0, 0, 0, 0, 0};
  Type types[10] = {type_x, type_value,type_x, type_value,type_ln,type_sub, type_cos, type_pow, type_div,type_sin};
  double validValues[18] = {0, 0, 0, 0, 123,     0, 0, 0, 0,
                            0, 0, 0, 0, 123.123, 0, 0, 0, 0};
  Type validTypes[18] = {type_sin,
                         type_bracket_l,
                        type_x,
                         type_div,
                         type_value,
                         type_pow,
                         type_bracket_l,
                         type_cos,
                         type_bracket_l,
                        type_x,
                        type_sub,
                        type_ln,
                         type_bracket_l,
                         type_value,
                         type_bracket_r,
                         type_bracket_r,
                         type_bracket_r,
                         type_bracket_r};
  struct list *valid = notation;
  for (int i = 0; i < 18; ++i) {
    ck_assert_ptr_nonnull(valid);
    ck_assert_double_le(validValues[i] - getValue(valid), 1E-7);
    ck_assert_int_eq(validTypes[i], getType(valid));
    valid = valid->next;
  }
  struct list *temp = polishNotation;
  for (int i = 0; i < 10; ++i) {
    ck_assert_ptr_nonnull(temp);
    ck_assert_double_le(values[i] - getValue(temp), 1E-7);
    ck_assert_int_eq(types[i], getType(temp));
    temp = temp->next;
  }
  int error = 0;
  const double result = calculation(polishNotation, 0);
  const double answer = -0.66415;
  ck_assert_double_le(answer - result, 1E-7);
  removeNotation(notation);
  removeNotation(polishNotation);
  const double end = wtime();
  const double resultTime = getResultTime(start, end);
  printf("Elapsed time test:calculate_test_1:%f seconds\n", resultTime);
}
END_TEST

int main() {
  const double timeout = 45.0;
  Suite *suite = suite_create("Smart Calc test");
  TCase *tests = tcase_create("Smart Calc tests");
  SRunner *runner = srunner_create(suite);
  suite_add_tcase(suite, tests);
  tcase_set_timeout(tests, timeout);
  tcase_add_test(tests, stack_check_1);
  tcase_add_test(tests, stack_check_2);
  tcase_add_test(tests, stack_test_1);
  tcase_add_test(tests, stack_test_2);
  tcase_add_test(tests, listest_1);
  tcase_add_test(tests, listest_2);
  tcase_add_test(tests, listest_3);
  tcase_add_test(tests, listest_4);
  tcase_add_test(tests, validation_test_1);
  tcase_add_test(tests, validation_test_4);
  tcase_add_test(tests, polishlistest_1);
  tcase_add_test(tests, polishlistest_2);
  tcase_add_test(tests, polishlistest_3);
  tcase_add_test(tests, polishlistest_4);
  tcase_add_test(tests, calculate_test_1);
  srunner_set_fork_status(runner, CK_FORK);
  printf("________________________Smart Calc test________________________\n");
  const double start = wtime();
  srunner_run_all(runner, CK_ENV);
  const double end = wtime();
  const double resultTime = getResultTime(start, end);
  printf("Elapsed Smart Calc test time:%f seconds\n", resultTime);
  printf("_______________________________________________________________\n");
  srunner_free(runner);
  return 0;
}

static double wtime() {
  double time = 0;
#ifdef CLOCK_MONOTONIC
  struct timespec ts = {.tv_nsec = 0, .tv_sec = 0};
  clock_gettime(CLOCK_MONOTONIC, &ts);
  time = ts.tv_sec + ts.tv_nsec * 1E-9;
#else
  time = clock();
#endif
  return time;
}

static double getResultTime(const double begin, const double end) {
  double time = 0;
#ifdef CLOCK_MONOTONIC
  time = end - begin;
#else
  time = (end - begin) / CLOCKS_PER_SEC;
#endif
  return time;
}