﻿# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(1.0, 0.95, 0.9));
	
	const Texture ebi(Emoji::LoadSilhouette(L"🍤"), TextureDesc::Mipped);

	while (System::Update())
	{
		ebi.drawAt(Cursor::Pos());
	}
}
