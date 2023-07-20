/**
 * @file calc.h
 * @author mavissig
 * @brief В этом файле содержатся объявления функций для парсера
 */
#ifndef SRC_HEADERS_PARSER_H_
#define SRC_HEADERS_PARSER_H_

#include "notation.h"
#include "utils.h"

/**
 * @brief функция для парсинга строки
 *
 * @param src строка которую парсим
 * @param status статус выполнения парсинга передаёт OK или ERROR
 * @return struct list*
 */
struct list* parser(const char* src, int* status);

/**
 * @brief вспомагательная функция парсинга числа
 *
 * @param src строка в которой находится число
 * @param index индекс
 * @return double
 */
double parsing_num(const char* src, int* index);

#endif  // SRC_HEADERS_PARSER_H_
