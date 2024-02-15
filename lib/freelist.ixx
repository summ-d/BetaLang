//
// Created by jack on 2/13/24.
//

export module util.allocator.freelist;

import util.utility;
import util.pointers;
import util.syscalls;

namespace beta::util::alloc::fl {

    export template<tps::size_t N>
    class PageCache;

    export template<tps::size_t N>
    class Page {
        ptr::SharedPtr<Page<N>> _prev;
        tps::u8 _data[N];
        ptr::SharedPtr<Page<N>> _next;

        bool _has_alloc = false;
        tps::size_t _alloc_ptr = 0;

        public:

        Page(): _data(nullptr), _next(nullptr), _prev(nullptr) {}

        void unlink() {
            if(this->linked()) return;
            if(this->_next){
                this->_next->prev = this->_prev;
            }
            this->_prev->next = this->_next;

            this->_prev = this->_next = nullptr;
        }

        bool linked(){
            return this->_prev.raw() == nullptr;
        }

        template<typename T, tps::size_t I>
        void page_alloc(T (&ptr)[I]) requires(sizeof(T) * I < N) {
            tps::u8* bytesOfT = reinterpret_cast<tps::u8*>(ptr);
            fn::memcpy(bytesOfT, this->_data, sizeof(T) * I);
            this->_has_alloc = true;
            this->_alloc_ptr = (sizeof(T) * I) - 1;
        }

        template<tps::size_t I>
        void raw_alloc(tps::u8 (&ptr)[I]) requires(I < N) {
            fn::memcpy(ptr, this->_data, I);
            this->_has_alloc = true;
            this->_alloc_ptr = I - 1;
        }

        friend class PageCache<N>;
    };

    export template<typename T>
    struct AllocDescriptor {
        ptr::SharedPtr<T> data;
        tps::size_t startidx;
        tps::size_t page_len;
        tps::size_t alloc_idx;
    };

    export template<tps::size_t N = 64>
    class PageCache {
        tps::size_t _alloc_ptr = 0;
        tps::size_t _allocs = 0;
        tps::size_t _length = 0;

        typedef struct {
            tps::size_t start_idx_free;
            tps::size_t end_idx_free;
        } freedis_t;

        freedis_t* _freed_blocks = nullptr;
        tps::size_t _free_size = 0;

        tps::size_t _freed_ptr = 0;

        tps::size_t* _allocation_blocks = nullptr;

        bool _overflowed = false;

        ptr::SharedPtr<Page<N>> _root = nullptr;

        void _insert_page_(ptr::SharedPtr<Page<N>>& prev) {
            //if(prev->linked()){
                ptr::SharedPtr<Page<N>> new_page = new Page<N>();
                new_page->_next = prev->_next;
                new_page->_prev = prev;
                prev->_next = new_page;
            //}
        }

        tps::size_t _cum_sum_(tps::size_t idx) {
            tps::size_t tmp = 0;
            for(int i = 0; i < this->_allocs && i < idx; i++) {
                tmp += this->_allocation_blocks[i];
            }
            return tmp;
        }

        tps::u8* _concat_pages_(tps::size_t start, tps::size_t end) {
            tps::u8* final = new tps::u8[(end - start) * N];
            for(int i = start; i <= end; i++){
                tps::u8* current_node_data = this[i]->_data;
                for(int j = 0; j < N; j++){
                    final[j + (i * N)] = current_node_data[j];
                }
            }
            return final;
        }

        tps::size_t _next_availble_page_(tps::size_t seg_len) {
            for(int i = 0; i < this->_free_size; i++){
                if(seg_len < (this->_freed_blocks[i].end_idx_free - this->_freed_blocks[i].start_idx_free)) {
                    return this->_freed_blocks[i].start_idx_free;
                }
            }
        }

        ptr::SharedPtr<Page<N>> operator[](int idx) {
            int i = 0;
            ptr::SharedPtr<Page<N>> temp = this->_root;
            while(i <= idx && temp) {
                temp = temp->_next;
                i++;
            }
            return temp;
        }

        public:

        template<tps::size_t C>
        explicit PageCache(tps::size_t inital = C){
            ptr::SharedPtr<Page<N>> temp = this->_root;
            for(int i = 0; i < inital; i++){
                this->_insert_page_(temp);
                temp = temp->_next;
            }
        }

        template<typename T, tps::size_t I>
        void alloc_page(T (&ptr)[I]) {
            this->_has_alloced = true;
            tps::size_t size = sizeof(T) * I;
            if(!this->_root->_next) return; // Page hasn't been added; wait
            ptr::SharedPtr<Page<N>> base = this[this->_next_availble_page_(size)];
            int i = 0;
            tps::u8* t_bytes = reinterpret_cast<tps::u8*>(ptr);
            while(i < (int)(size / N) + 1 && base) {
                for(int j = 0; j <= N; j++) {
                    base->_data[i] = t_bytes[j + (i * N)];
                }
                base = base->_next;
                i++;
            }
            auto* temp = new tps::size_t[this->_allocs];
            fn::memcpy(this->_allocation_blocks, temp, this->_allocs);
            this->_allocs++;
            this->_allocation_blocks = new tps::size_t[this->_allocs];
            fn::memcpy(temp, this->_allocation_blocks, this->_allocs - 1);
            this->_allocation_blocks[this->_allocs] = (int)(size / N) + 1;
        }

        template<typename T>
        AllocDescriptor<T> get_alloc(tps::size_t idx) {
            //if(idx < this->_freed_ptr || idx > this->_alloc_ptr) {
                tps::size_t pages_needed = this->_allocation_blocks[idx];
                tps::size_t indexof = this->_cum_sum_(idx);
                tps::u8* t_bytes = this->_concat_pages_(idx, pages_needed + idx);
                return AllocDescriptor<T>{
                    .data = reinterpret_cast<T*>(&t_bytes),
                    .page_len = pages_needed,
                    .startidx = indexof,
                    .alloc_idx = idx
                };
            //}
        }

        template<typename T>
        void free_alloc(AllocDescriptor<T>& alloc) {
            for(int i = alloc.startidx; i <= alloc.page_len + alloc.startidx; i++) {
                delete this[i]->_data;
            }
            freedis_t fdis = freedis_t {
                    .start_idx_free = alloc.startidx,
                    .end_idx_free = alloc.startidx + alloc.page_len
            };
            auto* temp = new freedis_t[this->_free_size];
            fn::memcpy(this->_freed_blocks, temp, this->_free_size);
            this->_free_size++;
            this->_freed_blocks = new freedis_t[this->_free_size];
            fn::memcpy(temp, this->_freed_blocks, this->_free_size);
            this->_freed_blocks[this->_free_size - 1] = fdis;
            tps::size_t* tmp = new tps::size_t[this->_allocs - 1];
            for(int i = 0; i < this->_allocs; i++){
                if(i <= alloc.alloc_idx){
                    tmp[i] = this->_allocation_blocks[i];
                } else if(i >= alloc.alloc_idx){
                    tmp[i - 1] = this->_allocation_blocks[i];
                }
                if(i == alloc.alloc_idx) continue;
            }
            this->_allocation_blocks = new tps::size_t[this->_allocs - 1];
            --this->_allocs;
            fn::memcpy(tmp, this->_allocation_blocks, this->_allocs);
        }


    };

    export template<tps::size_t N>
    class FreeList;

    export template<tps::size_t N>
    class FreeNode {
        ptr::SharedPtr<Page<N>> _prev;
        PageCache<N> _data;
        ptr::SharedPtr<Page<N>> _next;

        bool _has_alloc = false;
        tps::size_t _alloc_ptr = 0;

    public:

        FreeNode(): _data(nullptr), _next(nullptr), _prev(nullptr) {}

        void unlink() {
            if(this->linked()) return;
            if(this->_next){
                this->_next->prev = this->_prev;
            }
            this->_prev->next = this->_next;

            this->_prev = this->_next = nullptr;
        }

        bool linked(){
            return this->_prev.raw() == nullptr;
        }

        friend class FreeList<N>;
    };

    template<tps::size_t N>
    class FreeList {
        ptr::SharedPtr<FreeNode<N>> _root = nullptr;

        static volatile tps::SysInfo* _sys_info;

        void _add_node_(ptr::SharedPtr<FreeNode<N>>& prev) {
            ptr::SharedPtr<FreeNode<N>> new_node = new FreeNode<N>();
            new_node->_next = prev->_next;
            new_node->_prev = prev;
            prev->_next = new_node;
        }

        ptr::SharedPtr<FreeNode<N>> operator[](int idx) requires(idx < _sys_info->procs) {
            int i = 0;
            ptr::SharedPtr<FreeNode<N>> temp = this->_root;
            while(i < idx) {
                i++;
                temp = temp->_next;
            }
            return temp;
        }

        public:

        FreeList(): _root(new FreeNode<N>()) {
            ptr::SharedPtr<FreeNode<N>> temp = this->_root;
            for(int i = 0; i < _sys_info->procs; i++) {
                this->_add_node_(temp);
                temp = temp->_next;
            }
        }


        ptr::SharedPtr<PageCache<N>> get_cache() {
            FreeNode<N> returnCache = this->_root->_next;
            return ptr::SharedPtr<PageCache<N>>(&returnCache._data);
        }

        void return_cache(ptr::SharedPtr<PageCache<N>> cache) {
            this[_sys_info->procs - 1] = cache;
        }

        static volatile tps::SysInfo* get_sys_info(){
            return _sys_info;
        }

    };



    template<tps::size_t N>
    volatile tps::SysInfo* FreeList<N>::_sys_info = sys::sys_sysinfo();

}

