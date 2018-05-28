#include <iostream>

template <typename T>
class AvlTree
{

    T key;
    int height;
    AvlTree *left;
    AvlTree *right;

    static int get_height(AvlTree *p)
    {
        if (p != nullptr)
        {
            return p->height;
        }
        return 0;
    }

    int bfactor()
    {
        return get_height(right) - get_height(left);
    }

    void recount_height(AvlTree *p)
    {
        auto height_l = get_height(p->left);
        auto height_r = get_height(p->right);
        p->height = (height_l > height_r ? height_l : height_r) + 1;
    }

    AvlTree *small_right_rotate(AvlTree *p)
    {
        AvlTree *q = p->left;
        p->left = q->right;
        q->right = p;
        recount_height(p);
        recount_height(q);
        return q;
    }

    AvlTree *small_left_rotate(AvlTree *q)
    {

        AvlTree *p = q->right;
        q->right = p->left;
        p->left = q;
        recount_height(q);
        recount_height(p);

        return p;
    }

    AvlTree *balance()
    {
        recount_height(this);
        if (bfactor() == 2) //big left rotate
        {
            if (right->bfactor() < 0)           
                right = small_right_rotate(right);
            return small_left_rotate(this);
        }

        if (bfactor() == -2) // big right rotate
        {
            if (left->bfactor() > 0)
                left = small_left_rotate(left);
            return small_right_rotate(this);
        }
        return this;
    }

    AvlTree *findmin() //minimal key in subtree
    {
        return left ? left->findmin() : this;
    }

    AvlTree *removemin()
    {
        if (left == nullptr)
            return right;
        left = left->removemin();
        this->balance();
    }

  public:
    AvlTree(T key)
    {
        this->key = key;
        height = 1;
        left = nullptr;
        right = nullptr;
    }

    AvlTree *remove(T key)
    {
        if (this == nullptr)
            return nullptr;
        if (key < this->key)
            left =left->remove(key);
        else if (this->key < key)
            right = right->remove(key);
        else
        {
            AvlTree *min_in_right = right->findmin();
            min_in_right->right = right->removemin();
            min_in_right->left = left;
            
            delete this;
            return min_in_right->balance();
        }
    }
    AvlTree *insert(T key)
    {
        if (this == nullptr)
            return new AvlTree(key);
        if (key >= this->key)
            right = right->insert(key);
        else
            left = left->insert(key);
        return this->balance();
    }
};

int main(int argc, char *argv[])
{
    AvlTree<double> *tree = new AvlTree<double>(25);
    std::cerr << "1\n";
    tree = tree->insert(14);
    std::cerr << "2\n";
    tree = tree->insert(10);
    tree = tree->insert(11);
    std::cerr << "3\n";
    tree = tree->remove(14);
    tree = tree->insert(14);
    tree = tree->insert(13);
    tree = tree->insert(12);

    auto a = 67;
}
