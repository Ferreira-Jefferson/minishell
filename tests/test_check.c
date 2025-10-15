#include <check.h>

START_TEST(test_exemplo) {
    ck_assert_int_eq(2 + 2, 4);
}
END_TEST

Suite *suite(void) {
    Suite *s = suite_create("Exemplo");
    TCase *tc = tcase_create("Core");
    tcase_add_test(tc, test_exemplo);
    suite_add_tcase(s, tc);
    return s;
}

int main(void) {
    SRunner *sr = srunner_create(suite());
    srunner_run_all(sr, CK_NORMAL);
    srunner_free(sr);
    return 0;
}
