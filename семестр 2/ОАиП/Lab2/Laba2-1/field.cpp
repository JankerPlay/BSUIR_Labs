#include "field.h"

field::field()
{
    number=time=rate=0;
}
field::field(const field& other)
{
    name = other.name;
    number = other.number;
    time = other.time;
    rate = other.rate;
}
void field::set(QString name, ll number, ll time, ll rate)
{
    this->name = name;
    this->number = number;
    this->time = time;
    this->rate = rate;
}
QString field::get_name() const
{
    return name;
}
ll field::get_number() const
{
    return number;
}
ll field::get_rate() const
{
    return rate;
}
ll field::get_time() const
{
    return time;
}
field& field::operator = (const field& other)
{
    name = other.name;
    number = other.number;
    time = other.time;
    rate = other.rate;
    return *this;
}
