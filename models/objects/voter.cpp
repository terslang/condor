#include "voter.h"
#include "sqlobjects/voterobject.h"
#include <TreeFrogModel>

Voter::Voter()
  : TAbstractModel()
  , d(new VoterObject())
{
  // set the initial parameters
}

Voter::Voter(const Voter& other)
  : TAbstractModel()
  , d(other.d)
{
}

Voter::Voter(const VoterObject& object)
  : TAbstractModel()
  , d(new VoterObject(object))
{
}

Voter::~Voter()
{
  // If the reference count becomes 0,
  // the shared data object 'VoterObject' is deleted.
}

QString
Voter::email() const
{
  return d->email;
}

void
Voter::setEmail(const QString& email)
{
  d->email = email;
}

int
Voter::electionId() const
{
  return d->election_id;
}

Voter&
Voter::operator=(const Voter& other)
{
  d = other.d; // increments the reference count of the data
  return *this;
}

Voter
Voter::create(const QString& email, int electionId)
{
  VoterObject obj;
  obj.email = email;
  obj.election_id = electionId;
  if (!obj.create()) {
    return Voter();
  }
  return Voter(obj);
}

Voter
Voter::create(const QVariantMap& values)
{
  Voter model;
  model.setProperties(values);
  if (!model.d->create()) {
    model.d->clear();
  }
  return model;
}

Voter
Voter::get(const QString& email, int electionId)
{
  TSqlORMapper<VoterObject> mapper;
  TCriteria cri = TCriteria(VoterObject::ElectionId, electionId) &&
                  TCriteria(VoterObject::Email, email);
  return Voter(mapper.findFirst(cri));
}

int
Voter::count()
{
  TSqlORMapper<VoterObject> mapper;
  return mapper.findCount();
}

QList<Voter>
Voter::getAll()
{
  return tfGetModelListByCriteria<Voter, VoterObject>(TCriteria());
}

QJsonArray
Voter::getAllJson(const QStringList& properties)
{
  return tfConvertToJsonArray(getAll(), properties);
}

TModelObject*
Voter::modelData()
{
  return d.data();
}

const TModelObject*
Voter::modelData() const
{
  return d.data();
}

QDataStream&
operator<<(QDataStream& ds, const Voter& model)
{
  auto varmap = model.toVariantMap();
  ds << varmap;
  return ds;
}

QDataStream&
operator>>(QDataStream& ds, Voter& model)
{
  QVariantMap varmap;
  ds >> varmap;
  model.setProperties(varmap);
  return ds;
}
