/**
 * @file lexem_e.h
 * @author mavissig
 *
 * @brief В этом файле объявлены типы лексем
 */
#ifndef SRC_HEADERS_LEXEM_E_H_
#define SRC_HEADERS_LEXEM_E_H_

/**
 * @brief типы лексем
 *
 * @param type_init (0) инициализирующий тип
 * @param type_x (1) double Х
 * @param type_value (2) double value
 * @param type_sum (3) char '+'
 * @param type_sub (4) char '-'
 * @param type_mul (5) char '*'
 * @param type_div (6) char '/'
 * @param type_pow (7) char '^'
 * @param type_bracket_l (8) char '('
 * @param type_bracket_r (9) char ')'
 * @param type_mod (10) mod
 * @param type_sqrt (11) srqt
 * @param type_sin (12) sin
 * @param type_cos (13) cos
 * @param type_tan (14) tan
 * @param type_ln (15) ln
 * @param type_log (16) log
 * @param type_asin (17) asin
 * @param type_acos (18) acos
 * @param type_atan (19) atan
 * @param type_un_plus (20) unary plus
 * @param type_un_minus (21) unary minus
 *
 */
typedef enum {
  type_init,
  type_x,
  type_value,
  type_sum,
  type_sub,
  type_mul,
  type_div,
  type_pow,
  type_bracket_l,
  type_bracket_r,
  type_mod,
  type_sqrt,
  type_sin,
  type_cos,
  type_tan,
  type_ln,
  type_log,
  type_asin,
  type_acos,
  type_atan,
  type_un_plus,
  type_un_minus
} Type;

#endif  // SRC_HEADERS_LEXEM_E_H_
