#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

// file input/output
#include <fstream>

// when the string is loaded
#include <sstream>
#include <vector>

class WavefrontObj {
private:
    std::vector<glm::vec3> pos_vector;
    std::vector<glm::vec2> tex_vector;
public:
    WavefrontObj(const char* loc);
};

WavefrontObj::WavefrontObj(const char* loc){
    std::ifstream file(loc);
    std::string buffer;
    
    std::string name;
    glm::vec3 pos;
    glm::vec2 tex;

    while(getline(file, buffer)){
        std::stringstream stream(buffer);
        stream >> name;
        if (name == "v") break;
    }

    while(name == "v"){
        std::stringstream stream(buffer);
        stream >> name >> pos.x >> pos.y >> pos.z;
        this->pos_vector.push_back(pos);
        std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
        getline(file, buffer);
    }

    while(name == "vt"){
        std::stringstream stream(buffer);
        stream >> name >> tex.x >> tex.y;
        this->tex_vector.push_back(tex);
        std::cout << tex.x << " " << tex.y << std::endl;
        getline(file, buffer);
    }

    while(getline(file, buffer)){
        std::stringstream stream(buffer);
        stream >> name;
        if (name == "f") break;
    }
    
    std::cout << name << std::endl;
}

void loadObjInMem(const char* loc){

    // while(true){

    //     streamBuf >> name >> pos.x >> pos.y >> pos.z;

    //     if (name.compare("v") != 0) break;
    //     pos_vector.push_back(pos);
        
    //     std::cout << name << " " << pos.x << " " << pos.y << " " << pos.z << std::endl;

    //     getline(streamBuf, line);
    // }

    // while(true){
    //     std::stringstream streamData(data);
    //     std::string name;
    //     glm::vec2 pos;

    //     streamData >> name >> pos.x >> pos.y;

    //     if (name.compare("vt") != 0) break;
    //     tex_vector.push_back(pos);

    //     std::cout << name << " " << pos.x << " " << pos.y << std::endl;

    //     getline(inputData, data);
    // }
    // while the name is 'v'
}

int main(){
    WavefrontObj ojb("cube.obj");
}