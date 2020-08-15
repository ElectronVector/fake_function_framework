#include "unity.h"
#include "mock_variable_args.h"
#include <stdbool.h>

void my_printf_custom(const char* fmt, va_list ap)
{
  vprintf(fmt, ap);
}

void setUp(void)
{
  my_printf_fake.custom_fake = my_printf_custom;
}

void test_variable_args_dummy_test(void)
{
  //my_printf_fake.custom_fake = my_printf_custom;
  TEST_ASSERT(true);
}
