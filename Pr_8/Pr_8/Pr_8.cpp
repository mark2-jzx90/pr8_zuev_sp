// Pr_8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstring>
using namespace std;



struct Book {
    char title[60];
    char author[50];
    int year;
};

struct Node {
    Book data;
    Node* next;
    Node* prev;
};

struct List {
    Node* head = nullptr;
    Node* tail = nullptr;
};

void printBook(Book b) {
    cout << "Название: " << b.title << "Автор: " << b.author << "Год: " << b.year << endl;
}

void push_front(List* list, Book newBook) {
    Node* NewNode = new Node;
    NewNode->data = newBook;
    NewNode->next = list->head;
    NewNode->prev = nullptr;

    if (list->head != nullptr) {
        list->head->prev = NewNode;
    }
    else {
        list->tail = NewNode;
    }
    list->head = NewNode;
}

void push_back(List* list, Book newBook) {
    Node* NewNode = new Node;
    NewNode->data = newBook;
    NewNode->next = nullptr;
    NewNode->prev = list->tail;

    if (list->tail != nullptr) {
        list->tail->next = NewNode;
    }
    else {
        list->head = NewNode;
    }
    list->tail = NewNode;
}

void pop_front(List* list) {
    if (list->head == nullptr) {
        return;
    }

    Node* temp = list->head;
    list->head = list->head->next;
    if (list->head != nullptr) {
        list->head->prev = nullptr;
    }
    else {
        list->tail = nullptr;
    }
    delete temp;
}

void pop_back(List* list) {
    if (list->tail == nullptr) {
        return;
    }

    Node* temp = list->tail;
    list->tail = list->tail->prev;
    if (list->tail != nullptr) {
        list->tail->next = nullptr;
    }
    else {
        list->head = nullptr;
    }
    delete temp;
}

void display_forward(List* list) {
    if (list->head == nullptr) {
        cout << "Список пуст" << endl;
        return;
    }
    Node* curr = list->head;
    while (curr != nullptr) {
        printBook(curr->data);
        curr = curr->next;
    }
}

void display_backward(List* list) {
    if (list->tail == nullptr) {
        cout << "Список пуст" << endl;
        return;
    }
    Node* curr = list->tail;
    while (curr != nullptr) {
        printBook(curr->data);
        curr = curr->prev;
    }
}

Node* find_by_title(List* list, const char* title) {
    Node* curr = list->head;
    while (curr != nullptr) {
        if (strcmp(curr->data.title, title) == 0) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

void remove_node(List* list, Node* target) {
    if (target == nullptr) {
        return;
    }

    if (target == list->head) {
        pop_front(list);
        return;
    }
    if (target == list->tail) {
        pop_back(list);
        return;
    }
    target->prev->next = target->next;
    target->next->prev = target->prev;

    delete target;
}

void clear(List* list) {
    while (list->head != nullptr) {
        pop_front(list);
    }
}

void find_by_author(List* list, const char* author) {
    Node* current = list->head;
    bool found = false;
    while (current != nullptr) {
        if (strcmp(current->data.author, author) == 0) {
            printBook(current->data);
            found = true;
        }
        current = current->next;
    }
    if (!found) cout << "Книг этого автора не найдено ВАСЬ" << endl;
}

void delete_older_than(List* list, int year) {
    Node* current = list->head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        if (current->data.year < year) {
            remove_node(list, current);
        }
        current = nextNode;
    }
}

void move_to_front(List* list, Node* target) {
    if (target == nullptr || target == list->head) {
        return;
    }

    if (target == list->tail) {
        list->tail = target->prev;
        list->tail->next = nullptr;
    }
    else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }

    target->next = list->head;
    target->prev = nullptr;
    list->head->prev = target;
    list->head = target;
}

Book inputBook() {
    Book b;
    cout << "Введи название: ";
    cin.getline(b.title, 60);
    cout << "Введи автора: ";
    cin.getline(b.author, 50);
    cout << "Введи год: ";
    cin >> b.year;
    cin.ignore();
    return b;
}

int main() {
    setlocale(LC_ALL, "Russian");

    // указатель на список динамически
    List* myList = new List;
    int choice;

    do {
        cout << "1. Добавить элемент в начало" << endl;
        cout << "2. Добавить элемент в конец" << endl;
        cout << "3. Удалить первый элемент" << endl;
        cout << "4. Удалить последний элемент" << endl;
        cout << "5. Вывести список" << endl;
        cout << "6. Вывести список в обратном порядке" << endl;
        cout << "7. Найти элемент по названию" << endl;
        cout << "8. Найти и удалить книгу из середины" << endl;
        cout << "9. Вывести книги автора " << endl;
        cout << "10. Удалить книги старее года " << endl;
        cout << "11. Переместить книгу в начало " << endl;
        cout << "12. Выход" << endl;
        cout << "Выбери действие вась: ";
        cin >> choice;
        cin.ignore(); 

        if (choice == 1) {
            push_front(myList, inputBook());
        }
        else if (choice == 2) {
            push_back(myList, inputBook());
        }
        else if (choice == 3) {
            pop_front(myList);
            cout << "Первый элемент удален." << endl;
        }
        else if (choice == 4) {
            pop_back(myList);
            cout << "Последний элемент удален." << endl;
        }
        else if (choice == 5) {
            display_forward(myList);
        }
        else if (choice == 6) {
            display_backward(myList);
        }
        else if (choice == 7) {
            char title[60];
            cout << "Введи название для поиска: ";
            cin.getline(title, 60);
            Node* found = find_by_title(myList, title);
            if (found) {
                cout << "Найдено: ";
                printBook(found->data);
            }
            else {
                cout << "Книга не найдена." << endl;
            }
        }
        else if (choice == 8) {
            char title[60];
            cout << "Введи название для удаления вась: ";
            cin.getline(title, 60);
            Node* found = find_by_title(myList, title);
            if (found) {
                remove_node(myList, found);
                cout << "Книга удалена." << endl;
            }
            else {
                cout << "Книга не найдена." << endl;
            }
        }
        else if (choice == 9) {
            char author[50];
            cout << "Введи автора вась: ";
            cin.getline(author, 50);
            find_by_author(myList, author);
        }
        else if (choice == 10) {
            int year;
            cout << "Введи год вась: ";
            cin >> year;
            cin.ignore();
            delete_older_than(myList, year);
            cout << "Старые книги удалены." << endl;
        }
        else if (choice == 11) {
            char title[60];
            cout << "Введи название книги для перемещения вась: ";
            cin.getline(title, 60);
            Node* found = find_by_title(myList, title);
            if (found) {
                move_to_front(myList, found);
                cout << "Книга перемещена в начало." << endl;
            }
            else {
                cout << "Книга не найдена." << endl;
            }
        }

    } while (choice != 12);

    clear(myList);
    delete myList;
    return 0;
}





// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
