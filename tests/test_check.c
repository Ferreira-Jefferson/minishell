#include <check.h>

Suite *str_valid(void);
Suite *str_invalid(void);

int main(void) {
    SRunner *sr = srunner_create(str_valid());
	srunner_add_suite(sr, str_invalid());
    srunner_run_all(sr, CK_NORMAL);
    srunner_free(sr);
    return 0;
}
