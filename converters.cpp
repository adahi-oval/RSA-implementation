#include <iostream>
#include <string.h>
#include <vector>
#include <bitset>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <math.h>

typedef std::vector<std::bitset<8>> bitvector8;
typedef std::vector<int> intvector;
typedef std::bitset<8> byte;
typedef std::vector<std::vector<int>> intmatrix;
typedef std::vector<std::vector<std::string>> stringmatrix;
typedef std::vector<std::string> stringvector;



std::string IntToString(int num){
  std::stringstream resultStream;
  resultStream << num;
  std::string result = resultStream.str();

  return result;
}



void printIntvector(intvector vector){
  std::string string;
  for (int i = 0; i < vector.size(); i++){
    string += IntToString(vector[i]);
    string += ", ";
  }

  string.pop_back();
  string.pop_back();

  std::cout << string << std::endl;
}



bitvector8 ASCIIToBinary(intvector numbers){
  bitvector8 bytes;

  for (int i = 0; i < numbers.size(); i++){
    std::bitset<8> codigobit(numbers[i]);
    bytes.push_back(codigobit);
  }

  return bytes;
}



std::bitset<8> IntToBinary(int number){
  std::bitset<8> codigobit(number);

  return codigobit;
}



std::vector<std::bitset<8>> StringToBinary(std::string string){
  std::vector<int> ascii;
  std::vector<std::bitset<8>> bytes;
  
  for (int i = 0; i < string.size(); i++)
  {
    ascii.push_back(string[i]);
  }
  
  for (int i = 0; i < ascii.size(); i++)
  {
    std::bitset<8> codigobit(ascii[i]);
    bytes.push_back(codigobit);
  } 

  return bytes;
}



std::vector<int> StringToASCII(std::string string){
  std::vector<int> ascii;
  
  for (int i = 0; i < string.size(); i++)
  {
    ascii.push_back(string[i]);
  }

  return ascii;
}



std::vector<std::bitset<8>> BinaryToBitset(std::string string, int len){
  std::vector<std::bitset<8>> bitset;
  std::bitset<8> byte;
  std::string aux;
  for (int i = 0; i < len; i++){
    for (int j = 0; j < 8; j++){
      aux.push_back(string[0]);
      string.erase(0,1);
    }
    std::bitset<8> byte(aux);
    bitset.push_back(byte);
    aux.clear();
  }
  return bitset;
}



std::vector<std::bitset<8>> AddBinary(std::vector<std::bitset<8>> clave, std::vector<std::bitset<8>> mensaje){
  std::vector<std::bitset<8>> SumaBinario;
  if(clave.size() == mensaje.size()){
    for(int i = 0; i < clave.size(); i++){
      SumaBinario.push_back(clave[i]^=mensaje[i]);
    }
  }
  else{
    std::cout << "Introduzca el tamaño del mensaje original correcto, incluyendo espacios." << std::endl;
  }
  return SumaBinario;
}



std::string BinaryToString(std::vector<std::bitset<8>> bytes){
  std::vector<int> ascii;
  std::string string;

  for (int i = 0; i < bytes.size(); i++){
    ascii.push_back(bytes[i].to_ulong());
  }

  for (int i = 0; i < ascii.size(); i++){
    string.push_back((char) ascii[i]);
  }

  return string;
}



std::vector<int> BinaryToASCII(std::vector<std::bitset<8>> bytes){
  std::vector<int> ascii;

  for (int i = 0; i < bytes.size(); i++){
    ascii.push_back(bytes[i].to_ulong());
  }

  return ascii;
}



void PrintBitset(std::vector<std::bitset<8>> bytes){
  for(int i = 0; i < bytes.size(); i++){
    std::cout << bytes[i].to_string();
  }
  std::cout << std::endl;
}



std::string DecimalToHex(int decimalNumber){
  std::stringstream resultStream;
  resultStream << std::hex << decimalNumber;
  std::string resultString ( resultStream.str() );

  return resultString;
}



int HexToDecimal(std::string hexNumber){
  int result;
  std::stringstream converterStream;
  converterStream << hexNumber;
  converterStream >> std::hex >> result;

  return result;
}



byte HexToBinary(std::string hexnumber){

  return IntToBinary(HexToDecimal(hexnumber));

}



std::string ByteToHex(byte byte1){
  
  return DecimalToHex(byte1.to_ulong());

}



stringvector BytevectorToHexvector(bitvector8 bytes){
  stringvector result;
  for (int i = 0; i < bytes.size(); i++){
    result.push_back(ByteToHex(bytes.at(i)));
  }

  return result;
}



stringmatrix StringToHexMatrix(std::string string){
  stringmatrix hexmatrix;
  stringvector aux;
  std::string substring;
  std::string hexstring;

  for (int i = 0; i < string.length(); i = i + 8){
    substring = string.substr(i, 8);

    for (int j = 0; j < substring.length(); j = j + 2){
      hexstring.push_back(substring.at(j));
      hexstring.push_back(substring.at(j+1));
      aux.push_back(hexstring);
      hexstring.clear();
    }

    hexmatrix.push_back(aux);
    aux.clear();

  }

  return hexmatrix;
}



void PrintHexMatrix(stringmatrix hexmatrix){
  
  for (int i = 0; i < hexmatrix.size(); i++){
    for (int j = 0; j < hexmatrix.at(0).size(); j++){
      std::cout << hexmatrix.at(i).at(j) << " ";
    }
    std::cout << std::endl;
  }

}



std::vector<std::string> swap(std::vector<std::string> vector, int index1, int index2){
  std::string aux;
  aux = vector.at(index1);
  vector.at(index1) = vector.at(index2);
  vector.at(index2) = aux;

  return vector;
}



stringvector ShiftRight(stringvector row, int iterations){
  
  for (int i = 0; i < iterations; i++){
    row.push_back(row.front());
    row.erase(row.begin());
  }

  return row;
}


byte mod8(byte op, byte constant, int position){
  int bit_significativo;
  
  for (int i = 0; i < position; i++){
    bit_significativo = op[7];
    op = op<<1;

    if(bit_significativo == 1){
      op^=constant;
    }
  }

  return op;
}



byte BinaryProduct(byte op1, byte op2, byte constant){
  byte aux;
  byte result;

  for (int i = 0; i < op2.size(); i++){
    if(op2[i] == 1){
      aux = mod8(op1, constant, i);
      result^=aux;
    }
  }

  return result;
}