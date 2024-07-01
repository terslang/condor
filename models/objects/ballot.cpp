#include "ballot.h"
#include "sqlobjects/ballotobject.h"
#include <TreeFrogModel>

Ballot::Ballot()
  : TAbstractModel()
  , d(new BallotObject())
{
  // set the initial parameters
}

Ballot::Ballot(const Ballot& other)
  : TAbstractModel()
  , d(other.d)
{
}

Ballot::Ballot(const BallotObject& object)
  : TAbstractModel()
  , d(new BallotObject(object))
{
}

Ballot::~Ballot()
{
  // If the reference count becomes 0,
  // the shared data object 'BallotObject' is deleted.
}

QString
Ballot::id() const
{
  return d->id;
}

void
Ballot::setId(const QString& id)
{
  d->id = id;
}

int
Ballot::electionId() const
{
  return d->election_id;
}

void
Ballot::setElectionId(int electionId)
{
  d->election_id = electionId;
}

Ballot&
Ballot::operator=(const Ballot& other)
{
  d = other.d; // increments the reference count of the data
  return *this;
}

Ballot
Ballot::create(const QString& id, int electionId)
{
  BallotObject obj;
  obj.id = id;
  obj.election_id = electionId;
  if (!obj.create()) {
    return Ballot();
  }
  return Ballot(obj);
}

Ballot
Ballot::create(const QVariantMap& values)
{
  Ballot model;
  model.setProperties(values);
  if (!model.d->create()) {
    model.d->clear();
  }
  return model;
}

Ballot
Ballot::get(const QString& id)
{
  TSqlORMapper<BallotObject> mapper;
  return Ballot(mapper.findByPrimaryKey(id));
}

int
Ballot::count()
{
  TSqlORMapper<BallotObject> mapper;
  return mapper.findCount();
}

QList<Ballot>
Ballot::getAll()
{
  return tfGetModelListByCriteria<Ballot, BallotObject>(TCriteria());
}

QJsonArray
Ballot::getAllJson(const QStringList& properties)
{
  return tfConvertToJsonArray(getAll(), properties);
}

TModelObject*
Ballot::modelData()
{
  return d.data();
}

const TModelObject*
Ballot::modelData() const
{
  return d.data();
}

QDataStream&
operator<<(QDataStream& ds, const Ballot& model)
{
  auto varmap = model.toVariantMap();
  ds << varmap;
  return ds;
}

QDataStream&
operator>>(QDataStream& ds, Ballot& model)
{
  QVariantMap varmap;
  ds >> varmap;
  model.setProperties(varmap);
  return ds;
}
