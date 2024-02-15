//
// Created by jack on 2/14/24.
//

export module util.thread.atomic;

import util.pointers;
import util.utility;

namespace beta::util {


    export template<typename T>
    class Atomic {};

    export template<>
    class Atomic<bool> {};

    export template<typename T>
    class Atomic<T*> {};

    export template<typename T>
    class Atomic<ptr::SharedPtr<T>>{};

    export template<typename T>
    class Atomic<ptr::UniquePtr<T>> {};

}