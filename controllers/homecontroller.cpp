#include "homecontroller.h"
#include "homeservice.h"

static HomeService homeService;

bool HomeController::preFilter()
{
    if (!isUserLoggedIn()) {
        redirect(url("Account", "form"));
        return false;
    }
    return true;
}

void HomeController::index()
{  
    homeService.index();
    render();
}

// Don't remove below this line
T_DEFINE_CONTROLLER(HomeController)
