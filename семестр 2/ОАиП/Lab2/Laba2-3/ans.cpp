#include "ans.h"
#include "customVector.h"
#include "customStack.h"

int ans::priority(std::string alpha) {
    char alp = alpha[0];
    if (alp == '+' || alp == '-')
        return 1;
    if (alp == '*' || alp == '/' || alp == '%')
        return 2;
    return 0;
}

std::string ans::convert(customVector1 <std::string> infix) {
    int i = 0;
    std::string ans;
    Node* head = nullptr;
    customStack s;
    std::string ps;
    while (i != infix.size())
    {

        ps = infix[i];

        if (ps[0] == '-' and ps.size() != 1)
        {
            ps.replace(0, 1, "0");//вот здесь на 0 заменяю
        }

        if (ps >= "0" && ps <= "99999999999999999")
        {
            ans += infix[i];
            ans += " ";
            i++;
        }


        else if (ps == "(") {
            std::string str;
            str += infix[i];
            s.push(&head, str);
            i++;

        }

        else if (ps == ")") {
            while (s.top(head) != "(")
               ans += s.pop(head, &head);
            s.pop(head, &head);
            i++;
        }
        else {
            while (!s.isEmpty(&head) && priority(ps) <= priority(s.top(head))) {
                ans += s.pop(head, &head);
            }
            std::string str;
            str += infix[i];
            str += " ";
            s.push(&head, str);
            i++;
        }

    }
    while (!s.isEmpty(&head)) {
        ans += s.pop(head, &head);
    }
    return ans;
}

long double ans::result(std::string infix) {
    std::string inf;
    infix.erase(std::remove(infix.begin(), infix.end(), ' '), infix.end());

    std::string get_;
    std::string arr;

    customVector1<std::string> vector;

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
    if (!arr.empty()) vector.push_back(arr);
    std::string get_post = convert(vector);

    Node* head = nullptr;
    customStack container;
    customVector1<std::string> v;
    std::string var;


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

    customVector1<std::string> reversed;
    for (int i = v.size() - 1; i >= 0; --i) {

        reversed.push_back(v[i]);
    }

    for (int i = 0; i < reversed.size(); ++i) {

        container.push(&head, reversed[i]);
    }

    long double ans;

    customVector1<std::string> storage;
    while (!(container.isEmpty(&head)))
    {
        std::string get_ar = container.pop(head,&head);

        if (get_ar == "+")
        {
            ans = atof(storage[storage.size() - 2].c_str()) + atof(storage[storage.size() - 1].c_str());
            storage.pop_back();
            storage.pop_back();
            storage.push_back(std::to_string(ans));
        }
        else if (get_ar == "-")
        {
            ans = atof(storage[storage.size() - 2].c_str()) - atof(storage[storage.size() - 1].c_str());
            storage.pop_back();
            storage.pop_back();
            storage.push_back(std::to_string(ans));
        }
        else if (get_ar == "*")
        {
            ans = atof(storage[storage.size() - 2].c_str()) * atof(storage[storage.size() - 1].c_str());
            storage.pop_back();
            storage.pop_back();
            storage.push_back(std::to_string(ans));
        }
        else if (get_ar == "/")
        {
            ans = atof(storage[storage.size() - 2].c_str()) / atof(storage[storage.size() - 1].c_str());
            storage.pop_back();
            storage.pop_back();
            storage.push_back(std::to_string(ans));
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
    long double result = atof(storage[0].c_str());
    return result;
}

std::string ans::getPost(std::string infix) {
    std::string inf;
    infix.erase(std::remove(infix.begin(), infix.end(), ' '), infix.end());

    std::string get_;
    std::string arr;

    customVector1<std::string> vector;

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
    if (!arr.empty()) vector.push_back(arr);
    std::string get_post = convert(vector);
    return get_post;
}
