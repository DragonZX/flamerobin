/*
  Copyright (c) 2004-2008 The FlameRobin Development Team

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the
  "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to
  the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


  $Id$

*/

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "commands/ItemCommands.h"
#include "core/CommandIds.h"
#include "hierarchy/Generator.h"
//-----------------------------------------------------------------------------
// GeneratorCommands class
class GeneratorCommands : public ItemCommands
{
private:
    Generator* generatorM;
public:
    GeneratorCommands(PSharedItem item);
};
//-----------------------------------------------------------------------------
GeneratorCommands::GeneratorCommands(PSharedItem item)
    : ItemCommands(item), generatorM(0)
{
    generatorM = dynamic_cast<Generator*>(item.get());
    wxASSERT(generatorM);
}
//-----------------------------------------------------------------------------
static const ItemCommandsFactoryImpl<Generator, GeneratorCommands> factory;
//-----------------------------------------------------------------------------
