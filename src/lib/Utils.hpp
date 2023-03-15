#ifndef __UTILS_
#define __UTILS_

#include <functional>
#include <iostream>
#include <vector>

class Utils
{
  public:
    static std::string to_lower(std::string s)
    {
        std::string result;
        for (auto it = s.begin(); it != s.end(); it++) {
            result.push_back(std::tolower(*it));
        }
        return result;
    }

    static void clear_screen()
    {
        std::cout << "\033[2J\033[1;1H";
    }

    template <class T>
    static std::vector<T> filter_vector(const std::vector<T>& vec,
                                        std::function<bool(const T&)> predicate)
    {
        std::vector<T> filtered;
        for (const T& x : vec) {
            if (predicate(x)) {
                filtered.push_back(x);
            }
        }
        return filtered;
    }

    template <class T>
    static T max(const std::vector<T>& vec)
    {
        if (vec.empty()) {
            throw "Vector must have at least one element";
        }
        T m = vec[0];
        for (const T& x : vec) {
            if (x > m) {
                m = x;
            }
        }
        return m;
    }

    template <class T, class Category>
    static T maxBy(const std::vector<T>& vec, Category&& category)
    {
        if (vec.empty()) {
            throw "Vector must have at least one element";
        }
        T m = vec[0];
        for (auto& x : vec) {
            if (category(x) > category(m)) {
                m = x;
            }
        }
        return m;
    }

    template <class Container, class Action>
    static void forEach(Container&& container, Action&& action)
    {
        for (auto&& x : container) {
            action(x);
        }
    }

    template <class Type>
    static void input_validate(Type&& var, int lower, int upper)
    {
        std::cout << "> ";
        std::string temp;
        while (!(std::cin >> var) || var < lower || var > upper) {
            std::cout << "Masukan tidak valid!\n";
            std::cout << "> ";
            std::cin.clear();
            std::getline(std::cin, temp);
        }
    }

    static void splash_screen()
    {
        std::cout << "\n";
        // std::cout << " _    _   _____   _       _____   _____   __  __   _____     _____   _____     _____   _____   _____   __  __    ___    _____   _   _    ___    _   _     _   __   ___    _____   _____   _   _  " << std::endl;
        // std::cout << "| |  | | |  ___| | |     /  __ \\ |  _  | |  \\/  | |  ___|   |_   _| |  _  |   | ___ \\ |  ___| | ___ \\ |  \\/  |  / _ \\  |_   _| | \\ | |  / _ \\  | \\ | |   | | / /  / _ \\  | ___ \\ |_   _| | | | | " << std::endl;
        // std::cout << "| |  | | | |__   | |     | /  \\/ | | | | | .  . | | |__       | |   | | | |   | |_/ / | |__   | |_/ / | .  . | / /_\\ \\   | |   |  \\| | / /_\\ \\ |  \\| |   | |/ /  / /_\\ \\ | |_/ /   | |   | | | | " << std::endl;
        // std::cout << "| |/\\| | |  __|  | |     | |     | | | | | |\\/| | |  __|      | |   | | | |   |  __/  |  __|  |    /  | |\\/| | |  _  |   | |   | . ` | |  _  | | . ` |   |    \\  |  _  | |    /    | |   | | | | " << std::endl;
        // std::cout << "\\  /\\  / | |___  | |____ | \\__/\\ \\ \\_/ / | |  | | | |___      | |   \\ \\_/ /   | |     | |___  | |\\ \\  | |  | | | | | |  _| |_  | |\\  | | | | | | |\\  |   | |\\  \\ | | | | | |\\ \\    | |   | |_| | " << std::endl;
        // std::cout << " \\/  \\/  \\____/  \\_____/  \\____/  \\___/  \\_|  |_/ \\____/      \\_/    \\___/    \\_|     \\____/  \\_| \\_| \\_|  |_/ \\_| |_/  \\___/  \\_| \\_/ \\_| |_/ \\_| \\_/   \\_| \\_/ \\_| |_/ \\_| \\_|   \\_/    \\___/  " << std::endl;
        std::cout << "\e[0;95mWelcome To Permainan Kartu Kerajaan Permen\e[0m" << std::endl;
        std::cout << "\n";
    }
};

#endif // !__UTILS_