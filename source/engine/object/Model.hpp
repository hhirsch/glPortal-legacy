#ifndef __MODEL_HPP
#define __MODEL_HPP

#include "../../Exception.hpp"

#include <cstdio>
#include <string>
#include "Mesh.hpp"
#include <vector>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include <FreeImage.h>


#include <iostream>


using namespace std;

namespace glPortal {
  namespace engine {
    namespace object {

      class Model{
      public:
	      Model(const string & filename);
	      void draw();
	      void setPosition(int x, int y, int z);
	      void loadTextures(const struct aiScene *sc, const struct aiNode* nd);
            private:
	      vector<Mesh*> meshes;
	      const aiScene* scene;
	      Assimp::Importer* importer;
      };
    }
  }
}
#endif
