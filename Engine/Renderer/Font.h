#pragma once 
#include "Resource/Resource.h"
#include <string>

struct _TTF_Font;

namespace neu
{

	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		bool Create(const std::string filename, ...) override;
		void Load(const std::string& filename, int fontSize);

		friend class Text;
		friend class Renderer;

	private:
		_TTF_Font* m_ttfFont = nullptr;
	};
}