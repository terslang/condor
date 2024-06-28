#pragma once
#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT ElectionObject : public TSqlObject, public QSharedData {
public:
    int id {0};
    QString name;
    QString body;
    int quorum {0};
    QString polling_open;
    QString polling_close;
    QVariant result_id; // modified from int -> QVariant. As int cant be null but the column is nullable

    enum PropertyIndex {
        Id = 0,
        Name,
        Body,
        Quorum,
        PollingOpen,
        PollingClose,
        ResultId,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return Id; }
    QString tableName() const override { return QStringLiteral("election"); }

private:    /*** Don't modify below this line (You can't tell me what to do. You're not my mom ) ***/
    Q_OBJECT
    Q_PROPERTY(int id READ getid WRITE setid)
    T_DEFINE_PROPERTY(int, id)
    Q_PROPERTY(QString name READ getname WRITE setname)
    T_DEFINE_PROPERTY(QString, name)
    Q_PROPERTY(QString body READ getbody WRITE setbody)
    T_DEFINE_PROPERTY(QString, body)
    Q_PROPERTY(int quorum READ getquorum WRITE setquorum)
    T_DEFINE_PROPERTY(int, quorum)
    Q_PROPERTY(QString polling_open READ getpolling_open WRITE setpolling_open)
    T_DEFINE_PROPERTY(QString, polling_open)
    Q_PROPERTY(QString polling_close READ getpolling_close WRITE setpolling_close)
    T_DEFINE_PROPERTY(QString, polling_close)
    Q_PROPERTY(QVariant result_id READ getresult_id WRITE setresult_id)
    T_DEFINE_PROPERTY(QVariant, result_id)
};

