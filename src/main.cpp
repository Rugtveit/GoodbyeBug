#include "include/main.hpp"

static ModInfo modInfo;

static Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

const Logger& getLogger() {
  static const Logger& logger(modInfo);
  return logger;
}


extern "C" void setup(ModInfo &info)
{
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
}  

MAKE_HOOK_OFFSETLESS(PracticeViewController_Init, void, Il2CppObject* self, Il2CppObject* level, Il2CppObject* beatmapCharacteristics, Il2CppObject* beatmapDifficulty)
{
    // Running first game code first
    PracticeViewController_Init(self, level, beatmapCharacteristics, beatmapDifficulty);
    
    // Fixing practice speed lsider bug
    // Changing speed slider to be 31 number of steps
    GoodbyeBugs::FixSlider(self);
}

MAKE_HOOK_OFFSETLESS(HandleJoystickWasNotCeneteredThisFrame, void, Il2CppObject* self, Vector2 deltaPos)
{
    // If the ViewScroller is Veritcal then run Original code
    // FixScrolling runs the modified version of Horizontal TableView code. 
    if(!GoodbyeBugs::FixScrolling(self, deltaPos)) HandleJoystickWasNotCeneteredThisFrame(self, deltaPos);
}



extern "C" void load()
{
    auto* practiceViewControllerMethod = il2cpp_utils::FindMethodUnsafe("", "PracticeViewController", "Init", 3);
    auto* tableViewScrollerMethod = il2cpp_utils::FindMethodUnsafe("HMUI", "TableViewScroller", "HandleJoystickWasNotCenteredThisFrame", 1);
    INSTALL_HOOK_OFFSETLESS(PracticeViewController_Init, practiceViewControllerMethod);
    INSTALL_HOOK_OFFSETLESS(HandleJoystickWasNotCeneteredThisFrame, tableViewScrollerMethod);
}
