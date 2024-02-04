//
// Created by jack on 1/15/24.
//

#include <typeinfo>

export module util.extras;



/* Well, I have to do documentation, as per JetBrains (Generous) Open-Source License
 * This will make me a better programmer... probably
*/

/*
 *  anyway, this is the base util namespace for beta.
 *  The hierarchy goes something like this:
 *  beta
 *   |-- util
 *        |-- tps
 *        |-- alloc
 *        |-- any
 *   |--pp
 *   |--ast
 *   |--base
*/
export namespace beta::util{

    // Namespace for types and functions that are needed globally
    namespace tps {

        // because I don't want to add a lot of the standard library
        typedef unsigned short size_t;

    /**
     * gets the size of an array
     *
     * @param array The array needed
     * @return the size of the array
     * @returnType size_t
    */
    template<typename T, size_t N>
    constexpr size_t size(T (&)[N]) noexcept {
        return N;
    }


    /**
     * copies the contents of an array to a different array
     *
     * @param src The array to copy from
     * @param dest The array to copy into
     * @param size The size of the source array
     *
    */
    template<typename T>
    [[maybe_unused]] inline void memcpy(const T* src, T* dest, int size) noexcept {
        for(int i = 0; i < size; i++) dest[i] = src[i];
    }

    // Simple byte type; I just think it's neat
    typedef unsigned char u8;

    /**
     * Gets the size of a string
     *
     * @param s1 The string
     * @return the size of <code>s1</code>
     * @returnType size_t
    */
    inline size_t strlen(const char *s1) {
        const char* s;
        for(s = s1; *s; ++s);
        return (s - s1);
    }


    /**
    * checks whether two strings are equal
    *
    * @param one The first string
    * @param two The second string
    * @return Whether the strings <B>are equal or not</B>
    * @returnType bool
    */
    inline bool strcmp(const char* one, const char *two) {
        for(int i = 0; i < strlen(one) && i < strlen(two); i++) {
            if(two[i] != one[i]) return false;
        }
        return true;
    }

    /**
     * Swaps the contents of <code>a</code> and <code>b</code>
     *
     * @param a reference of the first operand
     * @param b reference of the second operand
    */
    template<typename T>
    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

} // End namespace tps

    // only thing in here is the Any class
    namespace any {

        // Class to handle any type
        class Any {
            /**
             * @class Placeholder
             * @brief Abstract class for the <code>Holder&lt;T&gt; </code> class
            */
            class Placeholder {
            public:
                /** Default Deconstruct for <code>Placeholder</code>*/
                ~Placeholder() = default;

                /**
                 * Virtual function for getting the type
                 * @return The type of the underlying type
                 * @returnType <code>const char*</code> (<code>const char[]</code>)
                */
                [[nodiscard]] virtual const char* type() const = 0;

                /**
                 * Virtual function for cloning the type
                 * @return <code>Placeholder*</code> containing the cloned type
                 * @returnType <code>Placeholder*</code>
                */
                [[nodiscard]] virtual Placeholder* clone() const = 0;
            };


            /**
             * @class Holder&lt;T&gt;
             * @inherits Placeholder
             * @brief Container for a certain type <code>T</code>
            */
            template<typename T>
            class Holder: public Placeholder {
            public:
                T stored; ///< The internal stored value of the instance

                /**
                 *  @brief Constructor
                 *  @param val The value to be stored
                */
                explicit Holder(const T& val): stored(val) {}

                // Override function from Placeholder

                [[nodiscard]] const char* type() const override {
                    return typeid(T).name();
                }

                [[nodiscard]] Placeholder* clone() const override {
                    return new Holder(this->stored);
                }

                /**
                 * @brief Deconstruct of <code>Holder&lt;T&gt;</code>
                */
                ~Holder() = default;
            };


            Placeholder* under; ///< Underlying instance of <code>Placeholder*</code>

        public:

            /**
             * @brief Construct that handles the underlying type <code>T</code>
             *
             * Initializes <code>under</code> with a <code>Holder&lt;T&gt;*</code>
            */
            template<typename T>
            explicit Any(const T& val): under(new Holder<T>(val)) {}

            /**
             * @brief copy Construct of <code>Holder&lt;T&gt;</code>
            */
            Any(const Any& other): under((other.under) ? other.under->clone() : nullptr) {}

            /**
             * @brief move Construct of <code>Holder&lt;T&gt;</code>
            */
            Any(Any&& other) noexcept: under((other.under) ? other.under : nullptr) {
                other.under = nullptr;
            }


            /**
             * Assignment operator
             * @param other the new assignment
             * @return The current instance
            */
            template<typename T>
            Any& operator=(const T& other) {
                delete this->under;
                this->under = new Holder<T>(other);
                return *this;
            }


            /**
             * Assignment operator overload
             * @param other the new assignment
             * @return The current instance
            */
            Any& operator=(const Any& other) {
                if(this != &other) {
                    delete this->under;
                    this->under = ((other.under) ? other.under->clone() : nullptr);
                }
                return *this;
            }

            /**
             * Assignment operator overload
             * @param other the new assignment
             * @return The current instance
            */
            Any& operator=(Any&& other) noexcept {
                delete this->under;
                this->under = ((other.under) ? other.under : nullptr);
                return *this;
            }

            /**
             * Casting Function
             * @return The casting value
             * @throws std::bad_cast if not successful
            */
            template<typename T>
            T*& cast() {
                if(this->under && tps::strcmp(typeid(T).name(), this->under->type())) {
                    return static_cast<Holder<T>*>(this->under)->stored;
                }
                throw std::bad_cast();
            }

            /**
             * @brief Deconstruct for <code>Any</code>
            */
            ~Any() {
                delete this->under;
            }
        }; // End class Any
    } // End namespace any

    template<typename T>
    struct ArrayWrap{
        T* array;
        tps::size_t length;
    };

} // End namespace beta::util
