#include "Parsers.h"
#include <fstream>

#include <unordered_map>

//function that splits a string into an std::vector of strings
void split(std::string to_split, std::string delim, std::vector<std::string>& result) {

}

//parses a wavefront object into passed arrays
bool Parsers::parseOBJ(std::string filename, std::vector<float>& vertices, std::vector<float>& uvs, std::vector<float>& normals, std::vector<unsigned int>& indices) {

    std::vector<lm::vec3> aux_vert;
    std::vector<lm::vec2> aux_uvs;
    std::vector<lm::vec3> aux_norm;
	std::unordered_map<std::string, int> index_map;

	std::ifstream in(filename, std::ios::in);

	if (!in)
	{
		std::cerr << "Cannot open " << filename << std::endl;
		return false;
	}
    
	std::string line;

	while (getline(in, line))
	{
		char delimiter = ' ';
		int pos = 0;
		std::vector<std::string> tokens;
        line.push_back(delimiter);

		while ((pos = line.find(delimiter)) != std::string::npos) {
			tokens.push_back(line.substr(0, pos));
			line.erase(0, pos + 1);
		}

		if (tokens.empty()) continue;
        		
        if (tokens[0].compare("v") == 0) 
        {
			lm::vec3 vertex;
			vertex.x = std::stof(tokens[1]);
			vertex.y = std::stof(tokens[2]);
			vertex.z = std::stof(tokens[3]);

			aux_vert.push_back(vertex);
		}
		else if (tokens[0].compare("vt") == 0) 
        {
			lm::vec2 uv;
			uv.x = std::stof(tokens[1]);
			uv.y = std::stof(tokens[2]);

			aux_uvs.push_back(uv);
		}
		else if (tokens[0].compare("vn") == 0) 
        {
			lm::vec3 normal;
			normal.x = std::stof(tokens[1]);
			normal.y = std::stof(tokens[2]);
			normal.z = std::stof(tokens[3]);

			aux_norm.push_back(normal);
		}
		else if (tokens[0].compare("f") == 0) 
        {
            int size = tokens.size();    
			for (int i = 1; i < 4; i++) 
            {
				std::vector<std::string> faces_tokens;
				std::string aux = tokens[i];

				char delimiter = '/';
				int pos = 0;
                aux.push_back(delimiter);

				while ((pos = aux.find(delimiter)) != std::string::npos) 
                {
					faces_tokens.push_back(aux.substr(0, pos));
					aux.erase(0, pos + 1);
				}
                
                if (index_map.count(tokens[i]) == 0)
                {
                    index_map.insert(std::make_pair(tokens[i], index_map.size()));

                    lm::vec3 cur_vert = aux_vert[std::stoi(faces_tokens[0])];
                    vertices.push_back(cur_vert.x);
                    vertices.push_back(cur_vert.y);
                    vertices.push_back(cur_vert.z);

                    lm::vec2 cur_uv = aux_uvs[std::stoi(faces_tokens[1])];
                    uvs.push_back(cur_uv.x);
                    uvs.push_back(cur_uv.y);

                    lm::vec3 cur_norm = aux_norm[std::stoi(faces_tokens[2])];
                    normals.push_back(cur_norm.x);
                    normals.push_back(cur_norm.y);
                    normals.push_back(cur_norm.z);
                }

                indices.push_back(index_map[tokens[i]]);
			}

            if ( size == 5 )
            {
                for ( int i = 1; i < 5; i++ )
                {
                    if ( i == 2 ) continue;

                    std::vector<std::string> face_tokens;
                    std::string aux = tokens[i];

                    char delimiter = '/';
                    int pos = 0;
                    aux.push_back(delimiter);

                    while ((pos = aux.find(delimiter)) != std::string::npos) 
                    {
                        face_tokens.push_back(aux.substr(0, pos));
                        aux.erase(0, pos + 1);
                    }
                    
                    if (index_map.count(tokens[i]) == 0)
                    {

                        index_map.insert(std::make_pair(tokens[i], index_map.size()));

                        lm::vec3 cur_vert = aux_vert[std::stoi(face_tokens[0])];
                        vertices.push_back(cur_vert.x);
                        vertices.push_back(cur_vert.y);
                        vertices.push_back(cur_vert.z);

                        lm::vec2 cur_uv = aux_uvs[std::stoi(face_tokens[1])];
                        uvs.push_back(cur_uv.x);
                        uvs.push_back(cur_uv.y);

                        lm::vec3 cur_norm = aux_norm[std::stoi(face_tokens[2])];
                        normals.push_back(cur_norm.x);
                        normals.push_back(cur_norm.y);
                        normals.push_back(cur_norm.z);
                    }

                    indices.push_back(index_map[tokens[i]]);
                }
            }
		}
	}

    return true;
}

// load uncompressed RGB targa file into an OpenGL texture
GLint Parsers::parseTexture(std::string filename) {
	std::string str = filename;
	std::string ext = str.substr(str.size() - 4, 4);


	GLuint texture_id;

	if (ext == ".tga" || ext == ".TGA")
	{
		TGAInfo* tgainfo = loadTGA(filename);
		if (tgainfo == NULL) {
			std::cerr << "ERROR: Could not load TGA file" << std::endl;
			return false;
		}

		//generate new openGL texture and bind it (tell openGL we want to do stuff with it)
		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id); //we are making a regular 2D texture

												  //screen pixels will almost certainly not be same as texture pixels, so we need to
												  //set some parameters regarding the filter we use to deal with these cases
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//set the mag filter
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //set the min filter
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4); //use anisotropic filtering

																		  //this is function that actually loads texture data into OpenGL
		glTexImage2D(GL_TEXTURE_2D, //the target type, a 2D texture
			0, //the base level-of-detail in the mipmap
			(tgainfo->bpp == 24 ? GL_RGB : GL_RGBA), //specified the color channels for opengl
			tgainfo->width, //the width of the texture
			tgainfo->height, //the height of the texture
			0, //border - must always be 0
			(tgainfo->bpp == 24 ? GL_BGR : GL_BGRA), //the format of the incoming data
			GL_UNSIGNED_BYTE, //the type of the incoming data
			tgainfo->data); // a pointer to the incoming data

							//we want to use mipmaps
		glGenerateMipmap(GL_TEXTURE_2D);

		//clean up memory
		delete tgainfo->data;
		delete tgainfo;
		return texture_id;
	}
	else {
		std::cerr << "ERROR: No extension or extension not supported" << std::endl;
		return -1;
	}
}

// this reader supports only uncompressed RGB targa files with no colour table
TGAInfo* Parsers::loadTGA(std::string filename)
{
	//the TGA header is 18 bytes long. The first 12 bytes are for specifying the compression
	//and various fields that are very infrequently used, and hence are usually 0.
	//for this limited file parser, we start by reading the first 12 bytes and compare
	//them against the pattern that identifies the file a simple, uncompressed RGB file.
	//more info about the TGA format cane be found at http://www.paulbourke.net/dataformats/tga/

	char TGA_uncompressed[12] = { 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
	char TGA_compare[12];
	char info_header[6];
	GLuint bytes_per_pixel;
	GLuint image_size;

	//open file
	std::ifstream file(filename, std::ios::binary);

	//read first 12 bytes
	file.read(&TGA_compare[0], 12);
	std::streamsize read_header_12 = file.gcount();
	//compare to check that file in uncompressed (or not corrupted)
	int header_compare = memcmp(TGA_uncompressed, TGA_compare, sizeof(TGA_uncompressed));
	if (read_header_12 != sizeof(TGA_compare) || header_compare != 0) {
		std::cerr << "ERROR: TGA file is not in correct format or corrupted: " << filename << std::endl;
		file.close();
		return nullptr;
	}

	//read in next 6 bytes, which contain 'important' bit of header
	file.read(&info_header[0], 6);

	TGAInfo* tgainfo = new TGAInfo;

	tgainfo->width = info_header[1] * 256 + info_header[0]; //width is stored in first two bytes of info_header
	tgainfo->height = info_header[3] * 256 + info_header[2]; //height is stored in next two bytes of info_header

	if (tgainfo->width <= 0 || tgainfo->height <= 0 || (info_header[4] != 24 && info_header[4] != 32)) {
		file.close();
		delete tgainfo;
		std::cerr << "ERROR: TGA file is not 24 or 32 bits, or has no width or height: " << filename << std::endl;
		return NULL;
	}

	//calculate bytes per pixel and then total image size in bytes
	tgainfo->bpp = info_header[4];
	bytes_per_pixel = tgainfo->bpp / 8;
	image_size = tgainfo->width * tgainfo->height * bytes_per_pixel;

	//reserve memory for the image data
	tgainfo->data = (GLubyte*)malloc(image_size);

	//read data into memory
	file.read((char*)tgainfo->data, image_size);
	std::streamsize image_read_size = file.gcount();

	//check it has been read correctly
	if (image_read_size != image_size) {
		if (tgainfo->data != NULL)
			free(tgainfo->data);
		file.close();
		std::cerr << "ERROR: Could not read tga data: " << filename << std::endl;
		delete tgainfo;
		return NULL;
	}

	file.close();

	return tgainfo;
}
