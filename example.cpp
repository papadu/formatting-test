#include "example.hpp"
#include <iostream>
void Example::set_value( int v ) { value=v;}
int Example::get_value( ) { return value; }
void Example::print_value() {std::cout<<"Value: "<<value<<std::endl; }
int main ( ) {Example e;e.set_value(42);
e.print_value();return 0; }
