#include "pch.h"
#include "panel.h"

#include "common/utils.h"
#include "system/serialize.h"

void hierarchy::render()
{
	int h;
	SDL_GetWindowSize(current_window->sdlwindow, nullptr, &h);
	ImGui::SetNextWindowSize({ 310, (float)h });
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::Begin("Hierarchy", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

	if (ImGui::TreeNode("field"))
	{
		for (auto&& tile : current_scene->field->tile_map)
		{
			render_tile_node(&tile);
			ImGui::Spacing();
		}

		ImGui::TreePop();
	}

	if (ImGui::TreeNode("entities"))
	{
		for (int i = 0; i < current_scene->entity_count; i++)
		{
			render_entity_node(current_scene->entities[i]->id, current_scene->entities[i]);
			ImGui::Spacing();
		}

		ImGui::TreePop();
	}

	ImGui::End();
}

void hierarchy::render_tile_node(tile* tile)
{
	if (ImGui::TreeNode(tile, tile->name))
	{
		ImGui::InputScalar("texture index", ImGuiDataType_U8, &tile->texture_index);
		ImGui::InputFloat("x position", &tile->x);
		ImGui::InputFloat("y position", &tile->y);
		ImGui::InputFloat("width",      &tile->w);
		ImGui::InputFloat("height",     &tile->h);
		ImGui::TreePop();

		if (ImGui::BeginPopupContextItem())
		{
			ImGui::Text("rename");
			ImGui::EndPopup();
		}
	}
}

void hierarchy::render_entity_node(uint32_t id, entity_base* entity)
{
	const char* name = entity->name; 

	if (ImGui::TreeNode(entity, name))
	{
		ImGui::InputFloat("x position", &entity->model.x);
		ImGui::InputFloat("y position", &entity->model.y);
		ImGui::InputFloat("width",      &entity->model.w);
		ImGui::InputFloat("height",     &entity->model.h);
		ImGui::Checkbox("collision",    &entity->collision);
		ImGui::Checkbox("controlled",   &entity->control);

		if (ImGui::TreeNode(&entity->hitbox, "hitbox")) // hitbox properties
		{
			entity_base* entity_item;
			ImGui::Text("touching");
			for (int i = 0; i < 8; i++)
			{
				ImGui::Text("	"); // tab
				if (entity->hitbox.touch[i] == nullptr)
				{
					ImGui::SameLine(); ImGui::TextColored(ImVec4{ 0.5, 0.5, 0.5, 1 }, "0x%p", entity->hitbox.touch[i]);
				}
				else
				{
					ImGui::SameLine(); ImGui::Text("0x%p -> %s", entity->hitbox.touch[i], ((entity_base*)entity->hitbox.touch[i])->name);
				}
			}
			ImGui::InputScalar("type", ImGuiDataType_U8, &entity->hitbox.type);

			ImGui::TreePop();
		}
		if (ImGui::TreeNode(&entity->model, "texture"))
		{
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}

	ImGui::PushID(entity);
	if (ImGui::BeginPopupContextItem())
	{
		if (ImGui::MenuItem("delete")) current_scene->delete_entity(id);
		ImGui::EndPopup();
	}
	ImGui::PopID();
}

void info::render()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::Begin("Info", 0, ImGuiWindowFlags_NoCollapse);

	ImGui::InputInt("frame limit",   (signed*)&current_window->framerate);
	ImGui::Checkbox("show hitboxes", &current_scene->display_hitbox);
	ImGui::Checkbox("show entities", &current_scene->display_entities);
	ImGui::Checkbox("show field",    &current_scene->display_field);
	ImGui::Checkbox("collision",     &current_scene->enable_collision);
	ImGui::Text("entities  %u",      current_scene->entity_count);
	ImGui::Text("framerate %.2fms",  io.Framerate);
	ImGui::Text("frametime %ums",    current_window->fc.delta);
	ImGui::Text("lag      ");
	if (current_window->fc.lag)
	{
		ImGui::SameLine(); ImGui::TextColored(ImVec4{ 1, 0.5, 0.5, 1 }, "%ums", current_window->fc.lag);
	}
	else
	{
		ImGui::SameLine(); ImGui::TextColored(ImVec4{ 0.5, 1, 0.5, 1 }, "%ums", current_window->fc.lag);
	}

	if (ImGui::Button("add entity")) current_scene->add_player("entity", 1326 / 2, 720 / 1.25, "red", false);
	if (ImGui::Button("save field")) serialize_field_binary(create_file(), *current_scene);
	if (ImGui::Button("open field")) deserialize_field_binary(open_file(), *current_scene);

	ImGui::End();
}

void memory::render()
{
	ImGui::Begin("Memory", 0, ImGuiWindowFlags_NoCollapse);
	ImGui::End();
}