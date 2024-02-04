//
// Created by jack on 1/14/24.
//

#include <istream>

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
    template<typename St = char, typename Al = alloc::sAllocator<St>>
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
        [[maybe_unused]] constexpr String(const St* s) {
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

        constexpr int strlen(const char* pSt) {
            const char* s;
            for(s = pSt; *s; ++s);
            return int(s - pSt);
        }

        void append(const String<St, Al>& other) {
            str temp = this->allocator.allocate(this->len + other.len - 1);
            copystr(this->underlying, temp, this->len - 1);
            this->underlying = this->allocator.allocate(this->len + tps::strlen(other.underlying));
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

        bool has(const St ele) const {
            for (int i = 0; i < this->len; i++) {
                if (this->underlying[i] == ele) return true;
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

        bool has(const String<St, Al>& other) const {
            for(int i = 0; i < this->len - other.len - 1; i++){
                str temp = this->allocator.allocate(other.len);
                copystr(this->underlying, temp, other.len, i);
                if(tps::strcmp(other.underlying, temp)) return true;
            }
            return false;
        }

        [[nodiscard]] tps::size_t length() const {
            return this->len;
        }

        String<St, Al>& getline(String<St, Al>& delim) {}

        friend std::istream& getline(std::istream& is, String<St, Al>& string, char delim = '\n') {
            char curr;
            tps::size_t size = 10;
            while(is.get(curr) && curr != delim) {
                if(string.len + 1 >= size) {
                    size *= 2;
                    char* newData = new char[size];
                    copystr(string.underlying, newData, string.len);
                    delete[] string.underlying;
                    string.underlying = newData;
                }
                string.underlying[string.len++] = curr;
            }
            return is;
        }

        friend std::istream& getline(std::istream& is, String<St, Al>& str, const String<St, Al>& delim) {
            char* curr = new char[delim.len];
            tps::size_t size = delim.len + 9;
            while(is.get(curr, delim.len) && !tps::strcmp(curr, delim)) {
                if(str.len + 1 >= size) {
                    size *= 2;
                    char* newData = new char[size];
                    copystr(str.underlying, newData, str.len);
                    delete[] str.underlying;
                    str.underlying = newData;
                }
                for(int i = 0; i < delim.len; i++) {
                    str.underlying[str.len + i] = curr[i];
                }
                str.len += delim.len;
            }
            return is;
        }

        // Differnce: substring() is non destructive
        String<St, Al> substring(int start, int end) const {
            if(end - start > 0 && start < this->len && end < this->len) {
                str temp = this->allocator.allocate(end - start);
                for(int i = start; i < end; i++) {
                    temp[i - start] = this->underlying[i];
                }
                return String(temp);
            }
            return String();
        }

        String<St, Al> popnum(int start, int end) {
            if(end - start > 0 && start < this->len && end < this->len) {
                str ret = this->allocator.allocate(end - start);
                str tempTwo = this->allocator.allocate(this->len);
                for(int i = start; i < end; i++) {
                    ret[i - start] = this->underlying[i];
                }
                copystr(this->underlying, tempTwo, this->len);
                this->underlying = this->allocator.allocate(this->len - (end - start));
                for(int i = 0; i < this->len - (end - start); i++) {
                    this->underlying[i] = tempTwo[i];
                    if(i == start) {
                        i += (end - start);
                    }
                    this->underlying[i - (end - start)] = tempTwo[i];
                }
                this->len -= (end - start);
                return String(ret);
            }
            return String();
        }

        int find(const St c) {
            for(int i = 0; i < this->len; i++) {
                if(this->underlying[i] == c) return i;
            }
            return -1;
        }

        int find(const String<St, Al>& str) {
            for(int i = 0; i < this->len - str.len; i++) {
                if(this->substring(i, i + str.len) == str) {
                    return i;
                }
            }
            return -1;
        }

        bool empty(){
            return this->len == 0 || this->underlying == nullptr;
        }

        ArrayWrap<String<St, Al>> split(St delim) const {
            str* strings;
            int j = 0;
            int lastI = 0;
            for(int i = 0; i < this->len; i++) {
                if(this->underlying[i] == delim) {
                    strings[j] = this->allocator.allocate(i - lastI);
                    copystr(this->substring(lastI, i).s_raw(), strings[j], i - lastI);
                    j++;
                }
            }
            ArrayWrap<String<St, Al>> wrap;
            for(int i = 0; i < j; i++) {
                wrap.array[i] = String(strings[i]);
            }
            wrap.length = j;
            return wrap;
        }

        ArrayWrap<int> numStringOccurs(const St ch) const{
            ArrayWrap<int> wrap = ArrayWrap<int>();
            int j = 0;
            for(int i = 0; i < this->len; i++) {
                if(this->underlying[i] == ch){
                    wrap.array[j] = i;
                    j++;
                }
            }
            return wrap;
        }

        St last() const {
            return this->underlying[this->len - 1];
        }

        St first() const{
            return this->underlying[0];
        }


        ~String() = default;
    };


    typedef String<char> string;

}

