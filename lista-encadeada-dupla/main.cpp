#include <iostream>

struct node {
  node* prev = nullptr;
  int data;
  node* next = nullptr;
  node(int value) : data(value) {}
};
class list {
 private:
  node* head = nullptr;  // Initialize to nullptr

 public:
  list() = default;

  ~list() { erase(); }

  void add(int value) {
    if (head == nullptr) {
      head = new node(value);
      return;
    }
    node* temp = head;
    while (temp->next != nullptr) {
      temp = temp->next;
    }
    node* newNode = new node(value);
    temp->next = newNode;
    newNode->prev = temp;
  }

  void remove(int index) {
    if (!head) return;

    node* temp = head;
    for (int i = 0; i < index && temp->next != nullptr; ++i) {
      temp = temp->next;
    }

    // 1. Update surrounding pointers
    if (temp->prev != nullptr) {
      temp->prev->next = temp->next;
    } else {
      // Removing the head
      head = temp->next;
    }

    if (temp->next != nullptr) {
      temp->next->prev = temp->prev;
    }

    delete temp;
  }

  int* get(int index) {
    node* temp = head;
    for (int i = 0; i < index; ++i) {
      if (temp == nullptr || temp->next == nullptr) return nullptr;
      temp = temp->next;
    }
    return (temp) ? &temp->data : nullptr;
  }

  void erase() {
    node* current = head;
    while (current != nullptr) {
      node* nextNode = current->next;
      delete current;
      current = nextNode;
    }
    head = nullptr;
  }
};
