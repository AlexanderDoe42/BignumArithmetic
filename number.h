
class Number {
private:
    bool negativeNum;
    int length;
    short * num; // main number
    short char_to_short(char c);
    Number addition(const Number&);
    Number subtraction(const Number&, const Number&); //the first number should be greater

public:
    Number();
    Number(std::string& num_str);
    Number(const Number&);              //copy constructor
    Number(Number&&);                   //move constructor
    void print();
    Number operator+ (const Number&);
    Number operator- (const Number&);
    Number operator* (const Number&);
    bool operator> (const Number&);
    bool operator== (const Number&) const;
    Number& operator= (const Number&);  //copy assignment
    Number& operator= (Number&&);       //move assignment
    Number abs() const;

    ~Number();
};
