#pragma once

//Aly Types

typedef unsigned char       U8;
typedef signed char         S8;
typedef unsigned short int  U16;
typedef signed short int    S16;
typedef unsigned long int   U32;

#define NULL (void*)0

#define REG_High 0xFF
#define REG_Low 0x00 

/**
This karim's types
*/

#define NULL_PTR    ((void*)0)

typedef unsigned char         uint8;          /*                   0 .. 255                    */
typedef signed char           sint8;          /*                 -128 .. +127                  */
typedef unsigned short        uint16;         /*                    0 .. 65535                 */
typedef signed short          sint16;         /*               -32768 .. +32767                */
typedef unsigned long         uint32;         /*                    0 .. 4294967295            */
typedef signed long           sint32;         /*          -2147483648 .. +2147483647           */
typedef unsigned long long    uint64;         /*                    0 .. 18446744073709551615  */
typedef signed long long      sint64;         /* -9223372036854775808 .. 9223372036854775807   */
typedef float                 float32;
typedef double                float64;

typedef unsigned char           u8;
typedef signed char             s8;
typedef unsigned short int      u16;
typedef signed short int        s16;
typedef unsigned long int       u32;
typedef signed long int         s32;
typedef float                   f32;
typedef double                  f64;
typedef long long               u64;

typedef enum 
{
    false,
    true
}bool;