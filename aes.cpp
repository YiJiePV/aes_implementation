#include <iostream>

//?? bit key - ?? rounds

//AES encryption (input: 128 bit/16 byte blocks):
//1. SubBytes
//2. ShiftRows
//3. MixColumns (omit for last round)
//4. Add Round Key

//AES decryption (input: 128 bit/16 byte blocks):
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
