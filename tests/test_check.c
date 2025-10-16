#include <check.h>

Suite *str_create_test(void);
Suite *str_len_test(void);
Suite *str_cat_test(void);
Suite *str_free_test(void);

int main(void) {
    SRunner *sr = srunner_create(NULL);
	srunner_add_suite(sr, str_create_test());
	srunner_add_suite(sr, str_len_test());
	srunner_add_suite(sr, str_cat_test());
	srunner_add_suite(sr, str_free_test());
    srunner_run_all(sr, CK_NORMAL);
    srunner_free(sr);
    return 0;
}
