#include <stdio.h>
#include <stdlib.h>

#define test(formula)\
if (formula){\
printf("[success] at %s:%d %s\n", __FILE__, __LINE__, #formula);\
}\
else {\
printf("[error] at %s:%d %s\n", __FILE__, __LINE__, #formula);\
abort();\
}

#define nortice(text)\
printf("[nortice] at %s:%d " text "\n", __FILE__, __LINE__);

#define error(text)\
printf("[error] at %s:%d " text "\n", __FILE__, __LINE__);\
abort();
