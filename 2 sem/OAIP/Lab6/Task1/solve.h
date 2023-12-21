#include <QString>
#include <QTreeWidget>
#include "bst.h"
#include "mainwindow.h"
extern QString preOrderOut;
extern QString postOrderOut;
extern QString inOrderOut;
class Solve : public AVLTree<int, QString>
{
private:
    void preOrder(Node *);
    void postOrder(Node *);
    void inOrder(Node *);
public:
    friend class MainWindow;
    Solve() = default;
    static void addNode(AVLTree<int, QString>::Node *node, QTreeWidgetItem *parentItem)
    {
        if (!node) return;
        QTreeWidgetItem *item = new QTreeWidgetItem(parentItem, QStringList(QString::number(node->key)));
        addNode(node->left, item);
        addNode(node->right, item);
    }
    void DeleteBranchWithKey(int key)
    {
        root = removeSubtree(root, key);
    }
    void preOrder()
    {
        preOrder(root);
    }
    void postOrder()
    {
        postOrder(root);
    }
    void inOrder()
    {
        inOrder(root);
    }
};
void Solve::inOrder(Node *node)
{
    if (!node)
        return;
    inOrder(node->left);
    inOrderOut.push_back(QString::number(node->key) + " ");
    inOrder(node->right);
}
void Solve::postOrder(Node *node)
{
    if (!node)
        return;
    postOrder(node->left);
    postOrder(node->right);
    postOrderOut.push_back(QString::number(node->key) + " ");
}
void Solve::preOrder(Node *node)
{
    if (!node)
        return;
    preOrderOut.push_back(QString::number(node->key) + " ");
    preOrder(node->left);
    preOrder(node->right);
}
