#include <TreeFrogModel>
#include "election.h"
#include "sqlobjects/electionobject.h"


Election::Election() :
    TAbstractModel(),
    d(new ElectionObject())
{
    // set the initial parameters
}

Election::Election(const Election &other) :
    TAbstractModel(),
    d(other.d)
{ }

Election::Election(const ElectionObject &object) :
    TAbstractModel(),
    d(new ElectionObject(object))
{ }

Election::~Election()
{
    // If the reference count becomes 0,
    // the shared data object 'ElectionObject' is deleted.
}

int Election::id() const
{
    return d->id;
}

QString Election::name() const
{
    return d->name;
}

void Election::setName(const QString &name)
{
    d->name = name;
}

QString Election::body() const
{
    return d->body;
}

void Election::setBody(const QString &body)
{
    d->body = body;
}

int Election::quorum() const
{
    return d->quorum;
}

void Election::setQuorum(int quorum)
{
    d->quorum = quorum;
}

QString Election::pollingOpen() const
{
    return d->polling_open;
}

void Election::setPollingOpen(const QString &pollingOpen)
{
    d->polling_open = pollingOpen;
}

QString Election::pollingClose() const
{
    return d->polling_close;
}

void Election::setPollingClose(const QString &pollingClose)
{
    d->polling_close = pollingClose;
}

QString Election::winnerOptionId() const
{
    return d->winner_option_id;
}

void Election::setWinnerOptionId(const QString &winnerOptionId)
{
    d->winner_option_id = winnerOptionId;
}

Election &Election::operator=(const Election &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

Election Election::create(const QString &name, const QString &body, int quorum, const QString &pollingOpen, const QString &pollingClose, const QString &winnerOptionId)
{
    ElectionObject obj;
    obj.name = name;
    obj.body = body;
    obj.quorum = quorum;
    obj.polling_open = pollingOpen;
    obj.polling_close = pollingClose;
    obj.winner_option_id = winnerOptionId;
    if (!obj.create()) {
        return Election();
    }
    return Election(obj);
}

Election Election::create(const QVariantMap &values)
{
    Election model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Election Election::get(int id)
{
    TSqlORMapper<ElectionObject> mapper;
    return Election(mapper.findByPrimaryKey(id));
}

int Election::count()
{
    TSqlORMapper<ElectionObject> mapper;
    return mapper.findCount();
}

QList<Election> Election::getAll()
{
    return tfGetModelListByCriteria<Election, ElectionObject>(TCriteria());
}

QList<Election> Election::getOngoing()
{
    return tfGetModelListByCriteria<Election, ElectionObject>(TCriteria(ElectionObject::WinnerOptionId, TSql::IsNull));
}

QList<Election> Election::getDecided()
{
    return tfGetModelListByCriteria<Election, ElectionObject>(TCriteria(ElectionObject::WinnerOptionId, TSql::IsNotNull));
}


QJsonArray Election::getAllJson(const QStringList &properties)
{
    return tfConvertToJsonArray(getAll(), properties);
}

TModelObject *Election::modelData()
{
    return d.data();
}

const TModelObject *Election::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Election &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Election &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}
