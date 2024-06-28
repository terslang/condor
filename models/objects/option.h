#pragma once
#include "tcriteria.h"
#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class OptionObject;
class QJsonArray;


class T_MODEL_EXPORT Option : public TAbstractModel {
public:
    Option();
    Option(const Option &other);
    Option(const OptionObject &object);
    ~Option();

    QString id() const;
    QString name() const;
    void setName(const QString &name);
    QString body() const;
    void setBody(const QString &body);
    int electionId() const;
    void setElectionId(int electionId);
    Option &operator=(const Option &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Option create(const QString &name, const QString &body, int electionId);
    static Option create(const QVariantMap &values);
    static Option get(const QString &id);
    static int count();
    static QList<Option> getAll();
    static QJsonArray getAllJson(const QStringList &properties = QStringList());
    static QList<Option> getByElectionId(int electionId);

private:
    QSharedDataPointer<OptionObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend T_MODEL_EXPORT QDataStream &operator<<(QDataStream &ds, const Option &model);
    friend T_MODEL_EXPORT QDataStream &operator>>(QDataStream &ds, Option &model);
};

Q_DECLARE_METATYPE(Option)
Q_DECLARE_METATYPE(QList<Option>)

