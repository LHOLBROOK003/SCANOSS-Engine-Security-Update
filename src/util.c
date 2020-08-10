// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * src/util.c
 *
 * Data conversion utilities
 *
 * Copyright (C) 2018-2020 SCANOSS.COM
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/* Reverse an uint32 number  */
void uint32_reverse(uint8_t *data)
{
	uint8_t tmp = data[0];
	data[0] = data[3];
	data[3] = tmp;
	tmp = data[1];
	data[1] = data[2];
	data[2] = tmp;
}

uint8_t h2d(uint8_t h)
{
	if (h >= '0' && h <= '9')
		return h - '0';
	else if (h >= 'a' && h <= 'f')
		return h - 'a' + 10;
	else if (h >= 'A' && h <= 'F')
		return h - 'A' + 10;
	return 0;
}

void hex_to_bin(char *hex, uint32_t len, uint8_t *out)
{
	uint32_t ptr = 0;
	for (uint32_t i = 0; i < len; i += 2)
		out[ptr++] = 16 * h2d(hex[i]) + h2d(hex[i + 1]);
}

bool md5cmp(uint8_t *md51, uint8_t *md52)
{
	for (int i = 0; i < 16; i++)
		if (md51[i] != md52[i])
			return false;
	return true;
}

void trim(char *str)
{
    int i = 0;

    /* Left trim */
    int len = strlen(str);
    for (i = 0; i < len; i++) if (!isspace(str[i])) break;
    if (i) memmove(str, str + i, strlen(str + i) + 1);

    /* Right trim */
    len = strlen(str);
    for (i = len - 1; i >= 0 ; i--) if (!isspace(str[i])) break;
    str[i + 1] = 0;
}

/*
    Returns a hexadecimal representation of the first "len" bytes in "bin"
*/
char *bin_to_hex(uint8_t *bin, uint32_t len)
{
	uint8_t digits[] = "0123456789abcdef";
	char *out = malloc(2 * len + 1);
	uint32_t ptr = 0;

	for (uint32_t i = 0; i < len; i++)
	{
		out[ptr++] = digits[(bin[i] & 0xF0) >> 4];
		out[ptr++] = digits[bin[i] & 0x0F];
	}

	out[ptr] = 0;
	return out;
}
