#include "tals.hpp"

template <typename T>
void memView(T ptr, int t_range = 10, bool print_hex = true)
{
    bool is_char = false;
    if (std::is_same_v<const char *, decltype(ptr)>)
        is_char = true;

    char seperator_char = ' ';

    std::cout << (void *)&ptr << " (" << typeid(*ptr).name() << ") : ";

    for (size_t i = 0; i < t_range; i++)
    {
        auto current_ptr = *(ptr + i);

        if (is_char)
        {
            if (current_ptr == '\n') // remove line break
            {
                std::cout << ' ';
            }
            else
            {
                std::cout << current_ptr << seperator_char;
            }
        }
        else
        {
            if (current_ptr < 16) // add leading zero
            {
                std::cout << 0;
            }
            if (print_hex)
            {
                std::cout << std::hex;
            }
            std::cout << current_ptr << std::dec << seperator_char;
        }
    }

    std::cout << "\n";
}

int main()
{
    std::cout << std::boolalpha; ////

    const char *ch = "hello!";

    long long num_arr[] = {17, 12, 3, 4, 5, 6, 7};

    int num = 7;

    memView(&num_arr[0]);

    return 0;
}