#include <stdint.h>
#include <math.h>

/** \file
 * External interface
 *
 * External functions required to compile demo file.
 */

void moveto(int x, int y);
void lineto(int x, int y);
void brightto(int x, int y, int bright);

extern int hour();
extern int minute();
extern int second();
extern int millis();
extern int year();
extern int month();
extern int day();
extern int weekday();

extern const char *dayStr(int weekday);



/** \file
 * Super simple font from Asteroids.
 *
 * http://www.edge-online.com/wp-content/uploads/edgeonline/oldfiles/images/feature_article/2009/05/asteroids2.jpg
 */

typedef struct {
	uint8_t points[8]; // 4 bits x, 4 bits y
} asteroids_char_t;

#define FONT_UP 0xFE
#define FONT_LAST 0xFF

#define P(x,y)	((((x) & 0xF) << 4) | (((y) & 0xF) << 0))
 
const asteroids_char_t asteroids_font[] = {
	['0' - 0x20] = { P(0,0), P(8,0), P(8,12), P(0,12), P(0,0), P(8,12), FONT_LAST },
	['1' - 0x20] = { P(4,0), P(4,12), P(3,10), FONT_LAST },
	['2' - 0x20] = { P(0,12), P(8,12), P(8,7), P(0,5), P(0,0), P(8,0), FONT_LAST },
	['3' - 0x20] = { P(0,12), P(8,12), P(8,0), P(0,0), FONT_UP, P(0,6), P(8,6), FONT_LAST },
	['4' - 0x20] = { P(0,12), P(0,6), P(8,6), FONT_UP, P(8,12), P(8,0), FONT_LAST },
	['5' - 0x20] = { P(0,0), P(8,0), P(8,6), P(0,7), P(0,12), P(8,12), FONT_LAST },
	['6' - 0x20] = { P(0,12), P(0,0), P(8,0), P(8,5), P(0,7), FONT_LAST },
	['7' - 0x20] = { P(0,12), P(8,12), P(8,6), P(4,0), FONT_LAST },
	['8' - 0x20] = { P(0,0), P(8,0), P(8,12), P(0,12), P(0,0), FONT_UP, P(0,6), P(8,6), },
	['9' - 0x20] = { P(8,0), P(8,12), P(0,12), P(0,7), P(8,5), FONT_LAST },
	[' ' - 0x20] = { FONT_LAST },
	['.' - 0x20] = { P(3,0), P(4,0), FONT_LAST },
	[',' - 0x20] = { P(2,0), P(4,2), FONT_LAST },
	['-' - 0x20] = { P(2,6), P(6,6), FONT_LAST },
	['+' - 0x20] = { P(1,6), P(7,6), FONT_UP, P(4,9), P(4,3), FONT_LAST },
	['!' - 0x20] = { P(4,0), P(3,2), P(5,2), P(4,0), FONT_UP, P(4,4), P(4,12), FONT_LAST },
	['#' - 0x20] = { P(0,4), P(8,4), P(6,2), P(6,10), P(8,8), P(0,8), P(2,10), P(2,2) },
	['^' - 0x20] = { P(2,6), P(4,12), P(6,6), FONT_LAST },
	['=' - 0x20] = { P(1,4), P(7,4), FONT_UP, P(1,8), P(7,8), FONT_LAST },
	['*' - 0x20] = { P(0,0), P(4,12), P(8,0), P(0,8), P(8,8), P(0,0), FONT_LAST },
	['_' - 0x20] = { P(0,0), P(8,0), FONT_LAST },
	['/' - 0x20] = { P(0,0), P(8,12), FONT_LAST },
	['\\' - 0x20] = { P(0,12), P(8,0), FONT_LAST },
	['@' - 0x20] = { P(8,4), P(4,0), P(0,4), P(0,8), P(4,12), P(8,8), P(4,4), P(3,6) },
	['$' - 0x20] = { P(6,2), P(2,6), P(6,10), FONT_UP, P(4,12), P(4,0), FONT_LAST },
	['&' - 0x20] = { P(8,0), P(4,12), P(8,8), P(0,4), P(4,0), P(8,4), FONT_LAST },
	['[' - 0x20] = { P(6,0), P(2,0), P(2,12), P(6,12), FONT_LAST },
	[']' - 0x20] = { P(2,0), P(6,0), P(6,12), P(2,12), FONT_LAST },
	['(' - 0x20] = { P(6,0), P(2,4), P(2,8), P(6,12), FONT_LAST },
	[')' - 0x20] = { P(2,0), P(6,4), P(6,8), P(2,12), FONT_LAST },
	['{' - 0x20] = { P(6,0), P(4,2), P(4,10), P(6,12), FONT_UP, P(2,6), P(4,6), FONT_LAST },
	['}' - 0x20] = { P(4,0), P(6,2), P(6,10), P(4,12), FONT_UP, P(6,6), P(8,6), FONT_LAST },
	['%' - 0x20] = { P(0,0), P(8,12), FONT_UP, P(2,10), P(2,8), FONT_UP, P(6,4), P(6,2) },
	['<' - 0x20] = { P(6,0), P(2,6), P(6,12), FONT_LAST },
	['>' - 0x20] = { P(2,0), P(6,6), P(2,12), FONT_LAST },
	['|' - 0x20] = { P(4,0), P(4,5), FONT_UP, P(4,6), P(4,12), FONT_LAST },
	[':' - 0x20] = { P(4,9), P(4,7), FONT_UP, P(4,5), P(4,3), FONT_LAST },
	[';' - 0x20] = { P(4,9), P(4,7), FONT_UP, P(4,5), P(1,2), FONT_LAST },
	['"' - 0x20] = { P(2,10), P(2,6), FONT_UP, P(6,10), P(6,6), FONT_LAST },
	['\'' - 0x20] = { P(2,6), P(6,10), FONT_LAST },
	['`' - 0x20] = { P(2,10), P(6,6), FONT_LAST },
	['~' - 0x20] = { P(0,4), P(2,8), P(6,4), P(8,8), FONT_LAST },
	['?' - 0x20] = { P(0,8), P(4,12), P(8,8), P(4,4), FONT_UP, P(4,1), P(4,0), FONT_LAST },
	['A' - 0x20] = { P(0,0), P(0,8), P(4,12), P(8,8), P(8,0), FONT_UP, P(0,4), P(8,4) },
	['B' - 0x20] = { P(0,0), P(0,12), P(4,12), P(8,10), P(4,6), P(8,2), P(4,0), P(0,0) },
	['C' - 0x20] = { P(8,0), P(0,0), P(0,12), P(8,12), FONT_LAST },
	['D' - 0x20] = { P(0,0), P(0,12), P(4,12), P(8,8), P(8,4), P(4,0), P(0,0), FONT_LAST },
	['E' - 0x20] = { P(8,0), P(0,0), P(0,12), P(8,12), FONT_UP, P(0,6), P(6,6), FONT_LAST },
	['F' - 0x20] = { P(0,0), P(0,12), P(8,12), FONT_UP, P(0,6), P(6,6), FONT_LAST },
	['G' - 0x20] = { P(6,6), P(8,4), P(8,0), P(0,0), P(0,12), P(8,12), FONT_LAST },
	['H' - 0x20] = { P(0,0), P(0,12), FONT_UP, P(0,6), P(8,6), FONT_UP, P(8,12), P(8,0) },
	['I' - 0x20] = { P(0,0), P(8,0), FONT_UP, P(4,0), P(4,12), FONT_UP, P(0,12), P(8,12) },
	['J' - 0x20] = { P(0,4), P(4,0), P(8,0), P(8,12), FONT_LAST },
	['K' - 0x20] = { P(0,0), P(0,12), FONT_UP, P(8,12), P(0,6), P(6,0), FONT_LAST },
	['L' - 0x20] = { P(8,0), P(0,0), P(0,12), FONT_LAST },
	['M' - 0x20] = { P(0,0), P(0,12), P(4,8), P(8,12), P(8,0), FONT_LAST },
	['N' - 0x20] = { P(0,0), P(0,12), P(8,0), P(8,12), FONT_LAST },
	['O' - 0x20] = { P(0,0), P(0,12), P(8,12), P(8,0), P(0,0), FONT_LAST },
	['P' - 0x20] = { P(0,0), P(0,12), P(8,12), P(8,6), P(0,5), FONT_LAST },
	['Q' - 0x20] = { P(0,0), P(0,12), P(8,12), P(8,4), P(0,0), FONT_UP, P(4,4), P(8,0) },
	['R' - 0x20] = { P(0,0), P(0,12), P(8,12), P(8,6), P(0,5), FONT_UP, P(4,5), P(8,0) },
	['S' - 0x20] = { P(0,2), P(2,0), P(8,0), P(8,5), P(0,7), P(0,12), P(6,12), P(8,10) },
	['T' - 0x20] = { P(0,12), P(8,12), FONT_UP, P(4,12), P(4,0), FONT_LAST },
	['U' - 0x20] = { P(0,12), P(0,2), P(4,0), P(8,2), P(8,12), FONT_LAST },
	['V' - 0x20] = { P(0,12), P(4,0), P(8,12), FONT_LAST },
	['W' - 0x20] = { P(0,12), P(2,0), P(4,4), P(6,0), P(8,12), FONT_LAST },
	['X' - 0x20] = { P(0,0), P(8,12), FONT_UP, P(0,12), P(8,0), FONT_LAST },
	['Y' - 0x20] = { P(0,12), P(4,6), P(8,12), FONT_UP, P(4,6), P(4,0), FONT_LAST },
	['Z' - 0x20] = { P(0,12), P(8,12), P(0,0), P(8,0), FONT_UP, P(2,6), P(6,6), FONT_LAST },
};



/** \file
 * Complete ASCII Hershey Simplex font.
 *
 * http://paulbourke.net/dataformats/hershey/
 *
 * A few characters are simplified and all are stored at
 * offset ' ' (0x20).
 */

typedef struct {
	uint8_t count;
	uint8_t width;
	int8_t points[62]; // up to 31 xy points
} hershey_char_t;

const hershey_char_t hershey_simplex[] = {
	 { 
	    0,16, /* Ascii 32 */
	},
    	 {
		8,10, /* Ascii 33 */
	    { 5,21, 5,7, -1,-1, 5,2, 4,1, 5,0, 6,1, 5,2, },
	},
	 {
	    5,16, /* Ascii 34 */
	    { 4,21, 4,14, -1,-1, 12,21, 12,14, },
	},
	 {
	   11,21, /* Ascii 35 */
	   11,25, 4,-7, -1,-1, 17,25, 10,-7, -1,-1, 4,12, 18,12, -1,-1, 3, 6, 17, 6,
	},
	 {
	   26,20, /* Ascii 36 */
	    8,25, 8,-4,-1,-1,12,25,12,-4,-1,-1,17,18,15,20,12,21, 8,21, 5,20, 3,
	   18, 3,16, 4,14, 5,13, 7,12,13,10,15, 9,16, 8,17, 6,17, 3,15, 1,12, 0,
	    8, 0, 5, 1, 3, 3,
	},
   	{
	   31,24, /* Ascii 37 */
	   { 21,21, 3, 0,-1,-1, 8,21,10,19,10,17, 9,15, 7,14, 5,14, 3,16, 3,18, 4,
	   20, 6,21, 8,21,10,20,13,19,16,19,19,20,21,21,-1,-1,17, 7,15, 6,14, 4,
	   14, 2,16, 0,18, 0,20, 1,21, 3,21, 5,19, 7,17, 7, },
	},
	{
#if 0
   34,26, /* Ascii 38 */
   23,12,23,13,22,14,21,14,20,13,19,11,17, 6,15, 3,13, 1,11, 0, 7, 0, 5,
    1, 4, 2, 3, 4, 3, 6, 4, 8, 5, 9,12,13,13,14,14,16,14,18,13,20,11,21,
    9,20, 8,18, 8,16, 9,13,11,10,16, 3,18, 1,20, 0,22, 0,23, 1,23, 2,-1,
#endif
	},
	{
    7,10, /* Ascii 39 */
    { 5,19, 4,20, 5,21, 6,20, 6,18, 5,16, 4,15, },
	},
	{
   10,14, /* Ascii 40 */
   { 11,25, 9,23, 7,20, 5,16, 4,11, 4, 7, 5, 2, 7,-2, 9,-5,11,-7, },
	},
	{
   10,14, /* Ascii 41 */
    3,25, 5,23, 7,20, 9,16,10,11,10, 7, 9, 2, 7,-2, 5,-5, 3,-7,-1,-1,-1,
	},
	{
    8,16, /* Ascii 42 */
    8,21, 8, 9,-1,-1, 3,18,13,12,-1,-1,13,18, 3,12,-1,-1,-1,-1,-1,-1,-1,
	},
	{
    5,26, /* Ascii 43 */
   13,18,13, 0,-1,-1, 4, 9,22, 9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	},
	{
    8,10, /* Ascii 44 */
    6, 1, 5, 0, 4, 1, 5, 2, 6, 1, 6,-1, 5,-3, 4,-4,-1,-1,-1,-1,-1,-1,-1,
	},
	{
    2,26, /* Ascii 45 */
    4, 9,22, 9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	},
	{
    5,10, /* Ascii 46 */
    5, 2, 4, 1, 5, 0, 6, 1, 5, 2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	},
	{
    2,22, /* Ascii 47 */
   20,25, 2,-7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	},
	{
   17,20, /* Ascii 48 */
    9,21, 6,20, 4,17, 3,12, 3, 9, 4, 4, 6, 1, 9, 0,11, 0,14, 1,16, 4,17,
    9,17,12,16,17,14,20,11,21, 9,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	},
	{
    4,20, /* Ascii 49 */
    6,17, 8,18,11,21,11, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	},
	{
   14,20, /* Ascii 50 */
    4,16, 4,17, 5,19, 6,20, 8,21,12,21,14,20,15,19,16,17,16,15,15,13,13,
   10, 3, 0,17, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	},
	{
   15,20, /* Ascii 51 */
    5,21,16,21,10,13,13,13,15,12,16,11,17, 8,17, 6,16, 3,14, 1,11, 0, 8,
    0, 5, 1, 4, 2, 3, 4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	},
	{
    6,20, /* Ascii 52 */
   13,21, 3, 7,18, 7,-1,-1,13,21,13, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	},
	{
   17,20, /* Ascii 53 */
   15,21, 5,21, 4,12, 5,13, 8,14,11,14,14,13,16,11,17, 8,17, 6,16, 3,14,
    1,11, 0, 8, 0, 5, 1, 4, 2, 3, 4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	},
	{
   23,20, /* Ascii 54 */
   16,18,15,20,12,21,10,21, 7,20, 5,17, 4,12, 4, 7, 5, 3, 7, 1,10, 0,11,
    0,14, 1,16, 3,17, 6,17, 7,16,10,14,12,11,13,10,13, 7,12, 5,10, 4, 7,
	},
	{
    5,20, /* Ascii 55 */
   17,21, 7, 0,-1,-1, 3,21,17,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	},
	{
   29,20, /* Ascii 56 */
    8,21, 5,20, 4,18, 4,16, 5,14, 7,13,11,12,14,11,16, 9,17, 7,17, 4,16,
    2,15, 1,12, 0, 8, 0, 5, 1, 4, 2, 3, 4, 3, 7, 4, 9, 6,11, 9,12,13,13,
   15,14,16,16,16,18,15,20,12,21, 8,21,
	},
	{
   23,20, /* Ascii 57 */
   16,14,15,11,13, 9,10, 8, 9, 8, 6, 9, 4,11, 3,14, 3,15, 4,18, 6,20, 9,
   21,10,21,13,20,15,18,16,14,16, 9,15, 4,13, 1,10, 0, 8, 0, 5, 1, 4, 3,
	},
	{
   11,10, /* Ascii 58 */
    5,14, 4,13, 5,12, 6,13, 5,14,-1,-1, 5, 2, 4, 1, 5, 0, 6, 1, 5, 2,
	},
	{
   14,10, /* Ascii 59 */
    5,14, 4,13, 5,12, 6,13, 5,14,-1,-1, 6, 1, 5, 0, 4, 1, 5, 2, 6, 1, 6,
   -1, 5,-3, 4,-4,
	},
	{
    3,24, /* Ascii 60 */
   20,18, 4, 9,20, 0,
	},
	{
    5,26, /* Ascii 61 */
    4,12,22,12,-1,-1, 4, 6,22, 6,
	},
	{
    3,24, /* Ascii 62 */
    4,18,20, 9, 4, 0,
	},
	{
   20,18, /* Ascii 63 */
    3,16, 3,17, 4,19, 5,20, 7,21,11,21,13,20,14,19,15,17,15,15,14,13,13,
   12, 9,10, 9, 7,-1,-1, 9, 2, 8, 1, 9, 0,10, 1, 9, 2,
	},
	{
#if 0
   55,27, /* Ascii 64 */
   18,13,17,15,15,16,12,16,10,15, 9,14, 8,11, 8, 8, 9, 6,11, 5,14, 5,16,
    6,17, 8,-1,-1,12,16,10,14, 9,11, 9, 8,10, 6,11, 5,-1,-1,18,16,17, 8,
   17, 6,19, 5,21, 5,23, 7,24,10,24,12,23,15,22,17,20,19,18,20,15,21,12,
   21, 9,20, 7,19, 5,17, 4,15, 3,12, 3, 9, 4, 6, 5, 4, 7, 2, 9, 1,12, 0,
   15, 0,18, 1,20, 2,21, 3,-1,-1,19,16,18, 8,18, 6,19, 5,
#endif
	},
	{
    8,18, /* Ascii 65 */
    9,21, 1, 0,-1,-1, 9,21,17, 0,-1,-1, 4, 7,14, 7,
	},
	{
   23,21, /* Ascii 66 */
    4,21, 4, 0,-1,-1, 4,21,13,21,16,20,17,19,18,17,18,15,17,13,16,12,13,
   11,-1,-1, 4,11,13,11,16,10,17, 9,18, 7,18, 4,17, 2,16, 1,13, 0, 4, 0,
	},
	{
   18,21, /* Ascii 67 */
   18,16,17,18,15,20,13,21, 9,21, 7,20, 5,18, 4,16, 3,13, 3, 8, 4, 5, 5,
    3, 7, 1, 9, 0,13, 0,15, 1,17, 3,18, 5,
	},
	{
   15,21, /* Ascii 68 */
    4,21, 4, 0,-1,-1, 4,21,11,21,14,20,16,18,17,16,18,13,18, 8,17, 5,16,
    3,14, 1,11, 0, 4, 0,
	},
	{
   11,19, /* Ascii 69 */
    4,21, 4, 0,-1,-1, 4,21,17,21,-1,-1, 4,11,12,11,-1,-1, 4, 0,17, 0,
	},
	{
    8,18, /* Ascii 70 */
    4,21, 4, 0,-1,-1, 4,21,17,21,-1,-1, 4,11,12,11,
	},
	{
   22,21, /* Ascii 71 */
   18,16,17,18,15,20,13,21, 9,21, 7,20, 5,18, 4,16, 3,13, 3, 8, 4, 5, 5,
    3, 7, 1, 9, 0,13, 0,15, 1,17, 3,18, 5,18, 8,-1,-1,13, 8,18, 8,
	},
	{
    8,22, /* Ascii 72 */
    4,21, 4, 0,-1,-1,18,21,18, 0,-1,-1, 4,11,18,11,
	},
	{
    2, 8, /* Ascii 73 */
    4,21, 4, 0,
	},
	{
   10,16, /* Ascii 74 */
   12,21,12, 5,11, 2,10, 1, 8, 0, 6, 0, 4, 1, 3, 2, 2, 5, 2, 7,
	},
	{
    8,21, /* Ascii 75 */
    4,21, 4, 0,-1,-1,18,21, 4, 7,-1,-1, 9,12,18, 0,
	},
	{
    5,17, /* Ascii 76 */
    4,21, 4, 0,-1,-1, 4, 0,16, 0,
	},
	{
   11,24, /* Ascii 77 */
    4,21, 4, 0,-1,-1, 4,21,12, 0,-1,-1,20,21,12, 0,-1,-1,20,21,20, 0,
	},
	{
    8,22, /* Ascii 78 */
    4,21, 4, 0,-1,-1, 4,21,18, 0,-1,-1,18,21,18, 0,
	},
	{
   21,22, /* Ascii 79 */
    9,21, 7,20, 5,18, 4,16, 3,13, 3, 8, 4, 5, 5, 3, 7, 1, 9, 0,13, 0,15,
    1,17, 3,18, 5,19, 8,19,13,18,16,17,18,15,20,13,21, 9,21,
	},
	{
   13,21, /* Ascii 80 */
    4,21, 4, 0,-1,-1, 4,21,13,21,16,20,17,19,18,17,18,14,17,12,16,11,13,
   10, 4,10,
	},
	{
   24,22, /* Ascii 81 */
    9,21, 7,20, 5,18, 4,16, 3,13, 3, 8, 4, 5, 5, 3, 7, 1, 9, 0,13, 0,15,
    1,17, 3,18, 5,19, 8,19,13,18,16,17,18,15,20,13,21, 9,21,-1,-1,12, 4,
   18,-2,
	},
	{
   16,21, /* Ascii 82 */
    4,21, 4, 0,-1,-1, 4,21,13,21,16,20,17,19,18,17,18,15,17,13,16,12,13,
   11, 4,11,-1,-1,11,11,18, 0,
	},
	{
   20,20, /* Ascii 83 */
   17,18,15,20,12,21, 8,21, 5,20, 3,18, 3,16, 4,14, 5,13, 7,12,13,10,15,
    9,16, 8,17, 6,17, 3,15, 1,12, 0, 8, 0, 5, 1, 3, 3,
	},
	{
    5,16, /* Ascii 84 */
    8,21, 8, 0,-1,-1, 1,21,15,21,
	},
	{
   10,22, /* Ascii 85 */
    4,21, 4, 6, 5, 3, 7, 1,10, 0,12, 0,15, 1,17, 3,18, 6,18,21,
	},
	{
    5,18, /* Ascii 86 */
    1,21, 9, 0,-1,-1,17,21, 9, 0,
	},
	{
   11,24, /* Ascii 87 */
    2,21, 7, 0,-1,-1,12,21, 7, 0,-1,-1,12,21,17, 0,-1,-1,22,21,17, 0,
	},
	{
    5,20, /* Ascii 88 */
    3,21,17, 0,-1,-1,17,21, 3, 0,
	},
	{
    6,18, /* Ascii 89 */
    1,21, 9,11, 9, 0,-1,-1,17,21, 9,11,
	},
	{
    8,20, /* Ascii 90 */
   17,21, 3, 0,-1,-1, 3,21,17,21,-1,-1, 3, 0,17, 0,
	},
	{
   11,14, /* Ascii 91 */
    4,25, 4,-7,-1,-1, 5,25, 5,-7,-1,-1, 4,25,11,25,-1,-1, 4,-7,11,-7,
	},
	{
    2,14, /* Ascii 92 */
    0,21,14,-3,
	},
	{
   11,14, /* Ascii 93 */
    9,25, 9,-7,-1,-1,10,25,10,-7,-1,-1, 3,25,10,25,-1,-1, 3,-7,10,-7,
	},
	{
   10,16, /* Ascii 94 */
    6,15, 8,18,10,15,-1,-1, 3,12, 8,17,13,12,-1,-1, 8,17, 8, 0,
	},
	{
    2,16, /* Ascii 95 */
    0,-2,16,-2,
	},
	{
    7,10, /* Ascii 96 */
    6,21, 5,20, 4,18, 4,16, 5,15, 6,16, 5,17,
	},
	{
   17,19, /* Ascii 97 */
   15,14,15, 0,-1,-1,15,11,13,13,11,14, 8,14, 6,13, 4,11, 3, 8, 3, 6, 4,
    3, 6, 1, 8, 0,11, 0,13, 1,15, 3,
	},
	{
   17,19, /* Ascii 98 */
    4,21, 4, 0,-1,-1, 4,11, 6,13, 8,14,11,14,13,13,15,11,16, 8,16, 6,15,
    3,13, 1,11, 0, 8, 0, 6, 1, 4, 3,
	},
	{
   14,18, /* Ascii 99 */
   15,11,13,13,11,14, 8,14, 6,13, 4,11, 3, 8, 3, 6, 4, 3, 6, 1, 8, 0,11,
    0,13, 1,15, 3,
	},
	{
   17,19, /* Ascii 100 */
   15,21,15, 0,-1,-1,15,11,13,13,11,14, 8,14, 6,13, 4,11, 3, 8, 3, 6, 4,
    3, 6, 1, 8, 0,11, 0,13, 1,15, 3,
	},
	{
   17,18, /* Ascii 101 */
    3, 8,15, 8,15,10,14,12,13,13,11,14, 8,14, 6,13, 4,11, 3, 8, 3, 6, 4,
    3, 6, 1, 8, 0,11, 0,13, 1,15, 3,
	},
	{
    8,12, /* Ascii 102 */
   10,21, 8,21, 6,20, 5,17, 5, 0,-1,-1, 2,14, 9,14,
	},
	{
   22,19, /* Ascii 103 */
   15,14,15,-2,14,-5,13,-6,11,-7, 8,-7, 6,-6,-1,-1,15,11,13,13,11,14, 8,
   14, 6,13, 4,11, 3, 8, 3, 6, 4, 3, 6, 1, 8, 0,11, 0,13, 1,15, 3,
	},
	{
   10,19, /* Ascii 104 */
    4,21, 4, 0,-1,-1, 4,10, 7,13, 9,14,12,14,14,13,15,10,15, 0,
	},
	{
    8, 8, /* Ascii 105 */
    3,21, 4,20, 5,21, 4,22, 3,21,-1,-1, 4,14, 4, 0,
	},
	{
   11,10, /* Ascii 106 */
    5,21, 6,20, 7,21, 6,22, 5,21,-1,-1, 6,14, 6,-3, 5,-6, 3,-7, 1,-7,
	},
	{
    8,17, /* Ascii 107 */
    4,21, 4, 0,-1,-1,14,14, 4, 4,-1,-1, 8, 8,15, 0,
	},
	{
    2, 8, /* Ascii 108 */
    4,21, 4, 0,
	},
	{
   18,30, /* Ascii 109 */
    4,14, 4, 0,-1,-1, 4,10, 7,13, 9,14,12,14,14,13,15,10,15, 0,-1,-1,15,
   10,18,13,20,14,23,14,25,13,26,10,26, 0,
	},
	{
   10,19, /* Ascii 110 */
    4,14, 4, 0,-1,-1, 4,10, 7,13, 9,14,12,14,14,13,15,10,15, 0,
	},
	{
   17,19, /* Ascii 111 */
    8,14, 6,13, 4,11, 3, 8, 3, 6, 4, 3, 6, 1, 8, 0,11, 0,13, 1,15, 3,16,
    6,16, 8,15,11,13,13,11,14, 8,14,
	},
	{
   17,19, /* Ascii 112 */
    4,14, 4,-7,-1,-1, 4,11, 6,13, 8,14,11,14,13,13,15,11,16, 8,16, 6,15,
    3,13, 1,11, 0, 8, 0, 6, 1, 4, 3,
	},
	{
   17,19, /* Ascii 113 */
   15,14,15,-7,-1,-1,15,11,13,13,11,14, 8,14, 6,13, 4,11, 3, 8, 3, 6, 4,
    3, 6, 1, 8, 0,11, 0,13, 1,15, 3,
	},
	{
    8,13, /* Ascii 114 */
    4,14, 4, 0,-1,-1, 4, 8, 5,11, 7,13, 9,14,12,14,
	},
	{
   17,17, /* Ascii 115 */
   14,11,13,13,10,14, 7,14, 4,13, 3,11, 4, 9, 6, 8,11, 7,13, 6,14, 4,14,
    3,13, 1,10, 0, 7, 0, 4, 1, 3, 3,
	},
	{
    8,12, /* Ascii 116 */
    5,21, 5, 4, 6, 1, 8, 0,10, 0,-1,-1, 2,14, 9,14,
	},
	{
   10,19, /* Ascii 117 */
    4,14, 4, 4, 5, 1, 7, 0,10, 0,12, 1,15, 4,-1,-1,15,14,15, 0,
	},
	{
    5,16, /* Ascii 118 */
    2,14, 8, 0,-1,-1,14,14, 8, 0,
	},
	{
   11,22, /* Ascii 119 */
    3,14, 7, 0,-1,-1,11,14, 7, 0,-1,-1,11,14,15, 0,-1,-1,19,14,15, 0,
	},
	{
    5,17, /* Ascii 120 */
    3,14,14, 0,-1,-1,14,14, 3, 0,
	},
	{
    9,16, /* Ascii 121 */
    2,14, 8, 0,-1,-1,14,14, 8, 0, 6,-4, 4,-6, 2,-7, 1,-7,
	},
	{
    8,17, /* Ascii 122 */
   14,14, 3, 0,-1,-1, 3,14,14,14,-1,-1, 3, 0,14, 0,
	},
	{
#if 0
   39,14, /* Ascii 123 */
    9,25, 7,24, 6,23, 5,21, 5,19, 6,17, 7,16, 8,14, 8,12, 6,10,-1,-1, 7,
   24, 6,22, 6,20, 7,18, 8,17, 9,15, 9,13, 8,11, 4, 9, 8, 7, 9, 5, 9, 3,
    8, 1, 7, 0, 6,-2, 6,-4, 7,-6,-1,-1, 6, 8, 8, 6, 8, 4, 7, 2, 6, 1, 5,
   -1, 5,-3, 6,-5, 7,-6, 9,-7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
#endif
	},
	{
    2, 8, /* Ascii 124 */
    4,25, 4,-7,
	},
	{
#if 0
   39,14, /* Ascii 125 */
    5,25, 7,24, 8,23, 9,21, 9,19, 8,17, 7,16, 6,14, 6,12, 8,10,-1,-1, 7,
   24, 8,22, 8,20, 7,18, 6,17, 5,15, 5,13, 6,11,10, 9, 6, 7, 5, 5, 5, 3,
    6, 1, 7, 0, 8,-2, 8,-4, 7,-6,-1,-1, 8, 8, 6, 6, 6, 4, 7, 2, 8, 1, 9,
   -1, 9,-3, 8,-5, 7,-6, 5,-7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
#endif
	},
	{
   23,24, /* Ascii 126 */
    3, 6, 3, 8, 4,11, 6,12, 8,12,10,11,14, 8,16, 7,18, 7,20, 8,21,10,-1,
   -1, 3, 8, 4,10, 6,11, 8,11,10,10,14, 7,16, 6,18, 6,20, 7,21,10,21,12,
	},
};



/** \file
 * Basic drawing routines.
 *
 * Working with buffer specified by vex_t handle.
 */

int
draw_character(
	char c,
	int x,
	int y,
	int size
)
{
#ifdef CONFIG_FONT_HERSHEY
	const hershey_char_t * const f = &hershey_simplex[c - ' '];
	int next_moveto = 1;

	for(int i = 0 ; i < f->count ; i++)
	{
		int dx = f->points[2*i+0];
		int dy = f->points[2*i+1];
		if (dx == -1)
		{
			next_moveto = 1;
			continue;
		}

		dx = (dx * size) * 3 / 4;
		dy = (dy * size) * 3 / 4;

		if (next_moveto)
			moveto(x + dx, y + dy);
		else
			lineto(x + dx, y + dy);

		next_moveto = 0;
	}

	return (f->width * size) * 3 / 4;
#else
	// Asteroids font only has upper case
	if ('a' <= c && c <= 'z')
		c -= 'a' - 'A';

	const uint8_t * const pts = asteroids_font[c - ' '].points;
	int next_moveto = 1;

	for(int i = 0 ; i < 8 ; i++)
	{
		uint8_t delta = pts[i];
		if (delta == FONT_LAST)
			break;
		if (delta == FONT_UP)
		{
			next_moveto = 1;
			continue;
		}

		unsigned dx = ((delta >> 4) & 0xF) * size;
		unsigned dy = ((delta >> 0) & 0xF) * size;

		if (next_moveto)
			moveto(x + dx, y + dy);
		else
			lineto(x + dx, y + dy);

		next_moveto = 0;
	}

	return 12 * size;
#endif
}

void
draw_string(
	const char * s,
	int x,
	int y,
	int size
)
{
	while(*s)
	{
		char c = *s++;
		x += draw_character(c, x, y, size);
	}
}

static void
draw_test_pattern()
{
	// fill in some points for test and calibration
	moveto(0,0);
	lineto(1024,0);
	lineto(1024,1024);
	lineto(0,1024);
	lineto(0,0);

	// triangle
	moveto(4095, 0);
	lineto(4095-512, 0);
	lineto(4095-0, 512);
	lineto(4095,0);

	// cross
	moveto(4095,4095);
	lineto(4095-512,4095);
	lineto(4095-512,4095-512);
	lineto(4095,4095-512);
	lineto(4095,4095);

	moveto(0,4095);
	lineto(512,4095);
	lineto(0,4095-512);
	lineto(512, 4095-512);
	lineto(0,4095);

	moveto(2047,2047-512);
	brightto(2047,2047+512,63);

	moveto(2047-512,2047);
	brightto(2047+512,2047,63);

	// and a gradiant scale
	for(int i = 1 ; i < 63 ; i += 4)
	{
		moveto(1600, 2048 + i * 8);
		vex_append(1900, 2048 + i * 8, i); 
	}

	// draw the sunburst pattern in the corner
	moveto(0,0);
	for(unsigned j = 0, i=0 ; j <= 1024 ; j += 128, i++)
	{
		if (i & 1)
		{
			moveto(1024,j);
			vex_append(0,0, i * 7);
		} else {
			vex_append(1024,j, i * 7);
		}
	}

	moveto(0,0);
	for(unsigned j = 0, i=0 ; j < 1024 ; j += 128, i++)
	{
		if (i & 1)
		{
			moveto(j,1024);
			vex_append(0,0, i * 7);
		} else {
			vex_append(j,1024, i * 7);
		}
	}

	draw_string("http://v.st/", 2048 - 450, 2048 + 600, 6);

	draw_string("Firmware built", 2100, 1900, 3);
	draw_string(__DATE__, 2100, 1830, 3);
	draw_string(__TIME__, 2100, 1760, 3);

	int y = 2400;
	const int line_size = 70;

	//draw_string("Options:", 1100, y, 3); y -= line_size;
#ifdef CONFIG_VECTREX
	draw_string("VECTREX", 2100, y, 3); y -= line_size;
#else
	draw_string("Vectorscope", 2100, y, 3); y -= line_size;
#endif
#ifdef FLIP_X
	draw_string("FLIP_X", 2100, y, 3); y -= line_size;
#endif
#ifdef FLIP_Y
	draw_string("FLIP_Y", 2100, y, 3); y -= line_size;
#endif
#ifdef SWAP_XY
	draw_string("SWAP_XY", 2100, y, 3); y -= line_size;
#endif
#ifdef FULL_SCALE
	draw_string("Fullscale", 2100, y, 3); y -= line_size;
#endif
#ifdef CONFIG_FONT_HERSHEY
	draw_string("Font Hershey", 2100, y, 3); y -= line_size;
#else
	draw_string("Font Asteroid", 2100, y, 3); y -= line_size;
#endif
}




/** \file
 * Clock for vector displays.
 *
 * More info: https://trmm.net/V.st
 *
 */

const int cx = 1024;
const int cy = 1024;

void
draw_hand(
	float a,
	int r,
	int hw
)
{
	const float sh = sin(a * M_PI/180);
	const float ch = cos(a * M_PI/180);

	if (hw == 0) {
		moveto(cx + r*sh/4,cy + r*ch/4);
		brightto(cx + r*sh, cy + r*ch, 63);
	} else {
		//moveto(cx-hw*sh, cy-hw*ch);
		moveto(cx-hw*ch, cy+hw*sh);
		lineto(cx+r*sh, cy+r*ch);
		lineto(cx+hw*ch, cy-hw*sh);
		//lineto(cx-hw*sh, cy-hw*ch);
	}
}


void
draw_ymd(
	int year,
	int m,
	int d,
	int x,
	int y,
	int size
)
{
	char t[16];
	t[0] = '0' + (year / 1000) % 10;
	t[1] = '0' + (year / 100) % 10;
	t[2] = '0' + (year / 10) % 10;
	t[3] = '0' + (year / 1) % 10;
	t[4] = '-';
	t[5] = '0' + m / 10;
	t[6] = '0' + m % 10;
	t[7] = '-';
	t[8] = '0' + d / 10;
	t[9] = '0' + d % 10;
	t[10] = '\0';
	draw_string(t, x, y, size);
}


void
draw_hms(
	int h,
	int m,
	int s,
	int x,
	int y,
	int size
)
{
	char t[16];
	t[0] = '0' + h / 10;
	t[1] = '0' + h % 10;
	t[2] = ':';
	t[3] = '0' + m / 10;
	t[4] = '0' + m % 10;
	t[5] = ':';
	t[6] = '0' + s / 10;
	t[7] = '0' + s % 10;
	t[8] = '\0';

	draw_string(t, x, y, size);
}


void
scopeclock_analog()
{
	const int rh = 900;
	const int r1 = 950;
	const int r2 = 1000;

	for(int t = 0 ; t < 360 ; t += 6)
	{
		const float st = sin(t*M_PI/180);
		const float ct = cos(t*M_PI/180);

		if (t == 0)
		{
			// twelve o'clock
			moveto(cx + st*rh - 20, cy + ct*rh);
			lineto(cx + st*r2 - 20 , cy + ct*r2);
			lineto(cx + st*r2 + 20 , cy + ct*r2);
			lineto(cx + st*rh + 20, cy + ct*rh);
			lineto(cx + st*rh - 20, cy + ct*rh);
		} else if (t % 15 == 0)
		{
			// normal hour
			if (t % 30 == 0)
			{
				moveto(cx + st*rh, cy + ct*rh);
				lineto(cx + st*r2, cy + ct*r2);
			}

			int h = t / 15;
			char t[3] = { '0' + h / 10, '0' + h % 10, '\0' };
			draw_string(t,
				cx + st*(r1-150) - 12*6,
				cy + ct*(r1-150) - 5*6,
				5);
		} else if (t % 6 == 0)
		{
			// normal second/minute marker
			moveto(cx + st*r1, cy + ct*r1);
			lineto(cx + st*r2, cy + ct*r2);
		}
	}

	const int h = hour();
	const int m = minute();
	const int s = second();
	static int last_sec;
	static int last_millis;


	// track the millis of the rollover to the next second
	if (last_sec != s)
	{
		last_millis = millis();
		last_sec = s;
	}
	const int ms = (millis() - last_millis) % 1000;

	draw_hand((h*60 + m) * 15 / 60.0, rh/2, 50);
	draw_hand((m*60 + s) * 6 / 60.0, rh, 50);
	draw_hand((s*1000 + ms) * 6 / 1000.0, 1023, 0);

	const int y_off = 768-20 + (h*60 + m) * 512 / (24*60);
	//const int y_off = 768-20 + (s*1000 + ms) * 512 / (60000);

	draw_hms(h,m,s, cx - 650, cy + 150, 12);
	draw_string(dayStr(weekday()), cx - 250, cy - 250, 4);
	draw_ymd(year(), month(), day(), cx - 300, cy - 400, 4);
}


void
scopeclock_digital()
{
	char t[32];

	const int y_off = hour() * 60 + minute();

	draw_hms(hour(), minute(), second(), 16, 256+y_off, 21);
	draw_ymd(year(), month(), day(), 64, 0+y_off, 16);


	static int px = 0;
	static int py = 0;
	static int vx = 2;
	static int vy = 3;

	draw_string("http://v.st/", px, py, 8);

	px += vx;
	py += vy;
	if (px < 0) {
		px = 0;
		vx = -vx;
	} else if (px > 2048 - 8*12*12) {
		px = 2048 - 8*12*12;
		vx = -vx;
	}

	if (py < 0) {
		py = 0;
		vy = -vy;
	} else if (py > 2048 - 8*16) {
		py = 2048 - 8*16;
		vy = -vy;
	}

	//_circle(1024, 1024, 300, 0);
	//_circle(1024, 1024, 300, 1);
	//_circle(1024, 1024, 300, 2);
}


void
alphabet_test()
{
	int size = 13;   // hershey
	//int size = 17; // asteroids
	draw_string("abcdefghij", 0, 1800, size);
	draw_string("klmnopqrst", 0, 1400, size);
	draw_string("uvwxyz0123", 0, 1000, size);
	draw_string("456789:-!$", 0,  600, size);
	draw_string("%^&*()/=+{", 0,  200, size);
}

void
scopeclock(int t)
{
	switch(t) {
		case 0: scopeclock_digital(); break;
		case 1: scopeclock_analog(); break;
		case 2: alphabet_test(); break;
	}
}
