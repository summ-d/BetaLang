//
// Created by jack on 1/14/24.
//

#ifndef COMPILER_SMARTPTR_HPP
#define COMPILER_SMARTPTR_HPP

namespace beta::util::sp{

    template<typename T>
    class [[maybe_unused]] Smartptr{
        T* underlying;

    public:
        Smartptr() = default;
        explicit Smartptr(T* ptr = nullptr);
        Smartptr(const Smartptr<T>& other);
        [[maybe_unused]] Smartptr(Smartptr<T>&& other) noexcept;

        T* raw() const;

        Smartptr<T>& operator=(T*& other);
        Smartptr<T>& operator=(const Smartptr<T>& other);
        Smartptr<T>& operator=(Smartptr<T>&& other) noexcept;

        constexpr bool operator==(T*& other) const;
        constexpr bool operator==(const Smartptr<T>& other) const;
        constexpr bool operator==(Smartptr<T>&& other) const noexcept;

        const T& operator[](int idx) const;
        T& operator[](int idx);

        const T* operator->() const;
        T* operator->();

        const T& operator*() const;
        T& operator*();

        ~Smartptr() { delete this->underlying; }
    };

}



#endif //COMPILER_SMARTPTR_HPP
