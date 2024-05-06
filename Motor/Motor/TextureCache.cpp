#include "TextureCache.h"
#include "ImageLoader.h"

TextureCache::TextureCache()
{

}

TextureCache::~TextureCache()
{

}

GLTexture TextureCache::getTexture(string texturePath)
{
	//OPCION 1
	/*map<string, GLTexture>::iterator mit 
				= textureMap.find(texturePath);*/
	//OPCION 2
	auto mit = textureMap.find(texturePath);
	if (mit == textureMap.end()) {
		GLTexture texture = ImageLoader::loadPng(texturePath);
		//OPCION 1
		/*pair<string, GLTexture> newPair(texturePath, texture);
		textureMap.insert(newPair);*/
		//OPCION 2
		textureMap[texturePath] = texture;
		return texture;
	}
	return mit->second;
}
