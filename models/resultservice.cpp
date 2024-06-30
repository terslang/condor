#include "resultservice.h"
#include "objects/election.h"
#include "objects/option.h"
#include <TreeFrogModel>

void ResultService::show(int id)
{
    auto election = Election::get(id);
    auto optionList = Option::getByElectionId(id);
    texport(election);
    texport(optionList);
}

int ResultService::create(THttpRequest &request)
{
    auto election = request.formItems("election");
    auto model = Election::create(election);

    if (model.isNull()) {
        QString error = "Failed to create.";
        texport(error);
        texport(election);
        return -1;
    }

    QString notice = "Created successfully.";
    tflash(notice);
    return model.id();
}
