#include <TreeFrogModel>
#include "ballotchoice.h"
#include "sqlobjects/ballotchoiceobject.h"
#include "tmodelutil.h"


BallotChoice::BallotChoice() :
    TAbstractModel(),
    d(new BallotChoiceObject())
{
    // set the initial parameters
}

BallotChoice::BallotChoice(const BallotChoice &other) :
    TAbstractModel(),
    d(other.d)
{ }

BallotChoice::BallotChoice(const BallotChoiceObject &object) :
    TAbstractModel(),
    d(new BallotChoiceObject(object))
{ }

BallotChoice::~BallotChoice()
{
    // If the reference count becomes 0,
    // the shared data object 'BallotChoiceObject' is deleted.
}

QString BallotChoice::ballotId() const
{
    return d->ballot_id;
}

void BallotChoice::setBallotId(const QString &ballotId)
{
    d->ballot_id = ballotId;
}

QString BallotChoice::optionId() const
{
    return d->option_id;
}

void BallotChoice::setOptionId(const QString &optionId)
{
    d->option_id = optionId;
}

int BallotChoice::rank() const
{
    return d->rank;
}

void BallotChoice::setRank(int rank)
{
    d->rank = rank;
}

BallotChoice &BallotChoice::operator=(const BallotChoice &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

BallotChoice BallotChoice::create(const QString &ballotId, const QString &optionId, int rank)
{
    BallotChoiceObject obj;
    obj.ballot_id = ballotId;
    obj.option_id = optionId;
    obj.rank = rank;
    if (!obj.create()) {
        return BallotChoice();
    }
    return BallotChoice(obj);
}

BallotChoice BallotChoice::create(const QVariantMap &values)
{
    BallotChoice model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

BallotChoice BallotChoice::update(const QString &ballotId, const QString &optionId, int rank)
{
    BallotChoiceObject obj;
    obj.ballot_id = ballotId;
    obj.option_id = optionId;
    obj.rank = rank;
    if (!obj.update()) {
        return BallotChoice();
    }
    return BallotChoice(obj);
}

BallotChoice BallotChoice::get(const QString &ballotId)
{
    TSqlORMapper<BallotChoiceObject> mapper;
    return BallotChoice(mapper.findByPrimaryKey(ballotId));
}

int BallotChoice::count()
{
    TSqlORMapper<BallotChoiceObject> mapper;
    return mapper.findCount();
}

int BallotChoice::getOutrankingCount(const QString &optionAId, const QString &optionBId)
{
    TSqlQuery query;
    query.prepare("SELECT COUNT(*) "
                  "FROM ballot_choice a "
                  "JOIN ballot_choice b "
                  "ON a.ballot_id = b.ballot_id "
                  "WHERE a.option_id = ? AND b.option_id = ? AND a.rank < b.rank;");
    query.addBind(optionAId).addBind(optionBId);
    query.exec();
    if(query.next())
        return query.value(0).toInt();
    return -1;
}

QList<BallotChoice> BallotChoice::getAll()
{
    return tfGetModelListByCriteria<BallotChoice, BallotChoiceObject>(TCriteria());
}

QJsonArray BallotChoice::getAllJson(const QStringList &properties)
{
    return tfConvertToJsonArray(getAll(), properties);
}

QList<BallotChoice> BallotChoice::getByBallotId(const QString &ballotId)
{
    TCriteria crt(BallotChoiceObject::BallotId, ballotId);
    return tfGetModelListByCriteria<BallotChoice, BallotChoiceObject>(crt);
}

TModelObject *BallotChoice::modelData()
{
    return d.data();
}

const TModelObject *BallotChoice::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const BallotChoice &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, BallotChoice &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}
