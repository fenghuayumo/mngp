#pragma once
#include <string>

namespace NerfShot
{
    class EditorWindow
    {
    public:
        public:

		bool& Active()
		{
			return m_Active;
		}
		void SetActive(bool active)
		{
			m_Active = active;
		}

		void SetApplication(class Application* editor) { m_Editor = editor; }
		virtual void OnImGui() = 0;
	protected:
		bool m_Active = true;
		std::string m_Name;
		std::string m_SimpleName;
		class Application* m_Editor;
    };
}