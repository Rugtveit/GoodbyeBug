#include "include/main.hpp"

static ModInfo modInfo;

Logger& getLogger()
{
    static Logger* logger = new Logger(modInfo);
    return *logger;
}


extern "C" void setup(ModInfo &info)
{
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
}  


MAKE_HOOK_OFFSETLESS(HandleJoystickWasNotCeneteredThisFrame, void, Il2CppObject* self, Vector2 deltaPos)
{
    // If the ViewScroller is Veritcal then run Original code
    // FixScrolling runs the modified version of Horizontal TableView code. 
    if(!GoodbyeBugs::FixScrolling(self, deltaPos, getLogger())) HandleJoystickWasNotCeneteredThisFrame(self, deltaPos);
}



extern "C" void load()
{
    auto* tableViewScrollerMethod = il2cpp_utils::FindMethodUnsafe("HMUI", "TableViewScroller", "HandleJoystickWasNotCenteredThisFrame", 1);
    INSTALL_HOOK_OFFSETLESS(getLogger(), HandleJoystickWasNotCeneteredThisFrame, tableViewScrollerMethod);
}
