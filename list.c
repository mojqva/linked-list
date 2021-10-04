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

void print_list(List *list) {
    while (list)
    {
        // вывод значения узла
        printf("ID : %d, name : %s\n", list->id, list->name);
        // сдвиг указателя к следующему узлу
        list = list->next;
    }
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

//###############QUICKSORT-START######################

//функция для получения последнего элемента списка
List *getTail(List *cur){
    while(cur != NULL && cur -> next != NULL) {
        cur = cur -> next;
    }
    return cur;
};

// функция для разделения списка используя последний элемент как основу
List *partition(List *head, List *end, List *newHead, List *newEnd) {
    List *pivot = end;
    List *prev = NULL, *cur = head, *tail = pivot;

    // во время разделения списка, его начало и конец буду изменяться и 
    // записываться в newHead и newEnd
    while(cur != pivot) {
        if(cur -> id < pivot -> id) {
            // первый элемент который меньше чем опора (pivot)
            // становится новый началом (newHead)
            if(newHead == NULL) {
                newHead = cur;
            }
            prev = cur;
            cur = cur -> next;
        }
        // если текущий элемент cur больше чем пивот
        else {
            // Двигаем cur элемент к хвосту и меняем tail
            if(prev){
                prev -> next = cur -> next;
            }
            List *tmp = cur -> next;
            cur -> next = NULL;
            tail -> next = cur;
            tail = cur;
            cur = tmp;

        }
    }
    // если пивот - самый маленький айди в списке, то он идет в начало списка
    if(newHead == NULL) {
        newHead == pivot;
    }
    // Текущий последний элемент закидываем в newEnd
    newEnd = tail;
    // возвращаем опору (пивот)
    return pivot;
}

// функция сортировки списка рекурсивным методом исключая последний элемент
List *quickSortRecur(List *head, List *end) {
    // основное условие 
    if(!head || head == end) {
        return head;
    }

    List *newHead = NULL, *newEnd = NULL;
    // делим список, newHead и newEnd будут обновлены функцией деления partition
    List *pivot = partition(head, end, newHead, newEnd);
    // если пивот - самый маленький айди в списке , то левую часть не сортируем
    if(newHead != pivot) {
        // сохраняем элемент до того как обнулим пивот
        List *tmp = newHead;
        while(tmp -> next != pivot) {
            tmp = tmp -> next;
        }
        tmp -> next = NULL;

        // сортировка рекурсивом списка перед пивотом (левая часть)
        newHead = quickSortRecur(newHead, tmp);
        // меняем next у последнего элемента левой половины на значение пивота
        tmp = getTail(newHead);
        tmp -> next = pivot;  
    }
    // сортировка рекурсивом списка после пивота (правая часть)
    pivot -> next = quickSortRecur(pivot -> next, newEnd);

    return newHead;
}

// главнаяя функция-обертка для рекурсирной сортировки 
void quickSort(List *headRef) {
    headRef = quickSortRecur(headRef, getTail(headRef));
    return;
}

//###############QUICKSORT-END########################

int main() {
    // создаем элемент и помещаем его в указатель на переменную list 
    List *list = create(0, "Nik");

    printf("BEFORE\n\n\n");
    print_list(list);
    // добавляем элемент по указанному, с помощью "&", адресу
    add_element_front(&list, 7, "Buzz");
    add_element_front(&list, 2, "Leo");
    add_element_back(&list, 11, "John");
    add_element_back(&list, -2, "Liza");
    insert_element(&list, 2, 99, "INSERT");
    list = remove_element(&list, -2);
    update_element(&list, 99, 12, "Updated");
    List *by_id = search_by_id(&list, 7); // 7 Buzz
    List *by_name = search_by_name(&list, "Updated"); // 11 John

    //TODO
    // programm crashes
    // quickSort(list);

    printf("AFTER\n\n\n");
    print_list(list);

    printf("By ID:\n%d  %s\n\n", by_id -> id, by_id -> name);
    printf("By Name:\n%d  %s\n\n", by_name->id, by_name->name);

    // препятствую автоматическому закрытию консоли
    system("pause");
    return 0;
}