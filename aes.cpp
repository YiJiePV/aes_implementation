#include <iostream>
/*Hello-World!*/
//128 bit key - 10 rounds
//192 bit key - 12 rounds
//256 bit key - 14 rounds

//AES encryption (input: 128 bit/16 byte blocks):
//0. Get 16 byte grid
// Ex grid for Hello-World!:
//  [ H | o | r | * |
//  | e | - | l | * |
//  | l | W | d | * |
//  | l | o | ! | * ]
//1. SubBytes
//2. ShiftRows
//3. MixColumns (omit for last round)
//4. Add Round Key

//AES decryption (input: 128 bit/16 byte blocks):
//0. Get 16 byte grid
//1. Add Round Key
//2. Inverse MixColumns
//3. ShiftRows
//4. Inverse SubByte

//command line user interface
int main() {
  //get file input
    std::cout << "Hello World!";
    return 0;
}
