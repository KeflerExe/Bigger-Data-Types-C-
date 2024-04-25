/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: AyEDA
/// Curso: 2º
/// Práctica 2: Representación de números binarios grandes
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 27/02/2023
/// Archivo: bigint_main.cc

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stack>
#include <sstream>

#include "bigint.h"

// Función encargada de operar como una calculadora en Notación Polaca Inversa
template <size_t Base = 2>
void CalculadoraRPN(int linea_lectura_actual, std::map<std::string, BigInt<2>>& parejas, std::string& nombre_archivo_origen, std::string& nombre_archivo_destino) {
  std::stack<std::string> pila_operaciones;
  std::string operaciones;
  std::ifstream archivo_origen;
  std::string linea_extraida;
  archivo_origen.open(nombre_archivo_origen); 
  for (int iterador = 0; iterador < linea_lectura_actual; ++iterador) {
    getline(archivo_origen, linea_extraida);
  }
  while (getline(archivo_origen, linea_extraida)) {
    std::string etiqueta = linea_extraida.substr(0, linea_extraida.find_first_of('?'));  
    if (etiqueta[etiqueta.size() - 1] == ' ') {
      etiqueta.erase(etiqueta.size() - 1, 1);
    }   
    linea_extraida.erase(0, linea_extraida.find_first_of('?') + 1);
    if (linea_extraida[0] == ' ') {
      linea_extraida.erase(linea_extraida.begin());     
    }
    std::stringstream sstring(linea_extraida);
    while (getline(sstring, operaciones, ' ')) {
      char caracter_extraido = operaciones[0];
      switch (caracter_extraido) {
        case '+': {
          std::string etiqueta_extraida = pila_operaciones.top();
          BigInt<2> auxiliar(parejas[etiqueta_extraida]);
          pila_operaciones.pop();
          etiqueta_extraida = pila_operaciones.top();
          BigInt<2> auxiliar2(parejas[etiqueta_extraida]);
          pila_operaciones.pop();
          BigInt<2> auxiliar3 = auxiliar + auxiliar2;
          auxiliar3.EliminaCerosIzquierda();
          pila_operaciones.push(etiqueta);
          parejas[etiqueta] = auxiliar3;
          break;
        }
        case '-': {
          std::string etiqueta_extraida = pila_operaciones.top();
          BigInt<2> auxiliar(parejas[etiqueta_extraida]);
          pila_operaciones.pop();
          etiqueta_extraida = pila_operaciones.top();
          BigInt<2> auxiliar2(parejas[etiqueta_extraida]);
          pila_operaciones.pop();
          BigInt<2> auxiliar3 = auxiliar - auxiliar2;
          pila_operaciones.push(etiqueta);
          parejas[etiqueta] = auxiliar3;
          break;
        }
        case '*': {
          std::string etiqueta_extraida = pila_operaciones.top();
          BigInt<2> auxiliar(parejas[etiqueta_extraida]);
          pila_operaciones.pop();
          etiqueta_extraida = pila_operaciones.top();
          BigInt<2> auxiliar2(parejas[etiqueta_extraida]);
          pila_operaciones.pop();
          BigInt<2> auxiliar3 = auxiliar * auxiliar2;
          pila_operaciones.push(etiqueta);
          parejas[etiqueta] = auxiliar3;
          break;
        }
        case '/': {
          std::string etiqueta_extraida = pila_operaciones.top();
          BigInt<2> auxiliar(parejas[etiqueta_extraida]);
          pila_operaciones.pop();
          etiqueta_extraida = pila_operaciones.top();
          BigInt<2> auxiliar2(parejas[etiqueta_extraida]);
          pila_operaciones.pop();
          BigInt<2> auxiliar3 = auxiliar / auxiliar2;
          pila_operaciones.push(etiqueta);
          parejas[etiqueta] = auxiliar3;
          break;
        }
        case '%': {
          std::string etiqueta_extraida = pila_operaciones.top();
          BigInt<2> auxiliar(parejas[etiqueta_extraida]);
          pila_operaciones.pop();
          etiqueta_extraida = pila_operaciones.top();
          BigInt<2> auxiliar2(parejas[etiqueta_extraida]);
          pila_operaciones.pop();
          BigInt<2> auxiliar3 = auxiliar % auxiliar2;
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
  }
  while (!pila_operaciones.empty()) {
    pila_operaciones.pop();
  }
}

// Función encargada de extraer los datos de el archivo y pasarlos a la calculadora para operarlos
template <size_t Base>
void ExtractorDeDatos(BigInt<Base>& auxiliar, int linea_lectura_actual, std::string& nombre_archivo_origen, std::string& nombre_archivo_destino) {
  std::string linea_extraida;
  std::ifstream archivo_origen;
  archivo_origen.open(nombre_archivo_origen);
  int posicion_etiqueta{0};
  getline(archivo_origen, linea_extraida);
  std::map<std::string, BigInt<2>> parejas;
  while (getline(archivo_origen, linea_extraida)) {
    if (linea_extraida.find("?") != std::string::npos) {
      break;
    }
    if (linea_extraida[linea_extraida.find_first_of('=') + 1] == ' ') {
      linea_extraida.erase(linea_extraida.find_first_of('=') + 1, 1);
    }
    std::string etiqueta = linea_extraida.substr(0, linea_extraida.find_first_of('='));    
    if (etiqueta[etiqueta.size() - 1] == ' ') {
      etiqueta.erase(etiqueta.size() - 1, 1);
    } 
    std::string valor_bigint = linea_extraida.substr(linea_extraida.find_first_of('=') + 1, linea_extraida.size() - 1);
    BigInt<Base> auxiliar(valor_bigint);
    BigInt<2> auxiliar_base2 = auxiliar;
    if (valor_bigint[0] == '-') {
      auxiliar_base2 = auxiliar_base2.CalculaElC2();
    }
    parejas[etiqueta] = auxiliar_base2;
    linea_lectura_actual++;
  }
  CalculadoraRPN(linea_lectura_actual, parejas, nombre_archivo_origen, nombre_archivo_destino);
  archivo_origen.close();
  std::ofstream archivo_destino;
  archivo_destino.open(nombre_archivo_destino);
  archivo_destino << "Base = " << Base << '\n';
  typename std::map<std::string, BigInt<2>>::iterator iterador_map;
  BigInt<2> auxiliar_base2;
  BigInt<Base> auxiliar_imprimir;
  for (iterador_map = parejas.begin(); iterador_map != parejas.end(); ++iterador_map) {
    archivo_destino << iterador_map->first << " = ";
    auxiliar_base2 = iterador_map->second;
    auxiliar_imprimir = auxiliar_base2;
    for (int iterador = 0; iterador < auxiliar_imprimir.TamanioVector(); ++iterador) {
      int digito_imprimir = auxiliar_imprimir[iterador];
      char caracter_imprimir;
      if ((digito_imprimir <= 9) && (digito_imprimir >= 0)) {
        caracter_imprimir = '0' + digito_imprimir;
        archivo_destino << caracter_imprimir;
      } else {
        caracter_imprimir = digito_imprimir - 10 + 'A';
        archivo_destino << caracter_imprimir;
      }
    }
    archivo_destino << '\n';
  }
  BigInt<2> auxiliar_bytes = ("0111011011");
  size_t numero_bytes = auxiliar_bytes.ObtieneLaCantidadDeBytes();
  archivo_destino << numero_bytes;
  archivo_destino.close();
}

/// Función main
int main (int argc, char *argv[]) {
  Usage(argc, argv);
  std::string nombre_archivo_origen = argv[1];
  std::string nombre_archivo_destino = argv[2];
  std::ifstream archivo_origen;
  std::ofstream archivo_destino;
  int linea_lectura_actual{0};
  archivo_origen.open(nombre_archivo_origen);
  std::string linea_extraida;
  getline(archivo_origen, linea_extraida);
  linea_lectura_actual += 1;
  int indice_digitos = linea_extraida.find_first_of("0123456789");
  std::string base_str = linea_extraida.substr(indice_digitos, linea_extraida.size() - 1);
  int base = std::stoi(base_str);
  switch (base) {
    case 2: {
      BigInt<2> auxiliar;
      ExtractorDeDatos(auxiliar, linea_lectura_actual, nombre_archivo_origen, nombre_archivo_destino);
      break;
    }
    case 8: {
      BigInt<8> auxiliar;
      ExtractorDeDatos(auxiliar, linea_lectura_actual, nombre_archivo_origen, nombre_archivo_destino);
      break;
    }
    case 10: {
      BigInt<10> auxiliar;
      ExtractorDeDatos(auxiliar, linea_lectura_actual, nombre_archivo_origen, nombre_archivo_destino);
      break;
    }
    case 16: {
      BigInt<16> auxiliar;
      ExtractorDeDatos(auxiliar, linea_lectura_actual, nombre_archivo_origen, nombre_archivo_destino);
      break;
    }
    default: {
      exit(EXIT_FAILURE);
    }
  }
  return 0;
}