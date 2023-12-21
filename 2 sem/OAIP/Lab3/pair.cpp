template <typename First, typename Second>
struct Pair {
    First first;
    Second second;

    Pair() : first(), second() {}

    Pair(const First& first, const Second& second)
        : first(first), second(second) {}

    void swap(Pair<First, Second>& other) {
        First buf1 = first;
        first = other.first;
        other.first = buf1;
        Second buf2 = second;
        second = other.second;
        other.second = buf2;
    }

    Pair<First, Second>& operator=(const Pair<First, Second>& other) {
        if (this != &other) {
            first = other.first;
            second = other.second;
        }
        return *this;
    }
};

template <typename First, typename Second>
Pair<First, Second> make_pair(const First& first, const Second& second) {
    return Pair<First, Second>(first, second);
}
