//
// Created by jack on 1/20/24.
//

export module trans.basetranspiler;
import util.string;
import util.linkedlist;

export namespace beta::trans {

    class BaseTranspiler {
        virtual ~BaseTranspiler() = 0;
        virtual bool isValid() = 0;
        virtual void setName(util::string name) = 0;
        virtual void setNames(util::List<util::string>& names) = 0;
        virtual util::string transpile() = 0;
        virtual util::List<util::string> transpileAll() = 0;
    };
}