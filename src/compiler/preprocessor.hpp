#ifndef preprocessor_hpp
#define preprocessor_hpp

#include "util/collections/logger.hpp"


namespace beta::preproc {

    enum Types{
        ATSTART,
        ATUSE,
        ATINCLUDE,
        ATDEF,
        ATEND,
        ATEVAL,
        ATALIAS
    };

        
    typedef struct IOError: public util::BaseError{
        util::string fileName;
        IOError() = default;
        IOError(util::string filename, util::string message, int line);
    } ioerr_t;

    typedef struct Token{
        util::string token;
        Types type;
    } token_t;
    typedef struct GlobalConfig{
        util::u8 archType;
        util::string startPoint;
    } globconfig_t;

    class Preprocessor{
        std::ofstream outfile;
        std::ifstream inFile;
        util::LinkedList<util::string> tokens;

        static const util::string possible[7];

        void createAndCheck(util::string fileName){
            inFile.open(fileName.asStdStr());
            if(!inFile.is_open() || inFile.peek() == inFile.eof()){
                throw new IOError(fileName, "could not open file at line", __LINE__);
            }
            return;
        }

        public:
        Preprocessor(util::string fileName);
        void scanTokens();
        void evaluate();
        std::ofstream& getGeneratedFile();
        util::LinkedList<util::string> expose();
        ~Preprocessor();
    };


} // namespace beta

#endif