#include <iostream>
#include <algorithm>

using namespace std;

// Cấu trúc dữ liệu của một node trong cây AVL
struct Node {
    int key; // Giá trị của node
    Node* left; // Con trái
    Node* right; // Con phải
    int height; // Chiều cao của node

    Node(int value) : key(value), left(nullptr), right(nullptr), height(1) {}
};

// Hàm trả về chiều cao của một node
int getHeight(Node* node)
{
    return node ? node->height : 0;
}

// Hàm tính hệ số cân bằng của node
int getBalanceFactor(Node* node)
{
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Hàm xoay trái để cân bằng cây
Node* rotateLeft(Node* x)
{
    Node* y = x->right;
    Node* T = y->left;

    // Thực hiện xoay
    y->left = x;
    x->right = T;

    // Cập nhật chiều cao
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; // Trả về node mới sau khi xoay
}

// Hàm xoay phải để cân bằng cây
Node* rotateRight(Node* y)
{
    Node* x = y->left;
    Node* T = x->right;

    // Thực hiện xoay
    x->right = y;
    y->left  = T;

    // Cập nhật chiều cao
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;// Trả về node mới sau khi xoay
}

// Hàm chèn một node mới vào cây AVL
Node* insert(Node* node, int key)
{
    // Nếu cây rỗng, tạo node mới
    if(!node)
    {
        return new Node(key);
    }

    // Chèn vào cây con trái nếu key nhỏ hơn hoặc bằng node hiện tại
    if(key < node->key || key == node->key)
    {
        node->left = insert(node->left, key);
    }

    // Chèn vào cây con phải nêu key lớn hơn node hiện tại
    if(key > node->key)
    {
        node->right = insert(node->right, key);
    }

    // cập nhệt chiều cao của node hiện tại
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Tính hệ số cân bằng của node
    int balanceFactor = getBalanceFactor(node);

    // Trường họp mất cân bằng và thực hiện các loại xoay tương ứng

    // Trường hợp bên trái
    if(balanceFactor > 1 && key < node->left->key)
    {
        return rotateRight(node);
    }

    // Trường hợp bên phải
    if(balanceFactor < -1 && key > node->right->key)
    {
        return rotateLeft(node);
    }

    // Trường hợp trái phải
    if(balanceFactor > 1 && key > node->left->key)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Trường hợp phải trái
    if(balanceFactor < -1 && key < node->right->key)
    {
        node->right  = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node; // Trả về node gốc của cây sau khi chèn
}

// Hàm duyệt cây theo thứ tụ trung tố
void inOrder(Node* root)
{
    if(root)
    {
        inOrder(root->left); // Duyệt cây con trái
        cout << root->key << " "; // In giá trị của node hiện tại
        inOrder(root->right);// Duyệt cây con phải
    }
}

int main()
{
    Node* root = nullptr;
    
    // Mảng các phân tử cần chèn vào cây
    int arr[] = {17, 23, 201, 98, 67, 83, 13, 23, 10, 191, 84, 58};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Chèn từng phần tử vào cây
    for(int i = 0; i < n; i++)
    {
        root = insert(root, arr[i]);
    }

    // In kết quả duyệt cây theo thứ tự trung tố
    cout << "Duyet cay AVL theo thu tu trung to: ";
    inOrder(root);
    cout << endl;

    return 0;
}