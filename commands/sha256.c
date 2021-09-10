/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 17:53:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/09/05 17:53:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

#include "ft_ssl.h"

const t_u32 g_koef[] = {
	0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1,
	0x923F82A4, 0xAB1C5ED5, 0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
	0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174, 0xE49B69C1, 0xEFBE4786,
	0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
	0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147,
	0x06CA6351, 0x14292967, 0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
	0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85, 0xA2BFE8A1, 0xA81A664B,
	0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
	0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A,
	0x5B9CCA4F, 0x682E6FF3, 0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
	0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2};

void process_body(t_sha256_context *context)
{
}

void transform(unsigned char *digest, const t_sha256_context *context)
{
	t_u32 array[8];
	int i;

	array[0] = context->h0;
	array[1] = context->h1;
	array[2] = context->h2;
	array[3] = context->h3;
	array[4] = context->h4;
	array[5] = context->h5;
	array[6] = context->h6;
	array[7] = context->h7;
	i = 0;
	while (i < (sizeof(array) / sizeof(array[0]))) {
		digest[i * 4 + 0] = array[i];
		digest[i * 4 + 1] = array[i] >> 8;
		digest[i * 4 + 2] = array[i] >> 16;
		digest[i * 4 + 3] = array[i] >> 24;
		i++;
	}
}

void sha256_final(unsigned char *digest, t_sha256_context *context) {
	t_u32 *chunks;

	chunks = (t_u32 *)context->buf;
	context->buf[context->available++] = 0x80;
	if (context->available > 56) {
		while (context->available < 64) {
			context->buf[context->available++] = 0;
		}
		process_body(context);
		context->available = 0;
	}
	while (context->available < 56) {
		context->buf[context->available++] = 0;
	}
	context->length <<= 3;
	chunks[14] = context->length;
	chunks[15] = context->length >> 32;
	process_body(context);
	transform(digest, context);
}

void sha256_update(t_sha256_context *context, const char *buf, size_t size)
{
	context->length += size;
	while (size)
	{
		context->buf[context->available++] = *buf++;
		if (context->available == 64)
		{
			process_body(context);
			context->available = 0;
		}
		size--;
	}
}

void sha256_init(t_sha256_context *context)
{
	context->h0		   = 0x6A09E667;
	context->h1		   = 0xBB67AE85;
	context->h2		   = 0x3C6EF372;
	context->h3		   = 0xA54FF53A;
	context->h4		   = 0x510E527F;
	context->h5		   = 0x9B05688C;
	context->h6		   = 0x1F83D9AB;
	context->h7		   = 0x5BE0CD19;
	context->length	   = 0;
	context->available = 0;
}

int sha256(t_ft_ssl *ft_ssl)
{
	return (OK);
}
