export module util.allocators;


export namespace beta::util::alloc{

    template<typename T>
    class [[maybe_unused]] sAllocator{
        public:
        T* allocate(int num) const{
            return new T[num];
        }
        T* allocate_size(int size) {
            return (T*) new unsigned char[size];
        }

        void deallocate(T* ptr) {
            delete ptr;
        }
    };

}
