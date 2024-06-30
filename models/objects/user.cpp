#include <TreeFrogModel>
#include <qcryptographichash.h>
#include "user.h"
#include "sqlobjects/userobject.h"


User::User() :
    TAbstractUser(),
    TAbstractModel(),
    d(new UserObject())
{
    // set the initial parameters
}

User::User(const User &other) :
    TAbstractUser(),
    TAbstractModel(),
    d(other.d)
{ }

User::User(const UserObject &object) :
    TAbstractUser(),
    TAbstractModel(),
    d(new UserObject(object))
{ }


User::~User()
{
    // If the reference count becomes 0,
    // the shared data object 'UserObject' is deleted.
}

QString User::email() const
{
    return d->email;
}

void User::setEmail(const QString &email)
{
    d->email = email;
}

QString User::password() const
{
    return d->password;
}

void User::setPassword(const QString &password)
{
    d->password = password;
}

User &User::operator=(const User &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

User User::authenticate(const QString &email, const QString &password)
{
    if (email.isEmpty() || password.isEmpty())
        return User();

    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex());
    qDebug() << "HASHED" << hashedPassword;
    
    TSqlORMapper<UserObject> mapper;
    UserObject obj = mapper.findFirst(TCriteria(UserObject::Email, email));
    if (obj.isNull() || obj.password != hashedPassword) {
        obj.clear();
    }
    return User(obj);
}

User User::create(const QString &email, const QString &password)
{
    UserObject obj;
    obj.email = email;
    obj.password = password;
    if (!obj.create()) {
        return User();
    }
    return User(obj);
}

User User::create(const QVariantMap &values)
{
    User model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

User User::get(const QString &email)
{
    TSqlORMapper<UserObject> mapper;
    return User(mapper.findByPrimaryKey(email));
}

int User::count()
{
    TSqlORMapper<UserObject> mapper;
    return mapper.findCount();
}

QList<User> User::getAll()
{
    return tfGetModelListByCriteria<User, UserObject>();
}

QJsonArray User::getAllJson(const QStringList &properties)
{
    return tfConvertToJsonArray(getAll(), properties);
}

TModelObject *User::modelData()
{
    return d.data();
}

const TModelObject *User::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const User &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, User &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}
