/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 17:53:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/09/05 17:53:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha224.h"

static const t_u32 g_koef[] = {
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

static t_u32 letobe(t_u32 val)
{
	return (val << 24 | (val & 0xFF00) << 8 | (val & 0xFF0000) >> 8 | val >> 24);
}

static t_u32 cycle_rotate_right(t_u32 value, t_u32 shift) {
	return ((value >> shift) | (value << (32u - shift)));
}

static void process_body(t_sha224_context *context) {
	int i;
	t_u32 s0;
	t_u32 s1;
	t_u32 w[64];
	t_u32 a, b, c, d, e, f, g, h;
	t_u32 e0, ma, t2, e1, ch, t1;
	i = 0 - 1;
	while (++i < 16) {
		w[i] = letobe(context->chunks[i]);
	}
	i = 16 - 1;
	while (++i < 64) {
		s0 = cycle_rotate_right(w[i - 15], 7) ^
			 cycle_rotate_right(w[i - 15], 18) ^
			 (w[i - 15] >> 3);
		s1 = cycle_rotate_right(w[i - 2], 17) ^
			 cycle_rotate_right(w[i - 2], 19) ^
			 (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}
	a = context->h[0];
	b = context->h[1];
	c = context->h[2];
	d = context->h[3];
	e = context->h[4];
	f = context->h[5];
	g = context->h[6];
	h = context->h[7];
	i = 0 - 1;
	while (++i < 64) {
		e0 = cycle_rotate_right(a, 2) ^ cycle_rotate_right(a, 13) ^
			 cycle_rotate_right(a, 22);
		ma = (a & b) ^ (a & c) ^ (b & c);
		t2 = e0 + ma;
		e1 = cycle_rotate_right(e, 6) ^ cycle_rotate_right(e, 11) ^
			 cycle_rotate_right(e, 25);
		ch = (e & f) ^ ((~e) & g);
		t1 = h + e1 + ch + g_koef[i] + w[i];
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}
	context->h[0] += a;
	context->h[1] += b;
	context->h[2] += c;
	context->h[3] += d;
	context->h[4] += e;
	context->h[5] += f;
	context->h[6] += g;
	context->h[7] += h;
}

static void transform(unsigned char *digest, const t_sha224_context *context) {
	unsigned long	i;

	i = 0;
	while (i < (sizeof(context->h) / sizeof(context->h[0]) - 1)) {
		digest[i * 4 + 0] = context->h[i] >> 24;
		digest[i * 4 + 1] = context->h[i] >> 16;
		digest[i * 4 + 2] = context->h[i] >> 8;
		digest[i * 4 + 3] = context->h[i] >> 0;
		i++;
	}
}

void sha224_final(unsigned char *digest, t_sha224_context *context) {
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
	context->chunks[14] = letobe(context->length >> 32);
	context->chunks[15] = letobe(context->length);
	process_body(context);
	transform(digest, context);
}

void sha224_update(t_sha224_context *context, const char *buf, size_t size) {
	context->length += size;
	while (size) {
		context->buf[context->available++] = *buf++;
		if (context->available == 64) {
			process_body(context);
			context->available = 0;
		}
		size--;
	}
}

void sha224_init(t_sha224_context *context) {
	context->h[0]		   = 0xC1059ED8;
	context->h[1]		   = 0x367CD507;
	context->h[2]		   = 0x3070DD17;
	context->h[3]		   = 0xF70E5939;
	context->h[4]		   = 0xFFC00B31;
	context->h[5]		   = 0x68581511;
	context->h[6]		   = 0x64F98FA7;
	context->h[7]		   = 0xBEFA4FA4;
	context->length	   = 0;
	context->available = 0;
}
