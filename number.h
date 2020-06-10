#include "list.h"

class Number {
private:
    bool        negativeNum;
    int         length;
    List<short> num;        // main number
    short       char_to_short (char c);
    Number      addition      (const Number&);
    Number      subtraction   (const Number&, const Number&); //the first number should be greater
    Number      halfOf        (const Number&);
    Number      abs           (const Number&);

    Number      basicMult     (const Number&, const Number&);
    void        getLeftPart   (Number&, const Number&, int);
    void        getRightPart  (Number&, const Number&, int);
    void        addZeros      (Number&, int);
    Number      karatsMult    (const Number&, const Number&);

  public:
    Number ();
    Number (std::string &);
    Number (const char *);
    Number (const Number&);              //copy constructor
    Number (Number&&);                   //move constructor

    void    print      ();
    Number  operator+  (const Number&);
    Number  operator-  (const Number&);
    Number  operator*  (const Number&);
    Number  operator/  (const Number&);
    Number  operator++ (int);
    Number  operator-- (int);
    bool    operator>  (const Number&);
    bool    operator<  (const Number&);
    bool    operator>=  (const Number&);
    bool    operator== (const Number&) const;
    bool    operator!= (const Number&) const;
    Number& operator=  (const Number&);  //copy assignment
    Number& operator=  (Number&&);       //move assignment
    Number  abs        () const;

    ~Number();
};
