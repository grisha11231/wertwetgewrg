#include <iostream>
#include <string>

/*
пример ввода , где e1-название ребра, v1-название вершины,  названия можно задовать разные, 
из различных символов но чтобы задать ребро вид должен быть таков line(point_1, point_2)

     e1(v2, v1) e2(v3, v1) e5(v4, v2) e4(v1, v4) e3(v4, v3)

*/ 

using namespace std;

bool Sort_args(string str_in, string str_cprd) {
    if (str_in.length() < str_cprd.length()) {
        return true;
    }
    else if (str_in.length() > str_cprd.length()) {
        return false;
    }
    else {
        for (int i = 0; i < str_in.length(); i++) {
            if (str_in[i] < str_cprd[i]) {
                return true;
            }
            else if (str_in[i] > str_cprd[i]) {
                return false;
            }
        }
        return false;
    }
}

template<typename T>
class Node
{
public:
    Node<T>* pNext;
    T data;
    string name;
    Node(){}
    Node(T _data = T(), string _name = "", Node<T>* _pNext = nullptr)
    {
        this->data = _data;        
        this->pNext = _pNext;
        this->name = _name;
    }
};

template <typename T>
class List
{
public:
    int size;

    List() {
        Head = nullptr;
        size = 0;
    }
    ~List() {
        clear();
    }

    void push_back(T data, string _name) {
        if (!Head) {
            Head = new Node<T>(data, _name);
        }
        else {
            Node<T>* current = this->Head;            
            while (true) {                                
                if (_name == current->name) { return; }
                else if (Sort_args(_name, current->name)) {
                    Node<T>* tmp = new Node<T>(current->data, current->name);
                    tmp->pNext = current->pNext;
                    current->data = data;
                    current->name = _name;
                    current->pNext = tmp;
                    break;
                }
                else if (current->pNext == nullptr) {
                    current->pNext = new Node<T>(data, _name);
                    break;
                }
                else {
                    current = current->pNext;
                }                
            }
        }
        size++;
    }
   
    void clear() {
        if (size) {
            Node<T>* tmp = Head;
            Head = Head->pNext;
            delete tmp;
            size--;
        }
    }
    
    Node<T>* operator[](const int index)
    {
        int counter = 0;

        Node<T>* current = this->Head;

        while (current != nullptr)
        {
            if (counter == index)
            {
                return current;
            }
            current = current->pNext;
            counter++;
        }
    }

private:
    Node<T>* Head;
};

struct Point {
    Point(string _name = "") {
        name = _name;
    }
    string name;
};

struct Line {
    Line(){}
    Line(Point _p1, Point _p2, string _name) {
        p1 = _p1;
        p2 = _p2;
        name = _name;
    }
    Point p1;
    Point p2;
    string name;
};


class Graph {
public:

    Graph(string args) {
        p1_name = "";
        p2_name = "";
        Line_name = "";
        Graph_build(args);
    }
    
    void Graph_build(string args) {
        string str;
        for (int i = 0; i < args.length(); i++) {            
            if (!Line_name.length()) {
                if (BlackList(args[i])) { str += args[i]; }
                if (args[i] == '(' && str.length()) { Line_name = str; str = ""; }
            }
            else if (!p1_name.length()) {
                if (BlackList(args[i])) { str += args[i]; }
                if (args[i] == ',' && str.length()) { p1_name = str; str = ""; }
            }
            else if (!p2_name.length()) {
                if (BlackList(args[i])) { str += args[i]; }
                if (args[i] == ')' && str.length()) { p2_name = str; str = ""; }
            }

            if (Line_name.length() && p1_name.length() && p2_name.length()) {
                Point p1(p1_name);
                Point p2(p2_name);
                Line line(p1, p2, Line_name);
                Points.push_back(p1, p1_name);
                Points.push_back(p2, p2_name);                
                Lines.push_back(line, Line_name);
                p1_name = "";
                p2_name = "";
                Line_name = "";
            }
        }
    }
    
    bool BlackList(char ch) {
        if (ch == '(' || ch == ',' || ch == ')' || ch == ' ') { return false; }
        return true;
    }

    void print() {
        cout << "\t ---------- список смежности не ориентированный ------------- \n";
        for (int i = 0; i < Points.size; i++) {
            List<Point> Ps;
            string name = Points[i]->data.name;
            string str = name + " -> ";
            
            for (int j = 0; j < Lines.size; j++) {
                Line line = Lines[j]->data;
                if (name == line.p1.name) {
                    Ps.push_back(line.p2.name, line.p2.name);
                }
                else if (name == line.p2.name) {
                    Ps.push_back(line.p1.name, line.p1.name);
                }
            }

            for (int j = 0; j < Ps.size; j++) {
                str += Ps[j]->data.name + " ";
            }            
            cout << str <<endl;
        }

        cout << "\t ---------- список смежности ориентированный ------------- \n";
        for (int i = 0; i < Points.size; i++) {
            List<Point> Ps;
            string name = Points[i]->data.name;
            string str = name + " -> ";

            for (int j = 0; j < Lines.size; j++) {
                Line line = Lines[j]->data;
                if (name == line.p1.name) {
                    Ps.push_back(line.p2.name, line.p2.name);
                }                
            }

            for (int j = 0; j < Ps.size; j++) {
                str += Ps[j]->data.name + " ";
            }
            cout << str << endl;
        }

        cout << "\t ---------- матрица смежности не ориентированный ------------- \n";
        cout << "\t";
        for (int i = 0; i < Points.size; i++) {            
            cout << Points[i]->data.name << "\t";
        }
        cout << endl;
        for (int i = 0; i < Points.size; i++) {            
            cout << Points[i]->data.name + "\t";
            for (int j = 0; j < Points.size; j++) {
                int k = 0;
                for (int h = 0; h < Lines.size; h++) {
                    Line line = Lines[h]->data;
                    if (line.p1.name == Points[i]->data.name && line.p2.name == Points[j]->data.name || line.p2.name == Points[i]->data.name && line.p1.name == Points[j]->data.name) {
                        k = 1;
                    }
                }
                cout << k;
                cout << '\t';
            }
            cout << endl;
        }

        cout << "\t ---------- матрица смежности ориентированный ------------- \n";
        cout << "\t";
        for (int i = 0; i < Points.size; i++) {
            cout << Points[i]->data.name << "\t";
        }
        cout << endl;
        for (int i = 0; i < Points.size; i++) {
            cout << Points[i]->data.name + "\t";
            for (int j = 0; j < Points.size; j++) {
                int k = 0;
                for (int h = 0; h < Lines.size; h++) {
                    Line line = Lines[h]->data;
                    if (line.p1.name == Points[i]->data.name && line.p2.name == Points[j]->data.name) {
                        k = 1;
                    }
                }
                cout << k;
                cout << '\t';
            }
            cout << endl;
        }

        cout << "\t ---------- матрица инциденции не ориентированный ------------- \n";
        cout << "\t";
        for (int i = 0; i < Lines.size; i++) {
            cout << Lines[i]->data.name << "\t";
        }
        cout << endl;
        for (int i = 0; i < Points.size; i++) {
            cout << Points[i]->data.name + "\t";
            for (int j = 0; j < Lines.size; j++) {
                Line line = Lines[j]->data;
                int k = 0;
                if (line.p1.name == Points[i]->data.name || line.p2.name == Points[i]->data.name) {
                    k = 1;
                }
                cout << k;
                cout << '\t';
            }
            cout << endl;
        }

        cout << "\t ---------- матрица инциденции ориентированный ------------- \n";
        cout << "\t";
        for (int i = 0; i < Lines.size; i++) {
            cout << Lines[i]->data.name << "\t";
        }
        cout << endl;
        for (int i = 0; i < Points.size; i++) {
            cout << Points[i]->data.name + "\t";
            for (int j = 0; j < Lines.size; j++) {
                Line line = Lines[j]->data;
                int k = 0;
                if (line.p1.name == Points[i]->data.name) {
                    k = 1;
                }
                else if (line.p2.name == Points[i]->data.name) {
                    k = -1;
                }
                cout << k;
                cout << '\t';
            }
            cout << endl;
        }
    }

private:
    string p1_name;
    string p2_name;
    string Line_name;

    List<Point> Points;
    List<Line> Lines;
};





int main()
{
    setlocale(LC_ALL, "Ru");

    string str;
    getline(cin, str);

    Graph gr(str);
    gr.print();

}

