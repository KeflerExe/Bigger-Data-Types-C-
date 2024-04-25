/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: AyEDA
/// Curso: 2º
/// Práctica 1: Representación de números grandes en notación posicional
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 14/02/2023
/// Archivo: bigint.h

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#ifndef BIGINT_H
#define BIGINT_H

// Clase BigInt para operar con números grandes en diferentes bases
template <size_t Base>
class BigInt {
 public:
  /// Constructores
  BigInt(long n = 0);
  BigInt(std::string& string_introducida);
  BigInt(const char* );
  BigInt(const BigInt<Base>&);

  // Funciones complementarias
  char ConvierteNumeroAChar(int numero_convertir);
  int ConvierteCharANumero(char caracter_convertir);
  long long CalculaElValor() const;

  // Sobrecarga del operador de asignacion
  BigInt<Base>& operator=(const BigInt<Base>& bigint);
  
  // Funciones para obtener información de los atibutos de la clase
  bool signo() const { return signo_; }
  char operator[](int posicion) const { return digitos_.at(posicion); }
  int TamanioVector() const { return digitos_.size(); }
  BigInt<Base> OperacionOR(const BigInt<Base>&) const;


  // Sobrecarga de operadores lógicos
  bool operator==(const BigInt<Base>&) const;
  bool operator!=(const BigInt<Base>&) const;
  bool operator>=(const BigInt<Base>&) const;
  bool operator<=(const BigInt<Base>&) const;
  bool operator<(const BigInt<Base>&) const;
  bool operator>(const BigInt<Base>&) const; 

  // Sobrecarga de operadores lógicos
  BigInt<Base>& operator++();
  BigInt<Base> operator++(int); 
  BigInt<Base>& operator--(); 
  BigInt<Base> operator--(int); 

  // Sobrecarga de operadores aritmeticos
  BigInt<Base> operator+(const BigInt<Base>&) const;
  BigInt<Base> operator-(const BigInt<Base>&) const;
  BigInt<Base> operator*(const BigInt<Base>&) const;
  BigInt<Base> operator/(const BigInt<Base>&) const;
  BigInt<Base> operator%(const BigInt<Base>&) const;
  BigInt<Base> potencia(const BigInt<Base>&, const BigInt<Base>&) const;

  // Sobrecarga de los operadores de entrada/salida
  template <size_t B>
  friend std::ostream& operator<<(std::ostream&, const BigInt<B>& bigint);
  template <size_t B>
  friend std::istream& operator>>(std::istream&, BigInt<B>& bigint);
 private:
  std::vector<char> digitos_;
  bool signo_;
};  

// Función encargada de convertir un número entero a su valor correspondiente en char
template <size_t Base>
char BigInt<Base>::ConvierteNumeroAChar(int numero_convertir) {
  char caracter_obtenido;
  if ((numero_convertir <= 9) && (numero_convertir >= 0)) {
    return '0' + numero_convertir;
  } else {
    return numero_convertir - 10 + 'A';
  }
}

// Función encargada de convertir un caracter a su valor correspondiente en entero
template <size_t Base>
int BigInt<Base>::ConvierteCharANumero(char caracter_convertir) {
  int numero_obtenido{0};
  if ((caracter_convertir <= '9') && (caracter_convertir >= '0')) {
    numero_obtenido = caracter_convertir - '0';
    return numero_obtenido;
  } else {
    numero_obtenido = caracter_convertir - 'A' + 10;
    return numero_obtenido;
  }
}

// Función encargada de calcular el valor decimal de un número en otra base
template <size_t Base>
long long BigInt<Base>::CalculaElValor() const {
  long long valor_bigint{0};
  long long suma_parcial{0};
  long long potencia{0};
  long long base = Base;
  long long exponente = digitos_.size() - 1;
  for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
    potencia = pow(base, exponente);
    suma_parcial = (digitos_[iterador] * potencia);
    valor_bigint = valor_bigint + suma_parcial;
    --exponente;
    suma_parcial = 0;
  }
  return valor_bigint;
}

// Constructor mediante un tipo long
template <size_t Base>
BigInt<Base>::BigInt(long n) {
  if (n < 0) {
    signo_ = true;
  } else {
    signo_ = false;
  }
  char caracter_convertir;
  while (n > 0) {
    char caracter_convertir = n % 10;
    digitos_.push_back(caracter_convertir);
    n /= 10;
  }
}

// Constructor mediante un tipo string
template <size_t Base>
BigInt<Base>::BigInt(std::string& string_introducida) {
  char caracter_convertir;
  int iterador{0};
  if (string_introducida[0] == '-') {
    iterador = 1;
    signo_ = true;
  } else {
    signo_ = false;
  }
  for (iterador; iterador < string_introducida.size(); iterador++) {
    caracter_convertir = string_introducida[iterador];
    caracter_convertir = ConvierteCharANumero(caracter_convertir);
    digitos_.push_back(caracter_convertir);
  }
}

// Constructor mediante un tipo char*
template <size_t Base>
BigInt<Base>::BigInt(const char* cadena_introducida) {
  char caracter_convertir;
  std::string cadena_introducida_str = cadena_introducida;
  int iterador{0};
  if (cadena_introducida_str[0] == '-') {
    iterador = 1;
    signo_ = true;
  } else {
    signo_ = false;
  }
  for (iterador; iterador < cadena_introducida_str.size(); iterador++) {
    caracter_convertir = cadena_introducida_str[iterador];
    caracter_convertir = ConvierteCharANumero(caracter_convertir);
    digitos_.push_back(caracter_convertir);
  }
}

// Constructor mediante un tipo BigInt
template <size_t Base>
BigInt<Base>::BigInt(const BigInt<Base>& bigint) {
  digitos_ = bigint.digitos_;
  signo_ = bigint.signo_;
}

// Sobrecarga del operador de asignación
template <size_t Base>
BigInt<Base>& BigInt<Base>::operator=(const BigInt<Base>& bigint) {
  this->digitos_ = bigint.digitos_;
  this->signo_ = bigint.signo_;
  return *this;
}

// Sobrecarga del operador de igualdad
template <size_t Base>
bool BigInt<Base>::operator==(const BigInt<Base>& bigint) const {
  if (digitos_.size() != bigint.digitos_.size()) {
    return false;
  }
  if (signo_ != bigint.signo_) {
    return false;
  }
  for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
    if (digitos_[iterador] != bigint.digitos_[iterador]) {
      return false;
    } 
  }
  return true;
}

// Sobrecarga del operador de diferencia
template <size_t Base>
bool BigInt<Base>::operator!=(const BigInt<Base>& bigint) const {
  bool diferencia_encontrada{false};
  if (digitos_.size() != bigint.digitos_.size()) {
    return true;
  }
  if (signo_ != bigint.signo_) {
    return true;
  }
  for (int iterador = 0; iterador < bigint.digitos_.size(); ++iterador) {
    if (digitos_[iterador] != bigint.digitos_[iterador]) {
      diferencia_encontrada = true;
      break;
    }
  }
  return diferencia_encontrada;
}

// Sobrecarga del operador de comparación menor
template <size_t Base>
bool BigInt<Base>::operator<(const BigInt<Base>& bigint) const {
  if (signo_ != bigint.signo_) {
    if (signo_ == true) {
      return true;
    } else {
      return false;
    }
  } 
  if (signo_ == true) {
    if (digitos_.size() > bigint.digitos_.size()) {
      return true;
    } 
    if (digitos_.size() < bigint.digitos_.size()) {
      return false;
    } 
    for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
      if (digitos_[iterador] < bigint.digitos_[iterador]) {
        return false;
      } else {
        if (digitos_[iterador] > bigint.digitos_[iterador]) {
          return true;
        }
      }
    }
    return false;
  } else {
    if (digitos_.size() > bigint.digitos_.size()) {
      return false;
    } 
    if (digitos_.size() < bigint.digitos_.size()) {
      return true;
    } 
    for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
      if (digitos_[iterador] < bigint.digitos_[iterador]) {
        return true;
      } else {
        if (digitos_[iterador] > bigint.digitos_[iterador]) {
          return false;
        }
      }
    }
    return false;
  }
}

// Sobrecarga del operador de comparación menor igual
template <size_t Base>
bool BigInt<Base>::operator<=(const BigInt<Base>& bigint) const {
  if (signo_ != bigint.signo_) {
    if (signo_ == true) {
      return true;
    } else {
      return false;
    }
  } 
  if (signo_ == true) {
    if (digitos_.size() > bigint.digitos_.size()) {
      return true;
    } 
    if (digitos_.size() < bigint.digitos_.size()) {
      return false;
    } 
    for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
      if (digitos_[iterador] < bigint.digitos_[iterador]) {
        return false;
      } else {
        if (digitos_[iterador] > bigint.digitos_[iterador]) {
          return true;
        }
      }
    }
    return true;
  } else {
    if (digitos_.size() > bigint.digitos_.size()) {
      return false;
    } 
    if (digitos_.size() < bigint.digitos_.size()) {
      return true;
    } 
    for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
      if (digitos_[iterador] < bigint.digitos_[iterador]) {
        return true;
      } else {
        if (digitos_[iterador] > bigint.digitos_[iterador]) {
          return false;
        }
      }
    }
    return true;
  }
}

// Sobrecarga del operador de comparación mayor
template <size_t Base>
bool BigInt<Base>::operator>(const BigInt<Base>& bigint) const {
  if (signo_ != bigint.signo_) {
    if (signo_ == true) {
      return false;
    } else {
      return true;
    }
  } 
  if (signo_ == true) {
    if (digitos_.size() > bigint.digitos_.size()) {
      return false;
    } 
    if (digitos_.size() < bigint.digitos_.size()) {
      return true;
    } 
    for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
      if (digitos_[iterador] < bigint.digitos_[iterador]) {
        return true;
      } else {
        if (digitos_[iterador] > bigint.digitos_[iterador]) {
          return false;
        }
      }
    }
    return false;
  } else {
    if (digitos_.size() > bigint.digitos_.size()) {
      return true;
    } 
    if (digitos_.size() < bigint.digitos_.size()) {
      return false;
    } 
    for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
      if (digitos_[iterador] < bigint.digitos_[iterador]) {
        return false;
      } else {
        if (digitos_[iterador] > bigint.digitos_[iterador]) {
          return true;
        }
      }
    }
    return false;
  }
}

// Sobrecarga del operador de comparación mayor igual
template <size_t Base>
bool BigInt<Base>::operator>=(const BigInt<Base>& bigint) const {
  if (signo_ != bigint.signo_) {
    if (signo_ == true) {
      return false;
    } else {
      return true;
    }
  } 
  if (signo_ == true) {
    if (digitos_.size() > bigint.digitos_.size()) {
      return false;
    } 
    if (digitos_.size() < bigint.digitos_.size()) {
      return true;
    } 
    for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
      if (digitos_[iterador] < bigint.digitos_[iterador]) {
        return true;
      } else {
        if (digitos_[iterador] > bigint.digitos_[iterador]) {
          return false;
        }
      }
    }
    return true;
  } else {
    if (digitos_.size() > bigint.digitos_.size()) {
      return true;
    } 
    if (digitos_.size() < bigint.digitos_.size()) {
      return false;
    } 
    for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
      if (digitos_[iterador] < bigint.digitos_[iterador]) {
        return false;
      } else {
        if (digitos_[iterador] > bigint.digitos_[iterador]) {
          return true;
        }
      }
    }
    return true;
  }
}

// Sobrecarga del operador de suma
template <size_t Base>
BigInt<Base> BigInt<Base>::operator+(const BigInt<Base>& bigint) const {
  int acarreo = 0;
  BigInt<Base> auxiliar;
  BigInt<Base> auxiliar2;
  if (digitos_.size() != bigint.digitos_.size()) {
    if (digitos_.size() < bigint.digitos_.size()) {
      int digitos_faltantes = bigint.digitos_.size() - digitos_.size();
      auxiliar = *this;
      for (int iterador = 0; iterador < bigint.digitos_.size() - digitos_.size(); ++iterador) {
        auxiliar.digitos_.insert(auxiliar.digitos_.begin(), '\000');
      }
      auxiliar2 = bigint;
    } else {
      int digitos_faltantes = digitos_.size() - bigint.digitos_.size();
      auxiliar = bigint;
      for (int iterador = 0; iterador < digitos_faltantes; ++iterador) {
        auxiliar.digitos_.insert(auxiliar.digitos_.begin(), '\000');
      }
      auxiliar2 = *this;
    }
  } else {
    auxiliar = *this;
    auxiliar2 = bigint;
  }
  if (auxiliar.signo_ == auxiliar2.signo_) {
    BigInt<Base> resultado;
    for (int iterador = auxiliar.digitos_.size() - 1; iterador >= 0 ; iterador--) {
      int ai = auxiliar.digitos_[iterador];
      int bi = auxiliar2.digitos_[iterador];
      int sum = (ai + bi + acarreo) % Base;
      acarreo = (ai + bi + acarreo) / Base;
      resultado.digitos_.push_back(sum);
    }
    if (acarreo > 0) {
      resultado.digitos_.push_back(acarreo);
    }
    std::reverse(resultado.digitos_.begin(), resultado.digitos_.end());
    int ceros_eliminar{0};      
    for (int iterador = 0; iterador < resultado.digitos_.size(); ++iterador) {
      if (resultado.digitos_[iterador] == '\000') {
        ceros_eliminar++;      
      } else {
        break;
      }
    }
    resultado.digitos_.erase(resultado.digitos_.begin(), resultado.digitos_.begin() + ceros_eliminar);
    resultado.signo_ = auxiliar2.signo_;
    return resultado;   
  } else {
    BigInt<Base> auxiliar2_signo = auxiliar2;
    BigInt<Base> auxiliar_signo = auxiliar;
    auxiliar.signo_ = false;
    auxiliar2.signo_ = false;
    if (auxiliar < auxiliar2) {
      BigInt<Base> resultado;
      for (int iterador = auxiliar.digitos_.size()- 1; iterador >= 0 ; iterador--) {
        int d = auxiliar2.digitos_[iterador] - auxiliar.digitos_[iterador];
        if (d < 0) {
          int auxiliar_int = auxiliar2.digitos_[iterador] + Base;
          auxiliar2.digitos_[iterador - 1] = auxiliar2.digitos_[iterador - 1] - '\001'; 
          d = auxiliar_int - auxiliar.digitos_[iterador];
          resultado.digitos_.push_back(d);
        } else {
          resultado.digitos_.push_back(d);
        }
      }
      std::reverse(resultado.digitos_.begin(), resultado.digitos_.end());
      int ceros_eliminar{0};      
      for (int iterador = 0; iterador < resultado.digitos_.size(); ++iterador) {
        if (resultado.digitos_[iterador] == '\000') {
          ceros_eliminar++;      
        } else {
          break;
        }
      }
      resultado.digitos_.erase(resultado.digitos_.begin(), resultado.digitos_.begin() + ceros_eliminar);
      resultado.signo_ = auxiliar2_signo.signo_;
      return resultado;   
    } else {
      BigInt<Base> resultado;
      for (int iterador = auxiliar.digitos_.size()- 1; iterador >= 0 ; iterador--) { // terminar
        int d = auxiliar.digitos_[iterador] - auxiliar2.digitos_[iterador];
        if (d < 0) {
          int auxiliar_int = auxiliar.digitos_[iterador] + Base;
          auxiliar.digitos_[iterador - 1] = auxiliar.digitos_[iterador - 1] - '\001'; 
          d = auxiliar_int - auxiliar2.digitos_[iterador];
          resultado.digitos_.push_back(d);
        } else {
          resultado.digitos_.push_back(d);
        }
      }
      std::reverse(resultado.digitos_.begin(), resultado.digitos_.end());
      int ceros_eliminar{0};      
      for (int iterador = 0; iterador < resultado.digitos_.size(); ++iterador) {
        if (resultado.digitos_[iterador] == '\000') {
          ceros_eliminar++;      
        } else {
          break;
        }
      }
      resultado.digitos_.erase(resultado.digitos_.begin(), resultado.digitos_.begin() + ceros_eliminar);
      resultado.signo_ = auxiliar_signo.signo_;
      return resultado;     
    }
  }
}

// Sobrecarga del operador de resta
template <size_t Base>
BigInt<Base> BigInt<Base>::operator-(const BigInt<Base>& bigint) const {
  BigInt<Base> auxiliar;
  BigInt<Base> resultado;
  auxiliar = bigint;
  if (bigint.signo() == false) {
    auxiliar.signo_ = true;
  } else {
    auxiliar.signo_ = false;
  }
  resultado = *this + auxiliar;
  return resultado;
}

// Sobrecarga del operador de multiplicacion
template <size_t Base>
BigInt<Base> BigInt<Base>::operator*(const BigInt<Base>& bigint) const {
  BigInt<Base> resultado;
  long long valor_bigint = bigint.CalculaElValor();
  for (int iterador = 0; iterador < valor_bigint; ++iterador) {
    resultado = resultado + *this;
  }
  if (this->signo_ != bigint.signo_) {
    resultado.signo_ = true;
  } else {
    resultado.signo_ = false;
  }
  return resultado;
}

// Sobrecarga del operador de división
template <size_t Base>
BigInt<Base> BigInt<Base>::operator/(const BigInt<Base>& bigint) const {
  BigInt<Base> auxiliar2;
  BigInt<Base> cociente_parcial;
  BigInt<Base> cociente;
  BigInt<Base> auxiliar = bigint;
  auxiliar.signo_ = false;
  if (*this < auxiliar) {
    return auxiliar2;
  }
  for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
    if (auxiliar2 < auxiliar) {
      auxiliar2.digitos_.insert(auxiliar2.digitos_.begin() + iterador, digitos_[iterador]);
    } else {
      while (auxiliar2 >= auxiliar) {
        auxiliar2 = auxiliar2 - auxiliar;
        cociente_parcial++;
      }
      cociente.digitos_.insert(cociente.digitos_.begin(), cociente_parcial.digitos_[0]);
      cociente_parcial.digitos_.clear();
      auxiliar2.digitos_.push_back(digitos_[iterador]);
    }
  }
  if (auxiliar2 < auxiliar) {
    cociente_parcial.digitos_.clear();
    cociente_parcial.digitos_.push_back('\000');
  } else {
    while (auxiliar2 > auxiliar) {
      auxiliar2 = auxiliar2 - auxiliar;
      cociente_parcial++;
    }
  }
  cociente.digitos_.insert(cociente.digitos_.begin(), cociente_parcial.digitos_[0]);
  cociente_parcial.digitos_.clear();
  std::reverse(cociente.digitos_.begin(), cociente.digitos_.end());
  if (this->signo_ != bigint.signo_) {
    cociente.signo_ = true;
  } else {
    cociente.signo_ = false;
  }
  return cociente;
}

// Sobrecarga del operador de módulo
template <size_t Base>
BigInt<Base> BigInt<Base>::operator%(const BigInt<Base>& bigint) const {
  BigInt<Base> auxiliar2;
  BigInt<Base> cociente_parcial;
  BigInt<Base> cociente;
  BigInt<Base> auxiliar = bigint;
  auxiliar.signo_ = false;
  if (*this < auxiliar) {
    return auxiliar2;
  }
  for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
    if (auxiliar2 < auxiliar) {
      auxiliar2.digitos_.insert(auxiliar2.digitos_.begin() + iterador, digitos_[iterador]);
    } else {
      while (auxiliar2 >= auxiliar) {
        auxiliar2 = auxiliar2 - auxiliar;
        cociente_parcial++;
      }
      cociente.digitos_.insert(cociente.digitos_.begin(), cociente_parcial.digitos_[0]);
      cociente_parcial.digitos_.clear();
      auxiliar2.digitos_.push_back(digitos_[iterador]);
    }
  }
  if (auxiliar2 < auxiliar) {
    return auxiliar2;
  } else {
    while (auxiliar2 > auxiliar) {
      auxiliar2 = auxiliar2 - auxiliar;
      cociente_parcial++;
    }
    auxiliar2.signo_ = false;
    return auxiliar2;
  }
}

// Sobrecarga del operador de potencia
template <size_t Base>
BigInt<Base> BigInt<Base>::potencia(const BigInt<Base>& bigint, const BigInt<Base>& bigint2) const {
  BigInt<Base> resultado = bigint;
  BigInt<Base> auxiliar = bigint2;
  long long valor_auxiliar = auxiliar.CalculaElValor();
  for (int iterador = 0; iterador < valor_auxiliar - 1; ++iterador) {
    resultado = resultado * bigint;
  }
  resultado.signo_ = this->signo_;
  return resultado;
}

// Sobrecarga del operador de post-incremento
template <size_t Base>
BigInt<Base>& BigInt<Base>::operator++() {
  long incremento_long = 1;
  BigInt<Base> auxiliar(incremento_long);
  BigInt<Base> auxiliar2 = *this;
  *this = *this + auxiliar;
  return auxiliar2;
}

// Sobrecarga del operador de pre-incremento
template <size_t Base>
BigInt<Base> BigInt<Base>::operator++(int incremento) {
  long incremento_long = 1;
  BigInt<Base> auxiliar(incremento_long);
  *this = *this + auxiliar;
  return *this;
}

// Sobrecarga del operador de pre-decremento
template <size_t Base>
BigInt<Base>& BigInt<Base>::operator--() {
  long incremento_long = 1;
  BigInt<Base> auxiliar(incremento_long);
  BigInt<Base> auxiliar2 = *this;
  *this = *this - auxiliar;
  return auxiliar2;
}

// Sobrecarga del operador de post-decremento
template <size_t Base>
BigInt<Base> BigInt<Base>::operator--(int decremento) {
  long decremento_long = 1;
  BigInt<Base> auxiliar(decremento_long);
  *this = *this - auxiliar;
  return *this;
}

// Sobrecarga del operador de entrada
template <size_t Base>
std::istream& operator>>(std::istream& entrada, BigInt<Base>& bigint) {
  std::string string_auxiliar;
  char caracter_modificado;
  entrada >> string_auxiliar;
  for (int iterador = string_auxiliar.size() - 1; iterador >= 0; --iterador) {
    caracter_modificado = string_auxiliar[iterador];
  }
  return entrada;
}

// Sobrecarga del operador de entrada
template <size_t Base>
std::ostream& operator<<(std::ostream& salida, const BigInt<Base>& bigint) {
  for (int iterador = 0; iterador < bigint.digitos_.size() ; ++iterador) {
    salida << bigint.digitos_[iterador];
  }
  return salida;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::OperacionOR(const BigInt<Base>& bigint) const {
  BigInt<Base> auxiliar;
  BigInt<Base> auxiliar2;
  BigInt<Base> auxiliar3 = *this;
  BigInt<Base> auxiliar4 = bigint;
  BigInt<Base> suma;
  if (Base != 2) {
    std::cout << "No se puede realizar la operacion OR a un número que no esté en base 2" << std::endl;
    exit(EXIT_FAILURE);
  } else {
    BigInt<Base> resultado;
    for (int iterador = auxiliar.digitos_.size() - 1; iterador >= 0 ; iterador--) {
      if (*this > bigint) {
        BigInt<Base> auxiliar = auxiliar3[iterador];
        BigInt<Base> auxiliar2 = auxiliar4.digitos_[iterador];
      } else {
        BigInt<Base> auxiliar = auxiliar4.digitos_[iterador];
        BigInt<Base> auxiliar2 = auxiliar3[iterador]; 
      }
      suma = auxiliar + auxiliar2;
      if (suma.digitos_.size() == 2) {
        suma.digitos_.erase(suma.digitos_.begin());
        auxiliar3.digitos_[iterador - 1] = '\001';
        resultado.digitos_.push_back(suma[0]);
      } else {
        resultado.digitos_.push_back(suma[0]);
      } 
    }
    return resultado;
  }
}

void Usage(int argc, char *argv[]);

#endif