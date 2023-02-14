#include <iostream>
#include <string>

using std::string;
/*Hello-World!*/
//128 bit key - 10 rounds
//192 bit key - 12 rounds
//256 bit key - 14 rounds

//AES encryption (input: 128 bit/16 bytes of text input):
string encrypt(string input){
  //0. Get 16 byte grid
  // Ex grid for Hello-World!:
  //  [ H | o | r | * |
  //  | e | - | l | * |
  //  | l | W | d | * |
  //  | l | o | ! | * ]
  //for each round:
  //1. SubBytes
  //2. ShiftRows
  //3. MixColumns (omit for last round)
  //4. Add Round Key
  return ""; //ciphertext
}
//AES decryption (cipher: 128 bit/16 bytes of ciphertext):
string decrypt(string cipher){
  //0. Get 16 byte grid
  //for each round:
  //1. Add Round Key
  //2. Inverse MixColumns
  //3. ShiftRows
  //4. Inverse SubByte
  return ""; //regular text
}
//command line user interface
int main() {
  //get file input
    std::cout << "Hello World!";
    return 0;
}
