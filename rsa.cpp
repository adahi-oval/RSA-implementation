#include "converters.cpp"
#include "colors.cpp"

int ExponenciarRapido(int base, int exp, int m){
  unsigned long long x = 1;
  unsigned long long y = base % m;
  do{
    if(exp % 2 == 1) {
      x = (x*y) % m;
      exp = exp - 1;
    }
    else {
      y = (y*y) % m;
      exp = exp/2;
    }
  } while (exp > 0 && y > 1);

  return x;
}



int EuclideaExtendida(int a, int b, int *x, int *y)
{
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }
 
    int x1, y1;
    int euclidea = EuclideaExtendida(b%a, a, &x1, &y1);
 
    *x = y1 - (b/a) * x1;
    *y = x1;
 
    return euclidea;
}



int modInverse(int a, int m)
{
  int x, y;
  int g = EuclideaExtendida(a, m, &x, &y);

  if (g != 1)
    std::cout << "La inversa no existe";
  else
  {
    int res = (x%m + m) % m;
    return res;
  }
}



bool testPrimo(int num) {
  int a;
  int resto;
  srand(time(NULL));
  intvector primos = {2, 3, 5, 7, 11};

  for (int i = 0; i < 5; i++){
    if(num % primos.at(i) == 0 && num!= primos.at(i)) {
      return false;
    }
  }

  for (int i = 0; i < 100; i++){
    a = 1 + rand()%(num-1);
    resto = ExponenciarRapido(a, (num-1)/2, num);

    if(resto != (num - 1) && resto != 1){
      return false;
    }
  }

  return true;
}



int blockSize(int n){
  int rangemax, rangemin;
  for (int j = 0; j < 100; j++){
    rangemax = pow(26,j);
    rangemin = pow(26, j-1);
    if(rangemax > n && rangemin < n){
      return j-1;
    }
  }
}



std::string quitarEspacios(std::string mensaje){
  std::string mensaje_nuevo;
  int ascii;

  for (int i = 0; i < mensaje.size(); i++){
    ascii = mensaje[i];
    if(ascii <= 90 && ascii >= 65){
      mensaje_nuevo.push_back(mensaje[i]);
    }
  }

  return mensaje_nuevo;
}



intvector asciiBlock(std::string mensaje, int block_size){
  intvector vector;
  int res = 0;
  int ascii;

  for (int j = 0; j < mensaje.size(); j=j+block_size){
    std::string aux = mensaje.substr(j, block_size);
    for(int i = block_size-1, k = 0; i >= 0 && k < block_size; i--, k++){
      ascii = aux[k];
      res += (ascii-65)*pow(26, i);
    }
    vector.push_back(res);
    res = 0;
  }

  return vector;
}



intvector rsaEncrypt(intvector mensaje, int e, int n){
  intvector resultado;
  int aux;

  for(int i = 0; i < mensaje.size(); i++){
    aux = ExponenciarRapido(mensaje[i],e,n);
    resultado.push_back(aux);
  }

  return resultado;
}



int main(void){
  int p,q,d;
  std::string mensaje;
  
  std::cout << BOLDYELLOW "Introduzca el mensaje que desea cifrar:" RESET << std::endl;
  std::getline(std::cin, mensaje);
  mensaje = quitarEspacios(mensaje);

  std::cout << BOLDYELLOW "Introduzca el número primo p:" RESET << std::endl;
  std::cin >> p;
  if(testPrimo(p)){
    std::cout << BOLDGREEN "p es primo." RESET << std::endl << std::endl;
  }else{
    std::cout << BOLDRED "p no es primo. Inténtelo de nuevo." RESET << std::endl;
    return 0;
  }

  std::cout << BOLDYELLOW "Introduzca el número primo q:" RESET << std::endl;
  std::cin >> q;
  if(testPrimo(q)){
    std::cout << BOLDGREEN "q es primo." RESET << std::endl << std::endl;
  }else{
    std::cout << BOLDRED "q no es primo. Inténtelo de nuevo." RESET << std::endl;
    return 0;
  }

  int n = p*q;
  int fi = (p-1)*(q-1);
  int block_size = blockSize(n);

  std::cout << BOLDYELLOW "Introduzca el número entero d, coprimo de φ(n):" RESET << std::endl;
  std::cin >> d;

  int x,y;
  if (EuclideaExtendida(d, fi, &x, &y) == 1){
    std::cout << BOLDGREEN "d y φ(n) son coprimos." RESET << std::endl << std::endl;
  }else{
    std::cout << BOLDRED "d y φ(n) no son coprimos. Inténtelo de nuevo." RESET << std::endl;
    return 0;
  }

  int e = modInverse(d, fi);

  std::cout << BOLDBLUE"El parámetro e, inverso de d con mod φ(n) es: " BOLDWHITE << std::endl << e << std::endl << std::endl;

  intvector mensaje_bloque = asciiBlock(mensaje, block_size);

  std::cout << BOLDBLUE "El mensaje pasado a bloque decimal es: " BOLDWHITE << std::endl;
  printIntvector(mensaje_bloque);
  std::cout << std::endl;

  intvector mensaje_cifrado = rsaEncrypt(mensaje_bloque,e,n);

  std::cout << BOLDMAGENTA "El mensaje cifrado en bloque decimal es: " BOLDWHITE << std::endl;
  printIntvector(mensaje_cifrado);
  std::cout << std::endl;

  intvector mensaje_descifrado = rsaEncrypt(mensaje_cifrado,d,n);

  std::cout << BOLDMAGENTA "El mensaje descifrado en bloque decimal es: " BOLDWHITE << std::endl;
  printIntvector(mensaje_descifrado);
  std::cout << RESET << std::endl;

  return 0;   
}