/*
 * Fixed width font for numbers that looks like LCD panel digits
 * This font including pad pixels, will render 14x24 pixels on the display 
 *
 * This font is very useful when using overstrike as all characters & numbers
 * are all the same width.
 *
 * This font is not a complete character set. The font only contains
 * the characters: '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '9', ':'
 *
 * This font is nice for certain applications like clocks, signed values or decimal point values.
 *
 */


GLCDFONTDECL(lcdnums14x24) =
{
  0x0, 0x0,	// size of zero indicates fixed width font
    13,		// width  (will be 14 with pad pixel on right)
    23,		// height (will be 24 with pad pixel on bottom)
    '+',	// first char
    16,		// char count

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x10, 0x38, 0x38, 0x38, 0xff, 0xff, 0x38, 0x38, 0x38, 0x10, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,   // +

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x78, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00,   // ,

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x10, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x10, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // -

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xe0, 0xe0, 0x40, 0x00, 0x00, 0x00, 0x00,   // .

0x00, 0x00, 0x02, 0x06, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x06, 0x02, 0x00,
0x00, 0x00, 0x10, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x10, 0x00,
0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x00,   // /

0x00, 0xfc, 0xfa, 0xf6, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xf6, 0xfa, 0xfc,
0x00, 0xef, 0xc7, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0xc7, 0xef,
0x00, 0x7f, 0xbf, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f,   // 0

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0xfc,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0xc7, 0xef,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x7f,   // 1

0x00, 0x00, 0x02, 0x06, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xf6, 0xfa, 0xfc,
0x00, 0xe0, 0xd0, 0xb8, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x3b, 0x17, 0x0f,
0x00, 0x7f, 0xbf, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x00,   // 2

0x00, 0x00, 0x02, 0x06, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xf6, 0xfa, 0xfc,
0x00, 0x00, 0x10, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xbb, 0xd7, 0xef,
0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f,   // 3

0x00, 0xfc, 0xf8, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0xfc,
0x00, 0x0f, 0x17, 0x3b, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xbb, 0xd7, 0xef,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x7f,   // 4

0x00, 0xfc, 0xfa, 0xf6, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x06, 0x02, 0x00,
0x00, 0x0f, 0x17, 0x3b, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xb8, 0xd0, 0xe0,
0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f,   // 5

0x00, 0xfc, 0xfa, 0xf6, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x06, 0x02, 0x00,
0x00, 0xef, 0xd7, 0xbb, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xb8, 0xd0, 0xe0,
0x00, 0x7f, 0xbf, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f,   // 6

0x00, 0x00, 0x02, 0x06, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xf6, 0xfa, 0xfc,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0xc7, 0xef,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x7f,   // 7

0x00, 0xfc, 0xfa, 0xf6, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xf6, 0xfa, 0xfc,
0x00, 0xef, 0xd7, 0xbb, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xbb, 0xd7, 0xef,
0x00, 0x7f, 0xbf, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f,   // 8

0x00, 0xfc, 0xfa, 0xf6, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xf6, 0xfa, 0xfc,
0x00, 0x0f, 0x17, 0x3b, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xbb, 0xd7, 0xef,
0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f,   // 9

0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,  // :
0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0e, 0x0e, 0x04, 0x00, 0x00, 0x00, 0x00
};
