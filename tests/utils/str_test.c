#include <check.h>
#include "../../includes/str.h"

START_TEST(test_str_create_valid){
	ck_assert_ptr_nonnull(str_new(""));
	ck_assert_str_eq(str_new(""), "");
	ck_assert_str_eq(str_new("TEST"), "TEST");
	ck_assert_str_eq(str_new("TEST STR"), "TEST STR");
	ck_assert_str_eq(str_new("✅"), "✅");
}
END_TEST

START_TEST(test_str_create_invalid){
	ck_assert_ptr_null(str_new(0));
	ck_assert_ptr_null(str_new(NULL));
	char var; 
	ck_assert_str_eq(str_new(&var), "");
}
END_TEST


Suite *str_valid(void)
{
	Suite *s = suite_create("str_valid");
	TCase *tc_str_create = tcase_create("str_create():");
	tcase_add_test(tc_str_create, test_str_create_valid);
	suite_add_tcase(s, tc_str_create);
	return (s);
}

Suite *str_invalid(void)
{
	Suite *s = suite_create("str_invalid");
	
	TCase *tc_str_create = tcase_create("str_create():");
	tcase_add_test(tc_str_create, test_str_create_invalid);
	suite_add_tcase(s, tc_str_create);
	return (s);
}