/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 17:53:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/09/05 17:53:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"

static const t_u64 g_koef[] = {
	0x428a2f98d728ae22ul, 0x7137449123ef65cdul,
	0xb5c0fbcfec4d3b2ful, 0xe9b5dba58189dbbcul,
	0x3956c25bf348b538ul, 0x59f111f1b605d019ul,
	0x923f82a4af194f9bul, 0xab1c5ed5da6d8118ul,
	0xd807aa98a3030242ul, 0x12835b0145706fbeul,
	0x243185be4ee4b28cul, 0x550c7dc3d5ffb4e2ul,
	0x72be5d74f27b896ful, 0x80deb1fe3b1696b1ul,
	0x9bdc06a725c71235ul, 0xc19bf174cf692694ul,
	0xe49b69c19ef14ad2ul, 0xefbe4786384f25e3ul,
	0x0fc19dc68b8cd5b5ul, 0x240ca1cc77ac9c65ul,
	0x2de92c6f592b0275ul, 0x4a7484aa6ea6e483ul,
	0x5cb0a9dcbd41fbd4ul, 0x76f988da831153b5ul,
	0x983e5152ee66dfabul, 0xa831c66d2db43210ul,
	0xb00327c898fb213ful, 0xbf597fc7beef0ee4ul,
	0xc6e00bf33da88fc2ul, 0xd5a79147930aa725ul,
	0x06ca6351e003826ful, 0x142929670a0e6e70ul,
	0x27b70a8546d22ffcul, 0x2e1b21385c26c926ul,
	0x4d2c6dfc5ac42aedul, 0x53380d139d95b3dful,
	0x650a73548baf63deul, 0x766a0abb3c77b2a8ul,
	0x81c2c92e47edaee6ul, 0x92722c851482353bul,
	0xa2bfe8a14cf10364ul, 0xa81a664bbc423001ul,
	0xc24b8b70d0f89791ul, 0xc76c51a30654be30ul,
	0xd192e819d6ef5218ul, 0xd69906245565a910ul,
	0xf40e35855771202aul, 0x106aa07032bbd1b8ul,
	0x19a4c116b8d2d0c8ul, 0x1e376c085141ab53ul,
	0x2748774cdf8eeb99ul, 0x34b0bcb5e19b48a8ul,
	0x391c0cb3c5c95a63ul, 0x4ed8aa4ae3418acbul,
	0x5b9cca4f7763e373ul, 0x682e6ff3d6b2b8a3ul,
	0x748f82ee5defb2fcul, 0x78a5636f43172f60ul,
	0x84c87814a1f0ab72ul, 0x8cc702081a6439ecul,
	0x90befffa23631e28ul, 0xa4506cebde82bde9ul,
	0xbef9a3f7b2c67915ul, 0xc67178f2e372532bul,
	0xca273eceea26619cul, 0xd186b8c721c0c207ul,
	0xeada7dd6cde0eb1eul, 0xf57d4f7fee6ed178ul,
	0x06f067aa72176fbaul, 0x0a637dc5a2c898a6ul,
	0x113f9804bef90daeul, 0x1b710b35131c471bul,
	0x28db77f523047d84ul, 0x32caab7b40c72493ul,
	0x3c9ebe0a15c9bebcul, 0x431d67c49c100d4cul,
	0x4cc5d4becb3e42b6ul, 0x597f299cfc657e2aul,
	0x5fcb6fab3ad6faecul, 0x6c44198c4a475817ul
};

static t_u64 letobe64(t_u64 val) {
	t_u64 res;
	res = val >> 56;
	val <<= 8;
	res |= ((val >> 56) << 8);
	val <<= 8;
	res |= ((val >> 56) << 16);
	val <<= 8;
	res |= ((val >> 56) << 24);
	val <<= 8;
	res |= ((val >> 56) << 32);
	val <<= 8;
	res |= ((val >> 56) << 40);
	val <<= 8;
	res |= ((val >> 56) << 48);
	val <<= 8;
	res |= ((val >> 56) << 56);
	return (res);
}

static t_u64 cycle_rotate_right(t_u64 value, t_u64 shift) {
	return ((value >> shift) | (value << (64u - shift)));
}

static t_u64 Sigma0(t_u64 x) {
	return (cycle_rotate_right(x, 28) ^ cycle_rotate_right(x, 34) ^
			cycle_rotate_right(x, 39));
}

static t_u64 Sigma1(t_u64 x) {
	return (cycle_rotate_right(x, 14) ^ cycle_rotate_right(x, 18) ^
			cycle_rotate_right(x, 41));
}

static t_u64 sigma0(t_u64 x) {
	return (cycle_rotate_right(x, 1) ^ cycle_rotate_right(x, 8) ^
			(x >> 7));
}

static t_u64 sigma1(t_u64 x) {
	return (cycle_rotate_right(x, 19) ^ cycle_rotate_right(x, 61) ^
			(x >> 6));
}

static t_u64 Ch(t_u64 x, t_u64 y, t_u64 z) {
	return ((x & y) ^ ((~x) & z));
}
static t_u64 Maj(t_u64 x, t_u64 y, t_u64 z) {
	return ((x & y) ^ (x & z) ^ (y & z));
}

static void process_body(t_sha512_context *context) {
	int i;
	t_u64 s0;
	t_u64 s1;
	t_u64 w[16];
	t_u64 a, b, c, d, e, f, g, h;
	t_u64 t2, t1;

	a = context->h[0];
	b = context->h[1];
	c = context->h[2];
	d = context->h[3];
	e = context->h[4];
	f = context->h[5];
	g = context->h[6];
	h = context->h[7];
	i = 0 - 1;
	while (++i < 16) {
		w[i] = letobe64(context->chunks[i]);
		t1 = h + Sigma1(e) + Ch(e, f, g) + g_koef[i] + w[i];
		t2 = Sigma0(a) + Maj(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}
	i = 16 - 1;
	while (++i < 80) {
		s0 = sigma0(w[(i + 1) & 0xF]);
		s1 = sigma1(w[(i + 14) & 0xF]);
		w[i & 0xF] += s1 + w[(i + 9) & 0xF] + s0;
		t1 = h + Sigma1(e) + Ch(e, f, g) + g_koef[i] + w[i & 0xF];
		t2 = Sigma0(a) + Maj(a, b, c);
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

static void transform(unsigned char *digest, const t_sha512_context *context) {
	unsigned long	i;

	i = 0;
	while (i < (sizeof(context->h) / sizeof(context->h[0]))) {
		digest[i * 8 + 0] = context->h[i] >> 56;
		digest[i * 8 + 1] = context->h[i] >> 48;
		digest[i * 8 + 2] = context->h[i] >> 40;
		digest[i * 8 + 3] = context->h[i] >> 32;
		digest[i * 8 + 4] = context->h[i] >> 24;
		digest[i * 8 + 5] = context->h[i] >> 16;
		digest[i * 8 + 6] = context->h[i] >> 8;
		digest[i * 8 + 7] = context->h[i] >> 0;
		i++;
	}
}

void sha512_final(unsigned char *digest, t_sha512_context *context) {
	context->buf[context->available++] = 0x80;
	if (context->available > 120) {
		while (context->available < 128) {
			context->buf[context->available++] = 0;
		}
		process_body(context);
		context->available = 0;
	}
	while (context->available < 120) {
		context->buf[context->available++] = 0;
	}
	context->chunks[14] = letobe64(context->length[1]);
	context->chunks[15] = letobe64(context->length[0]);
	process_body(context);
	transform(digest, context);
}

void sha512_update(t_sha512_context *context, const char *buf, size_t size) {
	t_u64 length = size << 3;
	if ((context->length[0] + length) < context->length[0]) {
		context->length[1]++;
	}
	context->length[0] += length;
	while (size) {
		context->buf[context->available++] = *buf++;
		if (context->available == 128) {
			process_body(context);
			context->available = 0;
		}
		size--;
	}
}

void sha512_init(t_sha512_context *context) {
	context->h[0] = 0x6a09e667f3bcc908;
	context->h[1] = 0xbb67ae8584caa73b;
	context->h[2] = 0x3c6ef372fe94f82b;
	context->h[3] = 0xa54ff53a5f1d36f1;
	context->h[4] = 0x510e527fade682d1;
	context->h[5] = 0x9b05688c2b3e6c1f;
	context->h[6] = 0x1f83d9abfb41bd6b;
	context->h[7] = 0x5be0cd19137e2179;
	context->length[0] = 0;
	context->length[1] = 0;
	context->available = 0;
}
