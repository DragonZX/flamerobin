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

#include "core/StringUtils.h"

#include "engine/DatabaseConnection.h"

#include "hierarchy/Generator.h"
#include "hierarchy/ItemVisitor.h"
//-----------------------------------------------------------------------------
struct ItemHandleAndName {
    Item::Handle handle;
    std::string name;
};
//-----------------------------------------------------------------------------
// GeneratorLoadValueJob class
class GeneratorLoadValueJob: public DatabaseConnectionThreadJob
{
private:
    std::list<ItemHandleAndName> generatorsM;
    std::list<int64_t> generatorValuesM;
protected:
    virtual void executeJob(DatabaseConnectionThread* thread);
public:
    GeneratorLoadValueJob(SharedDatabase database,
        const ItemHandleAndName& generator);
    GeneratorLoadValueJob(SharedDatabase database,
        const std::list<ItemHandleAndName>& generators);
    virtual void processResults();
};
//-----------------------------------------------------------------------------
GeneratorLoadValueJob::GeneratorLoadValueJob(SharedDatabase database,
        const ItemHandleAndName& generator)
    : DatabaseConnectionThreadJob(database)
{
    generatorsM.push_back(generator);
}
//-----------------------------------------------------------------------------
GeneratorLoadValueJob::GeneratorLoadValueJob(SharedDatabase database,
        const std::list<ItemHandleAndName>& generators)
    : DatabaseConnectionThreadJob(database), generatorsM(generators)
{
}
//-----------------------------------------------------------------------------
void GeneratorLoadValueJob::executeJob(DatabaseConnectionThread* thread)
{
    wxASSERT(thread);
    IBPP::Database db = thread->getDatabase();
    if (db != 0 && db->Connected())
    {
        IBPP::Transaction tr = IBPP::TransactionFactory(db, IBPP::amRead);
        tr->Start();
        IBPP::Statement st = IBPP::StatementFactory(db, tr);

        generatorValuesM.clear();
        for (std::list<ItemHandleAndName>::iterator it = generatorsM.begin();
            it != generatorsM.end(); ++it)
        {
            std::string stmt = "select gen_id(" + (*it).name
                + ", 0) from rdb$database";
            st->Execute(stmt);
            st->Fetch();
            int64_t value;
            st->Get(1, &value);
            generatorValuesM.push_back(value);
        }
    }
}
//-----------------------------------------------------------------------------
void GeneratorLoadValueJob::processResults()
{
    wxASSERT(wxIsMainThread());

    if (hasError())
        reportError(_("An error occurred while fetching the generator values!"));

    std::list<int64_t>::const_iterator itValue = generatorValuesM.begin();
    for (std::list<ItemHandleAndName>::iterator it = generatorsM.begin();
        it != generatorsM.end() && itValue != generatorValuesM.end();
        ++it, ++itValue)
    {
        Item* item = Item::getFromHandle((*it).handle);
        Generator* generator = dynamic_cast<Generator*>(item);
        wxASSERT(generator);
        if (generator)
            generator->setValue(*itValue);
    }
}
//-----------------------------------------------------------------------------
// Generator class
Generator::Generator(const Identifier& identifier)
    : MetadataItemBase(), valueM(0), valueLoadedM(false)
{
    setIdentifier(identifier);
}
//-----------------------------------------------------------------------------
const wxString Generator::getTypeName() const
{
    return wxT("GENERATOR");
}
//-----------------------------------------------------------------------------
void Generator::accept(ItemVisitor* visitor)
{
    wxASSERT(visitor);
    if (visitor)
        visitor->visit(*this);
}
//-----------------------------------------------------------------------------
int64_t Generator::getValue() const
{
    wxASSERT(valueLoadedM);
    return valueM;
}
//-----------------------------------------------------------------------------
void Generator::setValue(int64_t value)
{
    if (!valueLoadedM || valueM != value)
    {
        valueLoadedM = true;
        valueM = value;
        notifyObservers();
    }
}
//-----------------------------------------------------------------------------
void Generator::loadValue()
{
    Database* db = getDatabase();
    wxCHECK_RET(db,
        wxT("Generator::loadValue() called without parent database"));
    SharedDatabaseConnection dbc = db->getMetadataConnection();
    if (dbc)
    {
        ItemHandleAndName me;
        me.handle = getHandle();
        me.name = wx2std(getIdentifier().getQuoted());

        SharedDBCThreadJob job(new GeneratorLoadValueJob(db->asShared(), me));
        dbc->executeJob(job);
    }
}
//-----------------------------------------------------------------------------
bool Generator::isValueLoaded() const
{
    return valueLoadedM;
}
//-----------------------------------------------------------------------------
// GeneratorCollection class
SharedItem GeneratorCollection::createCollectionItem(const Identifier& identifier)
{
    SharedItem generator(new Generator(identifier));
    generator->setParent(shared_from_this());
    return generator;
}
//-----------------------------------------------------------------------------
void GeneratorCollection::loadChildren()
{
    Database* db = getDatabase();
    wxCHECK_RET(db,
        wxT("GeneratorCollection::loadChildren() called without parent database"));
    SharedDatabaseConnection dbc = db->getMetadataConnection();
    if (dbc)
    {
        setLoadChildrenState(lcsLoading);
        std::string sql("select g.RDB$GENERATOR_NAME from RDB$GENERATORS g"
            " where g.RDB$SYSTEM_FLAG = 0 or g.RDB$SYSTEM_FLAG is null"
            " order by 1");
        dbc->loadCollection(getHandle(), sql);
        return;
    }

    // loading is not possible, so clear children and show empty collection
    SubjectLocker lock(this);
    clearChildren();
    setLoadChildrenState(lcsLoaded);
}
//-----------------------------------------------------------------------------
void GeneratorCollection::accept(ItemVisitor* visitor)
{
    wxASSERT(visitor);
    if (visitor)
        visitor->visit(*this);
}
//-----------------------------------------------------------------------------
void GeneratorCollection::loadValues()
{
    Database* db = getDatabase();
    wxCHECK_RET(db,
        wxT("Generator::loadValue() called without parent database"));
    SharedDatabaseConnection dbc = db->getMetadataConnection();
    if (dbc)
    {
        std::list<ItemHandleAndName> generators;
        for (unsigned i = 0; i < getChildrenCount(); ++i)
        {
            SharedItem item = getChild(i);
            Generator* generator = dynamic_cast<Generator*>(item.get());
            wxASSERT(generator);
            if (generator)
            {
                ItemHandleAndName han;
                han.handle = generator->getHandle();
                han.name = wx2std(generator->getIdentifier().getQuoted());
                generators.push_back(han);
            }
        }

        SharedDBCThreadJob job(new GeneratorLoadValueJob(db->asShared(),
            generators));
        dbc->executeJob(job);
    }
}
//-----------------------------------------------------------------------------
