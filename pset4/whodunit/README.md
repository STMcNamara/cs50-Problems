# Questions

## What's `stdint.h`?

stdint.h is a header file in the C standard library introduced in the C99 standard library section 7.18 to allow
programmers to write more portable code by providing a set of typedefs that specify exact-width integer types,
together with the defined minimum and maximum allowable values for each type, using macros.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

It defines the specific usuage that you have for that datatype, and also ensure that only the required memory
is reserved for it.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE = 8-bit , 1 Byte
DWORD = 32-bit, 4 Bytes
LONG = 32-bit, 4 Bytes
WORD = 16-bit, 4 Bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The file type, which must be "BM":

ASCII: BMTODO
Dec: 66 77
Hex: 42 4D

## What's the difference between `bfSize` and `biSize`?

bfSize - The size, in bytes, of the bitmap file.
biSize - The size of the BITMAPFILEHEADER structure, which is always 40

## What does it mean if `biHeight` is negative?

The height of the bitmap, in pixels. If biHeight is positive, the bitmap is a bottom-up DIB and its origin
is the lower-left corner. If biHeight is negative, the bitmap is a top-down DIB and its origin is the
upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount:

The number of bits-per-pixel. The biBitCount member of the BITMAPINFOHEADER structure determines the number of
bits that define each pixel and the maximum number of colors in the bitmap.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

On line 24, if there is no file to open in read mode, fopen will return NULL.

I don't understand for line 32, as attempting to open in write mode, which will create an empty file?

## Why is the third argument to `fread` always `1` in our code?

The third agument is the number of times to read, which is once.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4

bi.biWidth = 3
sizeof(RGBTRIPLE) = 3 Bytes
(bi.biWidth * sizeof(RGBTRIPLE)) = 9
(bi.biWidth * sizeof(RGBTRIPLE))%4 = 1
4 - (bi.biWidth * sizeof(RGBTRIPLE))%4 = 3
(4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4 = 3

Provides the amount of required padding in bytes

## What does `fseek` do?

Allows you to offset a pointer, which in this case presumably is skipping over the padding number of bytes

## What is `SEEK_CUR`?

Signifies that the baseline position of the pointer, prior to applying the offset is the current position

## Whodunit?

It was Professor Plum with the candlestick in the library.
