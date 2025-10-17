#include <check.h>
#include "../../includes/minishell.h"

START_TEST(test_hash_djb2_should_return_same_hash)
{
	char *key_1 = str_new("key_test");
	char *key_2 = str_new("key_test");
	size_t hash_1 = hash_djb2(key_1);
	size_t hash_2 = hash_djb2(key_2);
	ck_assert(hash_1 == hash_2);
} END_TEST

START_TEST(test_ht_create_should_return_valid_table)
{
    t_hash_table *table = ht_create();
    ck_assert_ptr_nonnull(table);
    ck_assert_int_eq(table->size, INITIAL_SIZE);
    ck_assert_ptr_nonnull(table->items);
    ht_delete(table, NULL);
} END_TEST

START_TEST(test_ht_insert_and_search_should_return_correct_value)
{
    t_hash_table *table = ht_create();
    ht_insert(table, "USER", "jefferson");
    char *result = ht_search(table, "USER");
    ck_assert_ptr_nonnull(result);
    ck_assert_str_eq(result, "jefferson");

    ht_insert(table, "LANG", "C");
    result = ht_search(table, "LANG");
    ck_assert_str_eq(result, "C");

    ht_insert(table, "LANG", "C++"); // overwrite test
    result = ht_search(table, "LANG");
    ck_assert_str_eq(result, "C++");

    ht_delete(table, "USER");
    ht_delete(table, "LANG");
} END_TEST

START_TEST(test_ht_search_should_return_null_for_missing_key)
{
    t_hash_table *table = ht_create();
    ht_insert(table, "EDITOR", "vim");
    char *result = ht_search(table, "NOT_FOUND");
    ck_assert_ptr_null(result);
    ht_delete(table, "EDITOR");
} END_TEST

START_TEST(test_ht_delete_should_remove_key)
{
    t_hash_table *table = ht_create();
    ht_insert(table, "PATH", "/usr/bin");
    ck_assert_str_eq(ht_search(table, "PATH"), "/usr/bin");

    ht_delete(table, "PATH");
    ck_assert_ptr_null(ht_search(table, "PATH"));
} END_TEST

START_TEST(test_ht_delete_should_handle_nonexistent_key_gracefully)
{
    t_hash_table *table = ht_create();
    ht_insert(table, "TERM", "xterm");
    ht_delete(table, "NON_EXISTENT"); // should not crash
    ck_assert_str_eq(ht_search(table, "TERM"), "xterm");
    ht_delete(table, "TERM");
} END_TEST

START_TEST(test_ht_insert_multiple_items_same_index)
{
    t_hash_table *table = ht_create();
    // These keys should ideally hash to the same index to test chaining
    ht_insert(table, "a", "1");
    ht_insert(table, "b", "2");
    ht_insert(table, "c", "3");

    ck_assert_str_eq(ht_search(table, "a"), "1");
    ck_assert_str_eq(ht_search(table, "b"), "2");
    ck_assert_str_eq(ht_search(table, "c"), "3");

    ht_delete(table, "a");
    ht_delete(table, "b");
    ht_delete(table, "c");
} END_TEST
