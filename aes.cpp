#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;
/*Hello-World!*/
//128 bit key - 10 rounds
//192 bit key - 12 rounds
//256 bit key - 14 rounds

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
