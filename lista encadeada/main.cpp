#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T data, Node* next = nullptr) : data(data), next(next) {}

    // Destrutor recursivo: deletar um nó deleta toda a sequência à frente
    ~Node() { delete next; }
};

template <typename T>
class LinkedList {
   private:
    Node<T>* head = nullptr;
    int _size;

   public:
    LinkedList() : head(nullptr), _size(0) {}

    ~LinkedList() { delete head; }

    void add(T value) {
        if (head == nullptr) {
            head = new Node<T>(value);
        } else {
            Node<T>* temp = head;
            while (temp->next != nullptr) temp = temp->next;
            temp->next = new Node<T>(value);
        }

        _size++;
    }

    void print() {
        if (!head) {
            std::cout << "Lista vazia" << std::endl;
            return;
        }
        Node<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void insert(T value, int index) {
        // Agora o índice é validado linearmente
        if (index < 0) index = 0;
        if (index > _size) index = _size;

        if (index == 0) {
            head = new Node<T>(value, head);
        } else {
            Node<T>* temp = head;
            for (int i = 0; i < index - 1; i++) temp = temp->next;
            temp->next = new Node<T>(value, temp->next);
        }
        _size++;
    }

    void remove(int index) {
        if (_size == 0 || index < 0 || index >= _size) return;

        Node<T>* toDelete = nullptr;

        if (index == 0) {
            toDelete = head;
            head = head->next;
            return;
        } else {
            Node<T>* temp = head;
            for (int i = 0; i < index - 1; i++) temp = temp->next;
            toDelete = temp->next;
            temp->next = toDelete->next;
            return;
        }
        Todelete->next = toDelete ? toDelete->next : nullptr;
        delete toDelete;
        _size--;
    }
}

    void erase() {
    delete head;
    head = nullptr;
    _size = 0;
}

T get(int index) {
    if (index < 0 || index >= _size || head == nullptr) {
        // Retorno padrão ou erro para índice inválido
        return T();
    }
    Node<T>* temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp->data;
}

int size() { return _size; }
}
;

int main() {
    LinkedList<int> list;

    for (int i = 0; i < 5; i++) {
        list.add(3 + i);
    }

    std::cout << "Lista inicial: ";
    list.print();

    std::cout << "Elemento no indice 2: " << list.get(2) << std::endl;

    list.insert(99, 2);
    std::cout << "Apos inserir 99 no indice 2: ";
    list.print();

    list.remove(0);
    std::cout << "Apos remover o indice 0: ";
    list.print();

    list.erase();
    std::cout << "Apos erase: ";
    list.print();

    return 0;
}