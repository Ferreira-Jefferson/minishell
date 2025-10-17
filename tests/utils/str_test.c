#include <check.h>
#include "../../includes/minishell.h"

START_TEST(test_str_create){
	ck_assert_ptr_null(str_new(0));
	ck_assert_ptr_null(str_new(NULL));
	char var; 
	ck_assert_str_eq(str_new(&var), "");
	ck_assert_ptr_nonnull(str_new(""));
	ck_assert_str_eq(str_new(""), "");
	ck_assert_str_eq(str_new("TEST"), "TEST");
	ck_assert_str_eq(str_new("TEST STR"), "TEST STR");
	ck_assert_str_eq(str_new("✅"), "✅");
} END_TEST

START_TEST(test_str_len_test){
	// should return len 0 if the string is NULL
	char	*given = str_new(0);
	int		expect = 0;
	int		result = str_len(given);
	ck_assert_int_eq(result, expect);

	// should return len 0 if the string is empty
	given = str_new("");
	expect = 0;
	result = str_len(given);
	ck_assert_int_eq(result, expect);

	// should return len 1 if the string "A" is passed
	given = str_new("A");
	expect = 1;
	result = str_len(given);
	ck_assert_int_eq(result, expect);

	// should return the same len with strlen 
	given = str_new("0123456789");
	expect = ft_strlen(given);
	result = str_len(given);
	ck_assert_int_eq(result, expect);
} END_TEST


START_TEST(test_str_cat_test){
	// should return null if base is null
	char	*base = str_new(0);
	ck_assert_ptr_null(str_cat(base, "end"));

	// should return "start" if base is start and complement is NULL
	base = str_new("start");
	char *given = str_cat(base, 0);
	char *expect = "start";
	ck_assert_str_eq(given, expect);

	// should return "start" if base is "start" and complement is empty
	base = str_new("start");
	given = str_cat(base, "");
	expect = "start";
	ck_assert_str_eq(given, expect);

	// should return "end" if base is empty and complement is "end"
	base = str_new("");
	given = str_cat(base, "end");
	expect = "end";
	ck_assert_str_eq(given, expect);

	// should return "startend" if base is "start" and complement is "end"
	base = str_new("start");
	given = str_cat(base, "end");
	expect = "startend";
	ck_assert_str_eq(given, expect);

	// should return "start end" if base is "start" and complement is " end"
	base = str_new("start");
	given = str_cat(base, " end");
	expect = "start end";
	ck_assert_str_eq(given, expect);
} END_TEST

START_TEST(test_str_free_test)
{
	// not should show error if a null string is passed
	char *given = str_new(0);
	str_free(given);
	ck_assert_ptr_null(given);

	// not should show error if a valid string is passed
	char *given2 = str_new("valid string");
	str_free(given2);
} END_TEST

Suite *str_create_test(void)
{
	Suite *s = suite_create("str_create");
	TCase *tc_str_create = tcase_create("str_create():");
	tcase_add_test(tc_str_create, test_str_create);
	suite_add_tcase(s, tc_str_create);
	return (s);
}

Suite *str_len_test(void)
{
	Suite *s = suite_create("str_len");
	
	TCase *tc_str_len = tcase_create("str_len():");
	tcase_add_test(tc_str_len, test_str_len_test);
	suite_add_tcase(s, tc_str_len);
	return (s);
}

Suite *str_cat_test(void)
{
	Suite *s = suite_create("str_cat");

	TCase *tc_str_cat = tcase_create("str_cat():");
	tcase_add_test(tc_str_cat, test_str_cat_test);
	suite_add_tcase(s, tc_str_cat);
	return (s);
}

Suite *str_free_test(void)
{
	Suite *s = suite_create("str_free");

	TCase *tc_str_free = tcase_create("str_free():");
	tcase_add_test(tc_str_free, test_str_free_test);
	suite_add_tcase(s, tc_str_free);
	return (s);
}