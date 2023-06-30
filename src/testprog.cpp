/**
 * Created Date: Wednesday June 7th 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Wednesday June 7th 2023 4:31:40 pm
 * Modified By: DefinitelyNotAGirl@github (definitelynotagirl115169@gmail.com)
 * -----
 * Copyright (c) 2023 DefinitelyNotAGirl@github
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#include <cargparse.hxx>

#include <iostream>

cargparse::handlertype incHandler(CARGPARSE_HANDLER_ARGS)
{
    std::cout << "incHandler invoked" << std::endl << "args: ";
    for(std::string I : args)
        std::cout << I << " ";
    std::cout << std::endl << std::endl;
}
cargparse::handlertype srcHandler(CARGPARSE_HANDLER_ARGS)
{
    std::cout << "srcHandler invoked" << std::endl << "args: ";
    for(std::string I : args)
        std::cout << I << " ";
    std::cout << std::endl << std::endl;
}
cargparse::handlertype unkownArgHandler(CARGPARSE_UNKOWNHANDLER_ARGS)
{
    std::cout << "unkown argument: \"" << arg << "\"" << std::endl << std::endl;
}

int main(int argc, char** argv)
{
    std::cout << "Hello, world" << std::endl;
    cargparse::instance ins;
    ins.unknownHandler = &unkownArgHandler;
    ins.addParameter(false,1,std::string("-I"),&incHandler);
    ins.addParameter(true ,1,std::string("-S"),&srcHandler);
    ins.addParameter(false,3,std::string("-include"),&incHandler);
    ins.addParameter(true ,3,std::string("-source"),&srcHandler);
    ins.parse(argc,argv);
    return 0;
}