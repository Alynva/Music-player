/*Biblioteca criada para o uso de diferentes tipos abstratos de dados dinâmicos,
  partindo do conceito de listas encadeadas para posterior reuso em projetos.
   
  Classes implementadas e testadas até a última revisão:
    Node
    Stack
   
  Classes ainda não testadas:
    Queue
     
  Classes a implementar:
    LinkedList
    BinaryTree
    BalancedTree
   
  Gabriel Alves,
  São Carlos - SP, 2017.
*/
 
#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
 
template<class T>
class Node {
    public:
        T value;
        Node* next;
        Node* previous;
        Node():next(this), previous(this) {};
        Node(const T val): value(val), next(this), previous(next) {};
        ~Node(){next = nullptr; previous = nullptr;}
};
 
template<class T>
class Stack {
    protected:
        Node<T> header;
        int size;
 
    public:
        Stack():size(0) {};
        ~Stack() { this->clear(); };
        bool isEmpty() const {bool check = (header.next == header) ? true : false; return check;};
 
        void push(const T, bool&);
        bool pop(T&);
        void clear();
        int getSize() const;
        Node<T>* peek() const;
};
 
template<class T>
inline void Stack<T>::push(const T element, bool& check){
    Node<T> *aux = new Node<T>;
    aux->value = element;
    aux->next = &header;
    aux->previous = header.previous;
    header.previous->next = aux;
    header.previous = aux;
    size++;
    check = true;
}
 
template<class T>
inline bool Stack<T>::pop(T& element) {
    if (!this->isEmpty()){
        element = header.previous->value;
        Node<T> *aux = header.previous;
        header.previous = aux->previous;
        aux->previous = &header;
        delete(aux);
        size--;
        return true;
    }
    return false;
}
 
template<class T>
inline void Stack<T>::clear() {
    while (!isEmpty()) {
        T temp;
        this->pop(temp);
    }
}
 
template<class T>
inline int Stack<T>::getSize() const {
    return size;
}
 
template<class T>
Node<T>* Stack<T>::peek() const {
    return header.next;
}
 
template<class T>
class Queue{
private:
    Node<T> header;
    int size;
 
public:
    Queue():size(0){};
    ~Queue(){this->clear();};
 
    void enqueue(const T, bool&);
    bool dequeue(T&);
    void clear();
    bool isEmpty() const {bool check = (header.next == &header) ? true : false; return check;};
    int getSize() const {return size;};
    Node<T>* getFront() const {return header.next;};
    Node<T>* getBack() const {return header.previous;};
};
 
template<class T>
void Queue<T>::enqueue(const T element, bool& check){
    check = false;
    Node<T> *aux = new Node<T>;
    aux->value = element;
    aux->next = &header;
    aux->previous = header.previous;
    header.previous->next = aux;
    header.previous = aux;
    size++;
    check = true;
}
 
 
template<class T>
bool Queue<T>::dequeue(T& element){
    if(!this->isEmpty()){
        element = header.next->value;
        Node<T>* aux = header.next;
        header.next = aux->next;
        aux->next->previous = &header;
        delete(aux);
        size--;
        return true;
    }
    return false;
}
 
template<class T>
void Queue<T>::clear(){
    T temp;
    while(!this->dequeue(temp));
}
 
template<class T>
class LinkedList{};
 
class BinaryTree{};
 
class BalancedTree{};
 
#endif
