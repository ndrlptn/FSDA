#include <iostream>
//----------------------------------------------
struct Node
{
    int val;
    Node* next;

    Node(int _val) : val(_val), next(nullptr) {}
};

struct up_list
{
    Node* first;
    Node* last;

    up_list() : first(nullptr) {}

    void list_ini()
    {

    }
    bool is_empty()
    {
        return first == nullptr;
    }


    void push_back(int val)
    {
        Node* ptr = new Node(val);

        if (is_empty())
        {
            first = ptr;
        }//endif
        else
        {
            Node* arrow = first;
            if (ptr->val <= arrow->val)
            {
                ptr->next = first;
                first = ptr;
            }//endif
            else
            {
                Node* left = first;
                arrow = left->next;
                while (arrow)
                {
                    if (arrow->val >= ptr->val)
                    {
                        left->next = ptr;
                        ptr->next = arrow;
                        break;
                    }
                    left = left->next;
                    arrow = arrow->next;
                }
                if ((arrow == nullptr) && (left->val < ptr->val))
                {
                    arrow = ptr;
                    left->next = arrow;
                    arrow->next = nullptr;
                }
            }
        }

    }


    void print()
    {
        int i = 1;
        Node* arrow = first;
        while (arrow)
        {
            std::cout << i << ". " << arrow->val << '\n';
            ++i;
            arrow = arrow->next;
        }
    }


    void delete_elements(int val)
    {
        Node* arrow = first;
        Node* left = first;

        while (arrow)
        {
            if ((arrow->val == val) && (arrow == first))
            {
                first = first->next;
            }
            else
                if (arrow->val == val)
                {
                    left->next = arrow->next;
                    arrow = arrow -> next;
                }
                else 
                {
                    left = arrow;
                    arrow = arrow->next;
                }
        }
    }
};
//-----------------------------------------------


up_list substraction(up_list list1, up_list list2);


//------------------
int main()
{
    up_list L;
    up_list L1, Result;
    int count;
    int input_val;
    int del_val;

    std::cout << "Input amount of numbers in list:";
    std::cin >> count;
    std::cout << '\n';

    for (int i = 0; i < count; ++i)
    {
        std::cout << "Input number: ";
        std::cin >> input_val;

        L.push_back(input_val);
    }

    L.print();

    std::cout << '\n';
    std::cout << "Input value to delete in list:";
    std::cin >> del_val;

    L.delete_elements(del_val);
    L.print();

    std::cout << '\n';
    std::cout << "Input amount of numbers in second list to substruct from 1st one:";
    std::cin >> count;
    std::cout << '\n';

    for (int i = 0; i < count; ++i)
    {
        std::cout << "Input number: ";
        std::cin >> input_val;

        L1.push_back(input_val);
    }
    Result = substraction(L, L1);
    Result.print();

    return 0;
}
//------------------


up_list substraction(up_list list1, up_list list2)
{
    Node* arrow2 = list2.first;

    while (arrow2)
    {
        list1.delete_elements(arrow2->val);
        arrow2 = arrow2->next;
    }

    return list1;
}

