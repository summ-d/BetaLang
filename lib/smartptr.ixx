//
// Created by jack on 1/14/24.
//

export module util.smartptr;

import util.extras;

export namespace beta::util::sp{

    template<typename T>
    class [[maybe_unused]] Smartptr{
        T* underlying;

    public:
        Smartptr() = default;

        explicit Smartptr(T* ptr) {
            this->underlying = ptr;
        }

        explicit Smartptr(std::nullptr_t np){
            this->underlying = np;
        }

        Smartptr(const Smartptr<T>& other) {
            this->underlying = other.underlying;
        }

        Smartptr(Smartptr<T>&& other) noexcept{
            tps::swap(this->underlying, other.underlying);
        }


        Smartptr<T>& operator=(T* other) {
            this->underlying = other;
            return *this;
        }

        Smartptr<T>& operator=(const Smartptr<T>& other) {
            if(&other != this){
                this->underlying = other.underlying;
            }
            return *this;
        }

        Smartptr<T>& operator=(Smartptr<T>&& other) noexcept {
            tps::swap(this->underlying, other.underlying);
            other.underlying = nullptr;
            return *this;
        }

        Smartptr<T>& operator=(std::nullptr_t np) {
            this->underlying = np;
            return *this;
        }

        T& operator*(){
            return *this->underlying;
        }

        const T& operator*() const{
            return *this->underlying;
        }

        T*& operator->(){
            return this->underlying;
        }

        const T*& operator->() const {
            return this->underlying;
        }


        explicit operator T*(){
            return this->underlying;
        }

        explicit operator std::nullptr_t() {
            return nullptr;
        }

        ~Smartptr() { delete this->underlying; }
    };

}
