#pragma once
#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class ElectionObject;
class QJsonArray;


class T_MODEL_EXPORT Election : public TAbstractModel {
public:
    Election();
    Election(const Election &other);
    Election(const ElectionObject &object);
    ~Election();

    int id() const;
    QString name() const;
    void setName(const QString &name);
    QString body() const;
    void setBody(const QString &body);
    int quorum() const;
    void setQuorum(int quorum);
    QString pollingOpen() const;
    void setPollingOpen(const QString &pollingOpen);
    QString pollingClose() const;
    void setPollingClose(const QString &pollingClose);
    QString winnerOptionId() const;
    void setWinnerOptionId(const QString &winnerOptionId);
    Election &operator=(const Election &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Election create(const QString &name, const QString &body, int quorum, const QString &pollingOpen, const QString &pollingClose, const QString &winnerOptionId);
    static Election create(const QVariantMap &values);
    static Election get(int id);
    static QList<Election> getOngoing();
    static QList<Election> getDecided();
    static int count();
    static QList<Election> getAll();
    static QJsonArray getAllJson(const QStringList &properties = QStringList());

private:
    QSharedDataPointer<ElectionObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend T_MODEL_EXPORT QDataStream &operator<<(QDataStream &ds, const Election &model);
    friend T_MODEL_EXPORT QDataStream &operator>>(QDataStream &ds, Election &model);
};

Q_DECLARE_METATYPE(Election)
Q_DECLARE_METATYPE(QList<Election>)

