//
// Created by jack on 1/20/24.
//

export module types.preprocessortypes;

import types.globaltypes;
import util.string;
import util.linkedlist;
import util.extras;
import trans.basetranspiler;

namespace beta::pp::types {


    enum PreprocessorKeys {
        AT_ALIAS,
        AT_START,
        AT_USE,
        AT_DEFUN,
        AT_EVAL,
        AT_DEF,
        AT_EXTERNAL,
        AT_INCLUDE,
        AT_END
    };

    [[maybe_unused]] typedef struct BasePreprocessorToken {
        util::string keyword;
        util::string value;
        PreprocessorKeys type;
    } bppt_t;

    [[maybe_unused]] typedef struct AliasToken: BasePreprocessorToken {
        base::types::prdis_t type;
        util::string alias;
    } atok_t;

    [[maybe_unused]] typedef struct StartToken: BasePreprocessorToken {
        bool is_valid = true;
        util::tps::u8 startCount = 0;
    } sttok_t;

    [[maybe_unused]] typedef struct UseToken: BasePreprocessorToken {
        bool is_valid = true;
        base::types::ValidArches arch;
    } usetok_t;

    [[maybe_unused]] typedef struct DefunToken: BasePreprocessorToken {
        util::string funcName;
        char leftp;
        util::list<base::types::any_t> args;
        char rightp;
        util::string end;
        base::types::any_t returnType;
        char semi;
        util::string contents;
        util::string endDir;
    } defuntok_t;

    [[maybe_unused]] typedef struct EvalToken: BasePreprocessorToken {
        util::string lhs;
        util::string rhs;
        base::types::Operators op;
        bool value = false;
    } evaltok_t;

    [[maybe_unused]] typedef struct DefToken: BasePreprocessorToken {
        util::string name;
        util::string value;
    } deftok_t;

    [[maybe_unused]] typedef struct ExternalToken: BasePreprocessorToken {
        trans::BaseTranspiler* transpiler = nullptr;
        util::string extName;
        util::string extension;
        util::list<util::string> imports;
    } externtok_t;

    [[maybe_unused]] typedef struct IncludeToken: BasePreprocessorToken {
        util::string incFile;
        bool valid = true;
    } inctok_t;

    [[maybe_unused]] typedef struct EndToken {
        bppt_t* source = nullptr;
    } end_t;
}
