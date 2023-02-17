#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <fstream>

using std::string;
using std::cout;
using std::endl;
using std::hex;
using std::vector;

//128 bit key - 10 rounds
//192 bit key - 12 rounds
//256 bit key - 14 rounds
const string key = "Thats my Kung Fu";
const string text = "Two One Nine Two";
//list of all possible 8bits
// const uint8_t sbox[256] = {
//   0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
//   0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
//   0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
//   0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
//   0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
//   0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
//   0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
//   0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
//   0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
//   0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
// };
const uint8_t sbox[256] =
{
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
	0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
	0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
	0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
	0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
	0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
	0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};
//Function to substitute the bytes
void SubBytes(uint8_t matrix[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix[i][j] = sbox[matrix[i][j]];
    }
  }
}

/// Function to Shift the rows
void ShiftRows(uint8_t matrix[4][4]) {
  uint8_t temp[4];
  // Shift first row by 0
  // Shift second row by 1
  temp[0] = matrix[1][0];
  temp[1] = matrix[1][1];
  temp[2] = matrix[1][2];
  temp[3] = matrix[1][3];
  for (int i = 0; i < 4; i++) {
    matrix[1][i] = temp[(i + 1) % 4];
  }
  // Shift third row by 2
  temp[0] = matrix[2][0];
  temp[1] = matrix[2][1];
  temp[2] = matrix[2][2];
  temp[3] = matrix[2][3];
  for (int i = 0; i < 4; i++) {
    matrix[2][i] = temp[(i + 2) % 4];
  }
  // Shift fourth row by 3
  temp[0] = matrix[3][0];
  temp[1] = matrix[3][1];
  temp[2] = matrix[3][2];
  temp[3] = matrix[3][3];
  for (int i = 0; i < 4; i++) {
    matrix[3][i] = temp[(i + 3) % 4];
  }
}

//Function to do multiplication of number to grid element
uint8_t MultiplyChar(uint8_t c, int i){
  //for encryption (plus the return at the very end)
  if(i == 2){
    int bit = (c >> 7);
    if(bit){
      return (c << 1) ^ 0x1B;
    }
    return c << 1;
  }
  else if(i == 3){
    int bit = (c & 0x80);
    if(bit){
      return (c << 1)^0x1B^c;
    }
    return (c << 1)^c;
  }//for decryption
  else if(i == 9){
    return (c << 3)^c;
  }
  else if(i == 11){
    return (((c << 2)^c) << 1)^c;
  }
  else if(i == 13){
    return (((c << 1)^c) << 2)^c;
  }
  else if(i == 14){
    return ((((c << 1)^c) << 1)^c) << 1;
  }
  return c; //i == 1
}

void MixColumns(uint8_t grid[4][4], vector<vector<uint8_t>>& output){
  int matrix[4][4] = {{2, 3, 1, 1},
                      {1, 2, 3, 1},
                      {1, 1, 2, 3},
                      {3, 1, 1, 2}};
  
  uint8_t r0 = 0;
  for(int i = 0; i < 4; i++){//each column of grid
    for(int j = 0; j < 4; j++){//row
      for(int k = 0; k < 4; k++){
        r0 ^= MultiplyChar(grid[k][i], matrix[j][k]);
      }
      output[j][i] = r0;
      r0 = 0;
    }
  }
}
// r-con table used in expansion
const uint8_t rcon[256] = {
	0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
	0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,
	0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a,
	0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
	0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
	0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc,
	0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,
	0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
	0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
	0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
	0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35,
	0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
	0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
	0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63,
	0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd,
	0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d
};

void LeftShift(uint8_t input[]){
  uint8_t temp = input[0];
  input[0] = input[1];
  input[1] = input[2];
  input[2] = input[3];
  input[3] = temp;
}

void SBoxReplace(uint8_t input[]){
  input[0] = sbox[input[0]];
  input[1] = sbox[input[1]];
  input[2] = sbox[input[2]];
  input[3] = sbox[input[3]];
}

void ExpandKey(string key, vector<string>& keys){
  keys.push_back(key);
  uint8_t lastKey[16];
  for(int i = 0; i < 16; i++){
    lastKey[i] = key.at(i);
  } 
  for(int i = 0; i < 10; i++){
    uint8_t temp[4];
    uint8_t keyExt[16];
    for(int j = 0; j < 4; j++){
      temp[j] = keys.at(i).at(12 + j);
    }
    for(int k = 0; k < 16; ){
      if(k == 0){
        LeftShift(temp);
        SBoxReplace(temp);
        temp[0] ^= rcon[i+1];
      }
      for(int l = 0; l < 4; l++){
        keyExt[k+l] = lastKey[k+l] ^ temp[l];
      }
      for(int o = 0; o < 4; o++){
        temp[o] = keyExt[k + o];
      }
      k += 4;
    }
    string neo = "";
    for(int m = 0; m < 16; m++){
      neo.push_back(char(keyExt[m]));
    }
    keys.push_back(neo);
    for(int n = 0; n < 16; n++){
      lastKey[n] = keyExt[n];
    }
  }
}

void AddKey(vector<vector<uint8_t>>& grid, string key){
  int index = 0;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      grid[j][i] ^= key.at(index);
      index++;
    }
  }
}

void AddKeyFirst(uint8_t grid[4][4], string key){
  int index = 0;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      grid[j][i] ^= key.at(index);
      index++;
    }
  }
}

//AES encryption (input: 128 bit/16 bytes of text input):
string Encrypt(const string& input){
  //0. Get 16 byte grid
  // Ex grid for Hello-World!:
  //  [ H | o | r | * |
  //  | e | - | l | * |
  //  | l | W | d | * |
  //  | l | o | ! | * ]
  uint8_t grid[4][4];
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
  vector<string> keys;
  ExpandKey(key, keys);
  AddKeyFirst(grid, keys.at(0));
  cout << hex << "[ " << int(grid[0][0]) << " | " << int(grid[0][1]) << " | " << int(grid[0][2]) << " | " << int(grid[0][3]) << " |" << endl;
  cout << hex << "| " << int(grid[1][0]) << " | " << int(grid[1][1]) << " | " << int(grid[1][2]) << " | " << int(grid[1][3]) << " |" << endl;
  cout << hex << "| " << int(grid[2][0]) << " | " << int(grid[2][1]) << " | " << int(grid[2][2]) << " | " << int(grid[2][3]) << " |" << endl;
  cout << hex << "| " << int(grid[3][0]) << " | " << int(grid[3][1]) << " | " << int(grid[3][2]) << " | " << int(grid[3][3]) << " ]" << endl;
  for(int i = 0; i < 10; i++){
    //1. SubBytes
    SubBytes(grid);
    cout << hex << "[ " << int(grid[0][0]) << " | " << int(grid[0][1]) << " | " << int(grid[0][2]) << " | " << int(grid[0][3]) << " |" << endl;
    cout << hex << "| " << int(grid[1][0]) << " | " << int(grid[1][1]) << " | " << int(grid[1][2]) << " | " << int(grid[1][3]) << " |" << endl;
    cout << hex << "| " << int(grid[2][0]) << " | " << int(grid[2][1]) << " | " << int(grid[2][2]) << " | " << int(grid[2][3]) << " |" << endl;
    cout << hex << "| " << int(grid[3][0]) << " | " << int(grid[3][1]) << " | " << int(grid[3][2]) << " | " << int(grid[3][3]) << " ]" << endl;
    //2. ShiftRows
    ShiftRows(grid);
    cout << hex << "[ " << int(grid[0][0]) << " | " << int(grid[0][1]) << " | " << int(grid[0][2]) << " | " << int(grid[0][3]) << " |" << endl;
    cout << hex << "| " << int(grid[1][0]) << " | " << int(grid[1][1]) << " | " << int(grid[1][2]) << " | " << int(grid[1][3]) << " |" << endl;
    cout << hex << "| " << int(grid[2][0]) << " | " << int(grid[2][1]) << " | " << int(grid[2][2]) << " | " << int(grid[2][3]) << " |" << endl;
    cout << hex << "| " << int(grid[3][0]) << " | " << int(grid[3][1]) << " | " << int(grid[3][2]) << " | " << int(grid[3][3]) << " ]" << endl;
    vector<vector<uint8_t>> result = {{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}};
    if(i != 9){
      //3. MixColumns (omit for last round)
      MixColumns(grid, result);
      cout << hex << int(result[0][0]) << ", " << int(result[0][1]) << ", "  << int(result[0][2]) << ", "  << int(result[0][3]) << endl;
      cout << hex << int(result[1][0]) << ", " << int(result[1][1]) << ", "  << int(result[1][2]) << ", "  << int(result[1][3]) << endl;
      cout << hex << int(result[2][0]) << ", " << int(result[2][1]) << ", "  << int(result[2][2]) << ", "  << int(result[2][3]) << endl;
      cout << hex << int(result[3][0]) << ", " << int(result[3][1]) << ", "  << int(result[3][2]) << ", "  << int(result[3][3]) << endl;
    }
    else{
      for(int k = 0; k < 4; k++){
        for(int j = 0; j < 4; j++){
          result[k][j] = grid[k][j];
        }
      }
    }
    //4. Add Round Key
    AddKey(result, keys.at(i+1));
    for(int k = 0; k < 4; k++){
      for(int j = 0; j < 4; j++){
        grid[k][j] = result[k][j];
      }
    }
    cout << hex << "[ " << int(grid[0][0]) << " | " << int(grid[0][1]) << " | " << int(grid[0][2]) << " | " << int(grid[0][3]) << " |" << endl;
    cout << hex << "| " << int(grid[1][0]) << " | " << int(grid[1][1]) << " | " << int(grid[1][2]) << " | " << int(grid[1][3]) << " |" << endl;
    cout << hex << "| " << int(grid[2][0]) << " | " << int(grid[2][1]) << " | " << int(grid[2][2]) << " | " << int(grid[2][3]) << " |" << endl;
    cout << hex << "| " << int(grid[3][0]) << " | " << int(grid[3][1]) << " | " << int(grid[3][2]) << " | " << int(grid[3][3]) << " ]" << endl;
  }
  return text; //ciphertext
}
//AES decryption (cipher: 128 bit/16 bytes of ciphertext):
string Decrypt(string cipher){
  //0. Get 16 byte grid
  uint8_t grid[4][4];
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
// string text;
//   //get file input
// std::fstream myfile;
//  myfile.open("hellobaby.txt");
//  if (myfile.is_open()){
 
//  while(getline(myfile, text)){
     
//  }
//  myfile.close();
//    }

  // uint8_t grid[4][4] = {{0xd4, 0xd4, 0xd4, 0xd4}, 
  //                     {0xbf, 0xbf, 0xbf, 0xbf}, 
  //                     {0x5d, 0x5d, 0x5d, 0x5d}, 
  //                     {0x30, 0x30, 0x30, 0x30}};
  // vector<vector<uint8_t>> result = {{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}};
  // MixColumns(grid, result);
  // cout << hex << int(result[0][0]) << endl;
  // cout << hex << int(result[0][0]) << ", " << int(result[0][1]) << ", "  << int(result[0][2]) << ", "  << int(result[0][3]) << endl;
  // cout << hex << int(result[1][0]) << ", " << int(result[1][1]) << ", "  << int(result[1][2]) << ", "  << int(result[1][3]) << endl;
  // cout << hex << int(result[2][0]) << ", " << int(result[2][1]) << ", "  << int(result[2][2]) << ", "  << int(result[2][3]) << endl;
  // cout << hex << int(result[3][0]) << ", " << int(result[3][1]) << ", "  << int(result[3][2]) << ", "  << int(result[3][3]) << endl;
  Encrypt(text);
  // vector<string> keys;
  // ExpandKey(key, keys);
  // for(int i = 0; i < keys.size(); i++){
  //   for(int j = 0; j < 16; j++){
  //     cout << hex << int(keys.at(i).at(j)) << ", ";
  //   }
  //   cout << endl;
  // }
  return 0;
}
