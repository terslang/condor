#include "homecontroller.h"
#include "homeservice.h"

static HomeService homeService;

void HomeController::index()
{  
    homeService.index();
    render();
}

// Don't remove below this line
T_DEFINE_CONTROLLER(HomeController)
