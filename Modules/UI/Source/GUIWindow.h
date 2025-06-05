#pragma once
#include "UIExport.h"

namespace Forgex::UI
{
	class UI_API GUIWindow
	{
	public:
		GUIWindow(const char* name, bool isActive = false);
		~GUIWindow();

		void Draw();
	protected:
		virtual void OnDraw() {};
		virtual void Update() {};
	private:
		bool m_IsActive = false;
		const char* m_Name;
	};
}
