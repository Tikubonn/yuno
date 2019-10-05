#include <stdio.h>
#include <stdlib.h>

/*
	与えられた式の結果がゼロであれば処理を中断します。
*/

#define test(formula)\
if (formula){\
fprintf(stdout, "[SUCCESS] at %s:%d %s\n", __FILE__, __LINE__, #formula);\
}\
else {\
fprintf(stdout, "[ERROR] at %s:%d %s\n", __FILE__, __LINE__, #formula);\
fflush(stdout);\
abort();\
}

/*
	与えられたふたつのNUL文字で終わる配列が一致しなければ処理を中断します。
*/

#define test_equal_string(a, b) {\
char *__test_equal_string_a = a;\
char *__test_equal_string_b = b;\
char *__test_equal_string_aiter = a;\
char *__test_equal_string_biter = b;\
while (1){\
if (*__test_equal_string_aiter == 0 && *__test_equal_string_biter == 0){\
fprintf(stdout, "[SUCCESS] at %s:%d %s == %s (\"%s\" == \"%s\")\n", __FILE__, __LINE__, #a, #b, __test_equal_string_a, __test_equal_string_b);\
break;\
}\
if (*__test_equal_string_aiter != *__test_equal_string_biter){\
fprintf(stdout, "[ERROR] at %s:%d %s == %s (\"%s\" == \"%s\")\n", __FILE__, __LINE__, #a, #b, __test_equal_string_a, __test_equal_string_b);\
break;\
}\
__test_equal_string_aiter++;\
__test_equal_string_biter++;\
}\
}
