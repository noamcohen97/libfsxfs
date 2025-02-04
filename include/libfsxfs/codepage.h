/*
 * Codepage definitions for libfsxfs
 *
 * Copyright (C) 2020-2023, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _LIBFSXFS_CODEPAGE_H )
#define _LIBFSXFS_CODEPAGE_H

#include <libfsxfs/types.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* The codepage definitions
 */
enum LIBFSXFS_CODEPAGES
{
	LIBFSXFS_CODEPAGE_ASCII				= 20127,

	LIBFSXFS_CODEPAGE_ISO_8859_1			= 28591,
	LIBFSXFS_CODEPAGE_ISO_8859_2			= 28592,
	LIBFSXFS_CODEPAGE_ISO_8859_3			= 28593,
	LIBFSXFS_CODEPAGE_ISO_8859_4			= 28594,
	LIBFSXFS_CODEPAGE_ISO_8859_5			= 28595,
	LIBFSXFS_CODEPAGE_ISO_8859_6			= 28596,
	LIBFSXFS_CODEPAGE_ISO_8859_7			= 28597,
	LIBFSXFS_CODEPAGE_ISO_8859_8			= 28598,
	LIBFSXFS_CODEPAGE_ISO_8859_9			= 28599,
	LIBFSXFS_CODEPAGE_ISO_8859_10			= 28600,
	LIBFSXFS_CODEPAGE_ISO_8859_11			= 28601,
	LIBFSXFS_CODEPAGE_ISO_8859_13			= 28603,
	LIBFSXFS_CODEPAGE_ISO_8859_14			= 28604,
	LIBFSXFS_CODEPAGE_ISO_8859_15			= 28605,
	LIBFSXFS_CODEPAGE_ISO_8859_16			= 28606,

	LIBFSXFS_CODEPAGE_KOI8_R			= 20866,
	LIBFSXFS_CODEPAGE_KOI8_U			= 21866,

	LIBFSXFS_CODEPAGE_WINDOWS_874			= 874,
	LIBFSXFS_CODEPAGE_WINDOWS_932			= 932,
	LIBFSXFS_CODEPAGE_WINDOWS_936			= 936,
	LIBFSXFS_CODEPAGE_WINDOWS_949			= 949,
	LIBFSXFS_CODEPAGE_WINDOWS_950			= 950,
	LIBFSXFS_CODEPAGE_WINDOWS_1250			= 1250,
	LIBFSXFS_CODEPAGE_WINDOWS_1251			= 1251,
	LIBFSXFS_CODEPAGE_WINDOWS_1252			= 1252,
	LIBFSXFS_CODEPAGE_WINDOWS_1253			= 1253,
	LIBFSXFS_CODEPAGE_WINDOWS_1254			= 1254,
	LIBFSXFS_CODEPAGE_WINDOWS_1255			= 1255,
	LIBFSXFS_CODEPAGE_WINDOWS_1256			= 1256,
	LIBFSXFS_CODEPAGE_WINDOWS_1257			= 1257,
	LIBFSXFS_CODEPAGE_WINDOWS_1258			= 1258
};

#define LIBFSXFS_CODEPAGE_US_ASCII			LIBFSXFS_CODEPAGE_ASCII

#define LIBFSXFS_CODEPAGE_ISO_WESTERN_EUROPEAN		LIBFSXFS_CODEPAGE_ISO_8859_1
#define LIBFSXFS_CODEPAGE_ISO_CENTRAL_EUROPEAN		LIBFSXFS_CODEPAGE_ISO_8859_2
#define LIBFSXFS_CODEPAGE_ISO_SOUTH_EUROPEAN		LIBFSXFS_CODEPAGE_ISO_8859_3
#define LIBFSXFS_CODEPAGE_ISO_NORTH_EUROPEAN		LIBFSXFS_CODEPAGE_ISO_8859_4
#define LIBFSXFS_CODEPAGE_ISO_CYRILLIC			LIBFSXFS_CODEPAGE_ISO_8859_5
#define LIBFSXFS_CODEPAGE_ISO_ARABIC			LIBFSXFS_CODEPAGE_ISO_8859_6
#define LIBFSXFS_CODEPAGE_ISO_GREEK			LIBFSXFS_CODEPAGE_ISO_8859_7
#define LIBFSXFS_CODEPAGE_ISO_HEBREW			LIBFSXFS_CODEPAGE_ISO_8859_8
#define LIBFSXFS_CODEPAGE_ISO_TURKISH			LIBFSXFS_CODEPAGE_ISO_8859_9
#define LIBFSXFS_CODEPAGE_ISO_NORDIC			LIBFSXFS_CODEPAGE_ISO_8859_10
#define LIBFSXFS_CODEPAGE_ISO_THAI			LIBFSXFS_CODEPAGE_ISO_8859_11
#define LIBFSXFS_CODEPAGE_ISO_BALTIC			LIBFSXFS_CODEPAGE_ISO_8859_13
#define LIBFSXFS_CODEPAGE_ISO_CELTIC			LIBFSXFS_CODEPAGE_ISO_8859_14

#define LIBFSXFS_CODEPAGE_ISO_LATIN_1			LIBFSXFS_CODEPAGE_ISO_8859_1
#define LIBFSXFS_CODEPAGE_ISO_LATIN_2			LIBFSXFS_CODEPAGE_ISO_8859_2
#define LIBFSXFS_CODEPAGE_ISO_LATIN_3			LIBFSXFS_CODEPAGE_ISO_8859_3
#define LIBFSXFS_CODEPAGE_ISO_LATIN_4			LIBFSXFS_CODEPAGE_ISO_8859_4
#define LIBFSXFS_CODEPAGE_ISO_LATIN_5			LIBFSXFS_CODEPAGE_ISO_8859_9
#define LIBFSXFS_CODEPAGE_ISO_LATIN_6			LIBFSXFS_CODEPAGE_ISO_8859_10
#define LIBFSXFS_CODEPAGE_ISO_LATIN_7			LIBFSXFS_CODEPAGE_ISO_8859_13
#define LIBFSXFS_CODEPAGE_ISO_LATIN_8			LIBFSXFS_CODEPAGE_ISO_8859_14
#define LIBFSXFS_CODEPAGE_ISO_LATIN_9			LIBFSXFS_CODEPAGE_ISO_8859_15
#define LIBFSXFS_CODEPAGE_ISO_LATIN_10			LIBFSXFS_CODEPAGE_ISO_8859_16

#define LIBFSXFS_CODEPAGE_KOI8_RUSSIAN			LIBFSXFS_CODEPAGE_KOI8_R
#define LIBFSXFS_CODEPAGE_KOI8_UKRAINIAN		LIBFSXFS_CODEPAGE_KOI8_U

#define LIBFSXFS_CODEPAGE_WINDOWS_THAI			LIBFSXFS_CODEPAGE_WINDOWS_874
#define LIBFSXFS_CODEPAGE_WINDOWS_JAPANESE		LIBFSXFS_CODEPAGE_WINDOWS_932
#define LIBFSXFS_CODEPAGE_WINDOWS_CHINESE_SIMPLIFIED	LIBFSXFS_CODEPAGE_WINDOWS_936
#define LIBFSXFS_CODEPAGE_WINDOWS_KOREAN		LIBFSXFS_CODEPAGE_WINDOWS_949
#define LIBFSXFS_CODEPAGE_WINDOWS_CHINESE_TRADITIONAL	LIBFSXFS_CODEPAGE_WINDOWS_950
#define LIBFSXFS_CODEPAGE_WINDOWS_CENTRAL_EUROPEAN	LIBFSXFS_CODEPAGE_WINDOWS_1250
#define LIBFSXFS_CODEPAGE_WINDOWS_CYRILLIC		LIBFSXFS_CODEPAGE_WINDOWS_1251
#define LIBFSXFS_CODEPAGE_WINDOWS_WESTERN_EUROPEAN	LIBFSXFS_CODEPAGE_WINDOWS_1252
#define LIBFSXFS_CODEPAGE_WINDOWS_GREEK			LIBFSXFS_CODEPAGE_WINDOWS_1253
#define LIBFSXFS_CODEPAGE_WINDOWS_TURKISH		LIBFSXFS_CODEPAGE_WINDOWS_1254
#define LIBFSXFS_CODEPAGE_WINDOWS_HEBREW		LIBFSXFS_CODEPAGE_WINDOWS_1255
#define LIBFSXFS_CODEPAGE_WINDOWS_ARABIC		LIBFSXFS_CODEPAGE_WINDOWS_1256
#define LIBFSXFS_CODEPAGE_WINDOWS_BALTIC		LIBFSXFS_CODEPAGE_WINDOWS_1257
#define LIBFSXFS_CODEPAGE_WINDOWS_VIETNAMESE		LIBFSXFS_CODEPAGE_WINDOWS_1258

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSXFS_CODEPAGE_H ) */

