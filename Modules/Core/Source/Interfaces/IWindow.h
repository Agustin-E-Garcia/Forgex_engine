#pragma once

namespace Forgex::Core::Interfaces
{
    class IWindow
    {
    public:
        virtual ~IWindow() = default;

        virtual void Update() = 0;
        virtual bool ShouldClose() const = 0;

        virtual int GetWidth() { return m_Width; }
        virtual int GetHeight() { return m_Height; }

    protected:
        int m_Width;
        int m_Height;
    };
}
