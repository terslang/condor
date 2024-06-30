#include <TreeFrogModel>
#include "pairwisecontest.h"
#include "sqlobjects/pairwisecontestobject.h"


PairwiseContest::PairwiseContest() :
    TAbstractModel(),
    d(new PairwiseContestObject())
{
    // set the initial parameters
}

PairwiseContest::PairwiseContest(const PairwiseContest &other) :
    TAbstractModel(),
    d(other.d)
{ }

PairwiseContest::PairwiseContest(const PairwiseContestObject &object) :
    TAbstractModel(),
    d(new PairwiseContestObject(object))
{ }

PairwiseContest::~PairwiseContest()
{
    // If the reference count becomes 0,
    // the shared data object 'PairwiseContestObject' is deleted.
}

int PairwiseContest::electionId() const
{
    return d->election_id;
}

QString PairwiseContest::optionAId() const
{
    return d->option_a_id;
}

void PairwiseContest::setOptionAId(const QString &optionAId)
{
    d->option_a_id = optionAId;
}

QString PairwiseContest::optionBId() const
{
    return d->option_b_id;
}

void PairwiseContest::setOptionBId(const QString &optionBId)
{
    d->option_b_id = optionBId;
}

int PairwiseContest::optionACount() const
{
    return d->option_a_count;
}

void PairwiseContest::setOptionACount(int optionACount)
{
    d->option_a_count = optionACount;
}

int PairwiseContest::optionBCount() const
{
    return d->option_b_count;
}

void PairwiseContest::setOptionBCount(int optionBCount)
{
    d->option_b_count = optionBCount;
}

PairwiseContest &PairwiseContest::operator=(const PairwiseContest &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

PairwiseContest PairwiseContest::create(int electionId, const QString &optionAId, const QString &optionBId, int optionACount, int optionBCount)
{
    PairwiseContestObject obj;
    obj.election_id = electionId;
    obj.option_a_id = optionAId;
    obj.option_b_id = optionBId;
    obj.option_a_count = optionACount;
    obj.option_b_count = optionBCount;
    if (!obj.create()) {
        return PairwiseContest();
    }
    return PairwiseContest(obj);
}

PairwiseContest PairwiseContest::create(const QVariantMap &values)
{
    PairwiseContest model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

QList<PairwiseContest> PairwiseContest::get(int electionId)
{
    return tfGetModelListByCriteria<PairwiseContest, PairwiseContestObject>(TCriteria(PairwiseContestObject::ElectionId, electionId));
}

int PairwiseContest::count()
{
    TSqlORMapper<PairwiseContestObject> mapper;
    return mapper.findCount();
}

QList<PairwiseContest> PairwiseContest::getAll()
{
    return tfGetModelListByCriteria<PairwiseContest, PairwiseContestObject>(TCriteria());
}

QJsonArray PairwiseContest::getAllJson(const QStringList &properties)
{
    return tfConvertToJsonArray(getAll(), properties);
}

TModelObject *PairwiseContest::modelData()
{
    return d.data();
}

const TModelObject *PairwiseContest::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const PairwiseContest &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, PairwiseContest &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}
