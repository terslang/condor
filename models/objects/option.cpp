#include "option.h"
#include "sqlobjects/optionobject.h"
#include <TreeFrogModel>

Option::Option()
  : TAbstractModel()
  , d(new OptionObject())
{
  // set the initial parameters
}

Option::Option(const Option& other)
  : TAbstractModel()
  , d(other.d)
{
}

Option::Option(const OptionObject& object)
  : TAbstractModel()
  , d(new OptionObject(object))
{
}

Option::~Option()
{
  // If the reference count becomes 0,
  // the shared data object 'OptionObject' is deleted.
}

QString
Option::id() const
{
  return d->id;
}

QString
Option::name() const
{
  return d->name;
}

void
Option::setName(const QString& name)
{
  d->name = name;
}

QString
Option::body() const
{
  return d->body;
}

void
Option::setBody(const QString& body)
{
  d->body = body;
}

int
Option::electionId() const
{
  return d->election_id;
}

void
Option::setElectionId(int electionId)
{
  d->election_id = electionId;
}

Option&
Option::operator=(const Option& other)
{
  d = other.d; // increments the reference count of the data
  return *this;
}

Option
Option::create(const QString& name, const QString& body, int electionId)
{
  OptionObject obj;
  obj.name = name;
  obj.body = body;
  obj.election_id = electionId;
  if (!obj.create()) {
    return Option();
  }
  return Option(obj);
}

Option
Option::create(const QVariantMap& values)
{
  Option model;
  model.setProperties(values);
  if (!model.d->create()) {
    model.d->clear();
  }
  return model;
}

Option
Option::get(const QString& id)
{
  TSqlORMapper<OptionObject> mapper;
  return Option(mapper.findByPrimaryKey(id));
}

int
Option::count()
{
  TSqlORMapper<OptionObject> mapper;
  return mapper.findCount();
}

QList<Option>
Option::getAll()
{
  return tfGetModelListByCriteria<Option, OptionObject>(TCriteria());
}

QJsonArray
Option::getAllJson(const QStringList& properties)
{
  return tfConvertToJsonArray(getAll(), properties);
}

QList<Option>
Option::getByElectionId(int electionId)
{
  TCriteria crt(OptionObject::ElectionId, electionId);
  return tfGetModelListByCriteria<Option, OptionObject>(crt);
}

TModelObject*
Option::modelData()
{
  return d.data();
}

const TModelObject*
Option::modelData() const
{
  return d.data();
}

QDataStream&
operator<<(QDataStream& ds, const Option& model)
{
  auto varmap = model.toVariantMap();
  ds << varmap;
  return ds;
}

QDataStream&
operator>>(QDataStream& ds, Option& model)
{
  QVariantMap varmap;
  ds >> varmap;
  model.setProperties(varmap);
  return ds;
}
