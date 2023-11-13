#include <iostream>
#include <string>

struct Key
{
    std::string name;
    std::string surname;
    std::string fathername;

    //Key() : name("name is empty"), fathername("fathername is empty"), surname("surname is empty") {};
};

struct Node
{
    Key  fio;
    Node* next;

    Node() : next(nullptr) {};
};

struct up_list
{
    Node* first;

    void __init__()
    {
        first = new Node();
    }

    bool is_empty()
    {
        return first == nullptr;
    }

    void push(Key fio)
    {
        Node* ptr = new Node();

        if (is_empty())
        {
            this->__init__();
            first = ptr;
        }//endif
        else
        {
            Node* arrow = first;
            if (ptr->fio.name <= arrow->fio.name)
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
                    if (arrow->fio.name >= ptr->fio.name)
                    {
                        left->next = ptr;
                        ptr->next = arrow;
                        break;
                    }
                    left = left->next;
                    arrow = arrow->next;
                }
                if ((arrow == nullptr) && (left->fio.name < ptr->fio.name))
                {
                    arrow = ptr;
                    left->next = arrow;
                    arrow->next = nullptr;
                }
            }
        }

    }

    Node* searchVal(Key _fio)
    {
        Node* arrow = first;
        while (arrow && (arrow->fio.name != _fio.name) && (arrow->fio.fathername != _fio.fathername))
        {
            arrow = arrow->next;
        }
        if (!arrow)
            return nullptr;
        else
            return arrow;
    }

    void print()
    {
        int i = 1;
        Node* arrow = first;
        while (arrow)
        {

            std::cout << i << ". " << arrow->fio.surname << ' ' << arrow->fio.name << ' ' << arrow->fio.fathername << '\n';
            ++i;
            arrow = arrow->next;
        }
    }

    void delete_elements(Key _fio)
    {
        if (!is_empty())
        {
            Node* left = first;
            Node* arrow = left->next;
            Node* memory;

            while (first && (first->fio.name == _fio.name) && ((first->fio.fathername == _fio.fathername)))
            {
                memory = first;
                first = first->next;
                delete(memory);

                left = first;
                if (left)
                    arrow = left->next;
            }
            while (arrow)
            {
                if (arrow && (arrow->fio.name == _fio.name) && ((arrow->fio.fathername == _fio.fathername)))
                {
                    memory = arrow;
                    left->next = arrow->next;
                    delete(memory);

                    if (left)
                        arrow = left->next;
                }
                else
                {
                    left = left->next;
                    if (left)
                        arrow = left->next;
                }
            }
        }
    }

    void deleteList()
    {
        Node* arrow = first->next;
        Node* memory = arrow;

        while (arrow)
        {
            memory = arrow;
            arrow = arrow->next;
            delete(memory);
        }
        first = nullptr;
    }
};

struct treeNode
{
    treeNode* parent;

    Key fio;

    up_list repeats;
    treeNode* left;
    treeNode* right;

    treeNode() : parent(nullptr), left(nullptr), right(nullptr){};
};

struct Tree
{
    treeNode* root;
    

    void __init__()
    {
        root = new treeNode();
    }
        
    void addElem(Key _fio, treeNode* subtree)
    {
        if (subtree == root && (root))
        {
            this->__init__();
            subtree->fio = _fio;
        }
        else
        {
            if (subtree->fio.surname == _fio.surname)//сравнение по алфавиту
            {
                //добавление в список повторяющихся фамилий, упорядоченный по именам
                if (subtree->repeats.first)
                    subtree->repeats.push(_fio);
                else
                {
                    subtree->repeats.__init__();
                    subtree->repeats.first->fio = _fio;
                }
                // конец 
            }
            else
            {
                int length = 0;
                if (subtree->fio.surname.length() >= _fio.surname.length())
                    length = subtree->fio.surname.length();
                else 
                    length = _fio.surname.length();

                for (int i = 0; i < length; ++i)
                {
                    if (subtree->fio.surname[i] < _fio.surname[i])
                    {
                        subtree->left = new treeNode();
                        subtree->left->parent = subtree;
                        addElem(_fio, subtree->left);                   //рекурсивно добавляем в левое поддерево
                        i += length;                                   //чтобы избежать повторных добавлений после проверке первой отличной буквы
                    }
                    if (subtree->fio.surname[i] > _fio.surname[i])
                    {
                        subtree->right = new treeNode();
                        subtree->right->parent = subtree;
                        addElem(_fio, subtree->right);                  //рекурсивно добавляем в правое поддерево
                        i += length;                                   //чтобы избежать повторных добавлений после проверке первой отличной буквы
                    }
                }
            }//конец сравнения по алфавиту
        }
    }

    void deleteElem(Key _fio) // замена на максимальное слева
    {
        treeNode* searchedItem = searchElem(_fio);

        if (searchedItem && (searchedItem->parent))
        {
            if (searchedItem->repeats.first)
            { 
                if ((searchedItem->fio.name == _fio.name) && (searchedItem->fio.fathername == _fio.fathername))
                {
                    searchedItem->fio = searchedItem->repeats.first->fio;
                    searchedItem->repeats.first = searchedItem->repeats.first->next;
                }
                else
                    searchedItem->repeats.delete_elements(searchedItem->fio);
            }
            else
            {
                treeNode* arrow = searchedItem;
               
                if (arrow->left)
                {
                    arrow = searchedItem->left;

                    while (!arrow->right)
                        arrow = arrow->left;
                    while (arrow->right)
                        arrow = arrow->right;
                    //теперь arrow - максимальный элемент в левом поддереве

                    treeNode* bufer = arrow;

                    searchedItem->fio = arrow->fio;
                    searchedItem->repeats = arrow->repeats;
                    if (arrow->parent->right == arrow)
                        arrow->parent->right = nullptr;
                    else
                        arrow->parent->left = nullptr;
                    delete(bufer);
                }
                else
                {
                    if (arrow->right)
                    {
                        while (arrow->right)
                            arrow = arrow->right;//максимальный элемент в поддереве
                        
                        treeNode* bufer = arrow;

                        searchedItem->fio = arrow->fio;
                        searchedItem->repeats = arrow->repeats;
                        if (arrow->parent->right == arrow)
                            arrow->parent->right = nullptr;
                        else
                            arrow->parent->left = nullptr;
                        delete(bufer);
                    }
                    //если нет ни left, ни right
                    //{
                    treeNode* bufer = arrow;

                    searchedItem->fio = arrow->fio;
                    searchedItem->repeats = arrow->repeats;

                    if (arrow->parent->right == arrow)
                        arrow->parent->right = nullptr;
                    else
                        arrow->parent->left = nullptr;
                    delete(bufer);
                    //}
                }
                
            }
        }
        if (!searchedItem->parent)
        {
            treeNode* arrow = searchedItem;
            while (!arrow->right)
                arrow = arrow->left;
            while (arrow->right)
                arrow = arrow->right;
            //теперь arrow - максимальный элемент в левом поддереве

            treeNode* bufer = arrow;
            searchedItem->fio = arrow->fio;
            searchedItem->repeats = arrow->repeats;

            if (arrow->parent->right == arrow)
                arrow->parent->right = nullptr;
            else
                arrow->parent->left = nullptr;
            delete(bufer);
        }
    }

    treeNode* searchElem(Key _fio)
    {
        treeNode* arrow = root;

        while (arrow->fio.surname != _fio.surname)
        {
            int length = 0;
            if (arrow->fio.surname.length() >= _fio.surname.length())
                length = arrow->fio.surname.length();
            else
                length = _fio.surname.length();

            for (int i = 0; i < length; ++i)
            {
                if (arrow->fio.surname[i] < _fio.surname[i])
                {
                    arrow = arrow->left;
                    i += length;                                   //чтобы избежать повторных добавлений после проверке первой отличной буквы
                }
                if (arrow->fio.surname[i] > _fio.surname[i])
                {
                    arrow = arrow->right;
                    i += length;                                   //чтобы избежать повторных добавлений после проверке первой отличной буквы
                }
            }
        }
        if (arrow)
            return arrow;
        else
            return nullptr;
    }

    Node* searchElemInReps(treeNode* tnode)// для searchElem
    {
        Node* listElem;
        listElem->fio.fathername = tnode->fio.fathername;
        listElem->fio.name = tnode->fio.name;
        listElem->fio.surname = tnode->fio.surname;
        if(tnode->repeats.searchVal(listElem->fio))
        return listElem;                                    
    }
};






int main()
{
    

    return 0;
}

