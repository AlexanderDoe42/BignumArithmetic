template <class T>
struct Node
{
    Node() : next_node(nullptr), previous_node(nullptr) {}
    T value;
    Node * next_node;
    Node * previous_node;
};

template <class T>
struct _iterator
{
    Node<T>* _node;

    _iterator() : _node(nullptr) {}
    _iterator(Node<T>* arg) : _node(arg) {}
    T& operator* ();
    bool operator!= (const _iterator&);
    _iterator operator++ (int);
    _iterator operator-- (int);
    _iterator& operator++ ();

};

template <class T>
class List
{
    int _size;
    Node<T> * first_node;
    Node<T> * last_node;
    Node<T> * end_node;  //concatenates the last and the first elements

public:
    typedef _iterator<T> iterator;

    List();
    List(const List<T>&);
    List(List<T>&&);
    void add(T);
    void add_front(T);
    void remove(const iterator&);
    int size();
    iterator begin() const;
    iterator end() const;    //past the last element
    iterator last() const;   //the actual last element
    List<T>& operator=  (const List<T>&);
    List<T>& operator=  (List<T>&&);
    void moveAssignment(List<T>&);

    ~List();
};

#include "list_impl.h"
