#include <iostream>
#include <string>
#include <fstream>

struct Key
{
    std::string name;
    std::string surname;
    std::string fathername;

};

struct numlist
{
    struct Node 
    {
        int num;
        Node* next;
        Node() : next(nullptr) {};
    };

    Node* first;
    numlist() : first(nullptr) {}

    void pushBack(int _num)
    {
        if (first)
        {
            Node* arrow = first;
            while (arrow->next)
                arrow = arrow->next;
            arrow->next = new Node();
            arrow->next->num = _num;
        }
        else
        {
            first = new Node();
            first->num = _num;
        }
    }

    Node* searchNum(int _num)
    {
        Node* arrow = first;
        while (arrow && (arrow->num != _num))
            return arrow;
        if (!arrow)
            return nullptr;
    }

    void print_f(std::basic_ofstream<char> &file)
    {
        Node* arrow = first;
        while (arrow)
        {
            file << arrow->num;
            if (arrow->next)
                file << ", ";
            arrow = arrow->next;
        }
        file << '\n';
    }

    void deleteList()
    {
        Node* arrow = first->next;
        Node* memory;

        while (arrow)
        {
            memory = arrow;
            arrow = arrow->next;
            delete(memory);
        }
        delete(first);
    }
};

struct Tree
{
    struct Node
    {
        Key fio;
        Node* parent;
        Node* left;
        Node* right;
        numlist repeats;


        Node() : parent(nullptr), left(nullptr), right(nullptr), repeats() {};
    };

    Node* root = nullptr;


    void addElem(Node* subtree, Key _fio, unsigned short int num)
    {
        if (!root)
        {
            root = new Node();
            root->fio = _fio;
        }
        else
        {
            char compareVal = compare(subtree, _fio);

            switch (compareVal)
            {
                case '=':
                {
                    subtree->repeats.pushBack(num);
                    break;
                }

                case '>':
                {
                    if (subtree->left)
                        addElem(subtree->left, _fio, num);
                    else
                    {
                        subtree->left = new Node();
                        subtree->left->parent = subtree;
                        subtree->left->fio = _fio;
                        subtree->left->repeats.pushBack(num);
                    }
                    break;
                }

                case '<':
                {
                    if (subtree->right)
                        addElem(subtree->right, _fio, num);
                    else
                    {
                        subtree->right = new Node();
                        subtree->right->parent = subtree;
                        subtree->right->fio = _fio;
                        subtree->right->repeats.pushBack(num);
                    }
                    break;
                }

                default:
                {
                    std::cerr << "!!!Compare Error!!!" << std::endl;
                    break;
                }
            }
        }
    }

    char compare(Node* subtree, Key _fio)
    {
        if (subtree->fio.surname == _fio.surname)
        {
            if (subtree->fio.name == _fio.name)
            {
                if (subtree->fio.fathername == _fio.fathername)
                    return '=';
                else
                {
                    int length = 0;
                    if (subtree->fio.fathername.length() >= _fio.fathername.length())
                        length = (int) subtree->fio.fathername.length();
                    else
                        length = (int) _fio.fathername.length();
                    for (int i = 0; i < length; ++i)
                        if (subtree->fio.fathername[i] < _fio.fathername[i])
                            return '<';
                        else
                            return '>';
                }
            }
            else
            {
                int length = 0;
                if (subtree->fio.name.length() >= _fio.name.length())
                    length = (int)subtree->fio.name.length();
                else
                    length = (int)_fio.name.length();
                for (int i = 0; i < length; ++i)
                    if (subtree->fio.name[i] < _fio.name[i])
                        return '<';
                    else
                        return '>';
            }
        }
        else
        {
            int length = 0;
            int flag = 0;
            if (subtree->fio.surname.length() < _fio.surname.length())
                length = (int)subtree->fio.surname.length();
            else
                length = (int)_fio.surname.length();
            for (int i = 0; i < length; ++i)
                if (subtree->fio.surname[i] < _fio.surname[i])
                    return '<';
                else
                    if (subtree->fio.surname[i] > _fio.surname[i])
                        return '>';
                    else
                        flag += 1;
            if (flag == length)
                return '>';
        }
    }

    void deleteElem(Key _fio) // замена на максимальное слева
    {
        Node* searchedItem = searchElem(_fio);

        if (searchedItem)
        {
            Node* leftM = search_max_in_left_subtree(searchedItem);
            if (leftM)
            {
                searchedItem->fio = leftM->fio;
                searchedItem->repeats = leftM->repeats;
                leftM->parent->right = leftM->left;
                if (leftM->left)
                    leftM->left->parent = leftM->parent;
                delete(leftM);
            }
            else
            {
                if (searchedItem->right)
                {
                    searchedItem->right->parent = searchedItem->parent;
                    if (searchedItem == searchedItem->parent->left)
                        searchedItem->parent->left = searchedItem->right;
                    if (searchedItem == searchedItem->parent->right)
                        searchedItem->parent->right = searchedItem->right;
                    delete(searchedItem);
                }
                else
                {
                    if (searchedItem == searchedItem->parent->left)
                        searchedItem->parent->left = nullptr;
                    if (searchedItem == searchedItem->parent->right)
                        searchedItem->parent->right = nullptr;
                    delete(searchedItem);
                }              
            }
           
        }
    }

    Node* search_max_in_left_subtree(Node* subtree) //nullptr если нет левых потомков
    {
        if (subtree)
        {
            Node* arrow = subtree->left;

            if (arrow)
            {
                while (arrow->right)
                    arrow = arrow->right;
                return arrow;
            }
            else
                return nullptr;
        }
       
    }

    Node* searchElem(Key _fio)
    {
        if (root)
        {
            Node* arrow = root;
            if ((arrow->fio.surname == _fio.surname) && (arrow->fio.name == _fio.name) && (arrow->fio.fathername == _fio.fathername))
                return arrow;
            while ((arrow->fio.surname != _fio.surname) && (arrow->fio.name != _fio.name) && (arrow->fio.fathername != _fio.fathername))
            {
                if (!arrow)
                    return nullptr;

                char compareVal = compare(arrow, _fio);

                switch (compareVal)
                {
                case '=':
                    return arrow;
                    break;

                case'<':
                    arrow = arrow->left;
                    break;

                case '>':
                    arrow = arrow->right;
                    break;

                default:
                    std::cerr << "!!!Compare error while searching!!!" << std::endl;
                    return nullptr;
                    break;
                }
            }
        }
        else
            return nullptr;
        
    }

    void deleteTree(Node* subtree)
    {
        if (subtree)
        {
            deleteTree(subtree->left);
            deleteTree(subtree->right);

            subtree->repeats.deleteList();
            delete(subtree);
        }
    }

    void goThrough_f(Node* subtree, std::basic_ofstream<char>& file)//обход слева направо(л-п --> вершина --> п-п)
    {
        if (subtree)
        {
            goThrough_f(subtree->left, file);
            file << subtree->fio.surname << ' ' << subtree->fio.name << ' ' << subtree->fio.fathername << std::endl;
            goThrough_f(subtree->right, file);
        }
    }

    void print_f(Node* subtree, std::basic_ofstream<char>& file, int space = 0)
    {
        if (subtree)
        {
            enum{COUNT = 2};
            space += COUNT;
            print_f(subtree->right, file, space);
            for (int i = COUNT; i < space; ++i)
                file << "  ";
            //file << root->fio.surname << ' ' << root->fio.name << ' ' << root->fio.fathername << std::endl << std::endl;
            file << subtree->fio.surname << '\n' << '\n';
            print_f(subtree->left, file, space);
        }
    }

    void read_f(std::ifstream &fin)
    {
        unsigned short int num = 0;

        while (!fin.eof() )
        {
            num += 1;
            Key _fio;

            fin >> _fio.surname;
            if (check_fio(_fio.surname))
            {
                fin >> _fio.name;
                if(check_fio(_fio.name))
                {
                    fin >> _fio.fathername;
                    if (check_fio(_fio.fathername))
                        addElem(root, _fio, num);
                }
            }
        }
    }

    bool check_fio(std::string anyname) // + edit
    {
        int check = 0;
        for (int i = 0; i < anyname.length(); ++i)
        {
            if ((anyname[i] < 65) || ((anyname[i] > 90) && (anyname[i] < 97)) || (anyname[i] > 122))
            {
                std::cerr << "file-reading error: check for english translete\n";
                return false;
            }
            else
                check += 1;
                if (anyname[i] >= 65 && anyname[i] <= 90 && i != 0) // 97 - 65 == 32
                    anyname[i] += 32;
        }
        if (anyname[0] >= 97 && anyname[0] <= 122) // 97 - 65 == 32
            anyname[0] -= 32;
        if (check == anyname.length())
            return true;
        else return false;
    }
};


int main()
{

    Tree tree = Tree();
    std::string surname;
    std::string name;
    std::string fathername;
    unsigned short int number = 0;
    Key fio;

    std::ifstream fin;
    std::ofstream fout;
    std::string input_file_name = "input_en.txt";
    std::string output_file_name = "output.txt";
    fin.open(input_file_name);

    tree.read_f(fin);

    fin.close();
    
    fout.open(output_file_name);
    tree.print_f(tree.root, fout, 0);

    fout << "-----------------check_delete-------------------\n";
    
    fio.name = "Rodion";
    fio.surname = "Stepachev";
    fio.fathername = "Eduardovic";

    tree.deleteElem(fio);
    
    tree.print_f(tree.root, fout, 0);

    fout << "--------------check_add_after_delete-------------\n";
    tree.addElem(tree.root, fio, number + 1);
    tree.print_f(tree.root, fout, 0);

    fout << "----------check_walk_from_left_to_right----------\n";
    tree.goThrough_f(tree.root, fout);

    fout << "---------------check_repeats_list----------------\n";
    fio.name = "Stepan";
    fio.surname = "Shaydurov";
    fio.fathername = "Egorovic";

    tree.searchElem(fio)->repeats.print_f(fout);//
    fout.close();
    
    tree.deleteTree(tree.root);
    return 0;
}
