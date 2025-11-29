#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

class numfilterbuf : public std::streambuf {
private:
	std::istream *in;
	std::ostream *out;
	
	int cur; //последнее считанное значение, используется в underflow()
protected:

	/* функции записи в поток: */
	
    virtual int overflow(int c) override {
        if (c == traits_type::eof()) {
            return traits_type::eof();
        }
        
        if (std::isdigit(c) || std::isspace(c)) {
            out->put(static_cast<char>(c));
        }
        return c;
    }
	
	/* функции чтения из потока: */
	
	//реализация по-умолчанию инкрементирует позицию указателя в буфере и вызывает segmentation fault
	virtual int uflow() override {
		int uflower = underflow();
        if (uflower != traits_type::eof()){
            cur = traits_type::eof();
        }

        return uflower;
	}
	
	virtual int underflow() override {
		if (cur == traits_type::eof()) {
            int check;
            while ((check = in->get()) != traits_type::eof()){
                if (std::isdigit(check) || std::isspace(check)) {
                    cur = check;
                    break;
                }
            }
        }
        return cur;
	}
public:
	numfilterbuf(std::istream &_in, std::ostream &_out)
		: in(&_in), out(&_out), cur(traits_type::eof())
	{}
};

int main(int argc, char **argv){
	const char str1[] = "In 4 bytes contains 32 bits";
	const char str2[] = "Unix time starts from Jan 1, 1970";
	std::istringstream str(str1);
	
	numfilterbuf buf(str, std::cout); // читать из stringstream, выводить в консоль
	std::iostream numfilter(&buf); // таким образом обходимся без реализации своего наследника iostream
	
	std::string val;
	std::getline(numfilter, val);
	numfilter.clear(); // сбросить невалидное состояние после EOF в процессе чтения из stringstream
	
	std::cout << "Original: '" << str1 << "'" << std::endl;
	std::cout << "Read from numfilter: '" << val << "'" << std::endl;
	
	std::cout << "Original: '" << str2 << "'" << std::endl;
	std::cout << "Written to numfilter: '";
	numfilter << str2;
	std::cout << "'" << std::endl;
	
	return 0;
}
