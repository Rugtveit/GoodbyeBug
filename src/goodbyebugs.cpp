#include "../include/goodbyebugs.hpp"

void setScrollDirection(Il2CppObject* self, int direction, Logger& log)
{
    RET_V_UNLESS(log, il2cpp_utils::SetFieldValue(self, "_lastJoystickScrollDirection", direction));
}


bool GoodbyeBugs::FixScrolling(Il2CppObject* self, Vector2 deltaPos, Logger& log)
{
    RET_0_UNLESS(log, il2cpp_utils::SetPropertyValue(self, "enabled", false));

    Il2CppObject* tableView =   RET_0_UNLESS(log, il2cpp_utils::GetFieldValue(self, "_tableView"));
    int tableType =             RET_0_UNLESS(log, il2cpp_utils::GetFieldValue<int>(tableView, "_tableType"));
    if(tableType == 0)          return false;

    if(deltaPos.x > 0.0f)       setScrollDirection(self, 4, log);
    else if(deltaPos.x < 0.0f)  setScrollDirection(self, 2, log);
    else                        setScrollDirection(self, 0, log);
        
    float scrollableSize =  RET_0_UNLESS(log, il2cpp_utils::GetFieldValue<float>(self, "_scrollableSize"));
    float position =        RET_0_UNLESS(log, il2cpp_utils::GetPropertyValue<float>(self, "position"));
    float timeDelta =       RET_0_UNLESS(log, il2cpp_utils::RunMethod<float>("UnityEngine", "Time", "get_deltaTime"));
    float num2 =            position - deltaPos.x * timeDelta * 60;
    
    scrollableSize = -scrollableSize;
    if(num2 < scrollableSize) num2 = scrollableSize;
    if(num2 > 0.0f ) num2 = 0.0f; 

    RET_0_UNLESS(log, il2cpp_utils::SetPropertyValue(self, "position", num2));
    RET_0_UNLESS(log, il2cpp_utils::SetFieldValue(self, "_targetPosition", num2));
    RET_0_UNLESS(log, il2cpp_utils::RunMethod(self, "RefreshScrollBar"));
    return true; 
}