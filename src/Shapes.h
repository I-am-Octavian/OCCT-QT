#pragma once

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepOffsetAPI_DraftAngle.hxx>
#include <TopExp_Explorer.hxx>
#include <Geom_Plane.hxx>
#include <Precision.hxx>
#include <TopoDS.hxx>

#include "Renderer.h"

const TopoDS_Shape Box(float length, float breadth, float height)
{
	BRepPrimAPI_MakeBox mkBox(length, breadth, height);
	return mkBox.Shape();
}

const TopoDS_Shape Sphere(gp_Pnt& point, float radius)
{

	BRepPrimAPI_MakeSphere mkSphere(point, radius);
	return mkSphere.Shape();
}

const TopoDS_Shape Sphere(float x_coordinate, float y_coordinate, float z_coordinate, float radius)
{
	gp_Pnt point(x_coordinate, y_coordinate, z_coordinate);
	BRepPrimAPI_MakeSphere mkSphere(point, radius);
	return mkSphere.Shape();
}

const TopoDS_Shape Cube(gp_Pnt& Pnt1, gp_Pnt& Pnt2, gp_Pnt& Pnt3, gp_Pnt& Pnt4)
{
	BRepBuilderAPI_MakeEdge Edge1 = BRepBuilderAPI_MakeEdge(Pnt1, Pnt2);
	BRepBuilderAPI_MakeEdge Edge2 = BRepBuilderAPI_MakeEdge(Pnt2, Pnt3);
	BRepBuilderAPI_MakeEdge Edge3 = BRepBuilderAPI_MakeEdge(Pnt3, Pnt4);
	BRepBuilderAPI_MakeEdge Edge4 = BRepBuilderAPI_MakeEdge(Pnt4, Pnt1);
	
	BRepBuilderAPI_MakeWire	Wire1 = BRepBuilderAPI_MakeWire(Edge1.Edge(), Edge2.Edge(), Edge3.Edge(), Edge4.Edge());
	BRepBuilderAPI_MakeWire	Wire2 = BRepBuilderAPI_MakeWire(Edge1, Edge2, Edge3, Edge4);

	BRepBuilderAPI_MakeFace FaceProfile = BRepBuilderAPI_MakeFace(Wire1.Wire());

	gp_Vec PrismVec = gp_Vec(0, 0, 20);
	BRepPrimAPI_MakePrism Body = BRepPrimAPI_MakePrism(FaceProfile.Face(), PrismVec);

	return Body.Shape();
}
/*
const TopoDS_Shape Draft_Angle()
{
	const TopoDS_Shape& S = Box(200, 300, 150);
	BRepOffsetAPI_DraftAngle draft(S);
	TopExp_Explorer topExp = TopExp_Explorer();
	topExp.Init(S, TopAbs_FACE);

	while (topExp.More())
	{
		const TopoDS_Shape& face_shape(topExp.Current());

		Geom_Plane* surf = Handle_Geom_Plane::DownCast(face_shape.TShape()).get();

		gp_Dir dirf = surf->Pln().Axis().Direction();
		gp_Dir ddd = gp_Dir(0, 0, 1);
		if (dirf.IsNormal(ddd, Precision::Angular()))
			draft.Add(TopoDS::Face(face_shape), ddd, 15, gp_Pln(gp_Ax3()));
		topExp.Next();
	}
	draft.Build();
	return draft.Shape();
}
*/