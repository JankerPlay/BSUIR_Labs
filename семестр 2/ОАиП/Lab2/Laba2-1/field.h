#ifndef FIELD_H
#define FIELD_H
#include "bibl.h"
class field
{
private:
    QString name;
    ll number;
    ll time;
    ll rate;
public:
    field();
        field(const field&);
        void set(QString, ll, ll, ll);
        QString get_name() const;
        ll get_number() const;
        ll get_time() const;
        ll get_rate() const;
        field& operator=(const field&);
};


#endif
