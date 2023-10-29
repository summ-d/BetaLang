


#include "util/collections/collections.hpp"
#include "util/collections/logger.hpp"
#include "util/typegen/typegen.hpp"

namespace beta::toml{

    typedef struct IOError: public util::BaseError{
        util::string fileName;
    } ioerr_t;

    typedef struct DependencyData{
        util::string packName;
        util::string version;
    } depdat_t;

    typedef struct TomlData {
        util::string packname;
        util::LinkedList<util::string> authors;
        util::string version;
        util::PossibleArch arch;
        util::string outDir;
        util::LinkedList<depdat_t> dependencies;
    } tomdat_t;
    
    
    class TomlParser{
        util::LinkedList<util::string> lines;
        public:
            TomlParser(util::string fileName);
            void parse();
            void expose();
            
    };


} // namespace beta::toml





