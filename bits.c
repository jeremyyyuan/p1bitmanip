/* 
 * CS:APP Data Lab 
 * 
 * Author: Jeremy Yuan
 * CNETID: jeremyyuan
 * 
 * bits.c - Source file with your solutions to the project.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the project by
editing the collection of functions in this source file.

CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function.

/*
 * STEP 2: Modify the following functions according to the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest checker to verify that your solutions produce
 *      the correct answers.
 */


#endif
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  // isolate the most significant bit of x
  int shift = x >> 0x1F;
  // make the sign 1 or 0
  int sign = (shift & 0x01);
  // XOR x to un-negate it or keep it positive, then add the sign to finish the abs
  return (shift ^ x) + sign;
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  // make a number filled with the sign of x
  int signx = (x >> 0x1F);
  // make a number filled with the sign of y
  int signy = (y >> 0x1F);
  // if the signs are different, return 1. If they are the same, return 0.
  int signdiff = !!(signx ^ signy);
  // make a number filled with the sign of the sum
  int signsum = (x + y) >> 0x1F;

  // if the signs are different, then operation can always be performed without overflow
  // if the sign of x is the same as sign of sum and the sign of y is same as sign
  // of sum, then there is also no overflow
  // however, if one of the signs is different from the sign of the sum,
  // then overflow must have occurred.
  return (!(signx ^ signsum) & !(signy ^ signsum)) | (signdiff);

}
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  // keep cutting the number in half and checking if all the even bits are 1
  x = x & (x >> 0x10);
  x = x & (x >> 0x08);
  x = x & (x >> 0x04);
  x = x & (x >> 0x02);
  // if all the even bits are one, each of the statements above should evaluate to x.
  // then all you have to do is & with 1 to get 1 (true). 
  // if not all the even bits are 1, then the 0 will keep shifting towards the LSB
  // and it will return 0 when & with 1.
  return x & 0x01;
}
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  // take the sign of x and the sign of -x and fill a number
  // if x is non-zero, then the | expression will evaluate to -1 always.
  // if x is zero, then the | expression will evaluate to 0.
  // adding 1 returns 1 for non-zero and 0 for zero.
  return ((x >> 0x1F) | ((~x + 0x01) >> 31)) + 0x01;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  // put a 1 at end of every quartile in the number
  // 00000001000000001
  int quartile1 = (0x01 << 0x18) | (0x01 << 0x10) | (0x01 << 0x08) | 0x01;
  // accumlate all the 1's into 1 number, if the digit is not set,
  // then it is a 0 in the final 1's accumulation number
  int accumulator = (x & quartile1) + ((x >> 1) & quartile1) + ((x >> 2) & quartile1) + ((x >> 3) & quartile1) + ((x >> 4) & quartile1) + ((x >> 5) & quartile1) + ((x >> 6) & quartile1) + ((x >> 7) & quartile1);
  // make a mask of 8 bits that is all 1's to count the 1's in each quartile
  int onemask = 0xFF; 
  // count all the 1's in each of the quartiles and add together to get total number of 1's
  int countsum = (accumulator & onemask) + ((accumulator>>8) & onemask) + ((accumulator >> 16) & onemask) + ((accumulator >> 24) & onemask);
  return countsum;
}
/*
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
  // ~ can be distributed through the | sign, giving ~x and ~y, which can be
  // & together to get the same result
  return (~x & ~y);
}
/*
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  // calculate the number of bit needed to be shifted for n and m, starting from the right
  int nmove = (n << 0x03);
  int mmove = (m << 0x03);
  // isolate both n byte and m byte on the LSB side of a number
  int niso = (x >> nmove) & 0xFF;
  int miso = (x >> mmove) & 0xFF;
  // calculate an offset used to readjust the reshifted bits in the new positions
  int offset = (niso ^ miso);
  // move the shifted bits back to their correct positions and then | then together
  int xor2 = (offset << nmove) | (offset << mmove);
  // put in the rest of the bits where they are supposed to be
  return (x ^ xor2);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // turn x into a boolean for simplified bitwise manipulation
  int boolean = !!x;
  // make a boolean that uses 0 and -1 rather than 0 and 1
  int negativeboolean = ~boolean + 0x01;
  // if the negativeboolean is all 1's (true), then returns y
  // if the negative boolean is all 0's (false), then return z
  return (negativeboolean & y) | (~negativeboolean & z);
}
/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) {
  // multiply x by 3 using bitwise first
  int y = (x + (x << 0x01));
  // fill an entire number with the sign of x after overflow occurs (if it does)
  int sign = y >> 0x1F;
  // create a 2 bit mask of 1's (00...0011)
  int mask = (0x01 << 0x02) + ~0x00;
  // turn all bits except for least significant 2 into 0's
  // adjust for truncation when dividing by 4
  // solves the off by one error for negative numbers
  int adjust = mask & sign;
  // add the adjustment to correct the off by one error for
  // negative numbers then divide by 4
  int result = ((y + adjust) >> 0x02);
  return result; 
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  // calculate the amount of shift necessary based on n bits
  int shift = 32 + (~n + 0x01);
  // fill the rest of the number with the sign bit
  int nbitnumb = (x << shift) >> shift;
  // check if the number of bits is enough
  return !(x ^ nbitnumb);
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  // first, calculate how many bit shifts are needed to get the wanted byte to
  // the least significant bit area
  // then, shift requested byte to the least significant byte, then mask it with 0xFF
  // to make all other bits 0 and only leaving requested bit
  return (x >> (n << 0x03)) & 0xFF;
}
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {
  // turn all the bits less significant than the leading bit to become 1
  x = x | x >> 0x01;
  x = x | x >> 0x02;
  x = x | x >> 0x04;
  x = x | x >> 0x08;
  x = x | x >> 0x0F;
  // invert x, then shift right 1 to move a 1 back to the most significant spot.
  // then correct the sign by ^ with 0x80000000
  // by &-ing x with the shifted inverse, all other bits become 0,
  // leaving only the most significant bit left
  x = x & ((~x >> 0x01) ^ (0x01 << 0x1F));
  return x;
}
/*
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) {
  // if x is 0, then expression is always true
  // otherwise, if x and y are equal, then it is also always true.
  // the only other case is covered to return 0 if both statements are false
  return (!x) | (!(x ^ y));
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  // create the upperbound and lowerbound
  int tmin= 0x01 << 0x1F;
  int lowerbound= ~(0x30);
  int upperbound= ~(tmin | 0x39);
  
  // if x is less than the upperbound, then will return 0
  int lessthanupperbound = (tmin & (x + upperbound)) >> 31;
  // if x is greater than the lowerbound, then will return 0
  int greaterthanlowerbound = (tmin & (x + lowerbound + 0x01)) >> 31;
  // if both conditions return 0, that means number is in the range.
  return !(lessthanupperbound | greaterthanlowerbound);
}
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  // if numbers are equal, then x ^ y will return 0, which gets banged to 1
  // otherwise, a non-zero number is returned
  return !(x ^ y);
}
/*
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {

  // if x and y are not equal, then return 1. Otherwise, return 0.
  int notequal = !(!(x ^ y));
  // calculate the logical difference between two numbers
  // this doesn't account for edge cases, like 0x80000000 and 0x7FFFFFFF
  int diff = y + (~x + 0x01);
  // if the difference is 0, then the numbers are equal. Otherwise, they are not.
  int equal = !diff;

  // declare lessorequal
  int lessorequal;
  
  int comp = (~(x ^ y) & ~diff) | ((x ^ y) & x);
  // turn all other bits except for signed bit into 0
  comp = comp & (0x01 << 0x1F);
  // isLess has two possibilites, 0 or Tmin, so double bang to get 1 or 0.
  // equal has to be included here to reset the boolean value.
  lessorequal = (!!comp) | (equal);
  // if x is less than or equal to, but not equal to y, then x has to be less than y.
  return lessorequal & notequal;  
}
/*
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
  // get the sign bit and check if it is negative or not
  return !(x >> 31);
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  int neg1 = ~0x00;
  int xminus1 = (x + neg1);
  int tmax = 1 << 31;
  // check if x is positive or not by banging the sign bit
  int positive = !(x & tmax);
  // x has to be positive and nonzero
  // if x is a power of 2, then & x and x - 1 will always give 0. 
  // a power of 2 - 1 is filled with 1's below the bit in question
  return ((!(x & xminus1)) & positive) & (!(!x));
}
/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
  // the minimum two's complement number 0x80000000 has a unique overflow
  // property where ^ to its arithmetic negation equals 0.
  // also check that x isn't 0, which has the same property as above
  return (!(x ^ (~x + 0x01))) & !(!x);
}
/*
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
  // flipping all bits of 0x00 will give all 1's which is -1 in signed 2's complement
  return ~0x00;
}
/*
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) {
  // calculate how much to rotate by
  int rt = 0x20 + (~n + 0x01);
  // shift the bits to the right by how much is desired
  int rightnbits = (x >> rt); 
  // create a positive mask that has all 0's until the rotation bit
  int mask = ~(0x01 << 0x1F) >> (0x1F + (~n + 0x01));
  // rotate x to the left, then fill in remaining bits by &-ing
  // the mask with the right bits calculated earlier
  return (x << n) | (rightnbits & mask);
}
/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
  // fill a number with the signed bit of x
  int signbit = (x >> 31);
  // fill a number with the second most significant bit of x
  int nextbit = (x << 1) >> 31;
  // calculate the product of x*2
  int x2 = (x << 1);
  // if first and second bit are the same, then x2 does not need to be saturated
  // otherwise, then x2 ^ (x2 ^ nextbit ^ (0x01 << 0x1F)) will give the saturated value
  return x2 ^ ((x2 ^ nextbit ^ (0x01 << 0x01F)) & (signbit ^ nextbit));
}