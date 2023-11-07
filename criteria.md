Requirements for BetaLang:
  1. It must have a zero-cost abstraction
  2. Modular code cannot sacrifice performance
  3. Generics cannot have performance issues similar to C++
  4. If the library is `@included`, it must have a strict one-include policy for every library.
  5. It should be easy for developers to embrace and use that come from a C, C++, and Java background.
  6. It should be easy to interop with C, C++, Assembly, and Java through the `external` keyword with zero-cost abstraction.

Solutions:
  For number 1:
    The solution is simple. I mean C, C++, and Rust all did that? Some ways I can do that is no runtime checking unless specified, a minimal garbage collector that only does the   bare bones, and rethinking virtual functions
      Rethinking virtual functions:
        take this section of code:
        
        abstract Obj Test{
          pub defun foo(x: Integer) => Integer;
        };

        Obj Bar: pub Test{
          override pub defun foo(x: Integer) => Integer;
        };
    

  Instead of runtime checking, the object Test will be checked for methods at compile time. If it is incorrect, the code will not be valid.
  so instead of trying to check at runtime, the check will happen at compile time, thus making it a zero-cost abstraction.
        
  For numbers 2 & 4: \
    One of the biggest problems with C and C++ is that producing modular code that can be nicely organized can make a huge hit on the performance of the program. Sometimes
    putting all of your codebase in one massive file that is ugly could save hours of compile time, as highlighted by this [answer](https://stackoverflow.com/a/318495/21485913). 
    The Solution:
      The problem is already mostly solved by the `import` keyword. The ONLY time anything will be copied/pasted into your file is when the function, composition, or object is\
      instantiated. However, there is another keyword. The `@include` preprocessor is discouraged, but if it is really needed it is there. There are strict rules that are in place \
      for this. For example, before it copy-pastes ANYTHING, it will recursively look through the other includes and figure out if there are ANY multiple includes. This makes sure
      that there is only one include of any file in any other file.

  For Number 3:\
    Another major problem with C++ is that Generics cause a performance hit if there are a lot of them.\
    Possible Solution: \
      Instead of instantiating the entire object or composition, we instantiate function by function. For example:
        
        List<Integer> intList = New List<Integer>();

        defun main(args: String[]) => Void{
          intList.add(5);
          Integer i = intList.get(0);
        }
        
        
  Since there are only 2 methods that are instantiated, ONLY 2 methods will be instantiated[^1] \

  For Number 5:\
    The syntax of the language is inspired by Rust, C, C++, and Java.\

  For Number 6:
    The `external` keyword specifies that you could look for the declaration somewhere else, and then is interpreted to BetaLang.
    Example: in somefile.cpp:\
            
                struct Bar{
                  int foo;
                  std::string baz;
                };
                
              

  Then in main.blp\
  
              
                external "path/to/somefile.cpp" comp Bar;
                Bar b = new Bar;
              


[^1]: Technically, due to other functions, there will be more functions that are getting instantiated, but that only adds 2 or 3 private functions that will get optimized







        

  
  
