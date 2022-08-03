//
// Created by os on 4/26/22.
//

#ifndef PROJECT_BASE_V1_0_LIST_HPP
#define PROJECT_BASE_V1_0_LIST_HPP

template<typename T>
class List{
private:
    struct Elem{
        T *data;
        Elem *next;

        Elem(T *data, Elem *next) : data(data), next(next){}
    };

    Elem *head, *tail;
public:
    List() : head(nullptr), tail(nullptr) {}

    List(const List<T> &) = delete;

    List<T> &operator=(const List<T> &) = delete;

    void addFirst(T *data){
        Elem *elem = new Elem(data, head);
        head = elem;
        if(!tail){ tail = head;}
    }
    void addLast(T *data){
        Elem *elem = new Elem(data, nullptr);
        if(tail){
            tail->next = elem;
            tail = elem;
        }else{
            head = tail = elem;
        }
    }
    T *removeFirst(){
        if(!head){ return nullptr; }

        Elem *elem = head;
        head = head->next;
        if(!head){ tail = nullptr; }

        T *ret = elem->data;
        delete elem;
        return ret;
    }
    T *peekFirst(){
        if(!head){ return nullptr; }
        return head->data;
    }
    T *removeLast(){
        if(!head){ return nullptr; }

        Elem *prev = nullptr;
        for(Elem *curr = head; curr && curr != tail; curr = curr->next){
            prev = curr;
        }

        Elem *elem = tail;
        if(prev){ prev->next = nullptr; }
        else{ head = nullptr; }
        tail = prev;

        T *ret = elem->data;
        delete elem;
        return ret;
    }
    T *peekLast(){
        if(!tail){ return nullptr; }
        return tail->data;
    }
    T *removeById(T *data){
        Elem *tek = head, *pom = nullptr;

        while(tek->sem != data  && tek != nullptr){
            pom = tek;
            tek = tek->next;
        }
        if(tek == nullptr)
            return nullptr;
        else if(tek == head)
            head = head->next;
        else
            pom->next = tek->next;

        return tek;
    }
};

#endif //PROJECT_BASE_V1_0_LIST_HPP
