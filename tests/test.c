/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 11:51:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/09/18 11:51:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"
#include "md5.h"
#include "sha256.h"

#include <stdlib.h>

START_TEST(test_md5_empty_string)
{
	t_md5_context context;
	unsigned char digest[16];
	unsigned char expected[] = {
		0xd4, 0x1d, 0x8c, 0xd9, 0x8f, 0x00, 0xb2, 0x04,
		0xe9, 0x80, 0x09, 0x98, 0xec, 0xf8, 0x42, 0x7e
	};

	md5_init(&context);
	md5_update(&context, "", 0);
	md5_final(digest, &context);
	ck_assert_mem_eq(digest, expected, 16);
}
END_TEST

START_TEST(test_sha256_empty_string)
{
	t_sha256_context context;
	unsigned char digest[32];
	unsigned char expected[] = {
		   0xe3, 0xb0, 0xc4, 0x42, 0x98, 0xfc, 0x1c, 0x14,
		   0x9a, 0xfb, 0xf4, 0xc8, 0x99, 0x6f, 0xb9, 0x24,
		   0x27, 0xae, 0x41, 0xe4, 0x64, 0x9b, 0x93, 0x4c,
		   0xa4, 0x95, 0x99, 0x1b, 0x78, 0x52, 0xb8, 0x55
	   };

	sha256_init(&context);
	sha256_update(&context, "", 0);
	sha256_final(digest, &context);
	ck_assert_mem_eq(digest, expected, 32);
}
END_TEST

Suite * money_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Processes");

	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_md5_empty_string);
	tcase_add_test(tc_core, test_sha256_empty_string);
	suite_add_tcase(s, tc_core);
	return s;
}

int main(void)
{
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = money_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_ENV);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
