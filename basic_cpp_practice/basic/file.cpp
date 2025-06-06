#include<iostream>
#include<string>

consteval int square(int s)
{
    return s*s;
}

constexpr int d = square(10);

int main(){
    std::string country = "";
    std::cout << "Execution Succesful"<< std::endl;
    std::cout << "Compile time evaluated expression is \t" << d << std::endl;
    
    std::cout << "Where do you live?"<<std::endl;
    std::cin >> country;
    std::cout << "I've heard great things about " << country << "." << "I'd like to go sometime" << std::endl;
    

    return 0;
}