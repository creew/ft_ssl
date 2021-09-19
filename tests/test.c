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

#include <sha224.h>
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


START_TEST(test_sha224_empty_string)
{
	t_sha224_context context;
	unsigned char digest[28];
	unsigned char expected[] = {
		   0xd1, 0x4a, 0x02, 0x8c, 0x2a, 0x3a, 0x2b,
		   0xc9, 0x47, 0x61, 0x02, 0xbb, 0x28, 0x82,
		   0x34, 0xc4, 0x15, 0xa2, 0xb0, 0x1f, 0x82,
		   0x8e, 0xa6, 0x2a, 0xc5, 0xb3, 0xe4, 0x2f
	   };

	sha224_init(&context);
	sha224_update(&context, "", 0);
	sha224_final(digest, &context);
	ck_assert_mem_eq(digest, expected, 28);
}
END_TEST

Suite * money_suite(void)
{
	Suite *s;
	TCase *md5, *sha256, *sha224;

	s = suite_create("Hashes");

	md5 = tcase_create("md5");
	tcase_add_test(md5, test_md5_empty_string);
	suite_add_tcase(s, md5);
	sha256 = tcase_create("sha256");
	tcase_add_test(sha256, test_sha256_empty_string);
	suite_add_tcase(s, sha256);
	sha224 = tcase_create("sha224");
	tcase_add_test(sha224, test_sha224_empty_string);
	suite_add_tcase(s, sha224);
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
