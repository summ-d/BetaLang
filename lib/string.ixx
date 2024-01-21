//
// Created by jack on 1/14/24.
//

export module util.string;

// for sAllocator<T>
import util.allocators;

// for strcmp, size
import util.extras;

export namespace beta::util {

    /**
     * Specialization of <code>memcpy</code> for strings
     * @param src source string
     * @param dest destination string
     * @param size size of <code>src</code>
    */
    inline void copystr(const char* src, char *dest, int size) {
        for(int i = 0; i < size; i++) dest[i] = src[i];
    }

    /**
     * Specialization of <code>memcpy</code> for strings
     * @param src source string
     * @param dest destination string
     * @param size size of <code>src</code>
     * @param offset the offset of the destination string
    */
    inline void copystr(const char* src, char* dest, int size, int offset) {
        for(int i = offset; i < size; i++) dest[i] = src[i - offset];
    }

    /**
     * @class String&lt;St, Al&gt;
     * @brief Generic String class
    */
    template<typename St, typename Al = alloc::sAllocator<St>>
    class [[maybe_unused]] String {
        using str = St *; ///< type alias for a <code>St</code> pointer

        str underlying; ///< underlying string

        Al allocator; ///< internal memory allocator

        tps::size_t len = 0; ///< internal length for O(1) access

    public:
        /**
         * Default construct
        */
        String() = default;

        /**
         * Basic String constructor
         * @param s the raw string
        */
        [[maybe_unused]] explicit String(const St*& s) {
            this->len = strlen(s);
            this->underlying = this->allocator.allocate(this->len);
            copystr(s, this->underlying, this->len);

        }

        [[maybe_unused]] explicit String(const St s[]) {
            this->len = strlen(s);
            this->underlying = this->allocator.allocate(this->len);
            copystr(s, this->underlying, this->len);
        }

        /**
         *
        */
        [[maybe_unused]] String(const String<St, Al> &other) {
            this->len = tps::strlen(other.underlying);
            this->underlying = this->allocator.allocate(this->len);
            copystr(other.underlying, this->underlying, this->len);
        }

        [[maybe_unused]] String(String<St, Al>&& other) noexcept {
            this->len = tps::strlen(other.underlying);
            this->underlying = this->allocator.allocate(this->len);
            copystr(other.underlying, this->underlying, this->len);
        }

        String<St, Al>& operator=(const St*& str) {
            this->len = tps::strlen(str);
            this->underlying = this->allocator.allocate(this->len);
            copystr(str, this->underlying, this->len);
            return *this;
        }

        String<St, Al>& operator=(const St* str){
            this->len = tps::strlen(str);
            this->underlying = this->allocator.allocate(this->len);
            copystr(str, this->underlying, this->len);
            return *this;
        }

        String<St, Al>& operator=(const String<St, Al>& other) {
            if(&other != this){
                this->len = tps::strlen(other.underlying);
                this->underlying = this->allocator.allocate(this->len);
                copystr(other.underlying, this->underlying, this->len);
            }
            return *this;
        }

        String<St, Al>& operator=(String<St, Al>&& other) noexcept {
            this->len = tps::strlen(other.underlying);
            this->underlying = this->allocator.allocate(this->len);
            copystr(other.underlying, this->underlying, this->len);
        }

        str s_raw() const {
            return this->underlying;
        }

        const St& operator[](int idx) const {
            if(idx < this->len && idx > 0) {
                return this->underlying[idx];
            }
            else return this->underlying[this->len - 1];
        }

        St& operator[](int idx) {
            if(idx < this->len && idx > 0){
                return this->underlying[idx];
            }
            else return this->underlying[this->len - 1];
        }

        constexpr bool operator==(St* &other) const {
            return tps::strcmp(this->underlying, other);
        }

        constexpr bool operator==(const String<St, Al>& other) const {
            return tps::strcmp(this->underlying, other.underlying);
        }

        constexpr bool operator==(String<St, Al>&& other) const noexcept {
            return tps::strcmp(this->underlying, other.underlying);
        }

        void append(St s) {
            str temp = this->allocator.allocate(this->len);
            copystr(this->underlying, temp, this->len - 1);
            this->underlying = this->allocator.allocate(this->len);
            temp[this->len] = s;
            copystr(temp, this->underlying, this->len);
            this->len++;
        }

        void append(str s) {
            str temp = this->allocator.allocate(this->len + strlen(s) - 1);
            copystr(this->underlying, temp, this->len - 1);
            this->underlying = this->allocator.allocate(this->len + strlen(s));
            copystr(s, temp, strlen(s), strlen(s));
            copystr(temp, this->underlying, strlen(s) + this->len - 1);
            this->len += tps::strlen(s);
        }

        void append(const String<St, Al>& other) {
            str temp = this->allocator.allocate(this->len + other.len - 1);
            copystr(this->underlying, temp, this->len - 1);
            this->underlying = this->allocator.allocate(this->len + strlen(other.underlying));
            copystr(other.underlying, temp, strlen(other.underlying), strlen(other.underlying));
            copystr(temp, this->underlying, strlen(other.underlying) + this->len - 1);
            this->len += tps::strlen(other.underlying);
        }

        void append(String<St, Al>&& other) noexcept {
            str temp = this->allocator.allocate(this->len + other.len - 1);
            copystr(this->underlying, temp, this->len - 1);
            this->underlying = this->allocator.allocate(this->len + strlen(other.underlying));
            copystr(other.underlying, temp, strlen(other.underlying), strlen(other.underlying));
            copystr(temp, this->underlying, strlen(other.underlying) + this->len - 1);
            this->len += tps::strlen(other.underlying);
        }

        String<St, Al>& operator+=(const St& s) {
            this->append(s);
            return *this;
        }

        String<St, Al>& operator+=(const str& s) {
            this->append(s);
            return *this;
        }

        String<St, Al>& operator+=(const String<St, Al>& other) {
            this->append(other);
            return *this;
        }

        String<St, Al>& operator+=(String<St, Al>&& other) noexcept {
            this->append(other);
            return *this;
        }

        bool has(St& ele) const {
            for (int i = 0; i < this->len; i++) {
                if (this[i] == ele) return true;
            }
            return false;
        }

        bool has(const str& ele) const {
            for(int i = 0; i < this->len - strlen(ele); i++){
                str temp = this->allocator.allocate(strlen(ele));
                copystr(this->underlying, temp, strlen(ele), i);
                if(tps::strcmp(ele, temp)) return true;
            }
            return false;
        }

        [[nodiscard]] tps::size_t length() const {
            return this->len;
        }



        ~String() = default;
    };

    [[maybe_unused]] typedef String<char> string;

}

