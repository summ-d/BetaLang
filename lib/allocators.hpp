//
// Created by jack on 1/14/24.
//

#ifndef COMPILER_ALLOCATORS_HPP
#define COMPILER_ALLOCATORS_HPP

namespace beta::util::alloc{

    template<typename T>
    class [[maybe_unused]] sAllocator{
        public:
        T* allocate(int num);
        T* allocate_size(int size);

        void deallocate(T* ptr);
    };

}



#endif //COMPILER_ALLOCATORS_HPP
