#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QElapsedTimer>
#include "qcustomplot.h"
#include <bits/stdc++.h>
template <typename Key, typename Value>
struct Node
{
    Key key;
    Value value;
    bool is_used;
    Node() : key(), value(), is_used(false) {}
    Node(const Key& k, const Value& v) : key(k), value(v), is_used(true) {}
};
template <typename Key, typename Value, size_t K = 2048>
class HashTable
{
private:
    Node<const Key, Value> *base;
    size_t _size;
    size_t hash(const Key &);
public:
    HashTable() : _size(0), base(new Node<const Key, Value>[K]{}) {}
    HashTable(const HashTable &);
    HashTable(HashTable &&) noexcept;
    HashTable &operator=(const HashTable &);
    HashTable &operator=(HashTable &&) noexcept;
    void insert(const Key &, const Value &);
    void erase(const Key &);
    Value &operator[](const Key &);
    bool contains(const Key &);
    void clear();
};
template<typename Key, typename Value, size_t K>
HashTable<Key, Value, K>& HashTable<Key, Value, K>::operator=(HashTable&& other) noexcept
{
    if (this != &other) {
        delete[] base;
        base = other.base;
        _size = other._size;
        other.base = nullptr;
        other.size_ = 0;
    }
    return *this;
}
template<typename Key, typename Value, size_t K>
HashTable<Key, Value, K>::HashTable(HashTable&& other) noexcept : base(nullptr), _size(0)
{
    *this = std::move(other);
}
template<typename Key, typename Value, size_t K>
HashTable<Key, Value, K> &HashTable<Key, Value, K>::operator=(const HashTable &other)
{
    if (this != &other)
    {
        typename std::aligned_storage<sizeof(Node<const Key, Value>), alignof(Node<const Key, Value>)>::type buffer[K];
        std::memcpy(buffer, other.base, sizeof(Node<const Key, Value>) * K);
        std::swap(base, reinterpret_cast<Node<const Key, Value>*>(buffer));
        _size = other._size;
    }
    return *this;
}
template<typename Key, typename Value, size_t K>
HashTable<Key, Value, K>::HashTable(const HashTable &other)
{
    base = reinterpret_cast<Node<const Key, Value>*>(new int8_t[sizeof(Node<const Key, Value>) * K]{});
    for (size_t i = 0; i < K; ++i)
    {
        new (base + i) Node<const Key, Value>(other.base[i]);
    }
    _size = other._size;
}
template<typename Key, typename Value, size_t K>
void HashTable<Key, Value, K>::clear()
{
    for (size_t i = 0; i < K; ++i)
    {
        if (base[i].isUsed)
        {
            base[i].~Node();
            _size--;
        }
    }
    delete[] reinterpret_cast<int8_t*>(base);
    base = nullptr;
}
template<typename Key, typename Value, size_t K>
bool HashTable<Key, Value, K>::contains(const Key &key)
{
    size_t i = hash(key);
    size_t j = i;
    do
    {
        if (!base[j].is_used)
            return false;
        else if (base[j].is_used && base[j].key == key)
            return true;
        ++j;
        j %= K;
    }
    while (j != i);
    return false;
}
template<typename Key, typename Value, size_t K>
Value &HashTable<Key, Value, K>::operator[](const Key &key)
{
    size_t i = hash(key);
    size_t j = i;
    do {
        if (!base[j].is_used)
        {
            new (base + j) Node(key, Value());
            _size++;
            return base[j].value;
        }
        else if (base[j].is_used && base[j].key == key)
            return base[j].value;
        ++j;
        j %= K;
    }
    while (j != i);
    return *(new Value());
}
template<typename Key, typename Value, size_t K>
void HashTable<Key, Value, K>::erase(const Key &key)
{
    size_t i = hash(key);
    size_t j = i;
    do
    {
        if (!base[j].isUsed)
            return;
        else if (base[j].isUsed && base[j].key == key)
        {
            base[j].value.~Value();
            base[j].isUsed = false;
            _size--;
            return;
        }
        ++j;
        j %= K;
    }
    while (i != j);
}
template<typename Key, typename Value, size_t K>
size_t HashTable<Key, Value, K>::hash(const Key &key)
{
    double A = (sqrt(5) - 1) / 2.0;
    return static_cast<size_t>(K * fmod((std::hash<Key>{}(key) * A), 1)) % K;
}
template<typename Key, typename Value, size_t K>
void HashTable<Key, Value, K>::insert(const Key &key, const Value &value)
{
    if (_size == K)
        throw std::out_of_range("not enough space in table");
    size_t i = hash(key);
    size_t j = i;
    do {
        if (!base[j].isUsed)
        {
            new (base + j) Node(key, value);
            _size++;
            base[j].isUsed = true;
            return;
        }
        else if (base[j].key == key && base[j].isUsed)
        {
            base[j].value = value;
            return;
        }
        ++j;
        j %= K;
    }
    while (i != j);
}
HashTable<int, int, 16> t16;
HashTable<int, int, 64> t64;
HashTable<int, int, 128> t128;
HashTable<int, int, 2048> t2048;
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::ShowGraphic16()
{
    QElapsedTimer timer;
    QCustomPlot* plot = new QCustomPlot(this);
    QVector<double> xData, yData;
    for (int i = 0; i < 500; ++i)
    {
        timer.start();
        t16[i];
        double elapsed = timer.nsecsElapsed() / 1000000.0;
        xData.append(i);
        yData.append(elapsed);
    }
    QCPGraph *graph = plot->addGraph();
    graph->setData(xData, yData);
    plot->xAxis->setRange(0, 500);
    plot->yAxis->setRange(0, 0.004);
    plot->legend->setVisible(true);
    plot->graph(0)->setName("Таблица на 16 элементов");
    plot->resize(400, 350);
    plot->move(QPoint(20, 20));
    plot->replot();
    plot->show();
}
void MainWindow::ShowGraphic64()
{
    QElapsedTimer timer;
    QCustomPlot* plot = new QCustomPlot(this);
    QVector<double> xData, yData;
    for (int i = 0; i < 1000; ++i)
    {
        timer.start();
        t64[i];
        double elapsed = timer.nsecsElapsed() / 1000000.0;
        xData.append(i);
        yData.append(elapsed);
    }
    QCPGraph *graph = plot->addGraph();
    graph->setData(xData, yData);
    plot->xAxis->setRange(0, 1000);
    plot->yAxis->setRange(0, 0.01);
    plot->legend->setVisible(true);
    plot->graph(0)->setName("Таблица на 64 элемента");
    plot->resize(400, 350);
    plot->move(QPoint(440, 20));
    plot->replot();
    plot->show();
}
void MainWindow::ShowGraphic128()
{
    QElapsedTimer timer;
    QCustomPlot* plot = new QCustomPlot(this);
    QVector<double> xData, yData;
    for (int i = 0; i < 2000; ++i)
    {
        timer.start();
        t128[i];
        double elapsed = timer.nsecsElapsed() / 1000000.0;
        xData.append(i);
        yData.append(elapsed);
    }
    QCPGraph *graph = plot->addGraph();
    graph->setData(xData, yData);
    plot->xAxis->setRange(0, 2000);
    plot->yAxis->setRange(0, 0.02);
    plot->legend->setVisible(true);
    plot->graph(0)->setName("Таблица на 128 элементов");
    plot->resize(400, 350);
    plot->move(QPoint(20, 390));
    plot->replot();
    plot->show();
}
void MainWindow::ShowGraphic2048()
{
    QElapsedTimer timer;
    QCustomPlot* plot = new QCustomPlot(this);
    QVector<double> xData, yData;
    for (int i = 0; i < 10000; ++i)
    {
        timer.start();
        t2048[i];
        double elapsed = timer.nsecsElapsed() / 1000000.0;
        xData.append(i);
        yData.append(elapsed);
    }
    QCPGraph *graph = plot->addGraph();
    graph->setData(xData, yData);
    plot->xAxis->setRange(0, 10000);
    plot->yAxis->setRange(0, 0.04);
    plot->legend->setVisible(true);
    plot->graph(0)->setName("Таблица на 2048 элементов");
    plot->resize(400, 350);
    plot->move(QPoint(440, 390));
    plot->replot();
    plot->show();
}
void MainWindow::on_pushButton_graphics_clicked()
{
    ShowGraphic16();
    ShowGraphic64();
    ShowGraphic128();
    ShowGraphic2048();
}