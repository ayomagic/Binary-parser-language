#include <iostream>
#include "parse.h"
#include <cstring>

class DoubleLL {
    class Node {
    public:
        Node *prev;
        Node *next;
        const char *var;
        int val;

        Node (Node *prev, Node *next, int val, const char *var) {
            this->prev = prev;
            this->next = next;
            this->val = val;
            this->var = var;
        }

        ~Node () {
            delete this->next;
        }
    };
public:

    int size;
    Node *ptr_to_head;

    DoubleLL (): size(0), ptr_to_head(nullptr) {};

    DoubleLL (int val, char *var) {
        this->ptr_to_head = new Node(nullptr, nullptr, val, var);
        this->size = 1;
    }

    ~DoubleLL() {
        Node *prev = nullptr;
        Node *curr = ptr_to_head;
        while (curr != nullptr) {
            prev = curr;
            curr = curr->next;
            delete prev;
        }
        ptr_to_head = nullptr;
    }

    bool AddElement (int val, const char *var) {
        Node *n = new Node(nullptr, ptr_to_head, val, var);
        ptr_to_head->prev = n;
        ptr_to_head = n;
        this->size++;
        return true;
    }

    bool RemoveElement (const char *var) {
        if (!SearchList(var)) return false;

        Node *curr = ptr_to_head;
        for (int i = 0; i < size; i++) {
            if (curr->var == var) {
                //Middle Node
                if (curr->prev != nullptr && curr->next != nullptr) {
                    Node *tmp = curr->prev;
                    Node *tmp_2 = curr->next;

                    tmp->next = curr->next;     //OR tmp->next = tmp_2->next; ???
                    tmp_2->prev = tmp->prev;    //OR tmp_2->prev = tmp->prev; ???
                    delete curr;
                    this->size--;
                    return true;
                    //Tail Node
                } else if (curr->next == nullptr) {
                    Node *tmp = curr->prev;
                    tmp->next = nullptr;
                    delete curr;
                    this->size--;
                    return true;
                    //Head node
                } else if (curr->prev == nullptr && curr->next != nullptr) {
                    Node *tmp = curr->next;
                    ptr_to_head = tmp;
                    delete curr;
                    this->size--;
                    return true;
                }
            }
            curr = curr->next;
        }
        return false;
    }

    /*
     * question:
     * WHY SHOULD I NOT PASS IN THE HEAD OF THE LIST AS ARGUEMNT?
     *
     * answer:
     * There is no need to pass in the head of the list as an arguemnt
     * This function will only be able to operate on This linked list
     */
    bool SearchList (const char var[]) {
        Node *tmp = ptr_to_head;

        //no el in list
        if (tmp == nullptr) return false;

        while (tmp) {
            if (tmp->var == var) {
                return true;
            } else {
                tmp = tmp->next;
            }
        }

        //not found
        return false;
    }

    int FindKey (const char var[]) {
        Node *tmp = ptr_to_head;
        if (tmp == nullptr) return 0;

        while (tmp) {
            if (tmp->var == var) {
                return tmp->val;
            } else {
                tmp = tmp->next;
            }
        }
        //not found
        return 0;
    }

    void UpdateVar(int res, const char var[]) {
        Node *tmp = ptr_to_head;
        while(tmp) {
            if (tmp->var == var) {
                tmp->val = res;
            } else {
                tmp = tmp->next;
            }
        }
    }

    //print
    void PrintList () {
        Node *tmp = ptr_to_head;
        for (int i = 0; i < this->size; i++) {
            std::cout << tmp->val << " ";
            tmp = tmp->next;
        }
        std::cout << std::endl;
    }

    void printnext () {
        Node *curr = ptr_to_head;
        printf("%d \n", curr->next->val);
    }
};

DoubleLL list;

int strCompare(char* str1, const char* str2) {
    /*
     EDGE CASES:
     If strings are not the same size
     */
    if (*str1 == '\0' && *str2 != '\0') {
        return -1;
    }
    // If strings are the same size
    if (*str1 == '\0' && *str2 == '\0') {
        return 0;
    }

    if (*str1 == *str2) {
        return strCompare(str1 + 1, str2 + 1);
    } else if (*str1 < *str2) {
        return -1;
    } else {
        return 1;
    }
}


int compute () {
    read_next_token();
    if (next_token_type == NUMBER) {
        return token_number_value;
    }
    const char *tmp = next_token();
    if ((tmp >= "a" && tmp <= "z") || (tmp >= "A" && tmp <= "z")) {
        // search through linked list class to find matching letter
        // return int that matches to letter
        return list.FindKey(next_token());
    }
    if (strCompare("+", tmp) == 0) {
        return compute() + compute();
    } else if (strCompare("!", tmp) == 0) {
        return !compute();
    } else if (strCompare("-", tmp) == 0) {
        return compute() - compute();
    } else if (strCompare("*", tmp) == 0) {
        return compute() * compute();
    } else if (strCompare("/", tmp) == 0) {
        return compute() / compute();
    } else if (strCompare("%", tmp) == 0) {
        return compute() % compute();
    } else if (strCompare("&&", tmp) == 0) {
        return compute() && compute();
    } else if (strCompare("||", tmp) == 0) {
        return compute() || compute();
    } else if (strCompare("<", tmp) == 0) {
        return compute() < compute();
    } else if (strCompare(">", tmp) == 0) {
        return compute() > compute();
    } else if (strCompare("==", tmp) == 0) {
        return compute() == compute();
    } else if (strCompare("!=", tmp) == 0) {
        return compute() != compute();
    } else if (strCompare("<=", tmp) == 0) {
        return compute() <= compute();
    } else if (strCompare(">=", tmp) == 0) {
        return compute() >= compute();
    } else if (strCompare("~", tmp) == 0) {
        return compute() * -1;
    } else {
        return 0;
    }
}



int check() {
    read_next_token();
    while (next_token_type != END) {
        if (next_token_type == NAME) {
            if (strCompare("set", next_token()) == 0) {
                read_next_token();
                const char *tmp = next_token();
                if (!(list.SearchList(tmp))) {
                    //Not Found
                    std::cout << "Variable " << tmp << " has not been declared yet" << std::endl;
                } else {
                    //Found
                    int res = compute();
                    list.UpdateVar(res, tmp);
                }
            } else if (strCompare("var", next_token()) == 0) {
                read_next_token();
                const char *tmp = next_token();
                if (list.SearchList(tmp)) {
                    //If el is in list
                    std::cout << "Variable " << tmp << " incorrectly re-initialized" << std::endl;
                } else {
                    //If el is not in list
                    int res = compute();
                    list.AddElement(res, tmp);
                }
            } else if (strCompare("output", next_token()) == 0) {
                std::cout << compute();
            } else if (strCompare("text", next_token()) == 0) {                                        // if text
                read_next_token();
                std::cout << next_token() << std::endl;
            }
        } else if (next_token_type == SYMBOL) {
            const char *op = next_token();
            if (strcmp(op, "//") == 1) {
                skip_line();
            }
        }
        read_next_token();
    }

}

int main () {
    set_input("test3.blip");
    check();
}