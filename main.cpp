#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <array>
#include <algorithm>
#include <fstream>


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


int parsingString(const std::string &line, T1 &a) 
{
    std::vector<std::string> v = split(line, '\t');
    if (v.size() != 3) return 1;

    std::vector<std::string> v2 = split(v.at(0), '.');
    if (v2.size() != 4) return 2;

    int i = 0;
    for (auto el = v2.cbegin(); el != v2.end(); ++el, ++i) {
        try {
            a[i] = std::stoi(*el);
        }
        catch (const std::exception &e) {
            return 3;
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
    std::fstream fs;
    fs.open("ip_filter/ip_filter.tsv", std::fstream::in);
    if (fs.is_open()) {
        std::cout << "file open" << std::endl;
        while (!fs.eof()) {
            std::string line;
            std::getline(fs, line);
            T1 ar;
            if (parsingString(line, ar) == 0) 
                mas.push_back(ar);
            else
                std::cout << "Ошибка ввода строки" << std::endl;            
        }
    }
    else 
        std::cout << "file not open" << std::endl;
    fs.close();
}


inline void printIP(const T1 &ip) 
{
    std::cout << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << std::endl;
}


int main(int argc, char const *argv[])
{
    bool flConsole {false};
    std::deque<T1> ipMas;

    if (flConsole)  inputConsole(ipMas);        // Ввод данных с консоли
    else inputFile(ipMas);                      // Ввод данных из файла

    // std::cout << "Количество элементов в массиве:" << ipMas.size() << std::endl;

    // 1. reverse lexicographically sort
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


    // 2. список адресов, первый байт которых равен 1
    std::for_each(ipMas.begin(), ipMas.end(), [](T1 a)
    {
        if (a.at(0) == 1) 
            printIP(a);
    }
    );

    // 3. список адресов, первый байт которых равен 46, а второй 70
    std::for_each(ipMas.begin(), ipMas.end(), [](T1 a)
    {
        if ((a.at(0) == 46) && (a.at(1) == 70))
            printIP(a);
    }
    );

    // 4. список адресов, любой байт которых равен 46
    std::for_each(ipMas.begin(), ipMas.end(), [](T1 a)
    {
        for (auto it : a)
            if (it == 46) {
                printIP(a);
                break;
            }
    }
    );

    return 0;
}