#include "SleepSort.h"

#include <iostream>

unsigned intRepr(const Widget& w)
{
   return w.i;
}
unsigned intRepr(const std::string& s)
{
   if (s.empty()) return 0;
   return static_cast<unsigned>(s[0]);
}

Widget::Widget(unsigned i) : i(i)
{};


int main()
{
   std::vector<Widget> v;
   for (auto i : { 6,5,4,3,2,160,50,40,30,20,10 })
      v.emplace_back(i);

   auto sorted = sleepSort(v);
   for (auto w : sorted)
      std::cout << intRepr(w) << ", ";
   std::cout << std::endl;

   std::vector<int> v1{ 6,5,4,3,2,160,50,40,30,20,10 };
   auto sorted1 = sleepSort(v1);
   for (auto w : sorted1)
      std::cout << w << ", ";
   std::cout << std::endl;

   std::vector<std::string> v2{ "6","5","4","3","2","160","50","40","30","20","10" };
   auto sorted2 = sleepSort(v2);
   for (auto w : sorted2)
      std::cout << w << ", ";
   std::cout << std::endl;

   // std::vector<Widget2> v3(5);
   // auto sorted3 = sleepSort(v3); // the associated constraints are not satisfied
}
