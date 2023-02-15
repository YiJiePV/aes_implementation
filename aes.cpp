#include <iostream>
#include <string>
#include <cstdint>

using std::string;
using std::cout;
using std::endl;
/*Hello-World!*/
//128 bit key - 10 rounds
//192 bit key - 12 rounds
//256 bit key - 14 rounds

//list of all possible 8bits
const uint8_t sbox[256] = {
  0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
  0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
  0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
  0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
  0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
  0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
  0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
  0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
  0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
  0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
};
//Function to substitute the bytes
void SubBytes(uint8_t state[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      state[i][j] = sbox[state[i][j]];
    }
  }
}

/// Function to Shift the rows
void ShiftRows(uint8_t state[4][4]) {
  uint8_t temp[4];
  // Shift first row by 0
  // Shift second row by 1
  temp[0] = state[1][0];
  temp[1] = state[1][1];
  temp[2] = state[1][2];
  temp[3] = state[1][3];
  for (int i = 0; i < 4; i++) {
    state[1][i] = temp[(i + 1) % 4];
  }
  // Shift third row by 2
  temp[0] = state[2][0];
  temp[1] = state[2][1];
  temp[2] = state[2][2];
  temp[3] = state[2][3];
  for (int i = 0; i < 4; i++) {
    state[2][i] = temp[(i + 2) % 4];
  }
  // Shift fourth row by 3
  temp[0] = state[3][0];
  temp[1] = state[3][1];
  temp[2] = state[3][2];
  temp[3] = state[3][3];
  for (int i = 0; i < 4; i++) {
    state[3][i] = temp[(i + 3) % 4];
  }
}
//AES encryption (input: 128 bit/16 bytes of text input):
string encrypt(const string& input){
  //0. Get 16 byte grid
  // Ex grid for Hello-World!:
  //  [ H | o | r | * |
  //  | e | - | l | * |
  //  | l | W | d | * |
  //  | l | o | ! | * ]
  char grid[4][4];
  int index = 0;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(index < input.size()){
        grid[j][i] = input.at(index);
        index++;
      }
      else{
        grid[j][i] = '*';
      }
    }
  }
  //Prints out grid
  // cout << "[ " << grid[0][0] << " | " << grid[0][1] << " | " << grid[0][2] << " | " << grid[0][3] << " |" << endl;
  // cout << "| " << grid[1][0] << " | " << grid[1][1] << " | " << grid[1][2] << " | " << grid[1][3] << " |" << endl;
  // cout << "| " << grid[2][0] << " | " << grid[2][1] << " | " << grid[2][2] << " | " << grid[2][3] << " |" << endl;
  // cout << "| " << grid[3][0] << " | " << grid[3][1] << " | " << grid[3][2] << " | " << grid[3][3] << " ]" << endl;
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
  char grid[4][4];
  int index = 0;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(index < cipher.size()){
        grid[j][i] = cipher.at(index);
        index++;
      }
      else{
        grid[j][i] = '*';
      }
    }
  }
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
    encrypt("Hello-World!");
    return 0;
}
