//
// Created by jack on 1/20/24.
//

export module types.globaltypes;

import util.string;
import util.linkedlist;
import util.extras;

export namespace beta::base::types {
    enum AllTypes {
        INTEGER,
        INT8,
        INT16,
        INT32,
        INT64,
        UINT8,
        UINT16,
        UINT32,
        UINT64,
        BIGINT,
        FLOAT,
        FLOAT8,
        FLOAT32,
        FLOAT64,
        BIGFLOAT,
        BOOLEAN,
        STRING,
        CHAR,
        ANY,
        VOID
    };

    enum NumberTypes {
        NINTEGER,
        NINT8,
        NINT16,
        NINT32,
        NINT64,
        NUINT8,
        NUINT16,
        NUINT32,
        NUINT64,
        NBIGINT,
        NFLOAT,
        NFLOAT8,
        NFLOAT32,
        NFLOAT64,
        NFLOATMAX,
        NBOOLEAN
    };

    enum OtherTypes {
        OSTRING,
        OCHAR,
        OANY,
        OVOID
    };

    enum Qualifiers {
        CONST,
        ABSTRACT,
        STATIC,
        MUT,
        REGISTER,
        THREAD,
        POINTER,
        REFERENCE
    };

    typedef struct VariableRules {
        VariableRules(bool can_abstract, bool can_static, bool can_mut, bool can_register,
                      bool can_thread, bool can_pointer, bool can_reference, bool can_const) {
            this->can_abstract = can_abstract;
            this->can_static = can_static;
            this->can_mut = can_mut;
            this->can_register = can_register;
            this->can_thread = can_thread;
            this->can_pointer = can_pointer;
            this->can_reference = can_reference;
            this->can_const = can_const;
        }

        VariableRules() = default;
        VariableRules clone() const {
            VariableRules n = VariableRules();
            n.can_abstract = this->can_abstract;
            n.can_static = this->can_static;
            n.can_mut = this->can_mut;
            n.can_register = this->can_register;
            n.can_thread = this->can_thread;
            n.can_pointer = this->can_pointer;
            n.can_reference = this->can_reference;
            n.can_const = this->can_const;
            return n;
        }
        bool can_abstract;
        bool can_static;
        bool can_mut;
        bool can_register;
        bool can_thread;
        bool can_const;
        mutable bool can_pointer;
        mutable bool can_reference;
    } varrule_t;

    const varrule_t in_local = VariableRules(false, false, false, true,
                                             true, true, false, true);

    const varrule_t in_global = VariableRules(false, true, false, true,
                                              true, true, false, true);

    const varrule_t in_parameter = VariableRules(false, false, false, false,
                                                false, true, true, true);

    const varrule_t in_object = VariableRules(true, true, true, true,
                                              true,true, false, true);

    const varrule_t in_composition = VariableRules(false, true, true, false,
                                                   true, true, false, true);

    typedef struct PrimitiveType {
        util::list<Qualifiers> qualifiers;
        AllTypes type;
        bool is_local = false;
        bool is_param = false;
        bool is_reference = false;
        bool is_class = false;
        bool is_tuple;
        util::tps::u8 refcount = 0;
        util::tps::u8 ptrcount = 0;
        varrule_t rules;
        util::string name;
    } prdis_t;

    typedef struct AnyType {
        util::string type;
        util::string name;
        bool is_local = false;
        bool is_param = false;
        bool is_reference = false;
        bool is_class = false;
        bool is_tuple = false;
        util::tps::u8 refcount = 0;
        util::tps::u8 ptrcount = 0;
        varrule_t rules;
    } any_t;

    typedef struct TupleType {
        util::list<AnyType> types;
        int elements = 0;
    } tuple_t;

    enum ValidArches {
        ARM,
        AVR,
        CIL,
        MSIL,
        x86_64,
        x86,
        MIPS,
        RISCV
    };

    enum Operators {
        EQUALS,
        NOT_EQUALS,
        GREATER_THAN,
        LESS_THAN,
        GREATER_THAN_OR,
        LESS_THEN_OR
    };

    enum Bitwise {
        NOT,
        OR,
        XOR,
        AND,
        LEFT,
        RIGHT
    };

}