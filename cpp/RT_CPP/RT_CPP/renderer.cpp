#include "renderer.h"
#include "camera.h"
#include "ray.h"

using namespace cameras;
using namespace utilities;



renderer::renderer(scene_database& db) : db(db)
{

}

void renderer::render()
{
	float width = db.get_scene().get_width();
	float height = db.get_scene().get_height();
	camera& cam = db.get_camera();
	vector<shape&> shapes = db.get_shapes();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			intersection_record& rec = run_intersection(cam, shapes, x, y);
			vector3 pxColor;
			if (rec.hit)
			{
				pxColor.x = 1;
				pxColor.y = 1;
				pxColor.z = 1;
			}
			else
			{
				pxColor = db.get_scene().get_background();
			}
		}
	}
}


intersection_record& renderer::run_intersection(camera const& cam, vector<shape&> const& shapes, int pX, int pY)
{
	intersection_record rec;
	ray r = cam.project(pX, pY);
	for (shape& s : shapes)
	{
		s.intersect(r, rec);
	}
	return rec;

}