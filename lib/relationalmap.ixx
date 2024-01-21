//
// Created by jack on 1/14/24.
//
export module util.relationalmap;

import util.extras;
import util.allocators;
import util.smartptr;

export namespace beta::util {

    [[maybe_unused]] const tps::u8 ONE{0};
    [[maybe_unused]] const tps::u8 TWO{1};

    template<typename One, typename Two>
    class RelMap {
        sp::Smartptr<One> underOne = nullptr;
        sp::Smartptr<Two> underTwo = nullptr;

        tps::size_t len = 0;

        alloc::sAllocator<One> allocOne;
        alloc::sAllocator<Two> allocTwo;

        struct Data {
            One one;
            Two two;
        };

    public:
        typedef struct Data data_t;

        RelMap() = default;
        [[maybe_unused]] RelMap(const One& one, const Two& two);
        [[maybe_unused]] RelMap(const One*& one, const Two*& two);
        RelMap(const RelMap& other);
        RelMap(RelMap&& other) noexcept;

        RelMap<One, Two>& operator=(const data_t& data);
        RelMap<One, Two>& operator=(const data_t*& data);
        RelMap<One, Two>& operator=(const RelMap<One, Two>& other);
        RelMap<One, Two>& operator=(RelMap<One, Two>&& other) noexcept;

        data_t operator[](int idx);
        const data_t operator[](int idx) const;


        any::Any operator()(int idx, tps::u8 active) const;

        void append(One one, Two two);
        void append(const One*& one, const Two*& two);
        void append(const RelMap<One, Two>& other);
        void append(RelMap<One, Two>&& other);

        RelMap<One, Two>& operator+=(const data_t& data);
        RelMap<One, Two>& operator+=(const data_t*& data);
        RelMap<One, Two>& operator+=(const RelMap<One, Two>& other);
        RelMap<One, Two>& operator+=(RelMap<One, Two>&& other);

        data_t* as_array() const;
        void foreach(auto& func);

        operator data_t*() const;

        [[nodiscard, gnu::always_inline, clang::always_inline]] inline tps::size_t length() const {
            return this->len;
        }

        ~RelMap();

    };

    template<typename One, typename Two>
    using map [[maybe_unused]] = RelMap<One, Two>;
}

