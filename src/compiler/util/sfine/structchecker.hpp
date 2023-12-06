#pragma once
#ifndef STRUCTCHECKER_HPP
#define STRUCTCHECKER_HPP

    namespace util{

        class DummyInheriter{
            const int x = 0;
        };

        template<typename IsUse>
        class is_use: public DummyInheriter{
            typedef char yes[1];
            typedef char no[2];

            template<typename T>
            static yes& test(typename T::use_t*){}

            template<typename>
            static no& test(...){}

            public:
            static const bool value = sizeof(test<IsUse>(nullptr)) == sizeof(yes);
        };

        template<typename IsAlias>
        class is_alias: public DummyInheriter{
            typedef char yes[1];
            typedef char no[2];

            template<typename T>
            static yes& test(typename T::alias_t*){}

            template<typename>
            static no& test(...){}


            public:

            static const bool value = sizeof(test<IsAlias>(nullptr)) == sizeof(yes);
        };

        template<typename IsStart>
        class is_start: public DummyInheriter{
            typedef char yes[1];
            typedef char no[2];

            template<typename T>
            static yes& test(typename T::alias_t*){}

            template<typename>
            static no& test(...){}

            public:

            static const bool value = sizeof(test<IsStart>(nullptr)) == sizeof(yes);
        };

        template<class IsEval>
        class is_eval: public DummyInheriter{

            typedef char yes[1];
            typedef char no[2];

            template<typename T>
            static yes& test(typename T::eval_t*){}

            template<typename>
            static no& test(...){}
            
            public:
            
            static const bool value = sizeof(test<IsEval>(nullptr)) == sizeof(yes);
        };  

        template<typename IsExtern>
        class is_external: public DummyInheriter{
            typedef char yes[1];
            typedef char no[2];
            
            template<typename T>
            static yes& test(typename T::extern_t*) {}

            template<typename>
            static no& test(...){}

            public:

            static const bool value = sizeof(test<IsExtern>(nullptr)) == sizeof(yes);
        };
    }


#endif