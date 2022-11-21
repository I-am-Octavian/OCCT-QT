#include "Renderer.h"
#include "Shapes.h"
#include "Boolean.h"
#include "Viewer.h"

// Uncomment to use Nvidia GPU
/*
extern "C"
{
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
*/

int main()
{
	/*
	const TopoDS_Shape& shape = Draw_Fuse(BRepPrimAPI_MakeBox(10, 10, 20), BRepPrimAPI_MakeBox(20, 30, 10));
	
	Renderer renderer;
	renderer.Render(shape);
	*/
	
	Viewer vout(50, 50, 500, 500);
	vout << BRepPrimAPI_MakeBox(10, 10, 20) << BRepPrimAPI_MakeBox(20, 30, 10);
	vout.StartMessageLoop();
	return 0;
}
