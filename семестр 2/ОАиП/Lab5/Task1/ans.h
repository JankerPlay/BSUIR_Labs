#ifndef ANS_H
#define ANS_H
#include <QString>
#include "queue.h"
class ans
{
private:
    queue<int> que;
public:
    ans() = default;
    void create();
    void clear();
    QString tostr();
    void task();
};

#endif // ANS_H
