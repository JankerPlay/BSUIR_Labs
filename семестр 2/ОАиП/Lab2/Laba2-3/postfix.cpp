#include "postfix.h"
#include "customStack.h"
#include "customVector.h"
ll postfix::priority(string alpha)
{
    char alp = alpha[0];
    if (alp == '+' or alp == '-')
        return 1;
    if (alp == '*' or alp == '/' or alp == '%')
        return 2;
    return 0;
}
string postfix::convert(CV<string> infix) {
    ll i = 0;
    string postfix;
    Node* head = nullptr;
    CS s;
    string ps;
    while (i != infix.size())
    {
        ps = infix[i];
        if (ps[0] == '-' and ps.size() != 1)
        {
            ps.replace(0, 1, "0");
        }
        if (ps >= "0" and ps <= "99999999999999999")
        {
            postfix += infix[i];
            postfix += " ";
            i++;
        }
        else if (ps == "(")
        {
            string str;
            str += infix[i];
            s.push(&head, str);
            i++;
        }
        else if (ps == ")")
        {
            while (s.top(head) != "(")
                postfix += s.pop(head, &head);
            s.pop(head, &head);
            i++;
        }
        else
        {
            while (!s.isEmpty(&head) && priority(ps) <= priority(s.top(head))) {
                postfix += s.pop(head, &head);
            }
            string str;
            str += infix[i];
            str += " ";
            s.push(&head, str);
            i++;
        }
    }
    while (!s.isEmpty(&head))
    {
        postfix += s.pop(head, &head);
    }
    return postfix;
}
ld postfix::result(std::string infix) {
    string inf;
    infix.erase(std::remove(infix.begin(), infix.end(), ' '), infix.end());
    string get_;
    string arr;
    CV<string> vector;
    for (ll i = 0; i < infix.size(); ++i)
    {
        if (infix[i] != ' ')
        {
            if (infix[i] == '-' and i == 0 or infix[i] == '-' and infix[i-1] == '(')
            {
                arr += infix[i];
            }
            else if (infix[i] == '(')
            {
                get_ += infix[i];
                vector.push_back(get_);
                get_.clear();
            }
            else if (infix[i] == ')')
            {
                if (!arr.empty())
                {
                    vector.push_back(arr);
                    arr.clear();
                }
                get_ += infix[i];
                vector.push_back(get_);
                get_.clear();
            }
            else
            {
                if (infix[i] != '+' and infix[i] != '-' and infix[i] != '*' and infix[i] != '/' and infix[i] != '%')
                {
                    arr += infix[i];
                }
                else
                {
                    if (!arr.empty())
                    {
                        vector.push_back(arr);
                        arr.clear();
                    }
                    get_ += infix[i];
                    vector.push_back(get_);
                    get_.clear();
                }
            }
        }
    }
    if (!arr.empty()) vector.push_back(arr);
    string get_post = convert(vector);
    Node* head = nullptr;
    CS container;
    CV<string> v;
    string var;
    for (char i : get_post)
    {
        if (i != ' ')
        {
            var += i;
        }
        else
        {
            v.push_back(var);
            var.clear();
        }
    }
    CV<string> reversed;
    for (ll i = v.size() - 1; i >= 0; --i)
    {
        reversed.push_back(v[i]);
    }
    for (ll i = 0; i < reversed.size(); ++i)
    {
        container.push(&head, reversed[i]);
    }
    ld ans;
    CV<string> storage;
    while (!(container.isEmpty(&head)))
    {
        string get_ar = container.pop(head,&head);

        if (get_ar == "+")
        {
            ans = atof(storage[storage.size() - 2].c_str()) + atof(storage[storage.size() - 1].c_str());
            storage.pop_back();
            storage.pop_back();
            storage.push_back(to_string(ans));
        }
        else if (get_ar == "-")
        {
            ans = atof(storage[storage.size() - 2].c_str()) - atof(storage[storage.size() - 1].c_str());
            storage.pop_back();
            storage.pop_back();
            storage.push_back(to_string(ans));
        }
        else if (get_ar == "*")
        {
            ans = atof(storage[storage.size() - 2].c_str()) * atof(storage[storage.size() - 1].c_str());
            storage.pop_back();
            storage.pop_back();
            storage.push_back(to_string(ans));
        }
        else if (get_ar == "/")
        {
            ans = atof(storage[storage.size() - 2].c_str()) / atof(storage[storage.size() - 1].c_str());
            storage.pop_back();
            storage.pop_back();
            storage.push_back(to_string(ans));
        }
        else if (get_ar == "%")
        {
            ans = atoi(storage[storage.size() - 2].c_str()) % atoi(storage[storage.size() - 1].c_str());
            storage.pop_back();
            storage.pop_back();
            storage.push_back(std::to_string(ans));
        }
        else
        {
            storage.push_back(get_ar);
        }
    }
    ld result = atof(storage[0].c_str());
    return result;
}
    string postfix::getPost(string infix) {
    string inf;
    infix.erase(std::remove(infix.begin(), infix.end(), ' '), infix.end());
    string get_;
    string arr;
    CV<string> vector;
    for (int i = 0; i < infix.size(); ++i)
    {
        if (infix[i] != ' ') {

            if (infix[i] == '-' and i == 0 or infix[i] == '-' and infix[i-1] == '(')
            {
                arr += infix[i];
            }
            else if (infix[i] == '(')
            {
                get_ += infix[i];
                vector.push_back(get_);
                get_.clear();
            }
            else if (infix[i] == ')')
            {
                if (!arr.empty()) {
                    vector.push_back(arr);
                    arr.clear();
                }
                get_ += infix[i];
                vector.push_back(get_);
                get_.clear();
            }
            else
            {
                if (infix[i] != '+' and infix[i] != '-' and infix[i] != '*' and infix[i] != '/' and infix[i] != '%')
                {
                    arr += infix[i];
                }
                else
                {
                    if (!arr.empty()) {
                        vector.push_back(arr);
                        arr.clear();
                    }
                    get_ += infix[i];
                    vector.push_back(get_);
                    get_.clear();
                }
            }
        }
    }
    if (!arr.empty())
        vector.push_back(arr);
    return convert(vector);
}
