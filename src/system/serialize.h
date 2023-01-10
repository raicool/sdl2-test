#pragma once

struct scene;

void serialize_field_yaml(const char* dir, scene& current_scene);
void serialize_field_binary(const char* dir, scene& current_scene);
void deserialize_field_yaml(const char* dir, scene& current_scene);
void deserialize_field_binary(const char* dir, scene& current_scene);