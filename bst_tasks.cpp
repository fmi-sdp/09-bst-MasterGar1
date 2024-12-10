#include "iostream"
#include "string"
#include "sstream"

template <typename T>
struct node {
     T data;
     node* left;
     node* right;
     explicit node(const T& data = T(), node* left = nullptr, node* right = nullptr) : data(data), left(left), right(right) {}

     void print() const {
          std::cout<<'('<<data;
          if(left) left->print();
          else std::cout<<"()";
          if(right) right->print();
          else std::cout<<"()";
          std::cout<<')';
     }

     ~node() {
          free(this);
     }
private:
     void free(node<T>* what) {
          if(!what)
               return;

          free(what->left);
          free(what->right);
          delete what;
     }
};

node<int>* tree_from_string(std::stringstream& ss) {
     char c;
     ss >> c;

     if (ss.peek() == ')') {
          while (ss.peek() == ')') {
               ss >> c;
          }
          return nullptr;
     }

     int data = 0;
     while (std::isdigit(ss.peek())) {
          ss >> c;
          data *= 10;
          data += c - '0';
     }
     return new node<int>(data, tree_from_string(ss), tree_from_string(ss));
}

int main() {
     std::string str = "(10(7(2()())(3()()))(12(11()())(15()())))";
     std::stringstream ss(str);

     const node<int>* tree = tree_from_string(ss);
     tree->print();
     delete tree;
     return 0;
}
