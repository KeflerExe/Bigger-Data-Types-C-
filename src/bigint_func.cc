/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: AyEDA
/// Curso: 2º
/// Práctica 2: Representación de números binarios grandes
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 27/02/2023
/// Archivo: bigint_func.cc

#include <iostream>
#include <string>

#include "bigint.h"

// Comprueba que los argumentos introducidos por línea de comandos sean los 
// correctos, además de proporcionar ayuda en caso de que el usuario no sepa como se han de introducir los argumentos.
void Usage(int argc, char *argv[]) {
  if (argc != 3) {
    std::string parametro_introducido = argv[1];
    if (parametro_introducido == "--help") {
      std::cout << "--BigInt" << std::endl;
      std::cout << "Modo de uso: ./bigint_main fichero_entrada fichero_salida" << std::endl;
      std::cout << "fichero_entrada: Fichero de texto donde se definen las operaciones." << std::endl;
      std::cout << "fichero_salida: Fichero de texto donde se escribe el resultado." << std::endl;
      exit(EXIT_SUCCESS);
    } else {
      std::cout << "--BigInt " << std::endl;
      std::cout << "Modo de uso: ./bigint_main fichero_entrada fichero_salida" << std::endl << "Pruebe ./bigint_main --help para más información" << std::endl;
      exit(EXIT_FAILURE);
    }
  }   
}