#include "ballotservice.h"
#include "objects/ballot.h"
#include <TreeFrogModel>


void BallotService::index()
{
    auto ballotList = Ballot::getAll();
    texport(ballotList);
}

void BallotService::show(const QString &id)
{
    auto ballot = Ballot::get(id);
    texport(ballot);
}

QString BallotService::create(THttpRequest &request)
{
    auto ballot = request.formItems("ballot");
    auto model = Ballot::create(ballot);

    if (model.isNull()) {
        QString error = "Failed to create.";
        texport(error);
        texport(ballot);
        return QString();
    }

    QString notice = "Created successfully.";
    tflash(notice);
    return model.id();
}

void BallotService::edit(TSession& session, const QString &id)
{
    auto model = Ballot::get(id);
    if (!model.isNull()) {
        auto ballot = model.toVariantMap();
        texport(ballot);
    }
}

int BallotService::save(THttpRequest &request, TSession &session, const QString &id)
{
    auto model = Ballot::get(id);
    
    if (model.isNull()) {
        QString error = "Original data not found. It may have been updated/removed by another transaction.";
        tflash(error);
        return 0;
    }

    auto ballot = request.formItems("ballot");
    model.setProperties(ballot);
    if (!model.save()) {
        texport(ballot);
        QString error = "Failed to update.";
        texport(error);
        return -1;
    }

    QString notice = "Updated successfully.";
    tflash(notice);
    return 1;
}

bool BallotService::remove(const QString &id)
{
    auto ballot = Ballot::get(id);
    return ballot.remove();
}

