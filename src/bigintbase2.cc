/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: AyEDA
/// Curso: 2º
/// Práctica 2: Representación de números binarios grandes
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 27/02/2023
/// Archivo: bigintbase2.cc

#include "bigint.h"

// Función para calcular el complemento a 2 de un número binario
BigInt<2> BigInt<2>::CalculaElC2() const {
  BigInt<2> auxiliar = *this;
  bool bit_encontrado{false};
  for (int iterador = auxiliar.digitos_.size() - 1; iterador >= 0; --iterador) {
    if (bit_encontrado == true) {
      if (auxiliar.digitos_[iterador] == 1) {
        auxiliar.digitos_[iterador] = 0;
      } else {
        auxiliar.digitos_[iterador] = 1;
      }
    }
    if (auxiliar.digitos_[iterador] == 1) {
      bit_encontrado = true;
    }
  }
  return auxiliar;
}

// Función que elimina los ceros no relevantes del número binario
BigInt<2> BigInt<2>::EliminaCerosIzquierda() const {
  BigInt<2> auxiliar = *this;
  int tamanio_numero = auxiliar.digitos_.size();
  for (int iterador = 0; iterador < tamanio_numero; ++iterador) {
    if (auxiliar.digitos_[0] == 1) {
      break;
    }
    auxiliar.digitos_.erase(auxiliar.digitos_.begin());
  }
  auxiliar.digitos_.insert(auxiliar.digitos_.begin(), 0);
  return auxiliar;
}

// Constructor mediante un tipo long
BigInt<2>::BigInt(long n) {
  int digito_extraido{0};
  while (n > 0) {
    digito_extraido = n % 10;
    digitos_.push_back(digito_extraido);
    n /= 10;
  }
}

// Constructor mediante un tipo string
BigInt<2>::BigInt(std::string& string_introducida) {
  int digito_introducir{0};
  char caracter_introducir;
  for (int iterador = 0; iterador < string_introducida.size(); iterador++) {
    caracter_introducir = string_introducida[iterador] - '0';
    digito_introducir = caracter_introducir;
    digitos_.push_back(digito_introducir);
  }
}

// Constructor mediante un tipo char*
BigInt<2>::BigInt(const char* cadena_introducida) {
  std::string cadena_introducida_str = cadena_introducida;
  int digito_introducir{0};
  char caracter_introducir;
  for (int iterador = 0; iterador < cadena_introducida_str.size(); iterador++) {
    caracter_introducir = cadena_introducida_str[iterador];
    digito_introducir = caracter_introducir;
    digitos_.push_back(digito_introducir);
  }
}

// Constructor mediante un tipo BigInt
BigInt<2>::BigInt(const BigInt<2>& bigint) {
  digitos_ = bigint.digitos_;
}

// Operador de asignación
BigInt<2>& BigInt<2>::operator=(const BigInt<2>& bigint) {
  this->digitos_ = bigint.digitos_;
  return *this;
}

// Operador de igualdad
bool BigInt<2>::operator==(const BigInt<2>& bigint) const {
  if (digitos_.size() != bigint.digitos_.size()) {
    return false;
  }
  for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
    if (digitos_[iterador] != bigint.digitos_[iterador]) {
      return false;
    }
  }
  return true;
}

// Operador de diferencia
bool BigInt<2>::operator!=(const BigInt<2>& bigint) const {
  bool diferencia_encontrada{false};
  if (digitos_.size() != bigint.digitos_.size()) {
    return true;
  }
  for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
    if (digitos_[iterador] != bigint.digitos_[iterador]) {
      diferencia_encontrada = true;
      break;
    }
  }
  return diferencia_encontrada;
}

// Operador menor que
bool BigInt<2>::operator<(const BigInt<2>& bigint) const {
  if (digitos_[0] != bigint.digitos_[0]) {
    if (digitos_[0] == 1) {
      return true;
    } else {
      return false;
    }
  }
  if (digitos_.size() < bigint.digitos_.size()) {
    return true;
  } else {
    if (digitos_.size() > bigint.digitos_.size()) {
      return false;
    }
    if (digitos_[0] == 0) {
      for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
        if (digitos_[iterador] < bigint.digitos_[iterador]) {
          return true;
        } else {
          if (digitos_[iterador] > bigint.digitos_[iterador]) {
            return false;
          }
        }
      }
    } else {
      for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
        if (digitos_[iterador] < bigint.digitos_[iterador]) {
          return false;
        } else {
          if (digitos_[iterador] > bigint.digitos_[iterador]) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

// Operador menor igual que
bool BigInt<2>::operator<=(const BigInt<2>& bigint) const {
  if (digitos_[0] != bigint.digitos_[0]) {
    if (digitos_[0] == 1) {
      return true;
    } else {
      return false;
    }
  }
  if (digitos_.size() < bigint.digitos_.size()) {
    return true;
  } else {
    if (digitos_.size() > bigint.digitos_.size()) {
      return false;
    }
    if (digitos_[0] == 0) {
      for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
        if (digitos_[iterador] < bigint.digitos_[iterador]) {
          return true;
        } else {
          if (digitos_[iterador] > bigint.digitos_[iterador]) {
            return false;
          }
        }
      }
    } else {
      for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
        if (digitos_[iterador] < bigint.digitos_[iterador]) {
          return false;
        } else {
          if (digitos_[iterador] > bigint.digitos_[iterador]) {
            return true;
          }
        }
      }
    }
  }
  return true;
}

// Operador mayor que
bool BigInt<2>::operator>(const BigInt<2>& bigint) const {
  if (digitos_[0] != bigint.digitos_[0]) {
    if (digitos_[0] == 1) {
      return false;
    } else {
      return true;
    }
  }
  if (digitos_.size() < bigint.digitos_.size()) {
    return false;
  } else {
    if (digitos_.size() > bigint.digitos_.size()) {
      return true;
    }
    if (digitos_[0] == 0) {
      for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
        if (digitos_[iterador] < bigint.digitos_[iterador]) {
          return false;
        } else {
          if (digitos_[iterador] > bigint.digitos_[iterador]) {
            return true;
          }
        }
      }
    } else {
      for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
        if (digitos_[iterador] < bigint.digitos_[iterador]) {
          return true;
        } else {
          if (digitos_[iterador] > bigint.digitos_[iterador]) {
            return false;
          }
        }
      }
    }
  }
  return false;
}

// Operador mayor igual que
bool BigInt<2>::operator>=(const BigInt<2>& bigint) const {
  if (digitos_[0] != bigint.digitos_[0]) {
    if (digitos_[0] == 1) {
      return false;
    } else {
      return true;
    }
  }
  if (digitos_.size() < bigint.digitos_.size()) {
    return false;
  } else {
    if (digitos_.size() > bigint.digitos_.size()) {
      return true;
    }
    if (digitos_[0] == 0) {
      for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
        if (digitos_[iterador] < bigint.digitos_[iterador]) {
          return false;
        } else {
          if (digitos_[iterador] > bigint.digitos_[iterador]) {
            return true;
          }
        }
      }
    } else {
      for (int iterador = 0; iterador < digitos_.size(); ++iterador) {
        if (digitos_[iterador] < bigint.digitos_[iterador]) {
          return true;
        } else {
          if (digitos_[iterador] > bigint.digitos_[iterador]) {
            return false;
          }
        }
      }
    }
  }
  return true;
}

// Sobrecarga del operador de suma
BigInt<2> BigInt<2>::operator+(const BigInt<2>& bigint) const {
  BigInt<2> resultado;
  int acarreo{0};
  BigInt<2> auxiliar1 = *this;
  BigInt<2> auxiliar2 = bigint;
  if (digitos_.size() != bigint.digitos_.size()) {
    if (digitos_.size() < bigint.digitos_.size()) {
      if (digitos_[0] == 1) {
        for (int iterador = 0; iterador < bigint.digitos_.size() - digitos_.size(); ++iterador) {
          auxiliar1.digitos_.insert(auxiliar1.digitos_.begin(), 1);
        }
      } else {
        for (int iterador = 0; iterador < bigint.digitos_.size() - digitos_.size(); ++iterador) {
          auxiliar1.digitos_.insert(auxiliar1.digitos_.begin(), 0);
        }
      }
    } else {
      if (bigint.digitos_[0] == 1) {
        for (int iterador = 0; iterador < digitos_.size() - bigint.digitos_.size(); ++iterador) {
          auxiliar2.digitos_.insert(auxiliar2.digitos_.begin(), 1);
        }
      } else {
        for (int iterador = 0; iterador < digitos_.size() - bigint.digitos_.size(); ++iterador) {
          auxiliar2.digitos_.insert(auxiliar2.digitos_.begin(), 0);
        }
      }
    }
  }
  for (int iterador = auxiliar1.digitos_.size() - 1; iterador >= 0 ; iterador--) {
    int digito_operando1 = auxiliar1.digitos_[iterador];
    int digito_operando2 = auxiliar2.digitos_[iterador];
    int sum = (digito_operando1 + digito_operando2 + acarreo) % 2;
    acarreo = (digito_operando1 + digito_operando2 + acarreo) / 2;
    resultado.digitos_.push_back(sum);
  }
  if (acarreo > 0) {
    resultado.digitos_.push_back(acarreo);
  }
  if (this->digitos_[0] == 0 && bigint.digitos_[0] == 0 && resultado.digitos_[resultado.digitos_.size() - 1] == 1) {
    resultado.digitos_.push_back(0); 
    std::reverse(resultado.digitos_.begin(), resultado.digitos_.end());
    resultado = resultado.EliminaCerosIzquierda();
  } else {
    if ((this->digitos_[0] == 1 && bigint.digitos_[0] == 0) || (this->digitos_[0] == 0 && bigint.digitos_[0] == 1)  && resultado.digitos_[resultado.digitos_.size() - 1] == 1) {
      if (acarreo == 1) {
        resultado.digitos_.pop_back();
      }
      std::reverse(resultado.digitos_.begin(), resultado.digitos_.end());
    } else {
      std::reverse(resultado.digitos_.begin(), resultado.digitos_.end());
    }
  }
  return resultado;
}

// Sobrecarga del operador de resta
BigInt<2> BigInt<2>::operator-(const BigInt<2>& bigint) const {
  BigInt<2> auxiliar2 = bigint.CalculaElC2();
  BigInt<2> resultado = *this + auxiliar2;
  return resultado;
}

// Sobrecarga del operador de multiplicación
BigInt<2> BigInt<2>::operator*(const BigInt<2>& bigint) const {
  BigInt<2> auxiliar1 = *this;
  BigInt<2> auxiliar2 = bigint;
  if (digitos_.size() != bigint.digitos_.size()) {
    if (digitos_.size() < bigint.digitos_.size()) {
      if (digitos_[0] == 1) {
        for (int iterador = 0; iterador < bigint.digitos_.size() - digitos_.size(); ++iterador) {
          auxiliar1.digitos_.insert(auxiliar1.digitos_.begin(), 1);
        }
      } else {
        for (int iterador = 0; iterador < bigint.digitos_.size() - digitos_.size(); ++iterador) {
          auxiliar1.digitos_.insert(auxiliar1.digitos_.begin(), 0);
        }
      }
    } else {
      if (bigint.digitos_[0] == 1) {
        for (int iterador = 0; iterador < digitos_.size() - bigint.digitos_.size(); ++iterador) {
          auxiliar2.digitos_.insert(auxiliar2.digitos_.begin(), 1);
        }
      } else {
        for (int iterador = 0; iterador < digitos_.size() - bigint.digitos_.size(); ++iterador) {
          auxiliar2.digitos_.insert(auxiliar2.digitos_.begin(), 0);
        }
      }
    }
  }
  if (auxiliar1.digitos_[0] == 1) {
    auxiliar1.digitos_.insert(auxiliar1.digitos_.begin(), 1);
  } else {
    auxiliar1.digitos_.insert(auxiliar1.digitos_.begin(), 0);
  }
  BigInt<2> operador_a;
  for (int iterador = 0; iterador < auxiliar1.digitos_.size(); ++iterador) {
    operador_a.digitos_.push_back(0);
  }
  BigInt<2> auxiliar_desplazamiento;
  auxiliar2.digitos_.push_back(0);
  for (int iterador = 0; iterador <= auxiliar1.digitos_.size() - 1; ++iterador) {
    switch (auxiliar2.digitos_[auxiliar2.digitos_.size() - 1]) {
      case 1: {
        if (auxiliar2.digitos_[auxiliar2.digitos_.size() - 2] == 0) {
          int tamanio_operador_a = operador_a.digitos_.size();
          operador_a = operador_a + auxiliar1;
          if (tamanio_operador_a != operador_a.digitos_.size()) {
            operador_a.digitos_.erase(operador_a.digitos_.begin());
          }
        }
        break;
      }
      case 0: {
        if (auxiliar2.digitos_[auxiliar2.digitos_.size() - 2] == 1) {
          int tamanio_operador_a = operador_a.digitos_.size();         
          operador_a = operador_a - auxiliar1;
          if (tamanio_operador_a != operador_a.digitos_.size()) {
            operador_a.digitos_.erase(operador_a.digitos_.begin());
          }         
        }
        break;
      }
      default: {
        break;
      }
    }
    auxiliar_desplazamiento = operador_a;
    auxiliar_desplazamiento.digitos_.insert(auxiliar_desplazamiento.digitos_.end(), auxiliar2.digitos_.begin(), auxiliar2.digitos_.end());
    std::rotate(auxiliar_desplazamiento.digitos_.rbegin(), auxiliar_desplazamiento.digitos_.rbegin() + 1, auxiliar_desplazamiento.digitos_.rend());
    auxiliar_desplazamiento.digitos_[0] = auxiliar_desplazamiento.digitos_[1];
    std::vector<bool> resultado_desplazado;
    resultado_desplazado.resize(operador_a.digitos_.size());
    std::copy(auxiliar_desplazamiento.digitos_.begin(), auxiliar_desplazamiento.digitos_.begin() + auxiliar1.digitos_.size(), resultado_desplazado.begin());
    operador_a.digitos_ = resultado_desplazado;
    resultado_desplazado.clear();
    resultado_desplazado.resize(auxiliar2.digitos_.size());
    std::copy(auxiliar_desplazamiento.digitos_.begin() + auxiliar1.digitos_.size(), auxiliar_desplazamiento.digitos_.end(), resultado_desplazado.begin());
    auxiliar2.digitos_ = resultado_desplazado;
  }
  auxiliar_desplazamiento = operador_a;
  auxiliar_desplazamiento.digitos_.insert(auxiliar_desplazamiento.digitos_.end(), auxiliar2.digitos_.begin(), auxiliar2.digitos_.end() - 1);
  BigInt<2> resultado;
  if ((this->digitos_[0] == 1 && bigint.digitos_[0] == 0) || (this->digitos_[0] == 0 && bigint.digitos_[0] == 1)) {
    auxiliar_desplazamiento = auxiliar_desplazamiento.CalculaElC2();
    BigInt<2> resultado = auxiliar_desplazamiento.EliminaCerosIzquierda();
    resultado = resultado.CalculaElC2();
  } else {
    resultado = auxiliar_desplazamiento.EliminaCerosIzquierda();
  }
  resultado = resultado + resultado;
  return resultado;
}

// Sobrecarga del operador de división
BigInt<2> BigInt<2>::operator/(const BigInt<2>& bigint) const {
  BigInt<2> auxiliar1 = *this;
  BigInt<2> auxiliar2 = bigint;
  bool signo_auxiliar1{false};
  bool signo_auxiliar2{false}; 
  if (auxiliar1.digitos_[0] == 1) {
    auxiliar1 = auxiliar1.CalculaElC2();
    signo_auxiliar1 = true;
  }
  if (auxiliar2.digitos_[0] == 1) {
    auxiliar2 = auxiliar2.CalculaElC2();
    signo_auxiliar2 = true;
  }
  if (digitos_.size() != bigint.digitos_.size()) {
    if (digitos_.size() < bigint.digitos_.size()) {
      if (digitos_[0] == 1) {
        for (int iterador = 0; iterador < bigint.digitos_.size() - digitos_.size(); ++iterador) {
          auxiliar1.digitos_.insert(auxiliar1.digitos_.begin(), 1);
        }
      } else {
        for (int iterador = 0; iterador < bigint.digitos_.size() - digitos_.size(); ++iterador) {
          auxiliar1.digitos_.insert(auxiliar1.digitos_.begin(), 0);
        }
      }
    } else {
      if (bigint.digitos_[0] == 1) {
        for (int iterador = 0; iterador < digitos_.size() - bigint.digitos_.size(); ++iterador) {
          auxiliar2.digitos_.insert(auxiliar2.digitos_.begin(), 1);
        }
      } else {
        for (int iterador = 0; iterador < digitos_.size() - bigint.digitos_.size(); ++iterador) {
          auxiliar2.digitos_.insert(auxiliar2.digitos_.begin(), 0);
        }
      }
    }
  }
  auxiliar1.digitos_.erase(auxiliar1.digitos_.begin());
  BigInt<2> operador_a;
  for (int iterador = 0; iterador < auxiliar2.digitos_.size(); ++iterador) {
    operador_a.digitos_.push_back(0);
  }
  int tamanio_aux1 = auxiliar1.digitos_.size();
  bool bit_desplazado{false};
  for (int iterador = 0; iterador < tamanio_aux1; ++iterador) {
    bit_desplazado = auxiliar1.digitos_[0];
    auxiliar1.digitos_.erase(auxiliar1.digitos_.begin());
    operador_a.digitos_.push_back(bit_desplazado);
    operador_a.digitos_.erase(operador_a.digitos_.begin());
    int tamanio_operador_a = operador_a.digitos_.size();
    operador_a = operador_a - auxiliar2;
    if (tamanio_operador_a != operador_a.digitos_.size()) {
      operador_a.digitos_.erase(operador_a.digitos_.begin());
    }   
    if (operador_a.digitos_[0] == 1) {
      int tamanio_operador_a = operador_a.digitos_.size();
      operador_a = operador_a + auxiliar2;
      if (tamanio_operador_a != operador_a.digitos_.size()) {
        operador_a.digitos_.erase(operador_a.digitos_.begin());
      }      
      auxiliar1.digitos_.push_back(0);
    } else {
      auxiliar1.digitos_.push_back(1);
    }
  }
  auxiliar1 = auxiliar1.EliminaCerosIzquierda();
  if (signo_auxiliar1 != signo_auxiliar2) {
    return auxiliar1.CalculaElC2();
  } else {
    return auxiliar1;
  }
}

// Sobrecarga del operador de módulo
BigInt<2> BigInt<2>::operator%(const BigInt<2>& bigint) const {
  BigInt<2> auxiliar1 = *this;
  BigInt<2> auxiliar2 = bigint;
  bool signo_auxiliar1{false};
  bool signo_auxiliar2{false}; 
  if (auxiliar1.digitos_[0] == 1) {
    auxiliar1 = auxiliar1.CalculaElC2();
    signo_auxiliar1 = true;
  }
  if (auxiliar2.digitos_[0] == 1) {
    auxiliar2 = auxiliar2.CalculaElC2();
    signo_auxiliar2 = true;
  }
  if (digitos_.size() != bigint.digitos_.size()) {
    if (digitos_.size() < bigint.digitos_.size()) {
      if (digitos_[0] == 1) {
        for (int iterador = 0; iterador < bigint.digitos_.size() - digitos_.size(); ++iterador) {
          auxiliar1.digitos_.insert(auxiliar1.digitos_.begin(), 1);
        }
      } else {
        for (int iterador = 0; iterador < bigint.digitos_.size() - digitos_.size(); ++iterador) {
          auxiliar1.digitos_.insert(auxiliar1.digitos_.begin(), 0);
        }
      }
    } else {
      if (bigint.digitos_[0] == 1) {
        for (int iterador = 0; iterador < digitos_.size() - bigint.digitos_.size(); ++iterador) {
          auxiliar2.digitos_.insert(auxiliar2.digitos_.begin(), 1);
        }
      } else {
        for (int iterador = 0; iterador < digitos_.size() - bigint.digitos_.size(); ++iterador) {
          auxiliar2.digitos_.insert(auxiliar2.digitos_.begin(), 0);
        }
      }
    }
  }
  auxiliar1.digitos_.erase(auxiliar1.digitos_.begin());
  BigInt<2> operador_a;
  for (int iterador = 0; iterador < auxiliar2.digitos_.size(); ++iterador) {
    operador_a.digitos_.push_back(0);
  }
  int tamanio_aux1 = auxiliar1.digitos_.size();
  bool bit_desplazado{false};
  for (int iterador = 0; iterador < tamanio_aux1; ++iterador) {
    bit_desplazado = auxiliar1.digitos_[0];
    auxiliar1.digitos_.erase(auxiliar1.digitos_.begin());
    operador_a.digitos_.push_back(bit_desplazado);
    operador_a.digitos_.erase(operador_a.digitos_.begin());
    int tamanio_operador_a = operador_a.digitos_.size();
    operador_a = operador_a - auxiliar2;
    if (tamanio_operador_a != operador_a.digitos_.size()) {
      operador_a.digitos_.erase(operador_a.digitos_.begin());
    }  
    if (operador_a.digitos_[0] == 1) {
      int tamanio_operador_a = operador_a.digitos_.size();
      operador_a = operador_a + auxiliar2;
      if (tamanio_operador_a != operador_a.digitos_.size()) {
        operador_a.digitos_.erase(operador_a.digitos_.begin());
      }  
      auxiliar1.digitos_.push_back(0);
    } else {
      auxiliar1.digitos_.push_back(1);
    }
  }
  return operador_a.EliminaCerosIzquierda();
}

// Conversor de base binaria a octal
BigInt<2>::operator BigInt<8>() {
  BigInt<2> auxiliar = *this;
  if (auxiliar.digitos_[0] == 1) {
    auxiliar = auxiliar.CalculaElC2();
  }
  auxiliar.digitos_.erase(auxiliar.digitos_.begin());
  while (auxiliar.digitos_.size() % 3 != 0) {
    auxiliar.digitos_.insert(auxiliar.digitos_.begin(), 0);
  }
  std::string numero_octal;
  std::vector<bool> bits_extraidos;
  for (int iterador = 0; iterador < auxiliar.digitos_.size(); iterador++) {
    if ((iterador + 1) % 3 == 0) {
      bits_extraidos.push_back(auxiliar.digitos_[iterador]);
      int potencia_dos = 1;
      int valor_digito = 0;
      for (int iterador2 = bits_extraidos.size() - 1; iterador2 >= 0; --iterador2) {
        if (bits_extraidos[iterador2] == 1) {
          valor_digito += potencia_dos;
        }
        potencia_dos *= 2;
      }
      if (valor_digito >= 0) {
        char digito_octal;
        digito_octal = '0' + valor_digito;
        numero_octal = digito_octal + numero_octal; 
      }
      bits_extraidos.clear();
    } else {
      bits_extraidos.push_back(auxiliar.digitos_[iterador]);
    }
  }
  std::reverse(numero_octal.begin(), numero_octal.end());
  if (this->digitos_[0] == 1) {
    numero_octal.insert(numero_octal.begin(), '-');
  }
  BigInt<8> resultado(numero_octal);
  return resultado; 
}

// Conversor de base binaria a decimal
BigInt<2>::operator BigInt<10>() {
  BigInt<2> auxiliar = *this;
  if (auxiliar.digitos_[0] == 1) {
    auxiliar = auxiliar.CalculaElC2();
  }
  auxiliar.digitos_.erase(auxiliar.digitos_.begin());
  long long potencia_dos = 1;
  long long valor_digito = 0;
  for (int iterador = auxiliar.digitos_.size() - 1; iterador >= 0; iterador--) {
    if (auxiliar.digitos_[iterador] == 1) {
      valor_digito += potencia_dos;
    }
    potencia_dos *= 2;
  }
  std::string str_resultado = std::to_string(valor_digito);
  if (this->digitos_[0] == 1) {
    str_resultado.insert(str_resultado.begin(), '-');
  }
  BigInt<10> resultado(str_resultado);
  return resultado; 
}

// Conversor de base binaria a hexadecimal
BigInt<2>::operator BigInt<16>() {
  BigInt<2> auxiliar = *this;
  std::string numero_hexadecimal;
  if (auxiliar.digitos_[0] == 1) {
    auxiliar = auxiliar.CalculaElC2();
  }
  auxiliar.digitos_.erase(auxiliar.digitos_.begin());
  while (auxiliar.digitos_.size() % 4 != 0) {
    auxiliar.digitos_.insert(auxiliar.digitos_.begin(), 0);
  }
  std::vector<bool> bits_extraidos;
  for (int iterador = 0; iterador < auxiliar.digitos_.size(); iterador++) {
    if ((iterador + 1) % 4 == 0) {
      bits_extraidos.push_back(auxiliar.digitos_[iterador]);
      int potencia_dos = 1;
      int valor_digito = 0;
      for (int iterador2 = bits_extraidos.size() - 1; iterador2 >= 0; --iterador2) {
        if (bits_extraidos[iterador2] == 1) {
          valor_digito += potencia_dos;
        }
        potencia_dos *= 2;
      }
      if (valor_digito >= 0) {
        char digito_hex;
        if ((valor_digito <= 9) && (valor_digito >= 0)) {
          digito_hex = '0' + valor_digito;
        } else {
          digito_hex = valor_digito - 10 + 'A';
        }
        numero_hexadecimal = digito_hex + numero_hexadecimal; 
      }
      bits_extraidos.clear();
    } else {
      bits_extraidos.push_back(auxiliar.digitos_[iterador]);
    }
  }
  std::reverse(numero_hexadecimal.begin(), numero_hexadecimal.end());
  if (this->digitos_[0] == 1) {
    numero_hexadecimal.insert(numero_hexadecimal.begin(), '-');
  }
  BigInt<16> resultado(numero_hexadecimal);
  return resultado;
}

// Sobrecarga de operador de post-incremento
BigInt<2>& BigInt<2>::operator++() {
  long incremento_long = 1;
  BigInt<2> auxiliar(incremento_long);
  BigInt<2> auxiliar2 = *this;
  *this = *this + auxiliar;
  return auxiliar2;
}

// Sobrecarga de operador de pre-incremento
BigInt<2> BigInt<2>::operator++(int incremento) {
  long incremento_long = 1;
  BigInt<2> auxiliar(incremento_long);
  *this = *this + auxiliar;
  return *this;
}

// Sobrecarga de operador de post-decremento
BigInt<2>& BigInt<2>::operator--() {
  long decremento_long = 1;
  BigInt<2> auxiliar(decremento_long);
  BigInt<2> auxiliar2 = *this;
  *this = *this - auxiliar;
  return auxiliar2;
}

// Sobrecarga de operador de pre-decremento
BigInt<2> BigInt<2>::operator--(int decremento) {
  long decremento_long = 1;
  BigInt<2> auxiliar(decremento_long);
  *this = *this - auxiliar;
  return *this;
}

int BigInt<2>::ObtieneLaCantidadDeBytes() const {
  size_t cantidad_bytes{0};
  for (int iterador = 0; iterador < this->digitos_.size(); ++iterador) {
    cantidad_bytes = sizeof(this->digitos_[iterador]);
    cantidad_bytes += cantidad_bytes;
  }
  std::cout << sizeof(bool);
  return cantidad_bytes;
}
