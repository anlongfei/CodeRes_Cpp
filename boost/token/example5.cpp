/// simple_example_5.cpp
#include<iostream>
#include<boost/token_iterator.hpp>
#include<string>

int main()
{
   using namespace std;
   using namespace boost;
   string s = "12252001";
   int offsets[] = {2,2,4};
   offset_separator f(offsets, offsets+3);
   typedef token_iterator_generator<offset_separator>::type Iter;
   Iter beg = make_token_iterator<string>(s.begin(),s.end(),f);
   Iter end = make_token_iterator<string>(s.end(),s.end(),f); 
   // The above statement could also have been what is below
   // Iter end;
   for(;beg!=end;++beg){
     cout << *beg << "\n";
   }

   return 0;
}
