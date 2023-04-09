#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <array>
#include <algorithm>


using T1 = std::array<int,4>;


std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


int parsingString(std::string line, T1 &ar) 
{
    std::vector<std::string> v = split(line, '\t');
    if (v.size() != 3) return 1;

    std::vector<std::string> v2 = split(v.at(0), '.');
    if (v2.size() != 4) return 2;

    int i = 0;
    for (auto el = v2.cbegin(); el != v2.end(); ++el, ++i) {
        try {
            ar[i] = std::stoi(*el);
        }
        catch (const std::exception &e) {
            return 2;
        }        
    }

    return 0;
}


void inputConsole(std::deque<T1> &mas)
{
    std::string line;    
    while (std::getline(std::cin, line) && !line.empty()) {
        T1 ar;
        if (parsingString(line, ar) == 0) 
            mas.push_back(ar);
        else
            std::cout << "Ошибка ввода строки" << std::endl;
    }
}


void inputFile(std::deque<T1> &mas)
{

}


void printIP(T1 &ip) 
{
    std::cout << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << std::endl;
}


int main(int argc, char const *argv[])
{
    std::deque<T1> ipMas;
    // inputFile(ipMas);        // Ввод данных из файла
    inputConsole(ipMas);        // Ввод данных с консоли
    std::cout << "Количество элементов в массиве:" << ipMas.size() << std::endl;


    // TODO reverse lexicographically sort
    std::sort(ipMas.begin(), ipMas.end(), [](T1 b, T1 a)
    {
    for (auto it1 = a.cbegin(), it2 = b.cbegin(); it1 != a.end(); ++it1, ++it2)
    {
        if (*it1 > *it2) 
            return false;
        else if (*it1 < *it2) 
            return true;
    }
    return false;
    }
    );


    for(auto el: ipMas)
        printIP(el);


    

    std::cout << "Выход" << std::endl;

    return 0;
}