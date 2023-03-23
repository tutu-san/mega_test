#pragma once

template <class T>
struct Failable final {
    bool is_failure;
    T value;

    Failable(bool _is_failure = true) : is_failure(_is_failure), value(T()) {}
    Failable(bool _is_failure, const T& _value)
        : is_failure(_is_failure), value(_value) {}
    T* operator*() { return &value; }
    const T* operator*() const { return &value; }
    T* operator->() { return &value; }
    const T* operator->() const { return &value; }
    operator bool() { return !is_failure; }
    bool is_fail() const { return is_failure; }
    bool is_pass() const { return !is_failure; }
    T get() const { return value; }
    T& get_ref() { return value; }
};

template <class T>
static inline Failable<T> fail() {
    return Failable<T>(true);
}

template <class T>
static inline Failable<T> pass(const T& value) {
    return Failable<T>(false, value);
}
