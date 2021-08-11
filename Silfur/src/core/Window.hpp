#pragma once

#include "defines.hpp"

#include <memory>
#include <string>

namespace Silfur
{
    class SF_API Window
    {
    public:
        virtual ~Window() = default;

        static std::unique_ptr<Window> Create(const std::string& p_title, int p_width, int p_height);
        virtual void Update() = 0;
        virtual inline bool Closed() const = 0;

    private:
        virtual void Init(const std::string& p_title, int p_width, int p_height) = 0;
        virtual bool Shutdown() = 0;
    };
}
