
class Number {
private:
    int length;
    short * num; // a main number
    short char_to_short(char c);
public:
    Number();
    Number(std::string& num_str);
    Number(const Number&);              //copy constructor
    Number(Number&&);                   //move constructor
    void print();
    Number operator+ (const Number&);
    Number operator* (const Number&);
    Number& operator= (const Number&);  //copy assignment
    Number& operator= (Number&&);       //move assignment

    ~Number();
};
