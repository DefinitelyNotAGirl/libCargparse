/*
 * Created Date: Wednesday June 7th 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Wednesday June 7th 2023 4:59:52 pm
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

#include <instance.hxx>
#include <iostream>
#include <cstring>

namespace cargparse
{
    void instance::addParameter(bool needsSpace, uint64_t argnum, std::string prefix, handlerFunction handler)
    {
        this->parameters.push_back(param(needsSpace,argnum,prefix,handler));
    }

    void instance::addParameter(param& p)
    {
        this->parameters.push_back(p);
    }

    void instance::parse(int argc, char** argv)
    {
        for(uint64_t I = 1;I<argc;I++)
        {
            uint64_t argsToGo = 0;
            std::list<std::string> args;
            param* pp;
            for(param& p : this->parameters)
            {
                if(argv[I] == p.prefix)
                {
                    argsToGo = p.argnum;
                    pp = &p;
                    goto collectArgs;
                }
                else if(!p.needsSpace)
                {
                    if(std::string(argv[I]).substr(0,p.prefix.length()) == p.prefix)
                    {
                        args.push_back(std::string(argv[I]).substr(p.prefix.length(),strlen(argv[I])));
                        argsToGo = p.argnum-1;
                        pp = &p;
                        goto collectArgs;
                    }
                }
            }
            this->unknownHandler(argv[I]);
            continue;
            #ifdef CARGPARSE_DEBUG
                std::cout << "found parameter: " << pp->prefix << std::endl;
            #endif
            collectArgs: ;
            uint64_t i = I;
            while(argsToGo>0)
            {
                args.push_back(argv[++I]);
                argsToGo--;
            }

            pp->handler(i,args);//... *sigh*
        }
    }
}