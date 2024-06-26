#include "optioncontroller.h"
#include "optionservice.h"
#include <TreeFrogController>

static OptionService service;


void OptionController::index()
{
    service.index();
    render();
}

void OptionController::show(const QString &id)
{
    service.show(id);
    render();
}

void OptionController::create()
{
    QString id;

    switch (request().method()) {
    case Tf::Get:
        render();
        break;
    case Tf::Post:
        id = service.create(request());
        if (!id.isEmpty()) {
            redirect(urla("show", id));
        } else {
            render();
        }
        break;
    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void OptionController::save(const QString &id)
{
    int res;

    switch (request().method()) {
    case Tf::Get:
        service.edit(session(), id);
        render();
        break;
    case Tf::Post:
        res = service.save(request(), session(), id);
        if (res > 0) {
            // Save completed
            redirect(urla("show", id));
        } else if (res < 0) {
            // Failed
            render();
        } else {
            // Retry
            redirect(urla("save", id));
        }
        break;
    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void OptionController::remove(const QString &id)
{
    switch (request().method()) {
    case Tf::Post:
        service.remove(id);
        redirect(urla("index"));
        break;
    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

// Don't remove below this line
T_DEFINE_CONTROLLER(OptionController)
