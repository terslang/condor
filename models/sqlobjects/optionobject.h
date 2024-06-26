#pragma once
#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT OptionObject : public TSqlObject, public QSharedData {
public:
    QString id;
    QString name;
    QString body;
    int election_id {0};

    enum PropertyIndex {
        Id = 0,
        Name,
        Body,
        ElectionId,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return -1; }
    QString tableName() const override { return QStringLiteral("option"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(QString id READ getid WRITE setid)
    T_DEFINE_PROPERTY(QString, id)
    Q_PROPERTY(QString name READ getname WRITE setname)
    T_DEFINE_PROPERTY(QString, name)
    Q_PROPERTY(QString body READ getbody WRITE setbody)
    T_DEFINE_PROPERTY(QString, body)
    Q_PROPERTY(int election_id READ getelection_id WRITE setelection_id)
    T_DEFINE_PROPERTY(int, election_id)
};

