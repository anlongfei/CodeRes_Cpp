#include <vector>                                                                                                                                             
#include <iostream>
#include <typeinfo>
 
template<typename T>
class Lazy {
    public:
        Lazy() :ptr(nullptr) {}
        T* ptr;
};
 
template<typename T>
class Try {
    public:
        Try() : t(0) { } 
        T t;
};
 
template< template<typename> typename Alloc = std::allocator,
    typename... Ts>    
inline auto collectAll(std::vector<Lazy<Ts>, Alloc<Lazy<Ts>>>&&... inputs)
    -> Lazy<std::tuple<std::vector<Try<Ts>, Alloc<Try<Ts>>>...>> {    
    return Lazy<std::tuple<std::vector<Try<Ts>, Alloc<Try<Ts>>>...>>();
}
 
int main() {
    std::vector<Lazy<float>> fvl;
    std::vector<Lazy<int>> ivl;
    Lazy<float> f;
    Lazy<int> i;
 
    fvl.push_back(f);
    ivl.push_back(i);
    
    auto ret = collectAll(std::move(ivl), std::move(fvl));
    std::cout << typeid(ret).name() << std::endl;
    return 0;
}

// g++ -std=c++17 template_template.cpp
