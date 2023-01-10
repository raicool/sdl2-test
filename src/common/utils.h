#pragma once

#include "type.h"
#include "system/texture.h"

static char dir_buf[256]{ 0 };

template<typename T>
vector2<T> texture_size(std::string identifier)
{
	int32_t checkw, checkh;
	SDL_QueryTexture(texture::get_texture(identifier), NULL, NULL, &checkw, &checkh);
//	LOG_TRACE("Texture dimensions: {}, {}", checkw, checkh);

	return vector2<T>{ (T)checkw, (T)checkh };
}

// file management

/*
*	returns an fstream from an open file dialog
*	@param mode - ios open mode flags (ex: std::ios::binary | std::ios::in)
*/
static std::fstream open_file_s(uint32_t mode)
{
	std::fstream file;
#ifdef WIN32
	OPENFILENAMEA f{ 0 };
	f.lStructSize  = sizeof(f);
	f.lpstrFile    = dir_buf;         //< file name
	f.nMaxFile     = sizeof(dir_buf); //< max directory length
	f.lpstrFilter  = "All\0*.*\0Binary (*.bin)\0*.bin\0";
	f.nFilterIndex = 1;
	f.Flags        = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	GetOpenFileNameA(&f) ? LOG_INFO("file \"{}\" found", dir_buf) : void();
	file.open(dir_buf, mode);
#endif
	return file;
}

/*
*	returns a char array of the absolute path to a file from an open file dialog
*/
static const char* open_file()
{
#ifdef WIN32
	OPENFILENAMEA f{ 0 };
	f.lStructSize  = sizeof(f);
	f.lpstrFile    = dir_buf;         //< file name
	f.nMaxFile     = sizeof(dir_buf); //< max directory length
	f.lpstrFilter  = "All\0*.*\0Binary (*.bin)\0*.bin\0";
	f.nFilterIndex = 1;
	f.Flags        = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	GetOpenFileNameA(&f) ? LOG_INFO("file \"{}\" found", dir_buf) : void();
#endif
	return dir_buf;
}

/*
*	creates an empty file from a save file prompt and returns the absolute path
*/
static const char* create_file()
{
#ifdef WIN32
	OPENFILENAMEA f{ 0 };
	f.lStructSize  = sizeof(f);
	f.lpstrFile    = dir_buf;         //< file name
	f.nMaxFile     = sizeof(dir_buf); //< max directory length
	f.lpstrFilter  = "All\0*.*\0Binary (*.bin)\0*.bin\0";
	f.nFilterIndex = 1;
	f.Flags = OFN_PATHMUSTEXIST;
	GetSaveFileNameA(&f) ? LOG_INFO("file \"{}\" created", dir_buf) : void();
#endif
	return dir_buf;
}

/*
*	writes a set amount of bytes in a ofstream as a const char*
*	@param src  - location to copy data from to file
*   @param dst  - file's output stream
*   @param size - size of the data in bytes (optional, set to sizeof(T) if not specified)
*/
template<typename T>
static void bin_write(T* src, std::ofstream& dst, size_t size = sizeof(T))
{
	dst.write(reinterpret_cast<const char*>(src), size);
}

/*
*	read a set amount of bytes in a ifstream as a char*
*	@param dst    - location to copy file data to
*   @param src    - file's input stream
*   @param offset - offset of the data in file, in bytes (optional, set to 0 if not specified)
*	@param size   - size of the data in bytes (optional, set to sizeof(T) if not specified)
*/
template<typename T>
static void bin_read(T* dst, std::ifstream& src, uint32_t offset = 0, size_t size = sizeof(T))
{
	src.seekg(offset);
	src.read(reinterpret_cast<char*>(dst), size);
}

/* 
*	read a set amount of bytes in a ifstream as a char* 
*	@param dst    - location to copy file data to
*   @param src    - file's input stream
*	@param offset - pointer to offset of the data in file, in bytes (adds size param to offset after read)
*   @param size   - size of the data in bytes (optional, set to sizeof(T) if not specified)
*/
template<typename T>
static void bin_read(T* dst, std::ifstream& src, uint32_t* offset, size_t size = sizeof(T))
{
	src.seekg(*offset);
	src.read(reinterpret_cast<char*>(dst), size);
	*offset += size;
}

/*
*	verifies a file's magic number
*	@param header - header to look for
*	@param src    - file's input stream
*	@param size   - size of the magic number in bytes
*/
static bool verify_magic(const char* header, std::ifstream& src, uint8_t size)
{
	char* header_buffer = new char[32];
	bin_read<char>(header_buffer, src, 0u, sizeof(char) * size);
	header_buffer[size] = 0x00;

	return strcmp(header_buffer, header) != 0;
	delete[] header_buffer;
}