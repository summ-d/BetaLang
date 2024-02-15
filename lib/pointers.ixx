//
// Created by jack on 2/12/24.
//

export module util.pointers;

import util.utility;

namespace beta::util::ptr {

    export template<typename T>
    class UniquePtr{
        T* _int;

        public:

        UniquePtr(): _int(nullptr){}

        UniquePtr(T* ptr): _int(ptr){}

        UniquePtr(const UniquePtr<T>&) = delete;

        UniquePtr(UniquePtr<T>&& other) noexcept {
            fn::swap(other._int, this->_int);
        }

        UniquePtr<T>& operator=(tps::nullptr_t np){
            this->_int = np;
            return *this;
        }

        UniquePtr<T>& operator=(T* ptr) {
            this->_int = ptr;
            return *this;
        }

        UniquePtr<T>& operator=(const UniquePtr<T>&) = delete;

        UniquePtr<T>& operator=(UniquePtr<T>&& other) noexcept {
            fn::swap(other._int, this->_int);
            return *this;
        }

        explicit operator bool() {
            return this->_int == nullptr;
        }

        explicit operator T*(){
            return this->_int;
        }

        T* operator->(){
            return this->_int;
        }

        const T* operator->() const {
            return this->_int;
        }

        T& operator*(){
            return *this->_int;
        }

        const T& operator*() const {
            return *this->_int;
        }

        UniquePtr<T>& swap(UniquePtr<T>& other){
            fn::swap(other._int, this->_int);
            other._int = nullptr;
            return *this;
        }


        inline T* raw(){
            return this->_int;
        }

        ~UniquePtr() {
            delete this->_int;
        }
    };

    template<typename T>
    class UniquePtr<T[]> {
        T* _int = nullptr;
        tps::size_t _len = 0;

    public:

        UniquePtr(): _int(nullptr), _len(0){}

        template<tps::size_t N>
        explicit UniquePtr(T (&ptr)[N]): _int(ptr), _len(N){}

        UniquePtr(const UniquePtr<T[]>&) = delete;

        UniquePtr(UniquePtr<T[]>&& other) noexcept {
            fn::swap(other._int, this->_int);
            fn::swap(other._len, this->_len);
        }

        UniquePtr<T[]>& operator=(tps::nullptr_t np){
            this->_int = np;
            return *this;
        }

        UniquePtr<T[]>& operator=(T* ptr) {
            this->_int = ptr;
            return *this;
        }

        UniquePtr<T[]>& operator=(const UniquePtr<T>&) = delete;

        UniquePtr<T[]>& operator=(UniquePtr<T>&& other) noexcept {
            fn::swap(other._int, this->_int);
            return *this;
        }

        explicit operator bool() {
            return this->_int == nullptr;
        }

        explicit operator T*(){
            return this->_int;
        }

        T* operator->(){
            return this->_int;
        }

        const T* operator->() const {
            return this->_int;
        }

        T& operator*(){
            return *this->_int;
        }

        const T& operator*() const {
            return *this->_int;
        }

        const T& operator[](int idx) const requires(idx < this->_len){
            return this->_int[idx];
        }

        T& operator[](int idx) requires(idx < this->_len) {
            return this->_int[idx];
        }

        inline tps::size_t length(){
            return this->_len;
        }

        inline T* raw(){
            return this->_int;
        }

        ~UniquePtr() {
            delete this->_int;
        }
    };

    export template<typename T>
    class SharedPtr {
        tps::size_t _refCount = 0;
        tps::size_t _sId = 0;

        T* _ptr = nullptr;

        public:

        SharedPtr() = default;

        explicit SharedPtr(T* data): _ptr(data), _refCount(1), _sId(0) {}

        SharedPtr(const SharedPtr<T>& other): _ptr(other._ptr), _sId(other._sId + 1), _refCount(other._refCount++) {}

        SharedPtr(SharedPtr<T>&& other) noexcept {
            fn::swap(other._ptr, this->_ptr);
            other._ptr = nullptr;
            this->_refCount = other._refCount;
            this->_sId = other._sId;
        }

        SharedPtr<T>& operator=(tps::nullptr_t np) {
            if(this->_refCount == this->_sId) {
                delete this->_ptr;
                this->_ptr = np;
            }
            this->_refCount = 0;
            this->_sId--;
            this->_ptr = np;
            return *this;
        }

        SharedPtr<T>& operator=(T* data) {
            if(this->_refCount == this->_sId) {
                delete this->_ptr;
                this->_ptr = nullptr;
            }
            this->_refCount = 0;
            this->_sId--;
            this->_ptr = data;
            return *this;
        }

        SharedPtr<T>& operator=(const SharedPtr<T>& other) {
            if(&other != this) {
                if(this->_refCount == this->_sId) {
                    delete this->_ptr;
                    this->_ptr = nullptr;
                }
                this->_ptr = other._ptr;
                this->_sId = other._sId + 1;
                this->_refCount = other._refCount++;
            }
            return *this;
        }

        SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept {
            if(this->_refCount == this->_sId) {
                delete this->_ptr;
                this->_ptr = nullptr;
            }
            fn::swap(this->_ptr, other._ptr);
            fn::swap(this->_refCount, other._refCount);
            this->_sId = 0;
        }

        const T& operator*() const {
            return this->_ptr;
        }

        T& operator*(){
            return this->_ptr;
        }

        T* operator->(){
            return this->_ptr;
        }

        const T* operator->() const {
            return this->_ptr;
        }

        const T* raw() const {
            return this->_ptr;
        }

        T* raw(){
            return this->_ptr;
        }

        explicit operator bool() {
            return this->_ptr != nullptr;
        }

        explicit operator T*() {
            return this->_ptr;
        }

        ~SharedPtr() {
            //this->_refCount--;
            if(this->_refCount == this->_sId){
                delete this->_ptr;
            }
        }

    };

    export template<typename T>
    class SharedPtr<T[]> {
        tps::size_t _refCount = 0;
        tps::size_t _sId = 0;

        T* _ptr = nullptr;

        tps::size_t _len = 0;

    public:

        SharedPtr() = default;

        template<tps::size_t N>
        explicit SharedPtr(const T(&data)[N]): _ptr(data), _refCount(1), _sId(0), _len(N) {}

        SharedPtr(const SharedPtr<T[]>& other): _ptr(other._ptr), _sId(other._sId + 1), _refCount(other._refCount++), _len(other._len) {}

        SharedPtr(SharedPtr<T[]>&& other) noexcept {
            fn::swap(other._ptr, this->_ptr);
            fn::swap(other._len, this->_len);
            other._ptr = nullptr;
            this->_refCount = other._refCount;
            this->_sId = other._sId;
        }

        SharedPtr<T[]>& operator=(tps::nullptr_t np) {
            if(this->_refCount == this->_sId) {
                delete this->_ptr;
                this->_ptr = np;
            }
            this->_refCount = 0;
            this->_sId--;
            this->_ptr = np;
            this->_len = 0;
            return *this;
        }

        template<tps::size_t N>
        SharedPtr<T[]>& operator=(const T (&data)[N]) {
            if(this->_refCount == this->_sId) {
                delete this->_ptr;
                this->_ptr = nullptr;
            }
            this->_refCount = 0;
            this->_sId--;
            this->_ptr = data;
            this->_len = N;
            return *this;
        }

        SharedPtr<T[]>& operator=(const SharedPtr<T[]>& other) {
            if(&other != this) {
                if(this->_refCount == this->_sId) {
                    delete this->_ptr;
                    this->_ptr = nullptr;
                }
                this->_ptr = other._ptr;
                this->_sId = other._sId + 1;
                this->_refCount = other._refCount++;
                this->_len = other._len;
            }
            return *this;
        }

        SharedPtr<T[]>& operator=(SharedPtr<T[]>&& other) noexcept {
            if(this->_refCount == this->_sId) {
                delete this->_ptr;
                this->_ptr = nullptr;
            }
            fn::swap(this->_ptr, other._ptr);
            fn::swap(this->_refCount, other._refCount);
            fn::swap(this->_len, other._len);
            this->_sId = 0;
        }

        const T& operator*() const {
            return this->_ptr;
        }

        T& operator*(){
            return this->_ptr;
        }

        T* operator->(){
            return this->_ptr;
        }

        const T* operator->() const {
            return this->_ptr;
        }

        const T* raw() const {
            return this->_ptr;
        }

        T* raw(){
            return this->_ptr;
        }

        explicit operator bool() {
            return this->_ptr != nullptr;
        }

        explicit operator T*() {
            return this->_ptr;
        }

        T operator[](int idx) requires(idx < this->_len) {
            return this->_ptr[idx];
        }

        ~SharedPtr() {
            //this->_refCount--;
            if(this->_sId == this->_refCount){
                delete this->_ptr;
            }

        }
    };


}