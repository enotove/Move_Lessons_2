#include <iostream>
#include <string>
#include <vector>

class Big_integer
{
public:
    Big_integer(std::string value)
    {
        std::cout << value.size() << std::endl;
        this->size_class = value.size();
        if (value[0] == '-')
        {
            sign = 1;
        }
        int ending = (value.size() - sign) % Base;
        if ((value.size() - sign) >= Base)
        {
           
            for (auto i = value.size() - Base; i >= 0+sign; i -= Base)
            {
                chunks.push_back(value.substr(i, Base));
            }
        }
        if (ending != 0)
        {
            chunks.push_back(value.substr(0 + sign, ending));
        }
        
       
    }
    Big_integer(std::vector<std::string> container)
    {
        chunks = std::move(container);
    }
    void Print()
    {
        for (auto it : chunks)
        {
            std::cout << it << " ";
        }
    }
    
    Big_integer(const Big_integer& other) : Big_integer(other.chunks) {}
    Big_integer(Big_integer&& other) noexcept : chunks(std::exchange(other.chunks, nullptr)) {}
    Big_integer& operator=(const Big_integer& other) // оператор копирующего присваивания
    {
        return *this = Big_integer(other);
    }
   
    Big_integer& operator = (Big_integer&& other) noexcept
    {
        std::swap(chunks, other.chunks);
        return *this;
    }
    Big_integer operator + (std::string otherValue)
    {
        std::vector<std::string> tmp;
        int pref = 0;
        int sign_other;
        size_t counter;
        
        if (otherValue[0] == '-')
        {
            sign_other = 1;
        }
        int ending = (otherValue.size() - sign_other) % Base;
        for (auto i = otherValue.size() - Base; i >= 0 + sign_other; i -= Base)
        {
            if (counter > chunks.size())
            {
                break;
            }
            int result = std::stoi(chunks[counter]) + std::stoi(otherValue.substr(i, Base)) + pref;
            std::string s_result = std::to_string(result);
            if (s_result.size() == 3)
            {
                pref = 1;
                s_result.erase(0, 1);
            }
            else
            {
                pref = 0;
            }
            tmp.push_back(s_result);
            counter++;
        }
        if (ending != 0)
        {
            if (counter > chunks.size())
            {
                tmp.push_back(otherValue.substr(0 + sign_other, ending));
            }
            else
            {
                int result = std::stoi(chunks[counter]) + std::stoi(otherValue.substr(0 + sign_other, ending)) + pref;
                std::string s_result = std::to_string(result);
                if (s_result.size() == 3)
                {
                    pref = 1;
                    s_result.erase(0, 1);
                }
                else
                {
                    pref = 0;
                }
                tmp.push_back(s_result);
                counter++;
                if (pref == 1)
                {
                    if (counter >= chunks.size())
                    {
                        tmp.push_back(std::to_string(pref));
                    }
                    else
                    {
                        tmp.push_back(std::to_string(std::stoi(chunks[counter]) + pref));
                    }
                }
                    
            }
                
        }
        
        
        
        return Big_integer(tmp);
    }
    Big_integer operator +(Big_integer& other)
    {
        std::vector<std::string> tmp;
        int counter;
        for (int i = 0; i < other.chunks.size(); i++)
        {
            if (counter > chunks.size())
            {
                break;
            }
            int i_result = std::stoi(other.chunks[i]) + std::stoi(chunks[i]);

        }
    }
    
private:
    std::vector<std::string> chunks;
    size_t size_class = 0;
    int sign = 0;
    static const int Base = 2;
};

int main()
{
    Big_integer i = Big_integer("32528581381");
    i.Print();
}
