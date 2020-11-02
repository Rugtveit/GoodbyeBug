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

// Making the hook
// public static bool SetActiveScene(Scene scene)
// It's a static method, so there's no instance
// it expects a bool return 
// and has 1 variable which is Scene
// If the type isn't in typedef or you aren't using codegen then use Il2CppObject*
MAKE_HOOK_OFFSETLESS(SceneManager_SetActiveScene, bool, Scene scene)
{
    // Getting C# String from scene handle
    // private static extern string GetNameInternal(int sceneHandle);
    Il2CppString* sceneCsString = RET_V_UNLESS(il2cpp_utils::RunMethod("UnityEngine.SceneManagement", "Scene", "GetNameInternal", scene.m_Handle));

    // Converting from C# string to string
    // Converting from to_utf16 to utf8 string
    std::string sceneCppString = to_utf8(csstrtostr(sceneCsString));

    // Priting out current active scene
    getLogger().debug("Current active scene: %s", sceneCppString.data());

    // Running the original method
    return SceneManager_SetActiveScene(scene);
}



extern "C" void load()
{
    // Installing the hook
    // We first give it the name of our hook we made
    // Then we need to provide it with methodinfo* to find out where to hook
    // We run FindMethodUnsafe and provide it, namespace, klass, method and parameter count.
    INSTALL_HOOK_OFFSETLESS(SceneManager_SetActiveScene, il2cpp_utils::FindMethodUnsafe("UnityEngine.SceneManagement", "SceneManager", "SetSceneActive", 1));
}
