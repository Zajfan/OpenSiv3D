﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "PointVector.hpp"

namespace s3d
{
	enum class DragItemType
	{
		FilePaths,

		Text
	};

	struct DragStatus
	{
		DragItemType itemType;

		Point pos;
	};

	struct DroppedFilePath
	{
		FilePath path;

		Point pos;

		uint64 timeMillisec;
	};

	struct DroppedText
	{
		String text;

		Point pos;

		uint64 timeMillisec;
	};

	namespace DragDrop
	{
		void AcceptFilePaths(bool accept);

		void AcceptText(bool accept);

		Optional<DragStatus> DragOver();

		bool HasNewFilePaths();

		bool HasNewText();

		void Clear();

		Array<DroppedFilePath> GetDroppedFilePaths();

		Array<DroppedText> GetDroppedText();
	}
}
