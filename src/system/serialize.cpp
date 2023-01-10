#include "pch.h"
#include "serialize.h"

#include "common/log.h"
#include "common/utils.h"
#include "system/field.h"
#include "system/scene.h"

void serialize_field_binary(const char* dir, scene& _scene)
{
	std::ofstream file;
	file.open(dir, std::ios::out | std::ios::binary);

	// check if file exists
	if (!file.is_open())
	{
		LOG_ERROR("save failed : could not open \"{}\"", dir);
		return;
	}

	// header
	bin_write<const char>("RPG", file, sizeof(char) * 3);
	bin_write<uint32_t>(&_scene.field->width, file);
	bin_write<uint32_t>(&_scene.field->height, file);

	// tile data
	for (tile& it_tile : _scene.field->tile_map)
	{
		bin_write<float>(&it_tile.x, file);
		bin_write<float>(&it_tile.y, file);
		bin_write<float>(&it_tile.w, file);
		bin_write<float>(&it_tile.h, file);
		bin_write<uint8_t>(&it_tile.texture_index, file);
	}

	LOG_INFO("field saved to : \"{}\"", dir);
	file.close();
}

void deserialize_field_binary(const char* dir, scene& _scene)
{
	std::ifstream file;
	tile          tile_buffer;
	uint32_t      offset = 3; // starts at 3 to skip file magic number

	if (_scene.field) delete _scene.field;
	_scene.field = new field();

	file.open(dir, std::ios::in | std::ios::binary);

	if (!file)
	{
		LOG_ERROR("load failed : could not open \"{}\"", dir);
		return;
	}

	bin_read<uint32_t>(&_scene.field->width, file, &offset);
	bin_read<uint32_t>(&_scene.field->height, file, &offset);

	// file sanity check
	if (verify_magic("RPG", file, 3) || _scene.field->width > 25565 || _scene.field->height > 25565)
	{
		LOG_WARN("load warning : potentially corrupt scene file, loading anyways");
		LOG_WARN("field width  = {}", _scene.field->width);
		LOG_WARN("field height = {}", _scene.field->height);
	}

	_scene.field->tile_map.reserve(_scene.field->width * _scene.field->height);

	for (int i = 0; i <= _scene.field->width * _scene.field->height; i++)
	{
		bin_read<float>(&tile_buffer.x, file, &offset);
		bin_read<float>(&tile_buffer.y, file, &offset);
		bin_read<float>(&tile_buffer.w, file, &offset);
		bin_read<float>(&tile_buffer.h, file, &offset);
		bin_read<uint8_t>(&tile_buffer.texture_index, file, &offset);

		_scene.field->tile_map.push_back(tile_buffer);
	}

	file.close();
}
