#include "main.hpp"
// Use these include for compiling with codegen
//#include "UnityEngine/Rect.hpp" // This needs to be included before RectTransform
//#include "UnityEngine/RectTransform.hpp"
//#include "HMUI/TableView.hpp"
//#include "HMUI/ScrollView.hpp"
//#include "System/Tuple_2.hpp"

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

// Start no codegen version of code
// Defining Tuple_2 Class for use without codegen
template<typename T1, typename T2>
class Tuple_2 : public Il2CppObject {
public:
    T1 m_Item1;
    T2 m_Item2;
    template<::il2cpp_utils::CreationType creationType = ::il2cpp_utils::CreationType::Temporary>
    static Tuple_2<T1, T2>* New_ctor(T1 item1, T2 item2) {
        return THROW_UNLESS((::il2cpp_utils::New<Tuple_2<T1, T2>*, creationType>(item1, item2)));
    }
};
DEFINE_IL2CPP_ARG_TYPE_GENERIC_CLASS(Tuple_2, "System", "Tuple`2");

// Defining Rect struct for use without codegen
struct Rect {
    float m_XMin;
    float m_YMin;
    float m_Width;
    float m_Height;
};
DEFINE_IL2CPP_ARG_TYPE(Rect, "UnityEngine", "Rect");

using TupleType = Tuple_2<int, int>;

MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(
    TableView_GetVisibleCellsIdRange, "HMUI","TableView", "GetVisibleCellsIdRange",
    TupleType*,
    Il2CppObject* self
) {
    //Il2CppObject rect = self->viewportTransform->get_rect();
    //Rect rect = RET_0_UNLESS(getLogger(), il2cpp_utils::RunMethod<Rect>(il2cpp_utils::GetFieldValue(self, "_viewportTransform"), "get_rect"));
    Il2CppObject* viewportTransform = RET_0_UNLESS(getLogger(), il2cpp_utils::GetFieldValue(self, "_viewportTransform"));
    const static MethodInfo* get_rect = RET_0_UNLESS(getLogger(), il2cpp_utils::FindMethodUnsafe(viewportTransform, "get_rect", 0));
    Rect rect = RET_0_UNLESS(getLogger(), il2cpp_utils::RunMethod<Rect, false>(viewportTransform, get_rect));

    int tableType = RET_0_UNLESS(getLogger(), il2cpp_utils::GetFieldValue<int>(self, "_tableType"));
    float height = RET_0_UNLESS(getLogger(), il2cpp_utils::GetPropertyValue<float>(rect, "height"));
    float width = RET_0_UNLESS(getLogger(), il2cpp_utils::GetPropertyValue<float>(rect, "width"));
    float heightWidth = (tableType == 0) ? height : width;

    Il2CppObject* scrollView = RET_0_UNLESS(getLogger(), il2cpp_utils::GetFieldValue(self, "_scrollView"));
    float scrollViewPosition = RET_0_UNLESS(getLogger(), il2cpp_utils::GetPropertyValue<float>(scrollView, "position"));
    float position = (tableType == 0) ? scrollViewPosition : -scrollViewPosition;

    int cellSize = RET_0_UNLESS(getLogger(), il2cpp_utils::GetFieldValue<float>(self, "_cellSize"));
    //getLogger().debug("scrollViewPosition %f, position %f, cellSize %d", scrollViewPosition, position, cellSize);

    int min = floor(position / cellSize + cellSize * 0.001f);
    if (min < 0) {
        min = 0;
    }
    int max = floor((position + heightWidth - cellSize * 0.001f) / cellSize);
    int numberOfCells = RET_0_UNLESS(getLogger(), il2cpp_utils::GetFieldValue<int>(self, "_numberOfCells"));
    if (max > numberOfCells - 1) {
        max = numberOfCells - 1;
    }
//    getLogger().debug("numberOfCells %d, min %d, max %d", numberOfCells, min, max);
    return TupleType::New_ctor(min, max);
}
// End no codegen version

// Codegen version of above code
//using TupleType = System::Tuple_2<int, int>;
//
//MAKE_HOOK_MATCH(
//    TableView_GetVisibleCellsIdRange,
//    &HMUI::TableView::GetVisibleCellsIdRange,
//    TupleType*,
//    HMUI::TableView* self
//) {
//    using namespace HMUI;
//    UnityEngine::Rect rect = self->viewportTransform->get_rect();
//
//    float heightWidth = (self->tableType == TableView::TableType::Vertical) ? rect.get_height() : rect.get_width();
//    float position = (self->tableType == TableView::TableType::Vertical) ? self->scrollView->get_position() : -self->scrollView->get_position();
//
//    int min = floor(position / self->cellSize + self->cellSize * 0.001f);
//    if (min < 0) {
//        min = 0;
//    }
//    getLogger().debug("scrollViewPosition %f, position %f, cellSize %d", self->scrollView->get_position(), position, self->cellSize);
//
//
//    int max = floor((position + heightWidth - self->cellSize * 0.001f) / self->cellSize);
//    if (max > self->numberOfCells - 1) {
//        max = self->numberOfCells - 1;
//    }
//
//    return TupleType::New_ctor(min, max);
//}



extern "C" void load()
{
    INSTALL_HOOK(getLogger(), TableView_GetVisibleCellsIdRange)
}
