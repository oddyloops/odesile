#include "renderer.h"
#include "camera.h"
#include "ray.h"

using namespace cameras;
using namespace utility;



renderer::renderer(scene_database& db) : db(db)
{

}

vector3** renderer::render()
{
	int width = db.get_scene().get_width();
	int height = db.get_scene().get_height();
	camera& cam = db.get_camera();
	vector<shape*> shapes = db.get_shapes();
	vector3** finalImages = new vector3*[height];
	for (int y = 0; y < height; y++)
	{
		finalImages[y] = new vector3[width];
		for (int x = 0; x < width; x++)
		{
			intersection_record* rec = run_intersection(cam, shapes, x, y);
			vector3 pxColor;
			if (rec->hit)
			{
				shape* shape = db.get_shape_by_id(rec->shape_id);
				material* material = db.get_material_by_id(shape->get_material_id());
				pxColor = shape->paint(*rec, db.get_lights(),  db.get_scene().get_ambient_light(), cam.get_view_direction(),db.get_scene().get_generation(),
					&shapes,&db.get_materials());
			}
			else
			{
				pxColor = db.get_scene().get_background();
			}
			finalImages[y][x] = pxColor;
			delete rec;
		}

	}
	return finalImages;
}


intersection_record* renderer::run_intersection(camera const& cam, vector<shape*> const& shapes, int pX, int pY)
{
	intersection_record* rec = new intersection_record;
	ray r = cam.project(pX, pY);
	for (shape* s : shapes)
	{
		s->intersect(r, *rec);
	}
	return rec;

}