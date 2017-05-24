//usage: NoraShade.exe <source-directory> <shader-name>
//Release 1.0 (Tania): Vertex/Fragment shader compilation
//Update 1.1 (Nora): Geometry shader compatibility
#include <string>
#include <fstream>
#include <sstream>

void compileShader(const std::string& directory, const std::string& name);

int main(int argc, char* argv[]) {
	if (argc < 3 || argc > 3) {
		printf("\tInvalid number of arguments\n\tUsage: NoraShade <source-directory> <shader-name>\n");
		return -1;
	}
	else {
		compileShader(argv[1], argv[2]);
	}
	return 0;
}

std::string readFile(const std::string& path) {
	std::ifstream inFile;
	std::string outData;
	std::stringstream buffer;

	inFile = std::ifstream(path);
	if (inFile.fail()) {
		perror(path.c_str());
		return "NULL";
	}
	//Read file to stringstream buffer, and return it
	buffer << inFile.rdbuf();
	outData = buffer.str();
	inFile.close();
	return outData;
}

bool fileExists(const std::string& path) {
	std::ifstream ifile (path);
	return ifile.good();
}

void compileShader(const std::string& directory, const std::string& name) {
	//Compiles a new shader
	std::ofstream outFile;
	
	unsigned int attrSize, vertexSize, fragSize;
	std::string attrData, vertexData, fragData;

	unsigned int geoSize;
	std::string geoData;
	bool hasGeo;

	attrData = readFile(directory + "/attributes.txt");
	if (attrData == "NULL") {
		return;
	}

	//Geometry
	hasGeo = fileExists(directory + "/geometry.txt");
	if (hasGeo) {
		//Compile geometry
		geoData = readFile(directory + "/geometry.txt");
	}

	vertexData = readFile(directory + "/vertex.txt");
	if (vertexData == "NULL") {
		return;
	}

	fragData = readFile(directory + "/fragment.txt");
	if (fragData == "NULL") {
		return;
	}

	//Now compile this data together
	outFile = std::ofstream(name + ".shader", std::ios::binary);
	if (outFile.fail()) {
		perror(std::string(name + ".shader").c_str());
		return;
	}

	attrSize = attrData.size();
	vertexSize = vertexData.size();
	fragSize = fragData.size();
	
	if (hasGeo) {
		geoSize = geoData.size();
	}
	else {
		geoSize = 0;
	}

	unsigned int finalSize;
	finalSize = 4 + attrSize + vertexSize + fragSize + geoSize + (sizeof(unsigned int) * 4);

	if (hasGeo) {
		printf("\n\tGeometry.txt - %d bytes", geoSize);
	}
	printf("\n\tAttributes.txt - %d bytes\n\tVertex.txt - %d bytes\n\tFragment.txt - %d bytes\n\t%s.shader - %d bytes\n\n", attrSize, vertexSize, fragSize, name.c_str(), finalSize);

	outFile.write("SHDR", 4);
	outFile.write(reinterpret_cast<const char*>(&attrSize), sizeof(attrSize));
	outFile.write(reinterpret_cast<const char*>(&vertexSize), sizeof(vertexSize));
	outFile.write(reinterpret_cast<const char*>(&fragSize), sizeof(fragSize));
	outFile.write(reinterpret_cast<const char*>(&geoSize), sizeof(geoSize));
	outFile.write(attrData.c_str(), attrSize);
	outFile.write(vertexData.c_str(), vertexSize);
	outFile.write(fragData.c_str(), fragSize);
	if (hasGeo) {
		outFile.write(geoData.c_str(), geoSize);
	}

	outFile.close();
	printf("\t%s.shader has been compiled!\n", name.c_str());
}