#pragma once

#include "../CoreExports.h"
#include <string>


namespace Forgex::Core::HeaderSystem
{
    enum CORE_API VariableType
	{
		Text, Float, Int, Vector3, Vector2, Boolean
	};

    class CORE_API VariableData
    {
    public:
        VariableData() {}
        ~VariableData() {}

        std::string GetName() { return m_Name; }

    protected:
        std::string m_Name;
        void* valuePtr;
        size_t m_Offset;
    };

    class CORE_API FloatData : public VariableData
    {
    public:
        FloatData(float value) : VariableData(), m_Value(value) {}
        ~FloatData() {}

        void SetValue(float newValue) {}
        float* GetValuePtr() { return &m_Value; }
    private:
        float m_Value;
    };

    class CORE_API BoolData : public VariableData
    {
    public:
        BoolData(bool value) : VariableData(), m_Value(value) {}
        ~BoolData() {}

        void SetValue(bool newValue) {}
        bool* GetValuePtr() { return &m_Value; }
    private:
        bool m_Value;
    };

    class CORE_API Vec3Data : public VariableData
    {
    };

    class CORE_API UVec2Data : public VariableData
    {
    };
}
