// Scaled image resource
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Resources/ScaledTextureResource.h>

#include <Logging/Logger.h>

namespace OpenEngine {
namespace Resources {

ScaledTextureResource::~ScaledTextureResource() {
    Unload();
}

void ScaledTextureResource::Load() {
    if (loaded) return;
    originalResource->Load();

    width = originalResource->GetWidth() / scale;
    height = originalResource->GetHeight() / scale;
    depth = originalResource->GetDepth();
    unsigned int numberOfCharsPerColor = (depth/8);
    unsigned int size = width * height * numberOfCharsPerColor;

    logger.info << "from:[ ";
    logger.info << "h: " << originalResource->GetHeight();
    logger.info << " w: " << originalResource->GetWidth();
    logger.info << " d: " << originalResource->GetDepth();
    logger.info << " s: " << originalResource->GetHeight()*originalResource->GetWidth()*originalResource->GetDepth();
    logger.info << "]" << logger.end;

    logger.info << "to:[ ";
    logger.info << "h: " << height;
    logger.info << " w: " << width;
    logger.info << " d: " << depth;
    logger.info << " s: " << size;
    logger.info << "]" << logger.end;

    data = new unsigned char[size];

    unsigned char* originalData = originalResource->GetData();

    for (unsigned int i=0,j=0; i<size; 
         i+=numberOfCharsPerColor,j+=scale*numberOfCharsPerColor) {
        for(unsigned int k=0; k<numberOfCharsPerColor; k++) {
            /*
            logger.info << "copying - from: " << j+k;
            logger.info << " to: " << i+k;
            logger.info << " |  j: " << j;
            logger.info << " i: " << i;
            logger.info << " k: " << k;
            logger.info << logger.end;
            */
            data[i+k] = originalData[j+k];           
        }

        //if (i==65) exit(1);
    }

    loaded = true;
}

void ScaledTextureResource::Unload() {
    if (loaded) {
        delete[] data;
        loaded = false;
    }
}

int ScaledTextureResource::GetID(){
    return id;
}

void ScaledTextureResource::SetID(int id){
    this->id = id;
}

int ScaledTextureResource::GetWidth(){
    return width;
}

int ScaledTextureResource::GetHeight(){
    return height;
}

int ScaledTextureResource::GetDepth(){
    return depth;
}

unsigned char* ScaledTextureResource::GetData(){
    return data;
}

} //NS Resources
} //NS OpenEngine
