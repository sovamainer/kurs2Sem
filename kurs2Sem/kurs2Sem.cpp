#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
    int key;
    Node* left = NULL;
    Node* right = NULL;
};

struct trunk 
{
    trunk* prev = NULL;
    string str;
    trunk(trunk* prev, string& str) : prev(prev), str(str) {}
};

Node* getFreeTree(int value) {
    Node* root = (Node*)malloc(sizeof(Node));
    root->left = root->right = NULL;
    root->key = value;
    return root;
}

Node* search(int key, Node* root){           
    if (root != NULL)                       
    {
        if (key == root->key)           
            return root;                       
        if (key < root->key)            
            return search(key, root->left);  
        else                                   
            return search(key, root->right);   
    }
    else return NULL;                         
}

Node* findMaxElem(Node* root)
{
    if (root->right == NULL)
    {
        return root;
    }
    else
    {
        return findMaxElem(root->right);
    }
}

Node* deleteNode(int currKey, Node* root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else
    {
        if (currKey == root->key)
        {
            if ((root->left == NULL) && (root->right == NULL))
            {
                return NULL;
            }

            if (root->left == NULL)
            {
                return root->right;
            }
            if (root->right == NULL)
            {
                return root->left;
            }

            Node* maxElemInLeft = findMaxElem(root->left);
            root->key = maxElemInLeft->key;
            root->left = deleteNode(maxElemInLeft->key, root->left);
        }

        else if (currKey < root->key)
        {
            root->left = deleteNode(currKey, root->left);
        }
        else
        {
            root->right = deleteNode(currKey, root->right);
        }
        return root;
    }
}

Node* searchT(int currKey, Node* root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else
    {
        if (currKey == root->key)
        {
            return root;
        }
        else if (currKey < root->key)
        {
            return searchT(currKey, root->left);
        }
        else
        {
            return searchT(currKey, root->right);
        }
    }
}

void insert(int key, Node* root) {                                  
    if (key < root->key)           
    {
        if (root->left != NULL)          
            insert(key, root->left);     
        else                              
        {
            root->left = new Node;       
            root->left->key = key; 
            root->left->left = NULL;      
            root->left->right = NULL;     
        }
    }
    else if (key >= root->key) {    

        if (root->right != NULL)         
            insert(key, root->right);     
        else                              
        {
            root->right = new Node;       
            root->right->key = key; 
            root->right->left = NULL;    
            root->right->right = NULL;   
        }
    }
}

void showTrunk(trunk* p, int& count, ofstream& f2) {
    if (p == NULL)
        return;
    showTrunk(p->prev, count, f2);
    count++;
    f2 << p->str;
}

void printTree(Node* tree, trunk* prev, bool isRight, ofstream& f2) {
    if (tree == NULL)
        return;
    string prev_str = "    ";
    trunk* tmp = new trunk(prev, prev_str);
    printTree(tree->right, tmp, 1, f2);
    if (!prev)
        tmp->str = "-->";
    else if (isRight) {
        tmp->str = ".-->";
        prev_str = "   |";
    }
    else {
        tmp->str = "`-->";
        prev->str = prev_str;
    }
    int count = 0;
    showTrunk(tmp, count, f2);
    f2 << tree->key << endl;
    if (prev)
        prev->str = prev_str;
    tmp->str = "   |";
    printTree(tree->left, tmp, 0, f2);
}

bool checkNumberInArray(int arr[], int size, int number) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == number) {
            return true;
        }
    }
    return false;
}

void printFileLines(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void preOrderTravers(Node* root)
{
    if (root)
    {
        cout << root->key << " ";
        preOrderTravers(root->left);
        preOrderTravers(root->right);
    }
    else
    {
        return;
    }
}

void postOrderTravers(Node* root)
{
    if (root)
    {
        postOrderTravers(root->left);
        postOrderTravers(root->right);
        cout << root->key << " ";
    }
}

void levelOrderTravers(Node* root)
{
    queue<Node*> q;
    q.push(root);
    while (!q.empty())
    {
        Node* tree = q.front();
        cout << tree->key << " ";
        q.pop();

        if (tree->left != NULL)
        {
            q.push(tree->left);
        }
        if (tree->right != NULL)
        {
            q.push(tree->right);
        }
    }
}

void workWithTree(Node* tree) {
    cout << "Команды: \n"
        "[1]Вставка\n"
        "[2]Удаление\n"
        "[3]Поиск\n"
        "[4]Прямой обход\n"
        "[5]Обратный обход\n"
        "[6]Обход в ширину\n"
        "[0]Выход\n"
        "Команда: ";

    int choise;
    cin >> choise;

    if (choise == 1) {
        int key;
        cin >> key;
        insert(key, tree);
        system("cls");
        ofstream file5("output.txt", ios::trunc);
        printTree(tree, NULL, false, file5);
        printFileLines("output.txt");
        file5.close();
    }

    if (choise == 2) {
        int key;
        cin >> key;
        deleteNode(key, tree);
        system("cls");
        ofstream file4("output.txt", ios::trunc);
        printTree(tree, NULL, false, file4);
        printFileLines("output.txt");
        file4.close();
    }
    if (choise == 3) {
        int key;
        cin >> key;
        searchT(key, tree);
        system("cls");
        ofstream file6("output.txt", ios::trunc);
        printTree(tree, NULL, false, file6);
        printFileLines("output.txt");
        file6.close();
    }
    if (choise == 4) {
        system("cls");
        preOrderTravers(tree);
        cout << endl;
    }
    if (choise == 5) {
        system("cls");
        postOrderTravers(tree);
        cout << endl;
    }
    if (choise == 6) {
        system("cls");
        levelOrderTravers(tree);
        cout << endl;
    }
    if (choise == 0) {
        system("cls");
    }
}

int main()
{
    setlocale(LC_ALL, "RU");
    srand(time(NULL));
    Node* tree;
    int ki;
    while (true) {
        cout << "Команды: \n"
            "[1]Автоматическое заполнение\n"
            "[2]Ввод до остановки\n"
            "[3]Считывание с файла\n"
            "[0]Выход\n"
            "Команда: ";

        cin >> ki;
        if (ki == 1) {
            ofstream file("output.txt", ios::trunc);
            Node* tree;
            int val, p = 0;
            int mas[199];
            int a = rand() % 199 - 99;

            bool choise = true;

            cout << "Размерность дерева: ";
            cin >> val;

            system("cls");

            tree = getFreeTree(a);
            mas[p] = a;
            p += 1;

            for (int i = 0; i < val; i++) {
                if (choise) {
                    a = rand() % 199 - 99;
                }
                if (!checkNumberInArray(mas, 199, a)) {
                    insert(a, tree);
                    mas[p] = a;
                    p += 1;
                    choise = true;
                }
                else {
                    while (checkNumberInArray(mas, 199, a)) {
                        a = rand() % 199 - 99;
                        choise = false;
                    }
                }
            }
            printTree(tree, NULL, false, file);
            printFileLines("output.txt");
            file.close();
            workWithTree(tree);
        }
        if (ki == 2) {
            system("cls");
            vector<int> numbers;
            int num;
            Node* tree;

            while (cin >> num && num != 0) {
                numbers.push_back(num);
            }

            system("cls");

            tree = getFreeTree(numbers[0]);

            for (int i = 1; i < size(numbers); i++) {
                insert(numbers[i], tree);
            }

            ofstream file2("output.txt", ios::trunc);
            printTree(tree, NULL, false, file2);
            printFileLines("output.txt");
            file2.close();
            workWithTree(tree);
        }
        if (ki == 3) {
            system("cls");
            Node* tree;
            ifstream file("input.txt");
            int count;
            file >> count;

            vector<int> values;
            int value;

            while (file >> value) { 
                values.push_back(value);
            }

            file.close();

            int val, p = 0;
            int mas[199];
            int a = rand() % 199 - 99;

            tree = getFreeTree(values[0]);
            mas[p] = a;
            p += 1;

            for (int i = 1; i < size(values); i++) {
                insert(values[i], tree);
            }

            ofstream file1("output.txt", ios::trunc);
            printTree(tree, NULL, false, file1);
            printFileLines("output.txt");
            file1.close();
            workWithTree(tree);
        }
        if (ki == 0) {
            break;
        }
    }
}

