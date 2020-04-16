# Questions

## What's `stdint.h`?

standard header file of C library , declaring sets of integer types having specified widths and  corresponding sets of macros.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

to specify exact sizes of certain elements thus enabling efficient parsing of data from memory.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

typedef uint8_t  BYTE; 8 bits thus 1 byte
typedef uint32_t DWORD; 32 bits thus 4 bytes
typedef int32_t  LONG; 32 bits thus 4 bytes
typedef uint16_t WORD; 16 bits thus 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

424d

## What's the difference between `bfSize` and `biSize`?

1- former is from BMPFileHeader, The size, in bytes, of the bitmap file.

, latter - from BMPInforHeader, The number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.

If biHeight is negative, indicating a top-down DIB, biCompression must be either BI_RGB or BI_BITFIELDS. Top-down DIBs cannot be compressed.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount. There's a large chart to define details on that.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

wrong path or no permissions

## Why is the third argument to `fread` always `1` in our code?

because we read just a single file , while fread() reads nmemb items of data ( i.e. the parameter is telling how many files to read)

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?
 int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
  int padding = (4 - (3 * 3) % 4) % 4;
 int padding = (4 - (9) % 4) % 4;
     int padding = (4 - 9 % 4) % 4;
     int padding = (4 - 1) % 4;
     int padding = 3 % 4;
     int padding = 3


## What does `fseek` do?

The fseek() function sets the file position indicator for the stream pointed to by stream.
The new position, measured in bytes, is obtained by adding offset bytes to the position specified by whence

## What is `SEEK_CUR`?

current position
If whence is set to SEEK_SET , SEEK_CUR , or SEEK_END , the offset is relative to the start of the file,
the current position indicator, or end-of-file, respectively.

## Whodunit?

It was mister Plum with candlestick in the library.
