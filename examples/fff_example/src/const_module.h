#ifndef _CONST_MODULE_H
#define _CONST_MODULE_H

void a(int const* param1);
void b(int*const param2);
void c(const int* param3);
void d(const int* const param4);
void e(int const* const param5);
void f(int*param6);
void g(int param7);
void h(const int param8);

const char * i();
char const * j();
const int * k();
int const * l();

int * const m();
char * const n();

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
  uint8_t address;
  bool pressed;
}Button;

void Button_pollAll(Button * const *, size_t);

#endif // _CONST_MODULE_H
