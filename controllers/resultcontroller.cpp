#include "resultcontroller.h"
#include "resultservice.h"

static ResultService resultService;

void ResultController::show(const QString &id)
{
    resultService.show(id.toInt());
    render();
}

void ResultController::create()
{
}

// Don't remove below this line
T_DEFINE_CONTROLLER(ResultController)
