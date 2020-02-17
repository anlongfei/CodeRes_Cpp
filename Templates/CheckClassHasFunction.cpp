#include <iostream>

template <typename T>
class HasFunc1 {
    template <typename C>
    static int8_t test(decltype(std::declval<C>().Func1(nullptr))*);
    
    template <typename C>                                                                                                                                     
    static int16_t test(...);
 
public:
    static constexpr bool value = (sizeof(test<T>(nullptr)) == sizeof(int8_t));
};

template <typename T>
class HasFunc2 {
    template <typename C>
    static int8_t test(decltype(std::declval<C>().Func2(nullptr))*);
    
    template <typename C>
    static int16_t test(...);
 
public:
    static constexpr bool value = (sizeof(test<T>(nullptr)) == sizeof(int8_t));
};


template <typename T,
          std::enable_if_t<!HasFunc1<std::decay_t<T>>::value, int> = 0,
          std::enable_if_t<!HasFunc2<std::decay_t<T>>::value, int> = 0>
inline auto TestFunc(T&& t) {
  std::cout << "no no" << std::endl;
}
 
template <typename T,
          std::enable_if_t<!HasFunc1<std::decay_t<T>>::value, int> = 0,
          std::enable_if_t<HasFunc2<std::decay_t<T>>::value, int> = 0>
inline auto TestFunc(T&& t) {
  std::cout << "yes no" << std::endl;
}

template <typename T,
          std::enable_if_t<HasFunc1<std::decay_t<T>>::value, int> = 0,
          std::enable_if_t<HasFunc2<std::decay_t<T>>::value, int> = 0>
inline auto TestFunc(T&& t) {
  std::cout << "yes yes" << std::endl;
}

template <typename T,
          std::enable_if_t<HasFunc1<std::decay_t<T>>::value, int> = 0,
          std::enable_if_t<!HasFunc2<std::decay_t<T>>::value, int> = 0>
inline auto TestFunc(T&& t) {
  std::cout << "no yes" << std::endl;
}

class Test1 {
  public:
    void Func2(int* i) {
      std::cout << "Test1::Func2" << std::endl;
    }
};
class Test2 {
  public:
    void Func1(std::shared_ptr<int> i) {
      std::cout << "test2::Func1" << std::endl;
    }
};

class Test3 {
};

class Test4 {
  public:
    void Func1(std::shared_ptr<int> i) {
      std::cout << "test4::Func1" << std::endl;
    }
    void Func2(int* i) {
      std::cout << "Test4::Func2" << std::endl;
    }
};

int main () {
  Test1 t1;
  Test2 t2;
  Test3 t3;
  Test4 t4;

  std::cout << "t1" << std::endl;
  TestFunc(t1);
  std::cout << "t2" << std::endl;
  TestFunc(t2);
  std::cout << "t3" << std::endl;
  TestFunc(t3);
  std::cout << "t4" << std::endl;
  TestFunc(t4);
  return 0;
}

// g++  CheckClassHasFunction.cpp -std=c++17

