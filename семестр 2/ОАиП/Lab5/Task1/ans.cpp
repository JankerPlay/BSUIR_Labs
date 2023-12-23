#include "ans.h"
#include <QString>
#include <string>
#include <sstream>
void ans::create()
{
    que.clear();
    for (int i = 0; i < 25; i++)
    {
        que.push(rand() % 25);
    }
}
void ans::clear()
{
    que.clear();
}
QString ans::tostr()
{
    std::string line;
    auto qx = que;
    int x = qx.size();
    for (int i = 0; i < x; i++)
    {
        std::stringstream ss;
        ss << qx.front();
        line += ss.str() + " ";
        qx.pop();
    }
    QString qwe = QString::fromStdString(line);
    return qwe;
}
void ans::task()
{
que.removeDuplicates();
}
