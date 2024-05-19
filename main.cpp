#include <iostream>
#include <vector>
#include <list>
#include <type_traits>

//-------------------------------------------------------------------------------------
int index_of_value(int value, std::vector<int> v, int index = 0) {
  // 2 Condiciones Base
  if (index >= v.size()) return -1;
  if (value == v[index]) return index;
  // Condicion Recursiva
  return index_of_value(value, v, ++index);
}

void ejemplo_buscar_dato () {
  std::vector v = {1, 21, 33, 45, 67};
  
  auto indice = index_of_value(33, v);
  std::cout << indice << std::endl; // 2
  indice = index_of_value(1, v);
  std::cout << indice << std::endl; // 0
  indice = index_of_value(66, v);
  std::cout << indice << std::endl; // -1
}

//-------------------------------------------------------------------------------------
struct empty_type {};

template<typename T, typename U, typename ...Pack>
struct type_pos_ {
  static constexpr int value = 1 + type_pos_<T, Pack...>::value;
};

template<typename T, typename ...Pack> //
struct type_pos_<T, T, Pack...> {
  static constexpr int value = 0;
};

template<typename T> //
struct type_pos_<T, empty_type> {
  static constexpr int value = 0;
};

template<typename T, typename ...Pack>
struct type_pos_rec {
  static constexpr int value = type_pos_<T, Pack..., empty_type>::value;
};

template <typename ...Pack, typename T>
int index_of_rec(T) {
  auto pos = type_pos_rec<T, Pack...>::value;
  return pos >= sizeof...(Pack)? -1: pos;
}

void ejemplo_index_of_rec() {
  // Ejemplo 1
  char var1{};
  std::cout << index_of_rec<int, char>(var1) << std::endl;
  // Ejemplo 2
  std::vector<int> var3;
  std::cout << index_of_rec<int, char, std::vector<int>, std::list<double>>(var3) << std::endl;
  // Ejemplo 3
  std::string var2;
  std::cout << index_of_rec<int, char, double, float, std::string>(var2) << std::endl;
  // Ejemplo 4
  std::vector<double> var4;
  std::cout << index_of_rec<int, char, std::vector<int>, std::list<double>>(var4) << std::endl; // El resultado seria: -1
}
//-------------------------------------------------------------------------------------
template<typename T>
auto multiplication(T a, T b) {return a*b;}

template<typename ...Pack>
auto sumar(Pack...params) {
  return ( multiplication(params) + ...);
}

//-------------------------------------------------------------------------------------
template <typename ...Pack, typename T>
constexpr int index_of(T) {
  int index = 0;
  auto increase_index = [&index] { ++index; return false; };
  bool found = ( (std::is_same_v<T, Pack> || increase_index()) || ...);
  return found ? index: -1;
}

void ejemplo_index_of() {
  // Ejemplo 1
  char var1{};
  std::cout << index_of<int, char>(var1) << std::endl;
  // Ejemplo 2
  std::vector<int> var3;
  std::cout << index_of<int, char, std::vector<int>, std::list<double>>(var3) << std::endl;
  // Ejemplo 3
  std::string var2;
  std::cout << index_of<int, char, double, float, std::string>(var2) << std::endl;
  // Ejemplo 4
  std::vector<double> var4;
  std::cout << index_of<int, char, std::vector<int>, std::list<double>>(var4) << std::endl; // El resultado seria: -1
}

//-------------------------------------------------------------------------------------
// Este ejemplo muestra una de las characteristics del operador OR que evalúa los predicados hasta que encuentre
// uno verdadero (true).
// En el ejemplo el predicado verdadero aparece en el segundo predicado por tanto el valor del index = 1 y result = true
// Si todos los predicados fueran falsos:
// Ejemplo: bool result = (++index, false) || (++index, false) || (++index, false) || (++index, false);
// En este ejemplo todos los predicados se evaluarían, por tanto, index = 4 y result = false.
// Esta técnica se usa en la última solución de index_of.
void ejemplo_uso_or() {
  int index = 0;
  bool result = (++index, false) || true || (++index, false) || (++index, false);
  std::cout << std::boolalpha << index;
}

//-------------------------------------------------------------------------------------

int main() {
//  ejemplo_buscar_dato();
//  ejemplo_index_of_rec();
  ejemplo_index_of();
//  ejemplo_uso_or();
  return 0;
}
