#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// создаем новый тип 
typedef struct Node{
    // задаем хранимые значения
    int id;
    char *name;
    // создаем указатель на след. узел списка
    struct Node *next;
} 
// задаем название структуры
List;

List *create(int set_id, char *set_name) {
    // выделение памяти под корень списка
    List *tmp = (List*)malloc(sizeof(List));
    // присваивание значения узлу
    tmp -> id = set_id;
    tmp -> name = set_name;
    tmp -> next = NULL;
    // возвращаю значение которое сохраняется в указателе на список
    return tmp;
}

void add_element_front(List **list, int set_id, char *set_name){
    // создаю новый узел
    List *new_element = create(set_id, set_name);
    // присваиваю указателю на следующий элемент значения указателя на начало первоначального списка
    new_element -> next = *list;
    // переопределяю указатель на новый элемент
    // новый элемент становится самым первым в списке
    *list = new_element;
}

// добавление элемента в конец списка
void add_element_back(List **list, int set_id, char *set_name){
    // создаю новый узел
    List *new_element = create(set_id, set_name);
    // создаю копию указателя, что бы не потерять указатель на начало связного списка
    List *tmp = *list;
    // сдвиг копии указателя списка в самый конец первоначального списка
    while(tmp -> next != NULL) {
        tmp = tmp -> next;
    }
    // присваивание указателю tmp -> next значения созданного нового узла
    // переопределяю переменную next в последнем элементе связного списка
    tmp -> next = new_element;
}

// метод добавления нового элемента между элементом insert_id и следующим элементом
void insert_element(List **list, int insert_id, int set_id, char *set_name) { 
    // объявляю новый указатель-копию списка list
    List *tmp = *list;
    // итерация списка
    while (tmp -> next != NULL)
    {
        // останавливаюсь на элементе insert_id
        if (tmp -> id == insert_id)
        {
            // создаю новый элемент
            List *new_element = create(set_id, set_name);
            // нужно изменить указатели next в элементах insert_id и новом элемента
            // теперь новый элемент указывает на элемент , следующий за insert_id, на который insert_id раньше указывал
            new_element -> next = tmp -> next;
            // изменяет указатель next элемента insert_id на новый элемент
            tmp -> next = new_element;
        }
        // прохожусь по всем элементам списка
        tmp = tmp -> next;
    }
}

List *remove_element(List **list, int remove_id) {
    // Присваивание новому указателю tmp указателя list, p - NULL
    List *tmp = *list, *p = NULL;
    // Проверка списка на пустоту
    if(*list == NULL) {
        return NULL;
    }
    // Если список не пуст, поиск указателя на искомый элемент
    while(tmp && tmp -> id != remove_id) {
        p = tmp;
        tmp = tmp -> next;
    }
    // Если удаляемый элемент первый
    if(tmp == *list) {
        free(list);
        return tmp -> next;
    }
    // Если в списке нет искомого элемента, то возвращаем первоначальный список
    if (!tmp) {
        return *list;
    }
    // Присваивание указателю предыдущего элемента указателя tmp
    p -> next = tmp -> next;
    // Освобождение памяти для указателя tmp
    free(tmp);
    return *list;
}

// метод обновления элемента списка
// работает по принципу insert_element
void update_element(List **list, int update_id, int set_id, char *set_name) {
    List *tmp = *list;
    while(tmp -> next != NULL) {
        if(tmp -> id == update_id) {
            // заменяю значения выбранного элемента
            tmp -> id = set_id;
            tmp -> name = set_name;
        }
        tmp = tmp -> next;
    }
}

// поиск по айди
List *search_by_id(List **list, int search_id) {
    List *tmp = *list;
    // проходимся по списку
    while(tmp -> next != NULL) {
        // если айди совпадает, возвращаем нужное значение
        if(tmp -> id == search_id) {
            return tmp;
        }
        tmp = tmp -> next;
    }
    // если элемент не найден, возвращает первый элемент списка
    return *list;
}

// поиск по имени
List *search_by_name(List **list, char *search_name)
{
    List *tmp = *list;
    while (tmp->next != NULL)
    {
        if (tmp->name == search_name)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return *list;
}

int main() {
    // создаем элемент и помещаем его в указатель на переменную list 
    List *list = create(0, "Nik");
    // добавляем элемент по указанному, с помощью "&", адресу
    add_element_front(&list, -1, "Buzz");
    add_element_front(&list, -2, "Leo");
    add_element_back(&list, 1, "John");
    add_element_back(&list, 2, "Liza");
    insert_element(&list, 1, 999, "INSERT");
    list = remove_element(&list, -5);
    update_element(&list, -1, 9, "Buzz");

    List *look_for = search_by_name(&list, "Buzz");
    printf("id = %d\nname = %s\n", look_for -> id, look_for -> name);

    while(list) {
        // вывод значения узла
        printf("ID : %d, name : %s\n", list -> id, list -> name);
        // сдвиг указателя к следующему узлу
        list = list -> next;
    }

    // препятствую автоматическому закрытию консоли
    system("pause");
    return 0;
}