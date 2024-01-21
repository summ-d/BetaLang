//
// Created by jack on 1/14/24.
//

export module util.smartptr;

export namespace beta::util::sp{

    template<typename T>
    class [[maybe_unused]] Smartptr{
        T* underlying;

    public:
        Smartptr() = default;
        explicit Smartptr(T* ptr = nullptr) {
            this->underlying = new T;
            this->underlying = ptr;
        }

        Smartptr(const Smartptr<T>& other) {
            this->underlying = new T;
            this->underlying = other.underlying;
        }

        [[maybe_unused]] Smartptr(Smartptr<T>&& other) noexcept {
            this->underlying = new T;
            this->underlying = other.underlying;
        }

        T* raw() const {
            return this->underlying;
        }

        Smartptr<T>& operator=(T*& other) {
            this->underlying = new T;
            this->underlying = other;
            return *this;
        }

        Smartptr<T>& operator=(const Smartptr<T>& other) {
            if(&other != this){
                delete this->underlying;
                this->underlying = new T;
                this->underlying = other.underlying;
            }
            return *this;
        }

        Smartptr<T>& operator=(Smartptr<T>&& other) noexcept {
            delete this->underlying;
            this->underlying = new T;
            this->underlying = other.underlying;
            return *this;
        }

        constexpr bool operator==(T*& other) const {
            return other == this->underlying;
        }

        constexpr bool operator==(const Smartptr<T>& other) const {
            return other.underlying == this->underlying;
        }

        constexpr bool operator==(Smartptr<T>&& other) const noexcept {
            return other.underlying == this->underlying;
        }

        const T& operator[](int idx) const {
            return this->underlying[idx];
        }

        T& operator[](int idx) {
            return this->underlying[idx];
        }

        const T* operator->() const {
            return this->underlying;
        }

        T* operator->() {
            return this->underlying;
        }

        const T& operator*() const {
            return *this->underlying;
        }

        T& operator*() {
            return *this->underlying;
        }

        explicit operator T*() const {
            return this->underlying;
        }

        ~Smartptr() { delete this->underlying; }
    };

}
