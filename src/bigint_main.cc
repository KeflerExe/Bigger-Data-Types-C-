/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: AyEDA
/// Curso: 2º
/// Práctica 1: Representación de números grandes en notación posicional
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 14/02/2023
/// Archivo: bigint_main.cc

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stack>
#include <sstream>

#include "bigint.h"

// Función que extrae los datos de el archivo para realizar los cálculos y escribirlos
template <size_t Base>
void CalculadoraRPN(const BigInt<Base>& bigint, std::string& nombre_archivo_origen, std::string& nombre_archivo_destino) {
  std::map<std::string, BigInt<Base>> parejas;
  std::string linea_extraida;
  std::ifstream archivo_origen;
  archivo_origen.open(nombre_archivo_origen);
  int posicion_etiqueta{0};
  std::stack<std::string> pila_operaciones;
  while (getline(archivo_origen, linea_extraida)) {
    if (linea_extraida.find("Base") == std::string::npos) {
      if (linea_extraida[linea_extraida.find_first_of('=') + 1] == ' ') {
        linea_extraida.erase(linea_extraida.find_first_of('=') + 1, 1);
      }
      std::string etiqueta = linea_extraida.substr(0, linea_extraida.find_first_of('='));    
      if (etiqueta[etiqueta.size() - 1] == ' ') {
        etiqueta.erase(etiqueta.size() - 1, 1);
      } 
      if (linea_extraida.find('+') == std::string::npos && linea_extraida.find('-') == std::string::npos && linea_extraida.find('*') == std::string::npos && linea_extraida.find('/') == std::string::npos && linea_extraida.find('%') == std::string::npos && linea_extraida.find('^') == std::string::npos) {
        std::string valor_bigint = linea_extraida.substr(linea_extraida.find_first_of('=') + 1, linea_extraida.size() - 1);
        BigInt<Base> auxiliar(valor_bigint);
        parejas[etiqueta] = auxiliar;
      } else {
        std::string operaciones;
        linea_extraida.erase(0, linea_extraida.find_first_of('=') + 1);
        std::stringstream sstring(linea_extraida);
        while (getline(sstring, operaciones, ' ')) {
          char caracter_extraido = operaciones[0];
          switch (caracter_extraido) {
            case '+': {
              std::string etiqueta_extraida = pila_operaciones.top();
              BigInt<Base> auxiliar(parejas[etiqueta_extraida]);
              pila_operaciones.pop();
              etiqueta_extraida = pila_operaciones.top();
              BigInt<Base> auxiliar2(parejas[etiqueta_extraida]);
              pila_operaciones.pop();
              BigInt<Base> auxiliar3 = auxiliar + auxiliar2;
              pila_operaciones.push(etiqueta);
              parejas[etiqueta] = auxiliar3;
              break;
            }
            case '-': {
              std::string etiqueta_extraida = pila_operaciones.top();
              BigInt<Base> auxiliar(parejas[etiqueta_extraida]);
              pila_operaciones.pop();
              etiqueta_extraida = pila_operaciones.top();
              BigInt<Base> auxiliar2(parejas[etiqueta_extraida]);
              pila_operaciones.pop();
              BigInt<Base> auxiliar3 = auxiliar - auxiliar2;
              pila_operaciones.push(etiqueta);
              parejas[etiqueta] = auxiliar3;
              break;
            }
            case '*': {
              std::string etiqueta_extraida = pila_operaciones.top();
              BigInt<Base> auxiliar(parejas[etiqueta_extraida]);
              pila_operaciones.pop();
              etiqueta_extraida = pila_operaciones.top();
              BigInt<Base> auxiliar2(parejas[etiqueta_extraida]);
              pila_operaciones.pop();
              BigInt<Base> auxiliar3 = auxiliar * auxiliar2;
              pila_operaciones.push(etiqueta);
              parejas[etiqueta] = auxiliar3;             
              break;
            }
            case '/': {
              std::string etiqueta_extraida = pila_operaciones.top();
              BigInt<Base> auxiliar(parejas[etiqueta_extraida]);
              pila_operaciones.pop();
              etiqueta_extraida = pila_operaciones.top();
              BigInt<Base> auxiliar2(parejas[etiqueta_extraida]);
              pila_operaciones.pop();
              BigInt<Base> auxiliar3 = auxiliar / auxiliar2;
              pila_operaciones.push(etiqueta);
              parejas[etiqueta] = auxiliar3;             
              break;
            }
            case '%': {
              std::string etiqueta_extraida = pila_operaciones.top();
              BigInt<Base> auxiliar(parejas[etiqueta_extraida]);
              pila_operaciones.pop();
              etiqueta_extraida = pila_operaciones.top();
              BigInt<Base> auxiliar2(parejas[etiqueta_extraida]);
              pila_operaciones.pop();
              BigInt<Base> auxiliar3 = auxiliar % auxiliar2;
              pila_operaciones.push(etiqueta);
              parejas[etiqueta] = auxiliar3;
              break;
            }
            case '^': {
              std::string etiqueta_extraida = pila_operaciones.top();
              BigInt<Base> auxiliar(parejas[etiqueta_extraida]);
              pila_operaciones.pop();
              etiqueta_extraida = pila_operaciones.top();
              BigInt<Base> auxiliar2(parejas[etiqueta_extraida]);
              pila_operaciones.pop();
              BigInt<Base> auxiliar3 = auxiliar.potencia(auxiliar, auxiliar2);
              pila_operaciones.push(etiqueta);
              parejas[etiqueta] = auxiliar3;
              break;
            }
            case '|': {
              std::string etiqueta_extraida = pila_operaciones.top();
              BigInt<Base> auxiliar(parejas[etiqueta_extraida]);
              pila_operaciones.pop();
              etiqueta_extraida = pila_operaciones.top();
              BigInt<Base> auxiliar2(parejas[etiqueta_extraida]);
              pila_operaciones.pop();
              BigInt<Base> auxiliar3 = auxiliar.OperacionOR(auxiliar2);
              pila_operaciones.push(etiqueta);
              parejas[etiqueta] = auxiliar3;
              break;
            }
            default: {
              pila_operaciones.push(operaciones);
              break;
            }
          }
        }
        while (!pila_operaciones.empty()) {
          pila_operaciones.pop();
        }
      }
    }    
  }
  archivo_origen.close();
  std::ofstream archivo_destino;
  archivo_destino.open(nombre_archivo_destino);
  archivo_destino << "Base = " << Base << '\n';
  typename std::map<std::string, BigInt<Base>>::iterator iterador_map;
  BigInt<Base> auxiliar;
  for (iterador_map = parejas.begin(); iterador_map != parejas.end(); ++iterador_map) {
    archivo_destino << iterador_map->first << " = ";
    auxiliar = iterador_map->second;
    if (auxiliar.signo() == true) {
      archivo_destino << "-";
    }
    for (int iterador = 0; iterador < auxiliar.TamanioVector(); ++iterador) {
      int numero_extraido = auxiliar[iterador];
      char caracter_imprimir = auxiliar.ConvierteNumeroAChar(numero_extraido);
      archivo_destino << caracter_imprimir;
    }
    archivo_destino << '\n';
  }
  archivo_destino.close();
}

/// Función main
int main (int argc, char *argv[]) {
  Usage(argc, argv);
  std::string nombre_archivo_origen = argv[1];
  std::string nombre_archivo_destino = argv[2];
  std::ifstream archivo_origen;
  std::ofstream archivo_destino;
  archivo_origen.open(nombre_archivo_origen);
  std::string linea_extraida;
  getline(archivo_origen, linea_extraida);
  int indice_digitos = linea_extraida.find_first_of("0123456789");
  std::string base_str = linea_extraida.substr(indice_digitos, linea_extraida.size() - 1);
  int base = std::stoi(base_str);
  switch (base) {
    case 2: {
      BigInt<2> bigint;
      CalculadoraRPN(bigint, nombre_archivo_origen, nombre_archivo_destino);
      break;
    }
    case 8: {
      BigInt<8> bigint;
      CalculadoraRPN(bigint, nombre_archivo_origen, nombre_archivo_destino);
      break;
    }
    case 10: {
      BigInt<10> bigint;
      CalculadoraRPN(bigint, nombre_archivo_origen, nombre_archivo_destino);
      break;
    }
    case 16: {
      BigInt<16> bigint;
      CalculadoraRPN(bigint, nombre_archivo_origen, nombre_archivo_destino);
      break;
    }
    default: {
      exit(EXIT_FAILURE);
    }
  }
  return 0;
}