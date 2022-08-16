#include "Font.h" 
#include <SDL_ttf.h> 

namespace neu
{
	Font::Font(const std::string& filename, int fontSize)
	{
		Load(filename, fontSize); 
	}

	Font::~Font()
	{
		if (m_ttfFont)
		{
			TTF_CloseFont(m_ttfFont);
			m_ttfFont = nullptr;
		}
	}

	bool Font::Create(const std::string filename, ...)
	{
		return false;
	}

	void Font::Load(const std::string& filename, int fontSize)
	{ 
		m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);
	}
}