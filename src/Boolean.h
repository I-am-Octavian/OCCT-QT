#pragma once

#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Cut.hxx>

#include "Shapes.h"

const TopoDS_Shape Draw_Common(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2)
{
	auto Common_Shape = BRepAlgoAPI_Common(shape1, shape2).Shape();
	return Common_Shape;
}

const TopoDS_Shape Draw_Cut(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2)
{
	auto Common_Shape = BRepAlgoAPI_Cut(shape1, shape2).Shape();
	return Common_Shape;
}

const TopoDS_Shape Draw_Fuse(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2)
{
	auto Common_Shape = BRepAlgoAPI_Fuse(shape1, shape2).Shape();
	return Common_Shape;
}
